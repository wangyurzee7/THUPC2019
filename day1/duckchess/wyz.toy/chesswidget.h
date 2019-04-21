#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H

#include <QWidget>
#include <QLCDNumber>
#include <QTimer>
#include "paintingboard.h"

class ChessWidget : public QWidget
{
    Q_OBJECT
private:
    int timeLeft;
    QTimer *timer;
    void resetTimer();
    void minusOneSecond();

    void playMusic(QString fname);

    Side view;
    bool isWaiting();
public:
    bool waitingForBoard=false;
    explicit ChessWidget(QWidget *parent = nullptr);

    PaintingBoard* board;

    void doCmd(const Command& cmd);

    void paintEvent(QPaintEvent* p);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    void newBoard();
    void saveBoard(const string& path);
    void loadBoard(const string& path);
    void giveUp();
    void setView(Side s);

public slots:
    void receiveCmd(const Command&);
signals:
    void sendCmd(const Command&);
private slots:
    void timeSlot();
};

#endif // CHESSWIDGET_H
