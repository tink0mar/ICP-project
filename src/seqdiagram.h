#ifndef SEQDIAGRAM_H
#define SEQDIAGRAM_H

#include "seqobject.h"
#include "seqevent.h"
#include "diagram_class.h"
#include <QString>
#include <QList>

/**
 * @brief SeqDiagram class used to create and work with sequence diagram .
 */
class SeqDiagram
{
public:
    /**
     * @brief Constructor.
     * @param name Name of the diagram.
     * @param classD Diagram class.
     */
    SeqDiagram(QString name, DiagramClass* classD);

    /**
     * @brief Sets UUID.
     * @param uuid UUID.
     */
    void SetUUID(QString uuid);

    /**
     * @brief Sets Y coordination of base.
     * @param baseY Y coordination of base.
     */
    void SetBase(int baseY);

    /**
     * @brief Returns UUID.
     * @return UUID.
     */
    QString GetUUID();

    /**
     * @brief Returns list of objects.
     * @return List of object.
     */
    QList<SeqObject> GetObjectList();

    /**
     * @brief Returns list of events.
     * @return List of events.
     */
    QList<SeqEvent> GetEventList();

    /**
     * @brief Returns object.
     * @param id ID of the object.
     * @return Object.
     */
    SeqObject* FindObject(int id);

    /**
     * @brief Returns event with ID.
     * @param id ID of the event.
     * @return Event.
     */
    SeqEvent *FindEvent(int id);

    /**
     * @brief Returns event with order.
     * @param order Order of the event.
     * @return Event.
     */
    SeqEvent *FindEventOrder(int order);

    /**
     * @brief Adds object.
     * @param name Name of the object.
     * @param id ID of the object.
     * @param classID ID of the class.
     * @return Created object.
     */
    SeqObject* AddObject(QString name, int id, int classID);

    /**
     * @brief Edits object.
     * @param newName New name of the object.
     * @param classID New class of the object.
     * @param id ID of the edited object.
     */
    void EditObject(QString newName, int classID, int id);

    /**
     * @brief Adds new event.
     * @param o1 ID of the first object.
     * @param o2 ID of the second object.
     * @param type Type of the event.
     * @param msg Description of the message.
     * @param id ID of the event.
     * @param order Order of the event.
     * @param baseY Y coordination of base.
     */
    void AddEvent(int o1, int o2, EventType type, QString msg, int id, int order, int baseY);

    /**
     * @brief Edits event/message.
     * @param newMsg New description of the message.
     * @param id ID of the message.
     */
    void EditEvent(QString newMsg, int id);

    /**
     * @brief Moves the event down.
     * @param id ID of the event.
     */
    void MoveDown(int id);

    /**
     * @brief Moves the event up.
     * @param id ID of the event.
     */
    void MoveUp(int id);

    /**
     * @brief Deletes event.
     * @param id ID of the to-be deleted event.
     */
    void DeleteEvent(int id);

    /**
     * @brief Returns name of the object.
     * @return String representation of the name.
     */
    QString GetName();

    /**
     * @brief Deletes object.
     * @param id ID of the to-be deleted object.
     */
    void DeleteObject(int id);

    /**
     * @brief Formats source. Used while saving of the diagram to store spaces and empty strings.
     * @param src Source.
     * @return Formated string.
     */
    QString EscapeString(QString src);

    /**
     * @brief Formats source. Used while loading of the diagram to add spaces and empty strings.
     * @param src Source.
     * @return Formated string.
     */
    QString UnescapeString(QString src);

    /**
     * @brief Saves diagram.
     * @param filename Name of the file.
     */
    void SaveDiagram(QString filename);

    /**
     * @brief Loads diagram.
     * @param filename Name of the file.
     */
    void LoadDiagram(QString filename);

private:
    /**
     * @brief Next ID of the event.
     */
    int eventID;

    /**
     * @brief Next ID of the object.
     */
    int objectID;

    /**
     * @brief Next order of the event.
     */
    int eventOrder;

    /**
     * @brief Name of the diagram
     */
    QString name;

    /**
     * @brief List of objects.
     */
    QList<SeqObject> objectList;

    /**
     * @brief List of events.
     */
    QList<SeqEvent> eventList;

    /**
     * @brief Class diagram.
     */
    DiagramClass* classD;

    /**
     * @brief UUID inherited from class diagram.
     */
    QString uuid;

    /**
     * @brief Y coordination of base.
     */
    int baseY;
};

#endif // SEQDIAGRAM_H
