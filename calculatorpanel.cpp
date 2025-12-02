#include "calculatorpanel.h"
#include "ui_calculatorpanel.h"

#include <QDebug>

CalculatorPanel::CalculatorPanel(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::CalculatorPanel)
    , first(false)
{
    ui->setupUi(this);

    connect(ui->btn0, &QPushButton::clicked, this, &CalculatorPanel::processDigit);
    connect(ui->btn1, &QPushButton::clicked, this, &CalculatorPanel::processDigit);
    connect(ui->btn2, &QPushButton::clicked, this, &CalculatorPanel::processDigit);
    connect(ui->btn3, &QPushButton::clicked, this, &CalculatorPanel::processDigit);
    connect(ui->btn4, &QPushButton::clicked, this, &CalculatorPanel::processDigit);
    connect(ui->btn5, &QPushButton::clicked, this, &CalculatorPanel::processDigit);
    connect(ui->btn6, &QPushButton::clicked, this, &CalculatorPanel::processDigit);
    connect(ui->btn7, &QPushButton::clicked, this, &CalculatorPanel::processDigit);
    connect(ui->btn8, &QPushButton::clicked, this, &CalculatorPanel::processDigit);
    connect(ui->btn9, &QPushButton::clicked, this, &CalculatorPanel::processDigit);

    connect(ui->btnDot, &QPushButton::clicked, this, &CalculatorPanel::processDigit);

    connect(ui->btnDivide, &QPushButton::clicked, this, &CalculatorPanel::processOperator);
    connect(ui->btnMinus, &QPushButton::clicked, this, &CalculatorPanel::processOperator);
    connect(ui->btnMultiply, &QPushButton::clicked, this, &CalculatorPanel::processOperator);
    connect(ui->btnPlus, &QPushButton::clicked, this, &CalculatorPanel::processOperator);

    connect(ui->btnClear, &QPushButton::clicked, this, &CalculatorPanel::processClear);
    connect(ui->btnResult, &QPushButton::clicked, this, &CalculatorPanel::processOperator);

    connect(this, &CalculatorPanel::clearScreen, ui->CalcText, &QLineEdit::clear);
}

CalculatorPanel::~CalculatorPanel()
{
    delete ui;
}

void CalculatorPanel::processDigit()
{
    QString x = static_cast<QPushButton*>(QObject::sender())->text();
    ui->CalcText->insert(x);
}

void CalculatorPanel::processOperator()
{
    QString x = static_cast<QPushButton*>(QObject::sender())->text();
    QChar op = x.at(0);

    double input = ui->CalcText->text().toDouble();
    if(!first)
    {
        firstValue = input;
        ui->evaluationText->setText(QString::number(firstValue) + x);
        ui->CalcText->clear();
        first = true;
        action = op.unicode();
        //qDebug() << firstValue << action << secondValue;
    }
    else
    {
        secondValue = input;
        //qDebug() << firstValue << action << secondValue;
        qreal val = calculate(firstValue, secondValue, action);
        ui->evaluationText->setText(ui->evaluationText->text()
              + QString::number(secondValue) + "=" + QString::number(val));
        processClear();

    }

}

void CalculatorPanel::processClear()
{
    firstValue = 0;
    secondValue = 0;
    action = '\0';
    first = false;
    emit clearScreen();
}

qreal CalculatorPanel::calculate(qreal left, qreal right, QChar op)
{
    switch(op.unicode())
    {
    case u'+':
        return left + right;
        break;
    case u'-':
        return left - right;
        break;
    case u'*':
        return left * right;
        break;
    case u'/':
        return left / right;
        break;
    default:
        return 0;
    }
}

