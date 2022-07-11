#ifndef TWO_WIGHT_H
#define TWO_WIGHT_H

//第二级界面的设计

#include <QWidget>
#include <login.h>
#include"servewindow.h"
#include"room.h"
namespace Ui {
class Two_wight;
}

class Two_wight : public QWidget
{
    Q_OBJECT

public:
    explicit Two_wight(QWidget *parent = nullptr);
    ~Two_wight();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Two_wight *ui;
public:
    login lo;
    servewindow serve;
    room r;

};

#endif // TWO_WIGHT_H
