#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::aboutRequest);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::aboutRequest()
{
    QMessageBox::information(this, tr("About"), tr("Here are two implementations of calculator.\n* First one is simple.\n* Second can calculate long expressions (even with parenthesis)."));
}

