#include "mybutton.h"
#include<QDebug>

Mybutton::Mybutton(QWidget *parent) : QPushButton(parent),x(0),y(0)
{
    judge_press=0;
    for(int i=0;i<7;i++)
    {
        sate[i]=0;
    }
    resize(45,45);

    connect(this,&QPushButton::clicked,this,&Mybutton::myslot);
    setStyleSheet("background-color: rgb(255, 255, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");

}

Mybutton::~Mybutton()
{
}

void Mybutton::myslot()     //点击按钮发送信号，如果有棋子则发送坐标，如果没有则发送（0，0）
{
    qDebug()<<x<<y<<"slot";
    emit sigSub(x,y);
}
int Mybutton::jud_sate()
{
    int sum=0;
    for(int i=0;i<7;i++)
    {
        sum+=sate[i];
    }
    if(sum)return 1;
    return 0;
}
void Mybutton::putsate(int x)
{
    sate[x]=1;
    //改变状态的同时改变颜色
    switch (x) {
    case(1):setStyleSheet("background-color: rgb(255, 0, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(4):setStyleSheet("background-color: rgb(0, 170, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(3):setStyleSheet("background-color: rgb(255, 255, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(2):setStyleSheet("background-color: rgb(85, 255, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(5):setStyleSheet("background-color: rgb(170, 85, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(6):setStyleSheet("background-color: rgb(255, 170, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    }


}
int Mybutton::getsate()
{
    for(int i=0;i<7;i++)
    {
        if(sate[i]!=0)
        {
            return i;
        }
    }
    return 0;
}
void Mybutton::clearsate()
{
    for(int i=0;i<7;i++)
    {
        sate[i]=0;
    }
    setStyleSheet("background-color: rgb(255, 255, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");    //清除颜色
}
void Mybutton::put_x(int a1)
{
    x=a1;
}
void Mybutton::put_y(int a2)
{
    y=a2;
}
int Mybutton::get_x()
{
    return x;
}
int Mybutton::get_y()
{
    return y;
}

void Mybutton::enterEvent(QEvent *e)
{
    if(judge_press==0)
    {
    int x=getsate();    //设置进入的显示
    switch (x) {
    case(0):setStyleSheet("background-color: rgb(225, 225, 225);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(1):setStyleSheet("background-color: rgb(225, 0, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(4):setStyleSheet("background-color: rgb(0, 140, 225);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(3):setStyleSheet("background-color: rgb(225, 225, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(2):setStyleSheet("background-color: rgb(55, 225, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(5):setStyleSheet("background-color: rgb(140, 55, 225);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(6):setStyleSheet("background-color: rgb(225, 140, 225);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    }
    }
}

void Mybutton::leaveEvent(QEvent *e)
{
    if(judge_press==0)
    {
    int x=getsate();    //设置离开的显示
    switch (x) {
    case(0):setStyleSheet("background-color: rgb(255, 255, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(1):setStyleSheet("background-color: rgb(255, 0, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(4):setStyleSheet("background-color: rgb(0, 170, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(3):setStyleSheet("background-color: rgb(255, 255, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(2):setStyleSheet("background-color: rgb(85, 255, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(5):setStyleSheet("background-color: rgb(170, 85, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    case(6):setStyleSheet("background-color: rgb(255, 170, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");break;
    }
    }
}

//void Mybutton::mousePressEvent(QMouseEvent *e){
//    int x=getsate();    //设置点击的显示
//    QPushButton::mousePressEvent(e);
//    if (e->isAccepted())
//    {
//    switch (x) {
//    case(0):setStyleSheet("background-color: rgb(255, 255, 255);border:4px groove blue;border-radius:15px;padding:3px 4px;");break;
//    case(1):setStyleSheet("background-color: rgb(255, 0, 0);border:4px groove blue;border-radius:15px;padding:3px 4px;");break;
//    case(4):setStyleSheet("background-color: rgb(0, 170, 255);border:4px groove blue;border-radius:15px;padding:3px 4px;");break;
//    case(3):setStyleSheet("background-color: rgb(255, 255, 0);border:4px groove blue;border-radius:15px;padding:3px 4px;");break;
//    case(2):setStyleSheet("background-color: rgb(85, 255, 0);border:4px groove blue;border-radius:15px;padding:3px 4px;");break;
//    case(5):setStyleSheet("background-color: rgb(170, 85, 255);border:4px groove blue;border-radius:15px;padding:3px 4px;");break;
//    case(6):setStyleSheet("background-color: rgb(255, 170, 255);border:4px groove blue;border-radius:15px;padding:3px 4px;");break;
//    }
//    }
//    judge_press=1;
//}

//void Mybutton::mouseReleaseEvent(QMouseEvent *e)
//{
//    QPushButton::mouseReleaseEvent(e);
//    if (e->isAccepted())
//    {
//        //效果2实现代码
//    }
//}
