#ifndef ROOMVIEW_H
#define ROOMVIEW_H

#include <QWidget>

namespace Ui {
class roomview;
}

class roomview : public QWidget
{
    Q_OBJECT

public:
    explicit roomview(QWidget *parent = nullptr);
    ~roomview();

private:
    Ui::roomview *ui;
};

#endif // ROOMVIEW_H
