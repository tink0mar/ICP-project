#ifndef ADDATTRIBUTEDIALOG_H
#define ADDATTRIBUTEDIALOG_H

#include <QDialog>

namespace Ui {
class AddAttributeDialog;
}

class AddAttributeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAttributeDialog(QWidget *parent = nullptr);
    ~AddAttributeDialog();
    QString getLineEditName();
    QString getLineEditType();
    QString getComboBoxContent();

    void changeLineEdit1(QString str);
    void changeLineEdit2(QString str);
    void changeComboBox(QString str);
    void changeLabel2(QString str);

    void changeName(QString);

private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();

private:
    Ui::AddAttributeDialog *ui;
};

#endif // ADDATTRIBUTEDIALOG_H
