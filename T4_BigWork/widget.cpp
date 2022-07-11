#include "widget.h"
#include "ui_widget.h"
#include<QString>
#include<QDebug>
#include<cmath>
#include"room.h"
#include"networkserver.h"
#include"networkdata.h"
#include"networksocket.h"
#include<rankinglist.h>
#include"success.h"
#include"error.h"

extern room *Room;
extern Widget*Board;
extern NetworkSocket *socket;
extern QString PlayerName;
extern int num;
extern int me;
extern QString C_host;
extern quint16 C_port;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),ju_x(0),ju_y(0),X(0),Y(0),flag(0)
{
    this->resize(1000,1000);    //修改棋盘界面的大小
    ui->setupUi(this);          //用ui界面来处理一些不太好处理的部分
    set_position();             //生成一个棋盘的基础棋位
    //修改ui界面的一些样式
    setui();

    socket = new NetworkSocket(new QTcpSocket(),this);
    connect(socket,&NetworkSocket::receive,this, &Widget::receive);//
    connect (socket->base(),&QAbstractSocket::errorOccurred,this,&Widget::displayerror);//错误情况
    connect(socket->base(),&QAbstractSocket::connected, this,&Widget::connected);//连接之后执行
    host = C_host;
    port = C_port;
    socket->hello("10.46.54.135", 16666);//客户端和服务端连接

}

Widget::~Widget()
{
    delete ui;
}

void Widget::mycao(int a1, int a2)      //最重要的逻辑函数，可以完成点击按钮之后的各种操作
{
    //getsate获得状态，0没有棋子，123456为玩家123456的棋子（走棋第一步）
    if(btn[a1][a2]->getsate()!=0&&flag==0)
    {
        ju_x=a1;
        ju_y=a2;
    }
    //(走棋第二步）
    else
    {
        //双击棋子，导致前面的状态被清除，进入下一个人的回合
        if(ju_x==a1&&ju_y==a2)
        {
            ju_x=0;
            ju_y=0;
            flag=0;
            Change_Rouond();
        }
        //如果之前没有选中棋子，则不做操作
        if(ju_x==0&&ju_y==0){}
        //如果之前有选中棋子，则进入判断阶段
        else                                //ju_x,ju_y是原来棋子的位置，a1,a2是要走的位置
        {

            //判断是否进行单次跳跃
            if(jd.judgemove_01(ju_x, ju_y, a1, a2)&&judgeround(P,X,Y,ju_x,ju_y)&&flag==0)   //进行单次跳跃之后的函数
                        {
                        int sate=btn[ju_x][ju_y]->getsate();//获得之前棋格的状态
                        btn[ju_x][ju_y]->clearsate();//clearsate清空棋子
                        btn[a1][a2]->putsate(sate);//putsate设置棋子
                        X=a1;
                        Y=a2;
                        ju_x=0;
                        ju_y=0;
                        Change_Rouond();
                        }

            //进行隔跳之后的操作函数
            else if(jd.judgemove_02(ju_x, ju_y, a1, a2)&&btn[(ju_x+a1)/2][(ju_y+a2)/2]->getsate()!=0&&(judgeround(P,X,Y,ju_x,ju_y)||flag==1))
            {
                int sate=btn[ju_x][ju_y]->getsate();//获得之前棋格的状态
                btn[ju_x][ju_y]->clearsate();//clearsate清空棋子
                btn[a1][a2]->putsate(sate);//putsate设置棋子
                X=a1;
                Y=a2;
                //如果是第一次隔跳，则不结束当前回合而进入连跳的状态
                if(jd.judgemove_02(a1, a2,a1-2,a2+2)&&ju_x!=(a1-2)&&ju_y!=(a2+2)||jd.judgemove_02(a1, a2,a1+2,a2-2)&&ju_x!=(a1+2)&&ju_y!=(a2-2)||jd.judgemove_02(a1, a2,a1,a2+2)&&ju_x!=a1&&ju_y!=(a2+2)||jd.judgemove_02(a1, a2,a1,a2-2)&&ju_x!=a1&&ju_y!=(a2-2)||jd.judgemove_02(a1, a2,a1+2,a2)&&ju_x!=(a1+2)&&ju_y!=a2||jd.judgemove_02(a1, a2,a1-2,a2)&&ju_x!=(a1-2)&&ju_y!=a2){
                    ju_x=a1;
                    ju_y=a2;
                    flag=1;
                }
                //额...这是干啥的
                else {
                    flag=0;
                    ju_x=0;
                    ju_y=0;
                }

            }
            //如果既不是单跳也不是隔跳
            else {}
        }
    }
}

