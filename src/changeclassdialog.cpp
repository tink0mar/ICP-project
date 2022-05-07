#include "changeclassdialog.h"
#include "ui_changeclassdialog.h"

ChangeClassDialog::ChangeClassDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeClassDialog)
{
    ui->setupUi(this);
}

ChangeClassDialog::~ChangeClassDialog()
{
    delete ui;
}
