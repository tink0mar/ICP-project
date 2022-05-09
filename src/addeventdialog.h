#ifndef ADDEVENTDIALOG_H
#define ADDEVENTDIALOG_H

#include <QDialog>

namespace Ui {
class AddEventDialog;
}

/**
 * @brief AddEventDialog class used to create a window for creation of event/message.
 */
class AddEventDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Parent window.
     */
    explicit AddEventDialog(QWidget *parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~AddEventDialog();

    /**
     * @brief Fills comboboxes with available objects.
     * @param objects Available objects.
     */
    void SetObjects(QStringList objects);

    /**
     * @brief SetTypes Fills comboboxes with types of events/messages.
     * @param types Types of messages.
     */
    void SetTypes(QStringList types);

    /**
     * @brief Returns index of the first selected object.
     * @return Index of selected object.
     */
    int GetObj1();

    /**
     * @brief Returns index of the second selected object.
     * @return Index of selected object.
     */
    int GetObj2();

    /**
     * @brief Returns index of the selected type of event/message.
     * @return Index of selected type.
     */
    int GetType();

    /**
     * @brief Returns description of the message.
     * @return Message description.
     */
    QString GetMsg();

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
    Ui::AddEventDialog *ui;
    /**
     * @brief Index of the first selected object, second selected object and selected type.
     */
    int o1, o2, type;
    /**
     * @brief Description of the message.
     */
    QString msg;

};

#endif // ADDEVENTDIALOG_H