void Widget::Change_Rouond()
{
    if(P==2)
    {
        if(Player_Round==1)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(0, 170, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=4;
        }
        else if(Player_Round==4)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(255, 0, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=1;
        }
    }
    if(P==4)
    {
        if(Player_Round==1)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(255, 255, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=3;
        }
        else if(Player_Round==3)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(0, 170, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=4;
        }
        else if(Player_Round==4)
        {
            qDebug()<<"just a joke";

            ui->Push_Player->setStyleSheet("background-color: rgb(255, 170, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=6;
        }
        else if(Player_Round==6)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(255, 0, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=1;
        }
    }
    if(P==6)
    {
        if(Player_Round==1)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(85, 255, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=2;
        }
        else if(Player_Round==2)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(255, 255, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=3;
        }
        else if(Player_Round==3)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(0, 170, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=4;
        }
        else if(Player_Round==4)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(170, 85, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=5;
        }
        else if(Player_Round==5)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(255, 170, 255);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=6;
        }
        else if(Player_Round==6)
        {
            ui->Push_Player->setStyleSheet("background-color: rgb(255, 0, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");
            Player_Round=1;
        }
    }
}

void Widget::setui()
{
    ui->label_2->setStyleSheet("background-color: rgb(232,221,203);border:4px groove gray;border-radius:15px;padding:3px 4px;");
    ui->lab_1->setStyleSheet("background-color: rgb(205,179,128);border:4px groove gray;border-radius:15px;padding:3px 4px;");
    ui->lab_2->setStyleSheet("background-color: rgb(205,179,128);border:4px groove gray;border-radius:15px;padding:3px 4px;");
    ui->lab_1->lower();
    ui->Big_but1->setStyleSheet("background-color: rgb(235,235,235);border:4px groove gray;border-radius:15px;padding:3px 4px;");
    ui->Big_but2->setStyleSheet("background-color: rgb(235,235,235);border:4px groove gray;border-radius:15px;padding:3px 4px;");
    ui->Big_but3->setStyleSheet("background-color: rgb(235,235,235);border:4px groove gray;border-radius:15px;padding:3px 4px;");
    ui->Leave->setStyleSheet("background-color: rgb(235,235,235);border:4px groove gray;border-radius:15px;padding:3px 4px;");
    //设置状态栏的初始量
    ui->Push_Player->setStyleSheet("background-color: rgb(225, 225, 225);border:4px groove gray;border-radius:15px;padding:3px 4px;");
}

void Widget::on_Big_but1_clicked()      //生成双人对局的棋子
{
   on_Leave_clicked();
    set_player(1);
    set_player(4);
    P=2;
    Player_Round=1;
    ui->Push_Player->setStyleSheet("background-color: rgb(255, 0, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");
}
void Widget::on_Big_but2_clicked()      //生成四人对局棋子
{
    on_Leave_clicked();
    set_player(1);
    set_player(4);
    set_player(6);
    set_player(3);
    P=4;
    Player_Round=1;
    ui->Push_Player->setStyleSheet("background-color: rgb(255, 0, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");
}
void Widget::on_Big_but3_clicked()      //生成六人对局棋子
{
    on_Leave_clicked();
    set_player(1);
    set_player(4);
    set_player(6);
    set_player(3);
    set_player(2);
    set_player(5);
    P=6;
    Player_Round=1;
    ui->Push_Player->setStyleSheet("background-color: rgb(255, 0, 0);border:4px groove gray;border-radius:15px;padding:3px 4px;");
}
void Widget::on_pushButton_clicked()    //转动棋盘的按钮
{
    change_direction();
    qDebug()<<"wtf";
}

