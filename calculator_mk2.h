#ifndef CALCULATOR_MK2_H
#define CALCULATOR_MK2_H

#include <QWidget>

namespace Ui {
class Calculator_mk2;
}

class Calculator_mk2 : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator_mk2(QWidget *parent = nullptr);
    ~Calculator_mk2();

private:
    Ui::Calculator_mk2 *ui;
};

#endif // CALCULATOR_MK2_H
