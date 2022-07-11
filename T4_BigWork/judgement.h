#ifndef JUDGEMENT_H
#define JUDGEMENT_H


class Judgement
{
public:
    Judgement();
    int judge_out(int x,int y); //判断棋格btn[x][y]是否在有效棋盘之内
    int judge_P1(int x,int y);  //判断是否在P1的区域内，后以此类推
    int judge_P4(int x,int y);
    int judge_P2(int x,int y);
    int judge_P3(int x,int y);
    int judge_P5(int x,int y);
    int judge_P6(int x,int y);
    int judgemove_01(int x1,int y1,int x2,int y2);
    int judgemove_02(int x1,int y1,int x2,int y2);
};

#endif // JUDGEMENT_H
