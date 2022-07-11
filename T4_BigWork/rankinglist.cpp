#include "rankinglist.h"
#include<room.h>
#include<QLabel>
#include<QPainter>
extern room *Room;
RankingList::RankingList(QWidget *parent)
    : QMainWindow{parent}
{
    int len = Room->Player_num;
    this->resize(500,300);
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    for(int i=0;i<len;i++)
    {
        player_rank[i] = new QLabel(this);
        player_rank[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        player_rank[i]->setPalette(pe);

        player_rank[i]->setFrameShape(QFrame::Box);
        player_rank[i]->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(255, 170, 0);");
        player_rank[i]->setText("Ranking");
        player_rank[i]->move(100,50+30*i);
        player_rank[i]->resize(90,20);
        player_rank[i]->show();
    }

    QPushButton *btn = new QPushButton;
    btn->setParent(this);
    btn->setText("return");
    btn->move(this->width()/2+100,this->height()/2+100);
    btn->resize(60,30);
    btn->show();
    connect(btn,&QPushButton::clicked,[=](){
        for(int j=0;j<len;j++)
        {
            Room->player_name[j]->setText("召唤师");
            Room->playerList[j].clear();
            Room->playerstate[j].clear();
            Room->ListState[j]->setText("碾碎它！");
        }
        Room->Player_num=0;
        this->close();
        Room->show();
    });
}

void RankingList::Rank(NetworkData data)
{
    int len = Room->Player_num;
    for(int i=0;i<len;i++)
    {
        player_rank[i]->setText(data.data1.section(' ',i,i));
    }
}

void RankingList::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/pic/picture/rank.jpg"),QRect());
}
