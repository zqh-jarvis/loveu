#include "headwidget.h"
#include "ui_headwidget.h"
#include<QPushButton>


HeadWidget::HeadWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HeadWidget)
{
    ui->setupUi(this);      //登录界面只用ui实现就可以了
    this->setWindowTitle("登录窗口");
     //QPushButton *btn1 = new QPushButton;
     // QPushButton *btn2 = new QPushButton;

   // connect(btn2,&QPushButton::clicked,this,&HeadWidget::close);
}

HeadWidget::~HeadWidget()
{
    delete ui;
}

void HeadWidget::on_pushButton_2_clicked()
{
    this->hide();
    two.show();

   // return two.

}

void HeadWidget::on_pushButton_clicked()
{
    this->hide();
    //w->show();
}