void Widget::set_position()         //建立初始的棋子
{
    int deviation_x=460,deviation_y=1390;    //x,y轴位置的偏移量
    float new_x,new_y;                        //新坐标的位置
    float cha_x=1*30,cha_y=1.2*47.631;        //x,y轴的基础比例
    int mychange_x=1,mychange_y=1;          //用于以后直接调节按钮的距离比例的
    QString str_x,str_y;
    //生成部分
    for(int i=0;i<=16;i++)
    {
        for(int j=0;j<=16;j++)
        {
            if(jd.judge_out(i,j))
            {
                btn[i][j]=new Mybutton(this);
                new_x=mychange_x*(cha_x*i-cha_x*j)+deviation_x;
                new_y=-mychange_y*(cha_y*i+cha_y*j)+deviation_y;
                btn[i][j]->move(new_x,new_y);
                str_x=QString::number(i,10);
                str_y=QString::number(j,10);
                str_x.append(",");
                str_x.append(str_y);
                //btn[i][j]->setText(str_x);
                myconnect(i,j);
                btn[i][j]->put_x(i);
                btn[i][j]->put_y(j);
            }
        }
    }
}

void Widget::set_player(int x)
{
    //设置P1玩家的初始棋子
    if(x==1)
    {
        for(int i=0;i<17;i++)
        {
            for(int j=0;j<17;j++)
            {
                if(jd.judge_P1(i,j))
                {
                    //改变该棋位的状态和颜色
                    btn[i][j]->putsate(1);
                    btn[i][j]->put_x(i);
                    btn[i][j]->put_y(j);
                }
            }
        }
    }
    //设置P4玩家的初始棋子
    if(x==4)
    {
        for(int i=0;i<17;i++)
        {
            for(int j=0;j<17;j++)
            {
                if(jd.judge_P4(i,j))
                {
                    //改变该棋位的状态和颜色
                    btn[i][j]->putsate(4);
                    btn[i][j]->put_x(i);
                    btn[i][j]->put_y(j);
                }
            }
        }
    }
    if(x==2)
    {
        for(int i=0;i<17;i++)
        {
            for(int j=0;j<17;j++)
            {
                if(jd.judge_P2(i,j))
                {
                    //改变该棋位的状态和颜色
                    btn[i][j]->putsate(2);
                    btn[i][j]->put_x(i);
                    btn[i][j]->put_y(j);
                }
            }
        }
    }
    if(x==3)
    {
        for(int i=0;i<17;i++)
        {
            for(int j=0;j<17;j++)
            {
                if(jd.judge_P3(i,j))
                {
                    //改变该棋位的状态和颜色
                    btn[i][j]->putsate(3);
                    btn[i][j]->put_x(i);
                    btn[i][j]->put_y(j);
                }
            }
        }
    }
    if(x==5)
    {
        for(int i=0;i<17;i++)
        {
            for(int j=0;j<17;j++)
            {
                if(jd.judge_P5(i,j))
                {
                    //改变该棋位的状态和颜色
                    btn[i][j]->putsate(5);
                    btn[i][j]->put_x(i);
                    btn[i][j]->put_y(j);
                }
            }
        }
    }
    if(x==6)
    {
        for(int i=0;i<17;i++)
        {
            for(int j=0;j<17;j++)
            {
                if(jd.judge_P6(i,j))
                {
                    //改变该棋位的状态和颜色
                    btn[i][j]->putsate(6);
                    btn[i][j]->put_x(i);
                    btn[i][j]->put_y(j);
                }
            }
        }
    }

}

void Widget::myconnect(int x,int y)
{
    connect(btn[x][y],&Mybutton::sigSub,this,&Widget::mycao);
}

