#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clsdgrwidget.h"
#include "seqdiagramwidget.h"
#include <QInputDialog>
#include <QWidget>

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
    bool ok;
    ClsDiagramWidget* cdw;
    QString name = QInputDialog::getText(this, "Enter diagram name", "Diagram Name:", QLineEdit::Normal, "", &ok);
    if(ok){
        for(int i = ui->tabWidget->count()-1; i > 0; i--){
             ui->tabWidget->removeTab(i);
        }
        cdw = new ClsDiagramWidget();
        ui->tabWidget->addTab(cdw, name);
        ui->tabWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_actionNew_sequence_diagram_triggered()
{
    bool ok;
    SeqDiagramWidget* sdw = nullptr;
    QString name = QInputDialog::getText(this, "Enter diagram name", "Diagram Name:", QLineEdit::Normal, "", &ok);
    if(ok){
        sdw = new SeqDiagramWidget();
        ui->tabWidget->addTab(sdw, name);
        ui->tabWidget->setCurrentIndex(1);
    }
}


void MainWindow::on_actionLoad_class_diagram_triggered()
{

}


void MainWindow::on_actionLoad_sequence_diagram_triggered()
{

}


void MainWindow::on_actionSave_diagram_triggered()
{

}


void MainWindow::on_actionQuit_triggered()
{
    //Uvolnovat vsetko
    QApplication::quit();
}

