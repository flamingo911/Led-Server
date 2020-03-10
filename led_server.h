#ifndef LEDSERVER_H
#define LEDSERVER_H

#include <QObject>
#include <QtNetwork>
#include <memory>
#include "command.h"
#include "led.h"

//QT_BEGIN_NAMESPACE
//class QTcpServer;
//class QTcpSocket;
//QT_END_NAMESPACE

enum LedEventType
{
    STATE_CHANGED,
    COLOR_CHANGED,
    RATE_CHANGED
};

class LedServer: public QObject
{    
    Q_OBJECT
public:
    LedServer();
    virtual ~LedServer();

    bool Run(quint16 port, QString& error_str);
    bool IsRunning() const;

signals:
    void ChangeState(std::map<QString, QString>& led_info);

private slots:
    void onNewConnection();
    void onNewMessage();
    void onDisconnect();

private:
    bool ParseRequest(QString& request, QString& command_name, QString& command_arg) const;
    QSharedPointer<ICommand> CreateCommand(const QString& command_name, const QString& arg = "");
    void FillCommandList();
    void emitLedInfo();

private:

    //1. Название команды 2. Необходимость аргумента для неё
    typedef std::pair<const char*, bool> CommandSignature;

    std::vector<CommandSignature> mSupportedCommands;
    QSharedPointer<QTcpServer> mTcpServer;
    QList<QTcpSocket*> mClientList;
    QSharedPointer<Led> mLed;
    bool mRunning;
};

#endif // LEDSERVER_H
