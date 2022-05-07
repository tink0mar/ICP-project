#ifndef SEQEVENT_H
#define SEQEVENT_H
#include <QString>

enum EventType {
    SYNCHRONOUS_MESSAGE,
    ASYNCHRONOUS_MESSAGE,
    RETURN_MESSAGE,
    CREATE_OBJECT,
    DESTROY_OBJECT,
    ACTIVATION,
    DEACTIVATION
};

class SeqEvent
{
public:
    SeqEvent(int t1, int t2, EventType type, QString name, int id, int order);
    int GetID();
    QString GetEventName();
    void SetOrder(int order);
    void ChangeEventName(QString newName);
    int GetEventClass1ID();
    int GetEventClass2ID();
    EventType GetEventUdlType();
    void ZmenaUldTypu(int newType);
    QString GetEventTypeStr();
    int GetOrder();
private:
    int id;
    int t1;
    int t2;
    EventType type;
    QString name;
    int order;
};

#endif // SEQEVENT_H
