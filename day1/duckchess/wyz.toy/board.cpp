#include "board.h"

#include <QDebug>
#include <qdebug.h>
#include <cstdlib>
#include <QDebug>
#include <qdebug.h>

Chess& Board::getChess(int i,int j){
    for (Chess& ele:chess){
        if (ele.i==i&&ele.j==j)
            return ele;
    }
    return nullChess;
}
bool Board::removeChess(int i,int j){
    for (auto it=chess.begin();it!=chess.end();++it){
        if (it->i==i&&it->j==j){
            chess.erase(it);
            return true;
        }
    }
    return false;
}

Side Board::oppSide(Side s) const{
    if (s==red) return blue;
    if (s==blue) return red;
    return na;
}


Board::Board():nullChess(),nowSide(red),_gameover(false),_winner(na){
    qDebug("Board::Board");
    chess.push_back(Chess(captain,red,4,0));
    chess.push_back(Chess(guard,red,3,0));
    chess.push_back(Chess(guard,red,5,0));
    chess.push_back(Chess(elephant,red,2,0));
    chess.push_back(Chess(elephant,red,6,0));
    chess.push_back(Chess(horse,red,1,0));
    chess.push_back(Chess(horse,red,7,0));
    chess.push_back(Chess(car,red,0,0));
    chess.push_back(Chess(car,red,8,0));
    chess.push_back(Chess(duck,red,0,2));
    chess.push_back(Chess(duck,red,8,2));
    chess.push_back(Chess(soldier,red,0,3));
    chess.push_back(Chess(soldier,red,2,3));
    chess.push_back(Chess(soldier,red,4,3));
    chess.push_back(Chess(soldier,red,6,3));
    chess.push_back(Chess(soldier,red,8,3));

    chess.push_back(Chess(captain,blue,4,9));
    chess.push_back(Chess(guard,blue,3,9));
    chess.push_back(Chess(guard,blue,5,9));
    chess.push_back(Chess(elephant,blue,2,9));
    chess.push_back(Chess(elephant,blue,6,9));
    chess.push_back(Chess(horse,blue,1,9));
    chess.push_back(Chess(horse,blue,7,9));
    chess.push_back(Chess(car,blue,0,9));
    chess.push_back(Chess(car,blue,8,9));
    chess.push_back(Chess(duck,blue,0,7));
    chess.push_back(Chess(duck,blue,8,7));
    chess.push_back(Chess(soldier,blue,0,6));
    chess.push_back(Chess(soldier,blue,2,6));
    chess.push_back(Chess(soldier,blue,4,6));
    chess.push_back(Chess(soldier,blue,6,6));
    chess.push_back(Chess(soldier,blue,8,6));
    qDebug("Board::Board OK");
}

Board::Board(ifstream &in):nullChess(),nowSide(red),_gameover(false),_winner(na){
    in>>*this;
}

bool Board::checked(){
    for (Chess c1:chess)for (Chess c2:chess){
        if (c1.side==c2.side) continue;
        if (c1.type==captain&&commandValid(Command(c2.i,c2.j,c1.i,c1.j),false)) return true;
        if (c2.type==captain&&commandValid(Command(c1.i,c1.j,c2.i,c2.j),false)) return true;
    }
    return false;
}
Side Board::winner(){
    return _winner;
}
bool Board::gameover(){
    if (!_gameover){
        bool redCaptainFound=false;
        bool blueCaptainFound=false;
        for (auto&& ele:chess){
            if (ele.type==captain){
                if (ele.side==red) redCaptainFound=true;
                if (ele.side==blue) blueCaptainFound=true;
            }
        }
        if (redCaptainFound&&!blueCaptainFound) _winner=red;
        if (!redCaptainFound&&blueCaptainFound) _winner=blue;
        if (!redCaptainFound||!blueCaptainFound){
            _gameover=true;
            nowSide=na;
        }
    }
    return _gameover;
}

