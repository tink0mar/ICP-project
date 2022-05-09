#ifndef ADDOBJECTDIALOG_H
#define ADDOBJECTDIALOG_H

#include <QDialog>

namespace Ui {
class AddObjectDialog;
}

/**
 * @brief AddObjectDialog class used to create a window for creation of object.
 */
class AddObjectDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Parent window.
     */
    explicit AddObjectDialog(QWidget *parent = nullptr);

    /**
     * @brief Deconstructor.
     */
    ~AddObjectDialog();

    /**
     * @brief Fills combobox with available classes.
     * @param classes Available classes.
     */
    void SetClasses(QStringList classes);

    /**
     * @brief Returns name of the object.
     * @return String representation of the name.
     */
    QString GetName();

    /**
     * @brief Returns type (selected class) of the object.
     * @return String representation of type.
     */
    QString GetType();

private slots:
    /**
     * @brief Confirmation of the selection.
     */
    void on_btnOK_clicked();

    /**
     * @brief Cancelation.
     */
    void on_btnCancel_clicked();

private:
    /**
     * @brief User interface.
     */
    Ui::AddObjectDialog *ui;

    /**
     * @brief Name of the object.
     */
    QString name;

    /**
     * @brief type Type of the object.
     */
    QString type;
};

#endif // ADDOBJECTDIALOG_H
