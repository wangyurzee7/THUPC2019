from std import *
import sys
import os
import random

def percent(x):
    return random.randint(0,99)<x

def gen_query(board):
    if percent(7):
        return random.randint(0,R-1),random.randint(0,C-1),random.randint(0,R-1),random.randint(0,C-1)
    x,y=random.randint(0,R-1),random.randint(0,C-1)
    while not board[x][y]:
        x,y=random.randint(0,R-1),random.randint(0,C-1)
    valid=[]
    invalid=[]
    for i in range(R):
        for j in range(C):
            if moving(board,x,y,i,j):
                valid.append((i,j))
            else:
                invalid.append((i,j))
    if percent(20) and valid:
        return (x,y)+valid[random.randint(0,len(valid)-1)]
    else:
        return (x,y)+invalid[random.randint(0,len(invalid)-1)]

if __name__=='__main__':
    Q=1000
    print(Q)
    board=initial_board()
    side,cols=0,("red","blue")
    for _i in range(Q):
        x0,y0,x1,y1=gen_query(board)
        if not ((not moving(board,x0,y0,x1,y1)) or (board[x0][y0] and board[x0][y0][0]!=cols[side])):
            # print("valid")
            board[x1][y1]=board[x0][y0]
            board[x0][y0]=None
            side^=1
        print("{} {} {} {}".format(x0,y0,x1,y1))