#include "chess.h"

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
/*
    bool reversed=false;
    if (y>4){
        y=9-y;
        reversed=true;
    }
    bool overRiver=((side==blue)^reversed);
    switch (type) {
    case captain:
        return inRange(x,3,5)&&inRange(y,0,2);
    case guard:
        return inRange(x,3,5)&&(inRange(y,0,2)&&((x+y)%2==1))&&!overRiver;
    case elephant:
        return x%2==0&&y%2==0&&(x/2+y/2)%2==1&&!overRiver;
    case horse:
        return true;
    case car:
        return true;
    case duck:
        return true;
    case soldier:
        if (overRiver) return true;
        else return x%2==0&&y>=3;
    }
    return false;
*/
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
