#ifndef ADDRELATIONDIALOG_H
#define ADDRELATIONDIALOG_H

#include <QDialog>

namespace Ui {
class AddRelationDialog;
}

class AddRelationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRelationDialog(QWidget *parent = nullptr);
    ~AddRelationDialog();
    QString getLineEdit1();
    QString getLineEdit2();
    QString getLineEdit3();
    QString getComboBox1();
    QString getComboBox2();
    QString getComboBox3();
    void changeName(QString string);

    void changeLineEdit1(QString str);
    void changeLineEdit2(QString str);
    void changeLineEdit3(QString str);
    void addItemComboBox1(QString str);
    void addItemComboBox2(QString str);
    void changeComboBox3(QString str);


private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::AddRelationDialog *ui;
};

#endif // ADDRELATIONDIALOG_H
