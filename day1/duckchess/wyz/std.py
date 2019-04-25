import os
import sys
import json

def chess2str(chess):
    if chess:
        return ' '.join(chess);
    else:
        return 'NA';

R,C=10,9

def initial_board():
    ret=[[None for j in range(C)] for i in range(R)]
    ret[3][0]=ret[3][2]=ret[3][4]=ret[3][6]=ret[3][8]=("red","soldier")
    ret[2][0]=ret[2][8]=("red","duck")
    ret[0][0]=ret[0][8]=("red","car")
    ret[0][1]=ret[0][7]=("red","horse")
    ret[0][2]=ret[0][6]=("red","elephant")
    ret[0][3]=ret[0][5]=("red","guard")
    ret[0][4]=("red","captain")
    for i in range(R//2):
        for j in range(C):
            if ret[i][j]:
                ret[R-i-1][j]=("blue",ret[i][j][1])
    return ret

def moving(board,x0,y0,x1,y1):
    if not board[x0][y0]:
        return False
    if board[x1][y1] and board[x0][y0][0]==board[x1][y1][0]:
        return False
    delta_x=x1-x0
    delta_y=y1-y0
    def knight(dx,dy):
        if dx>dy:
            dx,dy=dy,dx
        if min(abs(delta_x),abs(delta_y))!=dx or max(abs(delta_x),abs(delta_y))!=dy:
            return False
        mx=dy
        for i in range(1,mx):
            half_x,half_y=int(delta_x*i/mx),int(delta_y*i/mx)
            if board[x0+half_x][y0+half_y]:
                return False
        return True
    _t=board[x0][y0][1]
    if _t=="captain":
        return knight(0,1)
    elif _t=="guard":
        return knight(1,1)
    elif _t=="elephant":
        return knight(2,2)
    elif _t=="horse":
        return knight(1,2)
    elif _t=="car":
        return knight(0,abs(delta_x)+abs(delta_y))
    elif _t=="duck":
        return knight(2,3)
    elif _t=="soldier":
        return knight(1,1) or knight(0,1)
    sys.stdout.write("Unknown error\n") # unknown chess type?
    exit()

def checked(board):
    for i in range(R):
        for j in range(C):
            if board[i][j] and board[i][j][1]=="captain":
                for x in range(R):
                    for y in range(C):
                        if moving(board,x,y,i,j):
                            return True
    return False
    
if __name__=='__main__':
    board=initial_board();
    Q=int(input())
    if Q<0 or Q>1000: # validate
        sys.stdout.write("Q out of range\n")
    gameovered=False
    side,cols=0,("red","blue")
    for _i in range(Q):
        x0,y0,x1,y1=list(map(int,input().split(" ")))
        if min(x0,x1)<0 or max(x0,x1)>=R or min(y0,y1)<0 or max(y0,y1)>=C: # validate
            sys.stdout.write("X,Y out of range\n")
            exit()
        if gameovered or (not moving(board,x0,y0,x1,y1)) or (board[x0][y0] and board[x0][y0][0]!=cols[side]):
            print("Invalid command")
        else:
            out_buf=[chess2str(board[x0][y0]),chess2str(board[x1][y1]),"no","no"]
            if board[x1][y1] and board[x1][y1][1]=="captain":
                gameovered=True
                out_buf[3]="yes"
            else:
                board[x1][y1]=board[x0][y0]
                board[x0][y0]=None
                if checked(board):
                    out_buf[2]="yes"
            print(";".join(out_buf))
            side^=1