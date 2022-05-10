#include "addrelationdialog.h"
#include "ui_addrelationdialog.h"
#include <QMessageBox>

AddRelationDialog::AddRelationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRelationDialog)
{
    ui->setupUi(this);
}

AddRelationDialog::~AddRelationDialog()
{
    delete ui;
}

void AddRelationDialog::on_btnOK_clicked()
{
    if (ui->lineEdit->displayText().size() != 0 ||
        ui->lineEdit_2->displayText().size() != 0 ||
        ui->lineEdit->displayText().size() != 0){
        accept();
    } else {
        QMessageBox::warning(this, "WARNING", "Empty lines");
    }

}

void AddRelationDialog::on_btnCancel_clicked()
{
    reject();
}

void AddRelationDialog::changeName(QString name){
    this->setWindowTitle(name);
}

QString AddRelationDialog::getLineEdit1(){
    return ui->lineEdit->displayText();
}

QString AddRelationDialog::getLineEdit2(){
    return ui->lineEdit_2->displayText();
}

QString AddRelationDialog::getLineEdit3(){
    return ui->lineEdit_3->displayText();
}

QString AddRelationDialog::getComboBox1(){
    return ui->comboBox->currentText();
}

QString AddRelationDialog::getComboBox2(){
    return ui->comboBox_2->currentText();
}

QString AddRelationDialog::getComboBox3(){
    return ui->comboBox_3->currentText();
}

void AddRelationDialog::changeLineEdit1(QString str){
   ui->lineEdit->setText(str);
}

void AddRelationDialog::changeLineEdit2(QString str){
    ui->lineEdit_2->setText(str);
}

void AddRelationDialog::changeLineEdit3(QString str){
    ui->lineEdit_3->setText(str);
}

void AddRelationDialog::addItemComboBox1(QString str){
    ui->comboBox->addItem(str);
}

void AddRelationDialog::addItemComboBox2(QString str){
    ui->comboBox_2->addItem(str);
}


void AddRelationDialog::changeComboBox3(QString str){
    ui->comboBox_3->setCurrentText(str);
}






