#include "roomview.h"
#include "ui_roomview.h"

roomview::roomview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roomview)
{
    ui->setupUi(this);
}

roomview::~roomview()
{
    delete ui;
}
