#ifndef ADDEVENTDIALOG_H
#define ADDEVENTDIALOG_H

#include <QDialog>

namespace Ui {
class AddEventDialog;
}

class AddEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEventDialog(QWidget *parent = nullptr);
    ~AddEventDialog();

    void SetObjects(QStringList objects);
    void SetTypes(QStringList types);
    int GetObj1();
    int GetObj2();
    int GetType();
    QString GetMsg();
private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::AddEventDialog *ui;
    int o1;
    int o2;
    QString msg;
    int type;

};

#endif // ADDEVENTDIALOG_H
