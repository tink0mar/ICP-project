#include "seqevent.h"
#include "seqobject.h"

SeqEvent::SeqEvent(int t1, int t2, EventType type, QString name, int id, int order)
{
    this->id = id;
    this->t1 = t1;
    this->t2 = t2;
    this->type = type;
    this->name = name;
    this->order = order;
}
int SeqEvent::GetID(){
        return id;
    }

QString SeqEvent::GetEventName(){
        return name;
    }

int SeqEvent::GetOrder(){
        return order;
    }

void SeqEvent::SetOrder(int order){
        this->order = order;
    }

void SeqEvent::ChangeEventName(QString newName){
        name = newName;
    }

int SeqEvent::GetEventClass1ID(){
        return t1;
    }

int SeqEvent::GetEventClass2ID(){
        return t2;
    }

QString SeqEvent::GetEventTypeStr(){
        return QString::number(type);
    }

EventType SeqEvent::GetEventUdlType(){
        return type;
    }
