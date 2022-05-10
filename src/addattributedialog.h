/**
 * @file addattributedialog.h
 * @author Martin Kozák
 * @brief file represents add atribute dialog
 * @date 2022-05-10
 *
 */
#ifndef ADDATTRIBUTEDIALOG_H
#define ADDATTRIBUTEDIALOG_H

#include <QDialog>

namespace Ui {
class AddAttributeDialog;
}

/**
 * @brief The AddAttributeDialog class represents dialog for
 */
class AddAttributeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAttributeDialog(QWidget *parent = nullptr);
    ~AddAttributeDialog();
    QString getLineEditName();
    QString getLineEditType();
    QString getComboBoxContent();

    /**
     * @brief changeLineEdit1 change line_edit of widget
     * @param str string to be printed into line_edit
     */
    void changeLineEdit1(QString str);

    /**
     * @brief changeLineEdit2 change line_edit2 of widget
     * @param str string to be printed into line_edit2
     */
    void changeLineEdit2(QString str);

    /**
     * @brief changeComboBox change comboBox of widget
     * @param str string to be appended to comboBox
     */
    void changeComboBox(QString str);

    /**
     * @brief changeLabel2 change label2
     * @param str string to be printed to label2
     */
    void changeLabel2(QString str);
    /**
     * @brief changeName
     * @param str string to printed
     */
    void changeName(QString str);

private slots:
    /**
     * @brief on_btnOK_clicked handles button OK
     */
    void on_btnOK_clicked();
    /**
     * @brief on_btnCancel_clicked handles button Cancel
     */
    void on_btnCancel_clicked();

private:
    Ui::AddAttributeDialog *ui;
};

#endif // ADDATTRIBUTEDIALOG_H
