#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QtNetwork>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    widget(new ChessWidget)
{
    ui->setupUi(this);
    this->setFixedSize(boardSize,boardSize);
    setCentralWidget(widget);

    listenSocket=new QTcpServer;

    connectTimer=new QTimer;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete widget;
}

bool MainWindow::areYouSure(const QString &info){
    return QMessageBox::information(this,"Are you sure?",info,"Yes","No")==0;
}


void MainWindow::on_actionNew_triggered()
{
    if (areYouSure("Are you sure?")){
        widget->newBoard();
        widget->setView(na);
    }
}

void MainWindow::on_actionGiveup_triggered()
{
    widget->giveUp();
}



