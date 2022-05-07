#include "addobjectdialog.h"
#include "ui_addobjectdialog.h"

#include <QMessageBox>

AddObjectDialog::AddObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddObjectDialog)
{
    ui->setupUi(this);
}

void AddObjectDialog::SetClasses(QStringList classes){
    ui->comboType->addItems(classes);
}

AddObjectDialog::~AddObjectDialog()
{
    delete ui;
}

QString AddObjectDialog::GetName(){
    return name;
}

QString AddObjectDialog::GetType(){
    return type;
}

void AddObjectDialog::on_btnOK_clicked()
{
    name = ui->strName->text();
    type = ui->comboType->currentText();
    accept();
}


void AddObjectDialog::on_btnCancel_clicked()
{
    reject();
}

