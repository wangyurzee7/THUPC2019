#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chesswidget.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_actionNew_triggered();
    void on_actionGiveup_triggered();
signals:
    void receiveCommand(const Command&);

private:
    void sendString(string);
    bool areYouSure(const QString&);
    ChessWidget *widget;

    Ui::MainWindow *ui;

    QTimer* connectTimer;

    QTcpServer  *listenSocket;
    QTcpSocket  *readWriteSocket;
};

#endif // MAINWINDOW_H