bool Board::commandValid(const Command& cmd,bool sideConsidered){
    if (gameover()) return false;

    if (cmd==admitingDefeat) return true;
    Chess& chess=getChess(cmd.fromI,cmd.fromJ);

    if (!chess.checkXY(cmd.toI,cmd.toJ)) return false;

    Side opps=getChess(cmd.toI,cmd.toJ).side;
    if (sideConsidered&&chess.side!=nowSide) return false;
    if (chess.side==opps) return false;

    int x=cmd.toI-cmd.fromI;
    int y=cmd.toJ-cmd.fromJ;
    auto knightCheck=[this,cmd,x,y](int dx,int dy){
        if (min(abs(x),abs(y))!=dx||max(abs(x),abs(y))!=dy) return false;
        int mx=max(abs(x),abs(y));
        for (int i=mx-1;i>0;--i){
            int halfx=x*i/mx,halfy=y*i/mx;
            if (getChess(cmd.fromI+halfx,cmd.fromJ+halfy).exist()) return false;
        }
        return true;
    };

    bool eaten=opps!=na;
    switch (chess.type) {
    case captain:
        return knightCheck(0,1);
    case guard:
        return knightCheck(1,1);
    case elephant:
        return knightCheck(2,2);
    case horse:
        return knightCheck(1,2);
    case car:{
        for (int i=1;i<=max(N,M);++i)
            if (knightCheck(0,i)) return true;
        return false;
    }
    case duck:
        return knightCheck(2,3);
    case soldier:
        return knightCheck(1,1)||knightCheck(0,1);
    }
    return false;
}
bool Board::executeCommand(const Command& cmd, bool &eaten){
    if (!commandValid(cmd)) return false;
    if (cmd==admitingDefeat){
        _winner=oppSide(nowSide);
        nowSide=na;
        _gameover=true;
        return true;
    }
    if (getChess(cmd.toI,cmd.toJ).check()){
        removeChess(cmd.toI,cmd.toJ);
        eaten=true;
    }
    else eaten=false;
    getChess(cmd.fromI,cmd.fromJ).move(cmd.toI,cmd.toJ);
    nowSide=oppSide(nowSide);
    return true;
}

ifstream& operator >>(ifstream& in, Board& dst){
    auto read=[&in](){
        int ret=0;char ch;in>>std::noskipws>>ch;
        for (;!isdigit(ch);in>>std::noskipws>>ch);
        for (;isdigit(ch);in>>std::noskipws>>ch) ret=ret*10-48+ch;
        return ret;
    };
    string ns;in>>ns;
    Side s;
    if (ns=="red") s=red;
    if (ns=="blue") s=blue;
    dst.nowSide=s;
    qDebug("%s",ns.data());

    dst.chess.clear();
    for (int round=0;round<2;++round,s=dst.oppSide(s)){
        qDebug("QwQ");
        for (int k=read();k;--k){int x=read(),y=read();dst.chess.push_back(Chess(captain,s,x,y));}
        for (int k=read();k;--k){int x=read(),y=read();dst.chess.push_back(Chess(guard,s,x,y));}
        for (int k=read();k;--k){int x=read(),y=read();dst.chess.push_back(Chess(elephant,s,x,y));}
        for (int k=read();k;--k){int x=read(),y=read();dst.chess.push_back(Chess(horse,s,x,y));}
        for (int k=read();k;--k){int x=read(),y=read();dst.chess.push_back(Chess(car,s,x,y));}
        for (int k=read();k;--k){int x=read(),y=read();dst.chess.push_back(Chess(duck,s,x,y));}
        for (int k=read();k;--k){int x=read(),y=read();dst.chess.push_back(Chess(soldier,s,x,y));}
    }
    return in;
}
ofstream& operator <<(ofstream& out, const Board& src){
    vector<Chess> chess=src.chess;
    Side s=src.nowSide;
    sort(chess.begin(),chess.end(),[s](const Chess& u,const Chess& v){
        if (u.side!=v.side) return u.side==s;
        return u.type<v.type;
    });
    auto it=chess.begin();
    for (int round=0;round<2;++round,s=src.oppSide(s)){
        if (s==red) out<<"red"<<std::endl;
        if (s==blue) out<<"blue"<<std::endl;
        for (int t=captain;t<=soldier;++t){
            vector<Chess> tmp(0);
            for (;it!=chess.end()&&it->type==t&&it->side==s;++it)
                tmp.push_back(*it);
            out<<int(tmp.size());
            for (auto ele:tmp) out<<' '<<'<'<<ele.i<<','<<ele.j<<'>';
            out<<std::endl;
        }
    }
    return out;
}

