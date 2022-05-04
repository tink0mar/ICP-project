#ifndef ADDOBJECTDIALOG_H
#define ADDOBJECTDIALOG_H

#include <QDialog>

namespace Ui {
class AddObjectDialog;
}

class AddObjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddObjectDialog(QWidget *parent = nullptr);
    ~AddObjectDialog();

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::AddObjectDialog *ui;
};

#endif // ADDOBJECTDIALOG_H
