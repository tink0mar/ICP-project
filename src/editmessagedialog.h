#ifndef EDITMESSAGEDIALOG_H
#define EDITMESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class EditMessageDialog;
}

class EditMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditMessageDialog(QWidget *parent = nullptr);
    ~EditMessageDialog();

    void SetObj1(QString o);
    void SetObj2(QString o);
    void SetType(QString type);
    void SetMsg(QString msg);
    QString GetMsg();
private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::EditMessageDialog *ui;
    QString msg;
};

#endif // EDITMESSAGEDIALOG_H
