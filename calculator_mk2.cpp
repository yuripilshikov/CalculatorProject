#include "calculator_mk2.h"
#include "ui_calculator_mk2.h"

Calculator_mk2::Calculator_mk2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calculator_mk2)
{
    ui->setupUi(this);
}

Calculator_mk2::~Calculator_mk2()
{
    delete ui;
}
