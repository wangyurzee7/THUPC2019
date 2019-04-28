#include "paintingboard.h"


Point PaintingBoard::center(int i,int j){
    if (view!=blue){
        i=N-i-1;
        j=M-j-1;
    }
    double x=basePoint.x()+i*gridLength;
    double y=basePoint.y()+j*gridLength;
    //if (view==na) swap(x,y);
    return Point(x,y);
}
Rectangle PaintingBoard::area(int i,int j){
    Point d(chessLength/2,chessLength/2);
    Point o=center(i,j);
    return Rectangle(o-d,o+d);
}
bool PaintingBoard::getGridPoint(int x,int y,int &ret_i,int &ret_j){
    for (int i=0;i<N;++i)for (int j=0;j<M;++j){
        //Rectangle rect=area(i,j);
        //qDebug("%d %d    %d %d %d %d",x,y,int(rect.left()),int(rect.right()),int(rect.bottom()),int(rect.top()));
        if (area(i,j).contains(x,y)){
            //qDebug("Yes!");
            ret_i=i;
            ret_j=j;
            return true;
        }
    }
    return false;
}


PaintingBoard::PaintingBoard(Side _view):Board(),view(_view),selected(false){}
PaintingBoard::PaintingBoard(ifstream &in, Side _view):Board(in),view(_view),selected(false){}

bool PaintingBoard::clickable(int x,int y){
    if (view!=na&&nowSide!=view) return false;
    int i,j;
    if (!getGridPoint(x,y,i,j)) return false;
    Side s=getChess(i,j).side;
    if (s==nowSide) return true;
    if (selected) return commandValid(Command(selectedI,selectedJ,i,j));
    return false;
}
bool PaintingBoard::click(int x,int y,Command& cmd){
    if (!clickable(x,y)) return false;
    int i,j;
    getGridPoint(x,y,i,j);
    Side s=getChess(i,j).side;
    if (s==nowSide){
        if (selected&&i==selectedI&&j==selectedJ) selected=false;
        else{
            selected=true;
            selectedI=i;
            selectedJ=j;
        }
        return false;
    }
    cmd=Command(selectedI,selectedJ,i,j);
    selected=false;
    return true;
}
Command PaintingBoard::admitDefeat(){
    return admitingDefeat;
}

bool PaintingBoard::mouseMoveTo(int x,int y){
    newHighed=area(N,M-2).contains(x,y);
    skinHighed=area(-1,1).contains(x,y);
    return newHighed||skinHighed;
}

void PaintingBoard::paint(QPainter* p){
    std::string skinPath=":/image/images/"+skins[curSkin]+"/";
    //qDebug("PaintingBoard::paint");
    QPixmap background;
    background.load(string(skinPath+"chessboard.jpg").data());
    p->drawPixmap(0,0,background);
    for (auto ele:chess){
        QPixmap chess;
        chess.load(string(skinPath+ele.sideToString()+"_"+ele.typeToString()+".png").data());
        p->drawPixmap(area(ele.i,ele.j).topLeft(),chess);
    }
    if (nowSide==red){
        QPixmap chess;
        chess.load(string(skinPath+"red.png").data());
        p->drawPixmap(area(N,1).topLeft(),chess);
    }
    if (nowSide==blue){
        QPixmap chess;
        chess.load(string(skinPath+"blue.png").data());
        p->drawPixmap(area(-1,M-2).topLeft(),chess);
    }
    QPixmap newBtn;
    newBtn.load(string(skinPath+"btn_new"+(newHighed?"_hilight":"")+".png").data());
    p->drawPixmap(area(N,M-2).topLeft(),newBtn);
    QPixmap skinBtn;
    skinBtn.load(string(skinPath+"btn_skin"+(skinHighed?"_hilight":"")+".png").data());
    p->drawPixmap(area(-1,1).topLeft(),skinBtn);
    auto drawRect=[this,p](int i,int j,QColor col){
        Rectangle rect=area(i,j);
        QPen pen(col);
        pen.setWidth(3);
        p->setPen(pen);
        Point tmpx(chessLength/5,0);
        Point tmpy(0,chessLength/5);
        p->drawLines({
                         QLineF(rect.topLeft(),rect.topLeft()+tmpx),
                         QLineF(rect.topLeft(),rect.topLeft()+tmpy),
                         QLineF(rect.topRight(),rect.topRight()-tmpx),
                         QLineF(rect.topRight(),rect.topRight()+tmpy),
                         QLineF(rect.bottomLeft(),rect.bottomLeft()+tmpx),
                         QLineF(rect.bottomLeft(),rect.bottomLeft()-tmpy),
                         QLineF(rect.bottomRight(),rect.bottomRight()-tmpx),
                         QLineF(rect.bottomRight(),rect.bottomRight()-tmpy)
                     });
    };
    if (selected){
        drawRect(selectedI,selectedJ,QColor(50,50,50));
        // drawRect(selectedI,selectedJ,QColor(100,100,255));
        for (int i=0;i<N;++i) for (int j=0;j<M;++j)
            if (commandValid(Command(selectedI,selectedJ,i,j)))
                drawRect(i,j,QColor(50,50,50));
                // drawRect(i,j,QColor(100,255,128));
    }
}