void Widget::on_Leave_clicked()     //清除所有棋子
{
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<17;j++)
        {
            if(jd.judge_out(i,j))
            {
                btn[i][j]->clearsate();
            }
        }
    }
    P=0;
    X=0;
    Y=0;
    flag=0;
    ju_x=0;
    ju_y=0;
    Player_Round=0;
    ui->Push_Player->setStyleSheet("background-color: rgb(225, 225, 225);border:4px groove gray;border-radius:15px;padding:3px 4px;");
}

int Widget::judgeround(int p,int x1,int y1,int x2,int y2)//(x1,y1)是旧位置，（x2,y2)是新位置；
{   if(x1==0&&y1==0&&btn[x2][y2]->getsate()==1)return 1;
    else if(p==2){
        if(btn[x1][y1]->getsate()==1&&btn[x2][y2]->getsate()==4||btn[x1][y1]->getsate()==4&&btn[x2][y2]->getsate()==1)return 1;
        else return 0;
    }
    else if(p==4){
        if(btn[x1][y1]->getsate()==1&&btn[x2][y2]->getsate()==3||btn[x1][y1]->getsate()==3&&btn[x2][y2]->getsate()==4||btn[x1][y1]->getsate()==4&&btn[x2][y2]->getsate()==6||btn[x1][y1]->getsate()==6&&btn[x2][y2]->getsate()==1)return 1;
        else return 0;
    }
    else if(p==6){
        if(btn[x2][y2]->getsate()-btn[x1][y1]->getsate()==1||btn[x1][y1]->getsate()==6&&btn[x2][y2]->getsate()==1)return 1;
        else return 0;
    }
}

void Widget::change_direction()     //转动棋盘的函数,顺时针转动60°
{
    for(int i=0;i<=4;i++)
    {
        for(int j=0;j<=4;j++)
        {
            if(i==4&&j==4);
            else
            btn[i][j]=new Mybutton(this);
        }
    }
    //0
    {
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                if(i>=4&&j>=4&&(i+j)<=12)
                {
                    exchange_position(i-4,j-4,i,j);
                    //printf("this (%d,%d) is %d %d\n",i,j,btn[i][j]->pos().x(),btn[i][j]->pos().y());
                }
            }
        }
    }
    //1
    {
    exchange_position(4,4,0,12);
    exchange_position(4,5,1,12);
    exchange_position(4,6,2,12);
    exchange_position(4,7,3,12);
    exchange_position(4,8,4,12);

    exchange_position(5,4,1,11);
    exchange_position(5,5,2,11);
    exchange_position(5,6,3,11);
    exchange_position(5,7,4,11);

    exchange_position(6,4,2,10);
    exchange_position(6,5,3,10);
    exchange_position(6,6,4,10);

    exchange_position(7,4,3,9);
    exchange_position(7,5,4,9);

    exchange_position(8,4,4,8);
    }
    //2
    {
    exchange_position(0,12,4,16);
    exchange_position(1,12,5,15);
    exchange_position(2,12,6,14);
    exchange_position(3,12,7,13);
    exchange_position(4,12,8,12);

    exchange_position(1,11,4,15);
    exchange_position(2,11,5,14);
    exchange_position(3,11,6,13);
    exchange_position(4,11,7,12);

    exchange_position(2,10,4,14);
    exchange_position(3,10,5,13);
    exchange_position(4,10,6,12);

    exchange_position(3,9,4,13);
    exchange_position(4,9,5,12);

    exchange_position(4,8,4,12);
    }
    //3
    {
    exchange_position(4,16,12,12);
    exchange_position(4,15,11,12);
    exchange_position(4,14,10,12);
    exchange_position(4,13,9,12);
    exchange_position(4,12,8,12);

    exchange_position(5,15,12,11);
    exchange_position(5,14,11,11);
    exchange_position(5,13,10,11);
    exchange_position(5,12,9,11);

    exchange_position(6,14,12,10);
    exchange_position(6,13,11,10);
    exchange_position(6,12,10,10);

    exchange_position(7,13,12,9);
    exchange_position(7,12,11,9);

    exchange_position(8,12,12,8);
    }
    //4
    {
    exchange_position(12,12,16,4);
    exchange_position(12,11,15,4);
    exchange_position(12,10,14,4);
    exchange_position(12,9,13,4);
    exchange_position(12,8,12,4);

    exchange_position(11,12,15,5);
    exchange_position(11,11,14,5);
    exchange_position(11,10,13,5);
    exchange_position(11,9,12,5);

    exchange_position(10,12,14,6);
    exchange_position(10,11,13,6);
    exchange_position(10,10,12,6);

    exchange_position(9,12,13,7);
    exchange_position(9,11,12,7);

    exchange_position(8,12,12,8);
    }
    //5
    {
    exchange_position(12,8,12,4);
    exchange_position(12,7,11,4);
    exchange_position(12,6,10,4);
    exchange_position(12,5,9,4);
    exchange_position(12,4,8,4);

    exchange_position(13,7,12,3);
    exchange_position(13,6,11,3);
    exchange_position(13,5,10,3);
    exchange_position(13,4,9,3);

    exchange_position(14,6,12,2);
    exchange_position(14,5,11,2);
    exchange_position(14,4,10,2);

    exchange_position(15,5,12,1);
    exchange_position(15,4,11,1);

    exchange_position(16,4,12,0);
    }
    //6
    {
    exchange_position(12,4,8-4,4-4);
    exchange_position(12,3,7-4,4-4);
    exchange_position(12,2,6-4,4-4);
    exchange_position(12,1,5-4,4-4);
    exchange_position(12,0,4-4,4-4);

    exchange_position(11,4,7-4,5-4);
    exchange_position(11,3,6-4,5-4);
    exchange_position(11,2,5-4,5-4);
    exchange_position(11,1,4-4,5-4);

    exchange_position(10,4,6-4,6-4);
    exchange_position(10,3,5-4,6-4);
    exchange_position(10,2,4-4,6-4);

    exchange_position(9,4,5-4,7-4);
    exchange_position(9,3,4-4,7-4);

    exchange_position(8,4,4-4,8-4);

    }
}

