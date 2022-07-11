#ifndef SUCCESS_H
#define SUCCESS_H

#include <QWidget>

namespace Ui {
class success;
}

class success : public QWidget
{
    Q_OBJECT

public:
    explicit success(QWidget *parent = nullptr);
    ~success();

private slots:
    void on_pushButton_clicked();

private:
    Ui::success *ui;
};

#endif // SUCCESS_H
