#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "led_server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class LedServer;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_serverButton_clicked();
    void onLedEvent(std::map<QString, QString>& led_info);

private:
    void StartServer();
    void StopServer();

private:
    Ui::MainWindow *ui;
    QSharedPointer<LedServer> mServer;
};
#endif // MAINWINDOW_H
