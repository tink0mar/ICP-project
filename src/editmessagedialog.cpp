#include "editmessagedialog.h"
#include "ui_editmessagedialog.h"

EditMessageDialog::EditMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMessageDialog)
{
    ui->setupUi(this);
}

EditMessageDialog::~EditMessageDialog()
{
    delete ui;
}

void EditMessageDialog::SetObj1(QString o){
    ui->strObj1->setText(o);
}

void EditMessageDialog::SetObj2(QString o){
    ui->strObj2->setText(o);
}

void EditMessageDialog::SetType(QString type){
    ui->strType->setText(type);
}

void EditMessageDialog::SetMsg(QString msg){
    ui->strMsg->setText(msg);
}

QString EditMessageDialog::GetMsg(){
    return msg;
}

void EditMessageDialog::on_btnOK_clicked()
{
    msg = ui->strMsg->text();
    accept();
}


void EditMessageDialog::on_btnCancel_clicked()
{
    reject();
}

