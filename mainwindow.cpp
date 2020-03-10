#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QValidator>
#include <QtWidgets>

#define MIN_PORT 1
#define MAX_PORT 65536

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mServer(QSharedPointer<LedServer>::create())
{
    ui->setupUi(this);
    ui->portLineEdit->setValidator(new QIntValidator(2, 65535, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_serverButton_clicked()
{    
    if(!mServer->IsRunning())
    {
        const auto port = ui->portLineEdit->text().toUInt();
        if(port < MIN_PORT || port > MAX_PORT)
        {
            QMessageBox::information(this, "Ошибка", "Недопустимый порт. Введите от 1 до 65536.");
            return;
        }

        StartServer();
    }
    else
        StopServer();
}

void MainWindow::onLedEvent(std::map<QString, QString>& led_info)
{
    ui->stateLedLabel->setText(led_info["state"]);
    ui->colorLedLabel->setText(led_info["color"]);
    ui->rateLedLabel->setText(led_info["rate"]);
}

void MainWindow::StartServer()
{
    ui->portLineEdit->setDisabled(true);
    ui->serverButton->setDisabled(true);
    ui->serverButton->setText("STARTING...");

    connect(mServer.data(), &LedServer::ChangeState, this, &MainWindow::onLedEvent );

    QString error_str;
    if( mServer->Run(ui->portLineEdit->text().toUInt(), error_str))
    {
        ui->serverButton->setDisabled(false);
        ui->serverButton->setText("STOP");
    }
    else
    {
        ui->portLineEdit->setDisabled(false);
        ui->serverButton->setDisabled(false);
        ui->serverButton->setText("START");

        QMessageBox::critical(this, "Ошибка", tr("Не удалось запустить сервер по причине: %1").arg(error_str));
    }
}

void MainWindow::StopServer()
{
    mServer.reset(new LedServer);

    ui->portLineEdit->setDisabled(false);
    ui->serverButton->setDisabled(false);
    ui->serverButton->setText("START");

    ui->stateLedLabel->setText("~");
    ui->colorLedLabel->setText("~");
    ui->rateLedLabel->setText("~");
}
