#include "calculatorpanel.h"
#include "ui_calculatorpanel.h"

CalculatorPanel::CalculatorPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorPanel)
{
    ui->setupUi(this);
}

CalculatorPanel::~CalculatorPanel()
{
    delete ui;
}
