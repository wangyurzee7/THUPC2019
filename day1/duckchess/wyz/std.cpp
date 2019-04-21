#include <bits/stdc++.h>

using namespace std;

namespace YV{ // Yazid Values

enum ChessType{
    captain=0,
    guard=1,
    elephant=2,
    horse=3,
    car=4,
    duck=5,
    soldier=6
};

enum Side{
    na=0,
    red=1,
    blue=2
};

}

using namespace YV;


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


ChessType Chess::int2type(int id){
    switch (id) {
    case 0:
        return captain;
    case 1:
        return guard;
    case 2:
        return elephant;
    case 3:
        return horse;
    case 4:
        return car;
    case 5:
        return duck;
    case 6:
        return soldier;
    }
    return soldier;
}

Side Chess::int2side(int id){
    switch (id) {
    case 0:
        return na;
    case 1:
        return red;
    case 2:
        return blue;
    }
    return na;
}


string Chess::typeToString() const{
    switch (type) {
    case captain:
        return "captain";
    case guard:
        return "guard";
    case elephant:
        return "elephant";
    case horse:
        return "horse";
    case car:
        return "car";
    case duck:
        return "duck";
    case soldier:
        return "soldier";
    }
    return "";
}
string Chess::sideToString() const{
    switch (side) {
    case red:
        return "red";
    case blue:
        return "blue";
    case na:
        return "na";
    }
    return "";
}

Chess::Chess(ChessType _t,Side _s,int _x,int _y):type(_t),side(_s),i(_x),j(_y){}
Chess::Chess():type(captain),side(na),i(-1),j(-1){}

inline bool inRange(int x,int l,int r){return l<=x&&x<=r;}

bool Chess::checkXY(int x,int y){
    if (x<0||x>=N) return false;
    if (y<0||y>=M) return false;
    return true;
}

bool Chess::check(){
    if (side==na) return false;
    return checkXY(i,j);
}

void Chess::move(int x,int y){
    if (side==na) return;
    i=x;
    j=y;
}

bool Chess::exist() const{
    return (side!=na);
}


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
public:
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

    Side whoseTurn(){return nowSide;}

    bool checked(); // "Jiang Jun" is translated into "check"
    bool gameover();
    Side winner();

    bool commandValid(const Command& cmd,bool sideConsidered=true);
    bool executeCommand(const Command& cmd,bool& eaten);
};

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

int main(){
    int Q;
    scanf("%d",&Q);
    Board* board=new Board();
    while (Q--){
        int x0,y0,x1,y1;
        scanf("%d%d%d%d",&y0,&x0,&y1,&x1);
        Command cmd(x0,y0,x1,y1);
        if (board->commandValid(cmd)){
            Chess c0=board->getChess(x0,y0);
            Chess c1=board->getChess(x1,y1);
            bool eaten;
            board->executeCommand(cmd,eaten);
            
            string c0_string=c0.sideToString()+" "+c0.typeToString();
            string c1_string=eaten?c1.sideToString()+" "+c1.typeToString():"NA";
            string res1=board->checked()?"yes":"no";
            string res2=board->gameover()?"yes":"no";
            
            cout<<c0_string<<';'<<c1_string<<';'<<res1<<';'<<res2<<endl;
        }
        else{
            cout<<"Invalid command"<<endl;
        }
    }
    delete board;
    
    return 0;
}