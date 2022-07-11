#include "servewindow.h"
#include "ui_servewindow.h"

servewindow::servewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::servewindow)
{
    ui->setupUi(this);
}

servewindow::~servewindow()
{
    delete ui;
}
