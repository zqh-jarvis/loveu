#ifndef SERVEWINDOW_H
#define SERVEWINDOW_H

#include <QWidget>

namespace Ui {
class servewindow;
}

class servewindow : public QWidget
{
    Q_OBJECT

public:
    explicit servewindow(QWidget *parent = nullptr);
    ~servewindow();

private:
    Ui::servewindow *ui;
};

#endif // SERVEWINDOW_H
