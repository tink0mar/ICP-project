#include "addattributedialog.h"
#include "ui_addattributedialog.h"

AddAttributeDialog::AddAttributeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAttributeDialog)
{
    ui->setupUi(this);
}

AddAttributeDialog::~AddAttributeDialog()
{
    delete ui;
}


void AddAttributeDialog::on_btnOK_clicked()
{
    accept();
}

void AddAttributeDialog::on_btnCancel_clicked()
{
    reject();
}

void AddAttributeDialog::changeName(QString name){
    this->setWindowTitle(name);
}

QString AddAttributeDialog::getLineEditName(){
    return ui->lineEdit->displayText();
}

QString AddAttributeDialog::getLineEditType(){
    return ui->lineEdit_2->displayText();
}

QString AddAttributeDialog::getComboBoxContent(){
    return ui->comboBox->currentText();
}

void AddAttributeDialog::changeLineEdit1(QString str){
    ui->lineEdit->setText(str);
}

void AddAttributeDialog::changeLineEdit2(QString str){
    ui->lineEdit_2->setText(str);
}

void AddAttributeDialog::changeComboBox(QString str){
    ui->comboBox->setCurrentText(str);
}

void AddAttributeDialog::changeLabel2(QString str){
    ui->label_2->setText(str);
}
