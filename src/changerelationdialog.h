#ifndef CHANGERELATIONDIALOG_H
#define CHANGERELATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeRelationDialog;
}

class ChangeRelationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeRelationDialog(QWidget *parent = nullptr);
    ~ChangeRelationDialog();
    QString getLineEdit1();
    QString getLineEdit2();
    QString getLineEdit3();
    QString getComboBox();

    void changeLineEdit1(QString str);
    void changeLineEdit2(QString str);
    void changeLineEdit3(QString str);
    void changeComboBox(QString str);

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::ChangeRelationDialog *ui;
};

#endif // CHANGERELATIONDIALOG_H
