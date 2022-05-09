#ifndef SEQEVENT_H
#define SEQEVENT_H
#include <QString>

/**
 * @brief Enumeration of types
 */
enum EventType {
    SYNCHRONOUS_MESSAGE, /*! Type synchronous message */
    ASYNCHRONOUS_MESSAGE, /*! Type asynchronous message */
    RETURN_MESSAGE, /*! Type return message */
    CREATE_OBJECT, /*! Type create object */
    DESTROY_OBJECT, /*! Type destroy object */
    ACTIVATION, /*! Type activation */
    DEACTIVATION /*! Type deactivation */
};

/**
 * @brief SeqEvent class used to create event.
 */
class SeqEvent
{
public:
    /**
     * @brief Constructor.
     * @param t1 ID of the first object.
     * @param t2 ID of the second object.
     * @param type Type of the event.
     * @param name Name of the event.
     * @param id ID of the event.
     * @param order Order of the event.
     */
    SeqEvent(int t1, int t2, EventType type, QString name, int id, int order);

    /**
     * @brief Returns ID of the event.
     * @return ID of the event.
     */
    int GetID();

    /**
     * @brief Returns name of the event.
     * @return String representation of the name.
     */
    QString GetEventName();

    /**
     * @brief Sets order of the event.
     * @param order New order of the event.
     */
    void SetOrder(int order);

    /**
     * @brief Changes name of the event.
     * @param newName New name of the event.
     */
    void ChangeEventName(QString newName);

    /**
     * @brief Returns ID of the first object.
     * @return ID of the object.
     */
    int GetEventClass1ID();

    /**
     * @brief Returns ID of the second object.
     * @return ID of the object.
     */
    int GetEventClass2ID();

    /**
     * @brief Returns type of the event.
     * @return Type of the event.
     */
    EventType GetEventUdlType();

    /**
     * @brief Changes type of the type.
     * @param New type of the event.
     */
    void ChangeEvtType(int newType);

    /**
     * @brief Returns string of the type of the event.
     * @return String of the type.
     */
    QString GetEventTypeStr();

    /**
     * @brief Returns order of the event.
     * @return Order of the event
     */
    int GetOrder();

private:
    /**
     * @brief ID of the event.
     */
    int id;

    /**
     * @brief ID of the first object.
     */
    int t1;

    /**
     * @brief ID of the second object.
     */
    int t2;

    /**
     * @brief Type of the event.
     */
    EventType type;

    /**
     * @brief Name of the event.
     */
    QString name;

    /**
     * @brief Order of the event.
     */
    int order;
};

#endif // SEQEVENT_H
