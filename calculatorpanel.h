#ifndef CALCULATORPANEL_H
#define CALCULATORPANEL_H

#include <QWidget>

namespace Ui {
class CalculatorPanel;
}

class CalculatorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorPanel(QWidget *parent = nullptr);
    ~CalculatorPanel();

private:
    Ui::CalculatorPanel *ui;
};

#endif // CALCULATORPANEL_H
