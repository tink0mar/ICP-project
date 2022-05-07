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

    void SetClasses(QStringList classes);
    QString GetName();
    QString GetType();
private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::AddObjectDialog *ui;
    QString name;
    QString type;
};

#endif // ADDOBJECTDIALOG_H
