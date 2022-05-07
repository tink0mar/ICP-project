#include "changerelationdialog.h"
#include "ui_changerelationdialog.h"

ChangeRelationDialog::ChangeRelationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeRelationDialog)
{
    ui->setupUi(this);
}

ChangeRelationDialog::~ChangeRelationDialog()
{
    delete ui;
}

void ChangeRelationDialog::on_btnOK_clicked()
{
    accept();
}

void ChangeRelationDialog::on_btnCancel_clicked()
{
    reject();
}

QString ChangeRelationDialog::getLineEdit1(){
    return ui->lineEdit->displayText();
}

QString ChangeRelationDialog::getLineEdit2(){
    return ui->lineEdit_2->displayText();
}

QString ChangeRelationDialog::getLineEdit3(){
    return ui->lineEdit_3->displayText();
}

QString ChangeRelationDialog::getComboBox(){
    return ui->comboBox->currentText();
}

void ChangeRelationDialog::changeLineEdit1(QString str){
   ui->lineEdit->setText(str);
}

void ChangeRelationDialog::changeLineEdit2(QString str){
    ui->lineEdit_2->setText(str);
}

void ChangeRelationDialog::changeLineEdit3(QString str){
    ui->lineEdit_3->setText(str);
}

void ChangeRelationDialog::changeComboBox(QString str){
    ui->comboBox->setCurrentText(str);
}
