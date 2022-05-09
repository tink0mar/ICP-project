#include "addeventdialog.h"
#include "ui_addeventdialog.h"

AddEventDialog::AddEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEventDialog)
{
    ui->setupUi(this);
}

AddEventDialog::~AddEventDialog()
{
    delete ui;
}

void AddEventDialog::SetObjects(QStringList objects){
    ui->comboObj1->addItems(objects);
    ui->comboObj2->addItems(objects);
}

void AddEventDialog::SetTypes(QStringList types){
    ui->comboType->addItems(types);
}

int AddEventDialog::GetObj1(){
    return o1;
}

int AddEventDialog::GetObj2(){
    return o2;
}

int AddEventDialog::GetType(){
    return type;
}

QString AddEventDialog::GetMsg(){
    return msg;
}

void AddEventDialog::on_btnOK_clicked()
{
    o1 = ui->comboObj1->currentIndex();
    o2 = ui->comboObj2->currentIndex();
    msg = ui->strMsgTxt->text();
    type = ui->comboType->currentIndex();
    accept();
}

void AddEventDialog::on_btnCancel_clicked()
{
    reject();
}
