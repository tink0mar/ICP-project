#ifndef CHANGECLASSDIALOG_H
#define CHANGECLASSDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeClassDialog;
}

class ChangeClassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeClassDialog(QWidget *parent = nullptr);
    ~ChangeClassDialog();

private:
    Ui::ChangeClassDialog *ui;
};

#endif // CHANGECLASSDIALOG_H
