#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QEvent>
#include<QMouseEvent>

class Mybutton : public QPushButton
{
    Q_OBJECT

//状态相关
public:
    explicit Mybutton(QWidget *parent = nullptr);
    ~Mybutton();
    void putsate(int x);    //改变状态数组的内容
    int getsate();          //获取状态数组内的存在棋子的位置，若没有棋子则返回0
    void clearsate();       //清除所有的棋子状态
    int jud_sate();         //判断棋位是否有棋子存在

    //填写和获取该按钮在直角坐标系中的位置
    int get_x();
    int get_y();
    void put_x(int a1);
    void put_y(int a2);



//记录每一个位置的状态的数组，0表示没有棋子，在sate[a]=1表示玩家a放了一颗棋子
private:
    int sate[7];
    int x;      //记录btn的直角坐标位置
    int y;
    //定义自定义信号函数

//与自定义信号函数相关的内容

public slots:
    void myslot();
signals:
    void sigSub(int,int);//自定义信号函数

//设置鼠标点击之后的颜色变化
//protected:
//    void mousePressEvent(QMouseEvent *e);
//    void mouseReleaseEvent(QMouseEvent *e);
//设置鼠标的进入和离开的颜色变化
public:
    void enterEvent(QEvent *e); //鼠标进入事件
    void leaveEvent(QEvent *e);//鼠标离开事件
    int judge_press;    //表示当该按钮被按下的时候不触发鼠标的进入和离开事件，0为没触发，1为触发了
};

#endif // MYBUTTON_H
