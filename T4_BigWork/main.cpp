#include "widget.h"

#include <QApplication>
#include"headwidget.h"
#include"two_wight.h"
#include<networksocket.h>
#include"room.h"
#include"success.h"


room * Room;
QString roomName;
QString PlayerName;
Widget *Board;
NetworkSocket *socket;
quint16 C_port;
QString C_host;
int me;
//Widget* w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HeadWidget hea_wid;     //生成登录界面
    Widget w;               //生成主界面(这里指单机界面)
    Two_wight t;
    hea_wid.show();
    return a.exec();
   // w.show();
     /*if(hea_wid.exec()==QDialog::Accepted)       //登录界面收到信号后打开单机界面
    {
        w.show();
        return a.exec();
    }
   else if(hea_wid.exec()==QDialog::Rejected)  //登录界面收到信号后打开联机界面
    {
        t.show();
        if(t.lo.exec()==QDialog::Accepted){
            w.show();

             return a.exec();
        }
        return a.exec();
    }
    else return 0;*/
}
