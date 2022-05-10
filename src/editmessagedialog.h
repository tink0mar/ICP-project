/**
 * @file editmessagedialog.h
 * @author Peter Pločica (xploci01)
 * @brief file represents edit message dialog
 * @date 2022-05-10
 *
 */
#ifndef EDITMESSAGEDIALOG_H
#define EDITMESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class EditMessageDialog;
}

/**
 * @brief EditMessageDialog class used to create a window for editing a message/event.
 */
class EditMessageDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Parent window.
     */
    explicit EditMessageDialog(QWidget *parent = nullptr);

    /**
     * @brief Deconstructor.
     */
    ~EditMessageDialog();

    /**
     * @brief Sets object into read-only line edit box.
     * @param o Object.
     */
    void SetObj1(QString o);

    /**
     * @brief Sets object into read-only line edit box.
     * @param o Object.
     */
    void SetObj2(QString o);

    /**
     * @brief Sets type into read-only line edit box.
     * @param type Type of the message.
     */
    void SetType(QString type);

    /**
     * @brief Sets description into line edit box.
     * @param Message description.
     */
    void SetMsg(QString msg);

    /**
     * @brief Returns new message description.
     * @return String representation of message description.
     */
    QString GetMsg();

private slots:
    /**
     * @brief Confirmation of changes.
     */
    void on_btnOK_clicked();

    /**
     * @brief Cancelation.
     */
    void on_btnCancel_clicked();

private:
    /**
     * @brief ui User interface.
     */
    Ui::EditMessageDialog *ui;

    /**
     * @brief New message description.
     */
    QString msg;
};

#endif // EDITMESSAGEDIALOG_H
