
#include "judgement.h"
#include"math.h"
#include"mybutton.h"

Judgement::Judgement()
{

}

int Judgement::judge_out(int x, int y)     //在棋盘内则返回1，不在则返回0
{
    if(x>=0&&x<4)
    {
        if(y<=12&&(x+y)>=12)
        {
            return 1;
        }
    }
    else if(x>=4&&x<8)
    {
        if(y>=4&&(x+y)<=20)
        {
            return 1;
        }
    }
    else if(x>=8&&x<=12)
    {
        if(y<=12&&(x+y)>=12)
        {
            return 1;
        }
    }
    else if(x>12&&x<=16)
    {
        if(y>=4&&(x+y)<=20)
        {
            return 1;
        }
    }
    return 0;
}

int Judgement::judge_P1(int x, int y)
{
    if(x>=4&&x<=8)
    {
        if(y>=4&&(x+y)<12)
        {
            return 1;
        }
    }
    return 0;
}

int Judgement::judge_P4(int x, int y)
{
    if(x>=8&&x<=12)
    {
        if(y<=12&&(x+y)>20)
        {
            return 1;
        }
    }
    return 0;
}

int Judgement::judge_P2(int x, int y)
{
    if(x>=8&&x<=12)
    {
        if(y<4&&(x+y)>=12)
        {
            return 1;
        }
    }
    return 0;
}

int Judgement::judge_P3(int x, int y)
{
    if(x>12&&x<=16)
    {
        if(y>=4&&(x+y)<=20)
        {
            return 1;
        }
    }
    return 0;
}

int Judgement::judge_P5(int x, int y)
{
    if(x>=4&&x<8)
    {
        if(y>12&&(x+y)<=20)
        {
            return 1;
        }
    }
    return 0;
}

int Judgement::judge_P6(int x, int y)
{
    if(x>=0&&x<4)
    {
        if(y<=12&&(x+y)>=12)
        {
            return 1;
        }
    }
    return 0;
}

int Judgement::judgemove_01(int x1,int y1,int x2,int y2)//普通跳：(x1,y1)是旧位置，（x2,y2)是新位置；
{
    if(judge_out(x2, y2)==1&&(fabs(x1-x2)==1&&y2==y1||x1==x2&&fabs(y1-y2)==1||(x1-x2)*(y1-y2)==-1))return 1;
    else return 0;
}

int Judgement::judgemove_02(int x1,int y1,int x2,int y2)//隔跳：(x1,y1)是旧位置，（x2,y2)是新位置；
{
    if(judge_out(x2, y2)==1&&(x1==x2&&fabs(y1-y2)==2||y1==y2&&fabs(x1-x2)==2||(x1-x2)==2&&(y1-y2)==-2||(x1-x2)==-2&&(y1-y2)==2))//条件缺一个&&btn[(x1+x2)/2][(y1+y2)/2]->getsate()!=0需要在widget.cpp里补充
        return 1;
    else return 0;
}
