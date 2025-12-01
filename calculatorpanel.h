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

signals:
    void clearScreen();
    void showResult(qreal result);

public slots:
    void processDigit();
    void processOperator();
    void processClear();

private:
    Ui::CalculatorPanel *ui;
    bool first;
    qreal firstValue;
    qreal secondValue;
    char action; // так себе идея. Но начнём с этого

    qreal calculate(qreal left, qreal right, QChar op);
};

#endif // CALCULATORPANEL_H
