#include "calculatorpanel.h"
#include "ui_calculatorpanel.h"

CalculatorPanel::CalculatorPanel(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::CalculatorPanel)
    , first(false)
{
    ui->setupUi(this);

    connect(this, &CalculatorPanel::sendDigit, this, &CalculatorPanel::readDigitButton);
    connect(this, &CalculatorPanel::sendChar, this, &CalculatorPanel::readOperatorButton);

    connect(ui->btn0, &QPushButton::clicked, this, [this]{emit sendDigit('0');});
    connect(ui->btn1, &QPushButton::clicked, this, [this]{emit sendDigit('1');});
    connect(ui->btn2, &QPushButton::clicked, this, [this]{emit sendDigit('2');});
    connect(ui->btn3, &QPushButton::clicked, this, [this]{emit sendDigit('3');});
    connect(ui->btn4, &QPushButton::clicked, this, [this]{emit sendDigit('4');});
    connect(ui->btn5, &QPushButton::clicked, this, [this]{emit sendDigit('5');});
    connect(ui->btn6, &QPushButton::clicked, this, [this]{emit sendDigit('6');});
    connect(ui->btn7, &QPushButton::clicked, this, [this]{emit sendDigit('7');});
    connect(ui->btn8, &QPushButton::clicked, this, [this]{emit sendDigit('8');});
    connect(ui->btn9, &QPushButton::clicked, this, [this]{emit sendDigit('9');});

    connect(ui->btnDot, &QPushButton::clicked, this, [this]{emit sendDigit('.');}); // decimal delimeter

    connect(ui->btnDivide, &QPushButton::clicked, this, [this]{emit sendChar('/');});
    connect(ui->btnMinus, &QPushButton::clicked, this, [this]{emit sendChar('-');});
    connect(ui->btnMultiply, &QPushButton::clicked, this, [this]{emit sendChar('*');});
    connect(ui->btnPlus, &QPushButton::clicked, this, [this]{emit sendChar('+');});

    connect(ui->btnClear, &QPushButton::clicked, this, &CalculatorPanel::processClear);
    connect(ui->btnClear, &QPushButton::clicked, ui->evaluationText, &QLabel::clear);

    connect(ui->btnResult, &QPushButton::clicked, this, [this]{emit sendChar('=');});

    connect(this, &CalculatorPanel::clearScreen, ui->CalcText, &QLineEdit::clear);
}

CalculatorPanel::~CalculatorPanel()
{
    delete ui;
}

void CalculatorPanel::processClear()
{
    firstValue = 0;
    secondValue = 0;
    action = '\0';
    first = false;
    emit clearScreen();
}

inline void CalculatorPanel::readDigitButton(QChar dig)
{
    ui->CalcText->insert(dig);
}

void CalculatorPanel::readOperatorButton(QChar op)
{
    double input = ui->CalcText->text().toDouble();
    if(!first)
    {
        firstValue = input;
        ui->evaluationText->setText(QString::number(firstValue) + op);
        ui->CalcText->clear();
        first = true;
        action = op.unicode();
    }
    else
    {
        secondValue = input;
        qreal val = calculate(firstValue, secondValue, action);
        ui->evaluationText->setText(ui->evaluationText->text()
              + QString::number(secondValue) + "=" + QString::number(val));
        processClear();
    }
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

