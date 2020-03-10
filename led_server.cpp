#include <QtNetwork>
#include <QtWidgets>
#include <QRegExp>

#include "led_server.h"
#include "command.h"

#include "command/led_set_state_command.h"
#include "command/led_get_state_command.h"
#include "command/led_get_color_command.h"
#include "command/led_set_color_command.h"
#include "command/led_get_rate_command.h"
#include "command/led_set_rate_command.h"

LedServer::LedServer(): mLed(QSharedPointer<Led>::create()), mRunning(false)
{
    FillCommandList();
}

LedServer::~LedServer()
{    
    for(auto it : mClientList)
    {
        if(it && it->isOpen() && it->isValid())
        {
            if(it->state() == QTcpSocket::ConnectedState)
            {
                it->disconnectFromHost();
                it->waitForDisconnected();
            }

            it->deleteLater();
        }
    }

    mClientList.clear();
}

void LedServer::FillCommandList()
{
    mSupportedCommands.push_back(std::make_pair("set-led-state", true ));
    mSupportedCommands.push_back(std::make_pair("set-led-color", true ));
    mSupportedCommands.push_back(std::make_pair("set-led-rate" , true ));
    mSupportedCommands.push_back(std::make_pair("get-led-state", false));
    mSupportedCommands.push_back(std::make_pair("get-led-color", false));
    mSupportedCommands.push_back(std::make_pair("get-led-rate" , false));
}

bool LedServer::IsRunning() const
{
    return mRunning;
}

bool LedServer::Run(quint16 port, QString& error_str)
{
    mTcpServer.reset(new QTcpServer(this));

    connect(mTcpServer.data(), &QTcpServer::newConnection, this, &LedServer::onNewConnection);

    if( !mTcpServer->listen(QHostAddress::Any, port) )
    {
        error_str = mTcpServer->errorString();
        return false;
    }

    emitLedInfo();
    mRunning = true;
    return true;
}

void LedServer::onNewConnection()
{
    QTcpSocket* new_client_ptr =mTcpServer->nextPendingConnection();

    try
    {
        connect(new_client_ptr, &QIODevice::readyRead, this, &LedServer::onNewMessage);
        connect(new_client_ptr, &QAbstractSocket::disconnected, this, &LedServer::onDisconnect);

        mClientList.push_back(new_client_ptr);

        return;
    }
    catch(...)
    {
        new_client_ptr->reset();
    }
}

void LedServer::onNewMessage()
{
    QTcpSocket* ready_socket = static_cast<QTcpSocket *>(sender());

    QByteArray request = ready_socket->readAll();
    QString req_str(request);

    std::vector<QString> parsed_words;
    QString command_name, command_arg;
    if( !ParseRequest(req_str, command_name, command_arg) )
    {
        ready_socket->write("FAILED");
    }
    else
    {
        try
        {
            QSharedPointer<ICommand> command = CreateCommand(command_name, command_arg);
            QString answer;

            command->Execute(command_arg, answer);

            emitLedInfo();

            QByteArray response = "OK ";

            if(!answer.isEmpty())
                response += answer.toUtf8();
            else
                response += command_arg.toUtf8();

            ready_socket->write(response);

        } catch (...)
        {
            ready_socket->write("FAILED");
        }
    }


    ready_socket->disconnectFromHost();
    ready_socket->waitForDisconnected();
}

void LedServer::onDisconnect()
{
    QTcpSocket* ready_socket = static_cast<QTcpSocket *>(sender());
    ready_socket->deleteLater();
    mClientList.removeOne(ready_socket);
}

bool LedServer::ParseRequest(QString &request, QString& command_name, QString& command_arg) const
{
    try
    {
        QRegularExpression reg_command( "([a-z]+-led-[a-z]+)( [a-z\\d]+)$|([a-z]+-led-[a-z]+)$" );
        auto match = reg_command.match(request, 0, QRegularExpression::MatchType::PartialPreferCompleteMatch );
        if( !match.isValid() )
            return false;

        command_name = match.captured(1);
        command_arg = match.captured(2).mid(1);

        if(command_name.isEmpty() || command_arg.isEmpty())
        {
            // Если пустые, значит прислали метод get
            command_name = match.captured(3);
            if(command_name.isEmpty())
            {
                return false;
            }
        }

        return true;
    }
    catch (...)
    {
        return false;
    }
}

QSharedPointer<ICommand> LedServer::CreateCommand(const QString& command_name, const QString& arg)
{
    if(!arg.isEmpty())
    {
        if(command_name == "set-led-state")
        {
            return QSharedPointer<ICommand>(new LedSetStateCommand(mLed));
        }
        else if(command_name == "set-led-color")
        {
            return QSharedPointer<ICommand>(new LedSetColorCommand(mLed));
        }
        else if(command_name == "set-led-rate")
        {
            return QSharedPointer<ICommand>(new LedSetRateCommand(mLed));
        }
    }
    else
    {
        if(command_name == "get-led-state")
        {
            return QSharedPointer<ICommand>(new LedGetStateCommand(mLed));
        }
        else if(command_name == "get-led-color")
        {
            return QSharedPointer<ICommand>(new LedGetColorCommand(mLed));
        }
        else if(command_name == "get-led-rate")
        {
            return QSharedPointer<ICommand>(new LedGetRateCommand(mLed));
        }
    }

    throw QException();
}

void LedServer::emitLedInfo()
{
    auto led_info = mLed->GetLedInfo();
    emit ChangeState(led_info);
}







