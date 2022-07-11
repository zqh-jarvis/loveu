#include "three_wight.h"
#include "ui_three_wight.h"

Three_Wight::Three_Wight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Three_Wight)
{
    ui->setupUi(this);
}

Three_Wight::~Three_Wight()
{
    delete ui;
}
