#ifndef THREE_WIGHT_H
#define THREE_WIGHT_H

#include <QWidget>

namespace Ui {
class Three_Wight;
}

class Three_Wight : public QWidget
{
    Q_OBJECT

public:
    explicit Three_Wight(QWidget *parent = nullptr);
    ~Three_Wight();

private:
    Ui::Three_Wight *ui;
};

#endif // THREE_WIGHT_H
