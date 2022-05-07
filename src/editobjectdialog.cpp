#include "editobjectdialog.h"
#include "ui_editobjectdialog.h"

EditObjectDialog::EditObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditObjectDialog)
{
    ui->setupUi(this);
}

void EditObjectDialog::SetClasses(QStringList classes){
    ui->comboType->addItems(classes);
}

void EditObjectDialog::SetName(QString name)
{
    ui->strName->setText(name);
}

void EditObjectDialog::SetType(int index){
    ui->comboType->setCurrentIndex(index);
}

QString EditObjectDialog::GetName(){
    return name;
}

QString EditObjectDialog::GetType(){
    return type;
}

EditObjectDialog::~EditObjectDialog()
{
    delete ui;
}

void EditObjectDialog::on_btnOK_clicked()
{
    name = ui->strName->text();
    type = ui->comboType->currentText();
    accept();
}


void EditObjectDialog::on_butCancel_clicked()
{
    reject();
}

