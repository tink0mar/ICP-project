#ifndef EDITOBJECTDIALOG_H
#define EDITOBJECTDIALOG_H

#include <QDialog>

namespace Ui {
class EditObjectDialog;
}

class EditObjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditObjectDialog(QWidget *parent = nullptr);
    ~EditObjectDialog();

    void SetClasses(QStringList classes);
    void SetName(QString name);
    void SetType(int index);
    QString GetName();
    QString GetType();
private slots:
    void on_btnOK_clicked();

    void on_butCancel_clicked();

private:
    Ui::EditObjectDialog *ui;
    QString name;
    QString type;
};

#endif // EDITOBJECTDIALOG_H
