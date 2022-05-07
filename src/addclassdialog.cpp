#include "addclassdialog.h"
#include "ui_addclassdialog.h"

AddClassDialog::AddClassDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClassDialog)
{
    ui->setupUi(this);
}

AddClassDialog::~AddClassDialog()
{
    delete ui;
}

void AddClassDialog::on_btnCancel_clicked()
{
    reject();
}

void AddClassDialog::on_btnOK_clicked()
{
    accept();
}

QString AddClassDialog::getLineEditConent(){

    return ui->lineEdit->displayText();
}

QString AddClassDialog::getComboBoxContent(){
    return ui->comboBox->currentText();
}

int AddClassDialog::getInterface(){

    if (ui->checkBox->isChecked()){
        return 1;
    } else {
        return 0;
    }

}

void AddClassDialog::changeName(QString name){
    this->setWindowTitle(name);
}

void AddClassDialog::changeLabel(QString text){
    ui->label->setText(text);
}


void AddClassDialog::checkCheckBox(){
    ui->checkBox->setCheckState(static_cast<Qt::CheckState>(2));
}

void AddClassDialog::removeCheckBox(){
    delete ui->checkBox;
}

void AddClassDialog::removeLineEdit(){
    delete ui->lineEdit;
}

void AddClassDialog::addItemComboBox(QString str){
    ui->comboBox->addItem(str);
}

void AddClassDialog::removeComboBox(){
    delete ui->comboBox;
}
