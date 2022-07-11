#include "room.h"
#include "ui_room.h"
#include<QString>
#include<networksocket.h>
#include<networkdata.h>
#include <QtNetwork/QTcpSocket>
#include<widget.h>
#include<QLabel>
#include<QPixmap>
#include<QPainter>


extern Widget *Board;
extern QString roomName;
extern QString PlayerName;
extern int me;
room::room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::room)
{
    ui->setupUi(this);
}

room::~room()
{
    delete ui;
}
void room::single_update(NetworkData data)
{
    player_name[Player_num]->setText(data.data1);
    ListState[Player_num]->setText("准备");
    playerList[Player_num] = data.data1;
    playerstate[Player_num] = '0';
    Player_num++;
}
void room::updateInform(NetworkData data)
{
//    qDebug()<<PlayerName<<"Debug";
    int Length = data.data2.length();
    qDebug()<<data.data2;
    qDebug()<<Length;
    int i=0;
    for(i=0;i<Length;i++)
    {
        player_name[i]->setText(data.data1.section(' ',i,i));
        playerstate[i]=data.data2[i];
        playerList[i]=player_name[i]->text();
        if(playerstate[i]=='0')
           ListState[i]->setText("准备");
        else
           ListState[i]->setText("开始");
    }
    player_name[Length]->setText(PlayerName);
    ListState[Length]->setText("准备");
    playerList[Length] = PlayerName;
    Player_num +=Length + 1;

}
void room::Dele(NetworkData data)
{
    int Length = Player_num;
    int i;
    for(i=0;i<Length;i++)
    {
        if(player_name[i]->text()==data.data1)

        {
            player_name[i]->clear();
            ListState[i]->clear();
        }
    }
    for(int j=i;j<Length-1;j++)
    {
        player_name[j]->setText(player_name[j+1]->text());
        ListState[j]->setText(ListState[j+1]->text());
    }
    player_name[Length-1]->clear();
    ListState[Length-1]->clear();
}

void room::Ready_change(NetworkData data)
{
    int len=Player_num;
    for(int i=0;i<len;i++)
    {
        if(player_name[i]->text()==data.data1)
        {
            playerstate[i]='1';
            ListState[i]->setText("开始");
            break;
        }
    }
}
void room::Loc_me()
{
    for(int i=0;i<Player_num;i++)
    {
        if(player_name[i]->text() == PlayerName)
        {
            me = i;
            return ;
        }
    }
}
void room::on_pushButton_clicked()
{
    roomName=ui->lineEdit->text();//房间名
    PlayerName=ui->lineEdit_2->text();//玩家名
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    NetworkData data(OPCODE::JOIN_ROOM_OP,roomName,PlayerName);
    Board->socket->send(data);
}
