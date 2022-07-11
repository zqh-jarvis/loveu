#ifndef WIDGET_H
#define WIDGET_H

#include"mybutton.h"
#include <QWidget>
#include"judgement.h"
#include"networkserver.h"
#include"networkdata.h"
#include"networksocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //int judge_out(int x,int y); //判断棋格btn[x][y]是否在有效棋盘之内
    void set_position();   //给btn设置位置
    void set_player(int x);     //设置Player x 的棋子

    //最重要的一个函数，点击按钮之后的槽函数
    void mycao(int,int);
    void myconnect(int x,int y);       //给每一个按钮设置连接函数
    int judgeround(int p,int x1,int y1,int x2,int y2);  //判断轮次的函数

    void setui();   //修改ui界面的函数集合
    void Change_Rouond();    //修改当前需要下棋的人的状态的函数
    void receive(NetworkData w);
    void displayerror();
    void connected();
     int pattern = 0;
      void game_win(NetworkData data);
     int former_route_number;
     QString former_route[8];   //记录玩家之前的路径
     int Area_num; //颜色编号
     int route[250]; //记录路径
     int change_mark(char mark); //将区域转为颜色编号
    int time_id2;
    int time_id3_clock_down;
    int count_down;
    void move_op(NetworkData data);
    void restart_time();
    QString get_id(QString a);    //根据区域返回玩家编号
    long long me_time;    //用来接收时间戳
    long long send_time;  //用来接收时间戳
    NetworkSocket *socket;
    QString host;
    quint16 port;
private slots:
    void on_Big_but1_clicked(); //生成双人对决的棋子

    void on_Big_but2_clicked();

    void on_Big_but3_clicked();

    void on_Leave_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void change_direction();    //转动棋盘的函数
    void exchange_position(int x1,int y1,int x2,int y2);   //交换单个棋子的位置的函数


private:
    Ui::Widget *ui;
    Mybutton *btn[17][17];      //代表整个直角坐标系下所有按钮的可能性
    Judgement jd;               //一个存储所有判断函数的类
    int ju_x,ju_y;              //临时存储
    int P;
    int flag;
    int X,Y;//记录上次所走的棋子位置;
    int Player_Round;

};
#endif // WIDGET_H
