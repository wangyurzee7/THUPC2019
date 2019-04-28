#include "chesswidget.h"

#include <QMouseEvent>
#include <QMessageBox>
#include <iostream>
#include <fstream>

#include <QtMultimedia/QMediaPlayer>

ChessWidget::ChessWidget(QWidget *parent) : QWidget(parent),board(new PaintingBoard),view(na)
{
    resize(boardSize,boardSize);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timeSlot()));
    resetTimer();
}

void ChessWidget::resetTimer(){
    timeLeft=20;
    timer->stop();
    if (view!=na) timer->start(1000);
}
void ChessWidget::minusOneSecond(){
    --timeLeft;
    update();
    if (timeLeft==0){
        timer->stop();
        if (isWaiting())
            QMessageBox::information(this,"Time out","Opponent time out! You win!");
        else
            QMessageBox::information(this,"Time out","Time out! You lose!");
        doCmd(board->admitDefeat());
    }
}
void ChessWidget::timeSlot(){
    minusOneSecond();
}

void ChessWidget::doCmd(const Command& cmd){
    if (!isWaiting()&&view!=na) sendCmd(cmd);
    bool eaten;
    board->executeCommand(cmd,eaten);
    if (eaten){
        playMusic("eat.wav");
    }
    if (board->checked()){
        //QMessageBox::information(this,"Info","Check!");
        playMusic("warning.wav");
    }

    if (board->gameover()){
        QString mes="Gameover!! ";
        if (board->winner()==red) mes+="<font color=red size=16>Red</font> wins.";
        if (board->winner()==blue) mes+="<font color=blue size=16>Blue</font> wins.";
        if (board->winner()==na) mes+="<font color=green size=13>Ties.</font></h3>";
        QMessageBox::information(this,"Gameover",mes);
        timer->stop();
    }
    else resetTimer();
}

void ChessWidget::playMusic(QString fname){
    QMediaPlayer *player=new QMediaPlayer;
    player->setMedia(QUrl("qrc:/audio/sounds/"+fname));
    player->setVolume(100);
    player->play();
}

void ChessWidget::paintEvent(QPaintEvent* p){
    QPainter *painter=new QPainter;
    painter->begin(this);

    board->paint(painter);

    painter->setPen(QPen(Qt::darkGreen));
/*
    char buf[23];
    sprintf(buf,"%d",timeLeft);
    painter->setFont(QFont("Consolas",20));
    painter->drawText(QPoint(950,30),buf);
*/

    painter->end();
    update();
}
void ChessWidget::mousePressEvent(QMouseEvent *e){
    Command cmd(-1,-1,-1,-1);
    if (board->click(e->pos().x(),e->pos().y(),cmd)){
        doCmd(cmd);
    }
    else if (board->newHighed){
        if (QMessageBox::information(this,"Are you sure?","Are you sure?","Yes","No")==0)
        newBoard();
        setView(na);
    }
    else if (board->skinHighed){
        board->changeSkin();
    }
}
void ChessWidget::mouseMoveEvent(QMouseEvent *e){
    //qDebug("ChessWidget::mouseMoveEvent");
    if (board->mouseMoveTo(e->pos().x(),e->pos().y())){
        setCursor(Qt::PointingHandCursor);
    }
    else if (board->clickable(e->pos().x(),e->pos().y())){
        setCursor(Qt::PointingHandCursor);
        //qDebug("setCursor(Qt::PointingHandCursor);");
    }
    else{
        setCursor(Qt::ArrowCursor);
        //qDebug("setCursor(Qt::ArrowCursor);");
    }
}

void ChessWidget::newBoard(){
    delete board;
    board=new PaintingBoard();
}
void ChessWidget::saveBoard(const string& path){
    ofstream out(path);
    out<<*board;
}
void ChessWidget::loadBoard(const string& path){
    delete board;
    ifstream in(path);
    board=new PaintingBoard(in);
}
void ChessWidget::giveUp(){
    if (isWaiting()){
        QMessageBox::information(this,"Error","It's not your turn! You can't give up");
        return;
    }
    doCmd(board->admitDefeat());
}

void ChessWidget::setView(Side s){
    board->view=view=s;
    resetTimer();
    update();
}
bool ChessWidget::isWaiting(){
    return view!=na&&view!=board->whoseTurn()&&!board->gameover();
}

void ChessWidget::receiveCmd(const Command& cmd){
    if (isWaiting()) doCmd(cmd);
}
