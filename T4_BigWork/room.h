#ifndef ROOM_H
#define ROOM_H
#include<networkdata.h>
#include<networksocket.h>
#include<networkserver.h>
#include <QMainWindow>
#include<QString>
#include<QLabel>
#include <QWidget>

namespace Ui {
class room;
}

class room : public QWidget
{
    Q_OBJECT

public:
    explicit room(QWidget *parent = nullptr);
    ~room();
    void single_update(NetworkData data);
    void updateInform(NetworkData data);

    QString playerList[6]; //“房间内玩家”数组
    QString playerstate[6];  //“房间内玩家状态“数组
    int Player_num = 0; //房间内玩家数
    void Dele(NetworkData data); //一个玩家退出房间
    void Ready_change(NetworkData data);  //准备状态改变
    QLabel *player_name[6]; //六个框中的玩家名称
    QLabel *ListState[6];   //六个框中的玩家状态
    //void paintEvent(QPaintEvent *);
      void Loc_me();
private:
       void on_pushButton_clicked();
    Ui::room *ui;
};

#endif // ROOM_H
