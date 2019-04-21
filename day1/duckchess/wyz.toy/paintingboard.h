#ifndef PAINTINGBOARD_H
#define PAINTINGBOARD_H

#include "values.h"
#include "chess.h"
#include "board.h"
#include <QPainter>
#include <QPen>
#include <QString>


typedef QPointF Point;
typedef QRectF Rectangle;

const double gridLength=70;
const double chessLength=50;
const double boardSize=770;

const Point basePoint(105,70);

const int nSkin=2;
const std::string skins[nSkin]={"classic","classic"};


class PaintingBoard: public Board
{
private:
    int curSkin=0;
    bool selected;
    int selectedI,selectedJ;

    Point center(int i,int j);
    Rectangle area(int i,int j);
    bool getGridPoint(int x,int y,int &ret_i,int &ret_j);
public:
    Side view;
    PaintingBoard(Side _view=na);
    PaintingBoard(ifstream&,Side _view=na);

    bool clickable(int x,int y);
    bool click(int x,int y,Command& cmd);
    Command admitDefeat();

    bool newHighed=false,skinHighed=false;
    bool mouseMoveTo(int x,int y);
    void changeSkin(){(++curSkin)%=nSkin;}

    PaintingBoard(string t):PaintingBoard(){
        qDebug("len: %d",int(t.size()));
        if (int(t.size())%4!=3||int(t.size())<3||t[0]!=2) return;
        view=Chess::int2side(t[1]);
        nowSide=Chess::int2side(t[2]);
        chess.clear();
        for (int i=3;i<int(t.size());i+=4){
            chess.push_back(Chess(
                Chess::int2type(t[i]),
                Chess::int2side(t[i+1]),
                t[i+2],
                t[i+3]
            ));
        }
    }
    operator string() const{
        string ret;
        ret.push_back(2);
        ret.push_back(view);
        ret.push_back(nowSide);
        for (int i=0;i<int(chess.size());++i){
            ret.push_back(chess[i].type);
            ret.push_back(chess[i].side);
            ret.push_back(chess[i].i);
            ret.push_back(chess[i].j);
        }
        qDebug("%d",int(ret.size()));
        return ret;
    }

    void paint(QPainter*);
};

#endif // PAINTINGBOARD_H
