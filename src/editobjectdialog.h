/**
 * @file editobjectdialog.h
 * @author Peter Pločica (xploci01)
 * @brief file represents edit object dialog
 * @date 2022-05-10
 *
 */
#ifndef EDITOBJECTDIALOG_H
#define EDITOBJECTDIALOG_H

#include <QDialog>

namespace Ui {
class EditObjectDialog;
}

/**
 * @brief EditObjectDialog class used to create a window for editing an object.
 */
class EditObjectDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Parent window.
     */
    explicit EditObjectDialog(QWidget *parent = nullptr);

    /**
     * @brief Deconstructor.
     */
    ~EditObjectDialog();

    /**
     * @brief Fills combobox with available types/classes.
     * @param classes Available classes.
     */
    void SetClasses(QStringList classes);

    /**
     * @brief Sets name into line edit box.
     * @param name Name of the object.
     */
    void SetName(QString name);

    /**
     * @brief Sets the type at the index in combobox.
     * @param index Index of the type.
     */
    void SetType(int index);

    /**
     * @brief Returns new name of the object.
     * @return String representation if the new name.
     */
    QString GetName();

    /**
     * @brief Returns new type of the object.
     * @return String representation of the selected type/class.
     */
    QString GetType();

private slots:
    /**
     * @brief Confirmation of the changes.
     */
    void on_btnOK_clicked();

    /**
     * @brief Cancelation.
     */
    void on_butCancel_clicked();

private:
    /**
     * @brief ui User interface.
     */
    Ui::EditObjectDialog *ui;

    /**
     * @brief Name of the object.
     */
    QString name;

    /**
     * @brief Type of the object.
     */
    QString type;
};

#endif // EDITOBJECTDIALOG_H
