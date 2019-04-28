#ifndef CHESS_H
#define CHESS_H

#include "values.h"
#include <string>
using namespace YV;
using namespace std;

const int N=9;
const int M=10;

class Chess
{
private:
public:
    static ChessType int2type(int id);
    static Side int2side(int id);

    int i,j;
    ChessType type;
    Side side;

    string typeToString() const;
    string sideToString() const;

    Chess();
    Chess(ChessType _t,Side _s,int _x,int _y);
    bool checkXY(int x,int y);
    bool check();
    void move(int x,int y);
    bool exist() const;

    //friend class ChessBoardPainter;
};

#endif // CHESS_H