void Widget::exchange_position(int x1,int y1,int x2,int y2)    //交换单个棋子的位置的函数(这样可以不改变棋子的属性)
{
//    int px1=btn[x1][y1]->pos().x();
//    int py1=btn[x1][y1]->pos().y();
    int px2=btn[x2][y2]->pos().x();
    int py2=btn[x2][y2]->pos().y();
    btn[x1][y1]->move(px2,py2);
    //btn[x2][y2]->move(px1,py1);
}

void Widget::on_pushButton_2_clicked()  //人工不智能托管
{

//    switch (Player_Round) {
//    case 1:
//    }
}




////////////////////////////////////////////////////////
void Widget::receive(NetworkData w){
    if(w.op==OPCODE::JOIN_ROOM_OP)
    {
        Room->single_update(w);
    }
    else if(w.op==OPCODE::JOIN_ROOM_REPLY_OP)
    {

        Room->updateInform(w);

    }
    else if(w.op==OPCODE::LEAVE_ROOM_OP)
    {
        //用户离开房间
        //data1为用户名
        //删除数组中对应的玩家
        //更新房间界面
        Room->Dele(w);
    }
    else if(w.op==OPCODE::CLOSE_ROOM_OP)
    {
        //没说干啥的
    }
    else if(w.op==OPCODE::PLAYER_READY_OP)
    {
        //data1为用户名
        //将用户名对应的状态数组改为1
        //更新房间界面
        Room->Ready_change(w);
    }
    ////////////////////////////////////////////////////////////////////////////////
    else if(w.op==OPCODE::START_GAME_OP)
    {

        Room->close();
        Room->Loc_me();
        if(pattern == 2) {
            on_Big_but1_clicked();
        }
        if(pattern == 3){
            on_Big_but2_clicked();
        }
        if(pattern == 6){
            on_Big_but3_clicked();
        }
        update();
        //init_occupied();   //必须要在确定pattern之后才能更新occupied数组的状态
        this->show();
        time_id3_clock_down = startTimer(1000);




    }
//////////////////////////////////////////////////////////////////////////////////////////////////
    else if(w.op==OPCODE::START_TURN_OP)
    {
        std::time_t t = std::time(0);
        send_time = w.data2.toLong();
        me_time = t;
        restart_time();
    }
    else if(w.op==OPCODE::MOVE_OP)
    {
        //data1为玩家初始区域
        //data2为旗子轨迹
        //更新棋盘
//        if(me == 0)
//            qDebug()<<w.data2<<"绿棋路径";
         move_op(w);

    }
    else if(w.op==OPCODE::END_TURN_OP)
    {
        //弹出获胜窗口（新窗口）
        //WinWindow * win = new WinWindow;//获胜窗口还未做
        //win->show();
    }
    else if(w.op==OPCODE::END_GAME_OP)
    {
        //游戏结束
        //data1为玩家排名列表，弹出窗口显示（新窗口）
        //回到房间界面，清空所有数组，重新输入加入房间
        game_win(w);
        socket->bye();
        this->close();
    }
    else if(w.op==OPCODE::ERROR_OP)
    {
        if(w.data1=="NOT_IN_ROOM")
        {
            //加入房间失败。可能由于用户名冲突引起
            //重新进入加房间界面
        }
        else if(w.data1=="ROOM_IS_RUNNING")
        {
            //棋子移动非法
            //重新发送mode_up
        }
        else if(w.data1=="ROOM_NOT_RUNNING")
        {
            //无法解析该请求
        }
        else if(w.data1=="INVALID_JOIN")
        {
            //当前用户不在房间内
        }
        else if(w.data1=="OUTTURN_MOVE")
        {
            //当前不在自己行动的轮次
        }
        else if(w.data1=="INVALID_MOVE")
        {
            //当前房间内的游戏正在进行
        }
        else if(w.data1=="INVALID_REQ")
        {
            //当前房间内没有正在进行的游戏
        }
        else if(w.data1=="OTHER_ERROR")
        {
            //前面没有提及的其他错误
        }
    }
}

