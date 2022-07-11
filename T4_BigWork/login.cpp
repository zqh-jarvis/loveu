#include "login.h"
#include "ui_login.h"
#include<QMessageBox>       //提示窗口的头文件声明QMessage

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_LoginBtn_clicked()//有关“开始”按钮的操作代码
{
    //当usrLineEdit和pwLineEdit都能匹配字符串时发出accept指令
    if(ui->usrLineEdit->text().trimmed()==tr("54321")&&ui->pwLineEdit->text().trimmed()==tr("12345"))
    {
        accept();

    }
    //如果不匹配则弹出提示窗口
    else
    {
        QMessageBox::warning(this,tr("Warning"),                       //第一行是窗口标题的字符
                             tr("Username or Password is wrong!"),      //第二行是warning窗口的提示字符串
                             QMessageBox::Yes);                         //调用Yes的按钮
        ui->usrLineEdit->clear();                                       //清除账号输入栏的内容
        ui->pwLineEdit->clear();                                        //清除密码输入栏的内容
        ui->usrLineEdit->setFocus();                                    //将光标转移到账号输入栏
    }
}
