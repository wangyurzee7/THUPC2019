#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "values.h"
#include "chess.h"


struct Command{
    int fromI,fromJ;
    int toI,toJ;
    Command():fromI(-1),fromJ(-1),toI(-1),toJ(-1){}
    Command(int i0,int j0,int i1,int j1):fromI(i0),fromJ(j0),toI(i1),toJ(j1){}
    bool operator ==(const Command& other) const{
        return fromI==other.fromI&&fromJ==other.fromJ&&toI==other.toI&&toJ==other.toJ;
    }
    Command(string t):Command(){
        if (int(t.size())!=5||t[0]!=1) return;
        fromI=t[1];
        fromJ=t[2];
        toI=t[3];
        toJ=t[4];
    }
    operator string() const{
        string ret="";
        ret.push_back(char(1));
        ret.push_back(char(fromI));
        ret.push_back(char(fromJ));
        ret.push_back(char(toI));
        ret.push_back(char(toJ));
        return ret;
    }
};
const Command admitingDefeat(-1,-1,0,0);

class Board
{
protected:
    Chess nullChess;
    Side nowSide;
    bool _gameover;
    Side _winner;
    vector<Chess> chess;
    Side oppSide(Side s) const;
    Chess& getChess(int i,int j);
    bool removeChess(int i,int j);
public:
    Board();
    Board(ifstream&);

    Side whoseTurn(){return nowSide;}

    bool checked(); // "Jiang Jun" is translated into "check"
    bool gameover();
    Side winner();

    bool commandValid(const Command& cmd,bool sideConsidered=true);
    bool executeCommand(const Command& cmd,bool& eaten);

    friend ifstream& operator >>(ifstream& in, Board& dst);
    friend ofstream& operator <<(ofstream& out, const Board& src);
};

#endif // BOARD_H