void Widget::displayerror(){
    error R;
    R.show();
    //失败
}

void Widget::connected(){
    success S;
       S.show();//成功
}


void Widget::restart_time()
{
    count_down = 15-(me_time-send_time);
    time_id3_clock_down = startTimer(1000);
}
void Widget::move_op(NetworkData data)
{
    int t=1;
    for(int i=0;i<Room->Player_num&&t;i++)     //确定当前发送路径的玩家的编号，以便存入对应储存前步路径的former_route
    {
        if(Room->playerList[i] == get_id(data.data1))
        {

            former_route_number = i;
            former_route[i] = data.data2;
            t=0;
            break;
        }
    }
    former_route[former_route_number] = data.data2;
    char *au;
    QByteArray ba2 = data.data1.toLatin1();
    au=ba2.data();
    char ai=*au;
    //  //////Area_num=change_mark(ai);
    QString str = data.data2;
    str.remove(QRegularExpression("\\s"));
    char * ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();
    //  //////change_char_to_int(ch);
//    qDebug()<<"DEBUG";
    time_id2 = startTimer(1000);
}
QString Widget::get_id(QString a)
{
    if(pattern == 2)
    {
        if(a == "A")
            return Room->playerList[0];
        else if(a == "D")
            return Room->playerList[1];
    }
    else if(pattern == 3)
    {
        if(a == "A")
            return Room->playerList[0];
        else if(a == "C")
            return Room->playerList[1];
        else if(a == "E")
            return Room->playerList[2];
    }
    else if(pattern == 6)
    {
        if(a == "A")
            return Room->playerList[0];
        else if(a == "B")
            return Room->playerList[1];
        else if(a == "C")
            return Room->playerList[2];
        else if(a == "D")
            return Room->playerList[3];
        else if(a == "E")
            return Room->playerList[4];
        else if(a == "F")
            return Room->playerList[5];
    }
}

void Widget::game_win(NetworkData data)
{
    RankingList * list = new RankingList;
    list->Rank(data);
    list->show();
}







