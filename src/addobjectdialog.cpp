#include "addobjectdialog.h"
#include "ui_addobjectdialog.h"

AddObjectDialog::AddObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddObjectDialog)
{
    ui->setupUi(this);
}

AddObjectDialog::~AddObjectDialog()
{
    delete ui;
}

void AddObjectDialog::on_btnOK_clicked()
{
    accept();
}


void AddObjectDialog::on_btnCancel_clicked()
{
    reject();
}

