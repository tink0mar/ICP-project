#ifndef ADDCLASSDIALOG_H
#define ADDCLASSDIALOG_H

#include <QDialog>

namespace Ui {
class AddClassDialog;
}

class AddClassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddClassDialog(QWidget *parent = nullptr);
    ~AddClassDialog();
    QString getLineEditConent();
    QString getComboBoxContent();
    int getInterface();
    void changeName(QString name);
    void changeLabel(QString text);
    void removeCheckBox();
    void checkCheckBox();
    void removeLineEdit();
    void removeComboBox();
    void addItemComboBox(QString str);


private slots:

    void on_btnCancel_clicked();

    void on_btnOK_clicked();

private:
    Ui::AddClassDialog *ui;
};

#endif // ADDCLASSDIALOG_H
