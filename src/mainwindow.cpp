#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clsdgrwidget.h"
#include "QWidget"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_class_diagram_triggered()
{
    clsdgrWidget* cdw = new clsdgrWidget();
    ui->tabWidget->addTab(cdw,"Class diagram");
    ui->tabWidget->setCurrentIndex(1);
}
