#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cdw = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_class_diagram_triggered()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Enter diagram name", "Diagram Name:", QLineEdit::Normal, "", &ok);
    if(ok){
        for(int i = ui->tabWidget->count()-1; i > 0; i--){
             ui->tabWidget->removeTab(i);
        }
        cdw = new ClsDiagramWidget();
        cdw->CreateNewClsDiagram(name);
        ui->tabWidget->addTab(cdw, name);
        ui->tabWidget->setCurrentIndex(1);
        sdList.clear();
    }
}

void MainWindow::on_actionNew_sequence_diagram_triggered()
{
    bool ok;
    if(cdw == NULL){
        QMessageBox::warning(this, "WARNING", "Diagram class needed");
        return;
    }
    SeqDiagramWidget* sdw = nullptr;
    QString name = QInputDialog::getText(this, "Enter diagram name", "Diagram Name:", QLineEdit::Normal, "", &ok);
    if(ok){
        sdw = new SeqDiagramWidget();
        sdw->CreateNewSeqDiagram(name, cdw->getDiagramCls());
        ui->tabWidget->addTab(sdw, name);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
        sdList.append(sdw->GetDiagram());
    }
}


void MainWindow::on_actionLoad_class_diagram_triggered()
{
    QString filter = "DiagramFiles (*.txt)";
    QString filename = QFileDialog::getOpenFileName(this, "Load class diagram", ".", filter);
    if(!filename.isEmpty()){
        for(int i = ui->tabWidget->count()-1; i > 0; i--){
             ui->tabWidget->removeTab(i);
        }
        cdw = new ClsDiagramWidget();
        cdw->LoadClsDiagram(filename);
        ui->tabWidget->addTab(cdw, cdw->getDiagramCls()->getName());
        ui->tabWidget->setCurrentIndex(1);
        sdList.clear();
    }
}


void MainWindow::on_actionLoad_sequence_diagram_triggered()
{
    if(cdw == NULL){
        QMessageBox::warning(this, "WARNING", "Diagram class needed");
        return;
    }
    QString filter = "DiagramFiles (*.txt)";
    QString filename = QFileDialog::getOpenFileName(this, "Load sequence diagram", ".", filter);
    SeqDiagramWidget* sdw = new SeqDiagramWidget();
    sdw->LoadSeqDiagram(filename, cdw->getDiagramCls());
    ui->tabWidget->addTab(sdw, sdw->GetDiagram()->GetName());
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    sdList.append(sdw->GetDiagram());
}


void MainWindow::on_actionSave_diagram_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if(index == 1){
        QString filter = "DiagramFiles (*.txt)";
        QString filename = QFileDialog::getSaveFileName(this, "Save class diagram", ".", filter);
        cdw->getDiagramCls()->saveDiagram(filename.toStdString());
    }
    else{
        SeqDiagram* seq = sdList[index-2];
        QString filter = "DiagramFiles (*.txt)";
        QString filename = QFileDialog::getSaveFileName(this, "Save sequence diagram", ".", filter);
        seq->SaveDiagram(filename);
    }
}


void MainWindow::on_actionQuit_triggered()
{
    //Uvolnovat vsetko
    QApplication::quit();
}

