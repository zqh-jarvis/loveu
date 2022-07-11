#ifndef HEADWIDGET_H
#define HEADWIDGET_H

#include <QDialog>
#include <QDebug>
#include"two_wight.h"
#include"widget.h"


namespace Ui {
class HeadWidget;
}

class HeadWidget : public QDialog
{
    Q_OBJECT

public:
    explicit HeadWidget(QWidget *parent = nullptr);
    ~HeadWidget();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::HeadWidget *ui;
    Two_wight two;
    //Widget* w;
};

#endif // HEADWIDGET_H



