#include "two_wight.h"
#include "ui_two_wight.h"
#include "login.h"
#include"servewindow.h"


Two_wight::Two_wight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Two_wight)
{
    ui->setupUi(this);

}

Two_wight::~Two_wight()
{
    delete ui;
}

void Two_wight::on_pushButton_2_clicked()
{
    lo.show();
}

void Two_wight::on_pushButton_clicked()
{
    r.show();
}

