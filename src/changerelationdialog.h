/**
 * @file clsdgrwidget.h
 * @author Martin Kozák
 * @brief file represents change relation dialog
 * @date 2022-05-10
 *
 */
#ifndef CHANGERELATIONDIALOG_H
#define CHANGERELATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeRelationDialog;
}

/**
 * @brief The ChangeRelationDialog class for changing the dialog
 */
class ChangeRelationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeRelationDialog(QWidget *parent = nullptr);
    ~ChangeRelationDialog();
    /**
     * @brief Returns line edit 1 text
     * @return
     */
    QString getLineEdit1();

    /**
     * @brief Returns line edit 2 text
     * @return
     */
    QString getLineEdit2();

    /**
     * @brief Returns line edit 3 text
     * @return
     */
    QString getLineEdit3();

    /**
     * @brief Returns combo box text
     * @return
     */
    QString getComboBox();

    /**
     * @brief Changes line edit 1
     * @param str
     */
    void changeLineEdit1(QString str);

    /**
     * @brief changeLineEdit2
     * @param str
     */
    void changeLineEdit2(QString str);

    /**
     * @brief changeLineEdit3
     * @param str
     */
    void changeLineEdit3(QString str);

    /**
     * @brief changeComboBox
     * @param str
     */
    void changeComboBox(QString str);

private slots:
    /**
     * @brief Accpets dialog
     */
    void on_btnOK_clicked();

    /**
     * @brief Rejects dialog
     */
    void on_btnCancel_clicked();

private:
    /**
     * @brief ui GUI interface
     */
    Ui::ChangeRelationDialog *ui;
};

#endif // CHANGERELATIONDIALOG_H
