#include "seqdiagram.h"
#include "seqevent.h"
#include "seqobject.h"

#include <QFile>
#include <QIODevice>


SeqDiagram::SeqDiagram(QString name, DiagramClass *classD)
{
    eventID = 1;
    objectID = 1;
    eventOrder = 1;
    this->name = name;
    objectList.clear();
    eventList.clear();
    this->classD = classD;
    uuid = "";
    baseY = 0;
}

QString SeqDiagram::GetName(){
    return name;
}

void SeqDiagram::SetUUID(QString uuid){
    this->uuid = uuid;
}

void SeqDiagram::SetBase(int baseY){
    this->baseY = baseY;
}

QString SeqDiagram::GetUUID(){
    return uuid;
}

QList<SeqObject> SeqDiagram::GetObjectList(){
    return objectList;
}

QList<SeqEvent> SeqDiagram::GetEventList(){
    return eventList;
}

SeqObject* SeqDiagram::FindObject(int id){

    for( int i = 0; i < objectList.count(); ++i ){

        if(objectList[i].GetID() == id){
            return &objectList[i];
        }
    }
    return NULL;
}

SeqEvent* SeqDiagram::FindEvent(int id){
    for( int i=0; i<eventList.count(); ++i ){
        if(eventList[i].GetID() == id){
            return &eventList[i];
        }
    }
    return NULL;
}

SeqEvent* SeqDiagram::FindEventOrder(int order){
    for( int i=0; i<eventList.count(); ++i ){
        if(eventList[i].GetOrder() == order){
            return &eventList[i];
        }
    }
    return NULL;
}

SeqObject* SeqDiagram::AddObject(QString name, int id, int classID){
    if(id == 0){
        id = objectID++;
    }
    SeqObject* obj = new SeqObject(name, id, classID);
    objectList.append(*obj);
    return &objectList[objectList.count()-1];
}

void SeqDiagram::EditObject(QString newName, int classID, int id){
    for( int i=0; i<objectList.count(); ++i ){
        if(objectList[i].GetID() == id){
            objectList[i].ChangeObjName(newName);
            objectList[i].ChangeObjType(classID);
        }
    }
}

void SeqDiagram::DeleteObject(int id){
    for(int i=0; i<objectList.count(); ++i){
        if(objectList[i].GetID() == id){
            for(int j = eventList.size()-1; j >= 0; j--){
                SeqEvent evt = eventList[j];
                if(evt.GetEventClass1ID() == objectList[i].GetID() || evt.GetEventClass2ID() == objectList[i].GetID()){
                    DeleteEvent(evt.GetID());
                }
            }
            objectList.remove(i);
            return;
        }
    }
}

void SeqDiagram::AddEvent(int o1, int o2, EventType type, QString msg, int id, int order, int baseY){
    if(id == 0){
        id = eventID++;
    }
    if(order == 0){
        order = eventOrder++;
    }
    SeqEvent* evt = new SeqEvent(o1, o2, type, msg, id, order);
    eventList.append(*evt);
    if(type == EventType::CREATE_OBJECT){
        SeqObject* o = FindObject(o2);
        o->SetPositionCreate(o->surSX(), baseY+order*50);
    }
}

void SeqDiagram::EditEvent(QString newMsg, int id){
    for( int i=0; i<eventList.count(); ++i ){
        if(eventList[i].GetID() == id){
            eventList[i].ChangeEventName(newMsg);
        }
    }
}

void SeqDiagram::MoveDown(int id){
    SeqEvent* evt1 = FindEvent(id);
    if(evt1->GetOrder()+1 == eventOrder){
        return;
    }
    SeqEvent* evt2 = FindEventOrder(evt1->GetOrder()+1);
    evt2->SetOrder(evt1->GetOrder());
    evt1->SetOrder(evt1->GetOrder()+1);
    if(evt1->GetEventUdlType() == EventType::CREATE_OBJECT){
        SeqObject* o = FindObject(evt1->GetEventClass2ID());
        o->SetPositionCreate(o->surSX(), evt1->GetOrder()*50+baseY);
    }
    if(evt2->GetEventUdlType() == EventType::CREATE_OBJECT){
        SeqObject* o = FindObject(evt2->GetEventClass2ID());
        o->SetPositionCreate(o->surSX(), evt2->GetOrder()*50+baseY);
    }
}

void SeqDiagram::MoveUp(int id){
    SeqEvent* evt1 = FindEvent(id);
    if(evt1->GetOrder() == 1){
        return;
    }
    SeqEvent* evt2 = FindEventOrder(evt1->GetOrder()-1);
    evt2->SetOrder(evt1->GetOrder());
    evt1->SetOrder(evt1->GetOrder()-1);
    if(evt1->GetEventUdlType() == EventType::CREATE_OBJECT){
        SeqObject* o = FindObject(evt1->GetEventClass2ID());
        o->SetPositionCreate(o->surSX(), evt1->GetOrder()*50+baseY);
    }
    if(evt2->GetEventUdlType() == EventType::CREATE_OBJECT){
        SeqObject* o = FindObject(evt2->GetEventClass2ID());
        o->SetPositionCreate(o->surSX(), evt2->GetOrder()*50+baseY);
    }
}

void SeqDiagram::DeleteEvent(int id){
    int order = 0;
    for( int i=0; i<eventList.count(); ++i ){
        if(eventList[i].GetID() == id){
            order = eventList[i].GetOrder();
            eventList.remove(i);
            eventOrder--;
            break;
        }
    }
    for( int i=0; i<eventList.count(); ++i ){
        if(eventList[i].GetOrder() > order){
            eventList[i].SetOrder(eventList[i].GetOrder()-1);
        }
    }
}

void SeqDiagram::SaveDiagram(QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        return;
    }
    QString str = "title " + EscapeString(name) + " " + uuid + "\n";
    file.write(str.toLatin1().data());
    str = "nextobjid " + QString::number(objectID) + "\n";
    file.write(str.toLatin1().data());
    str = "nextevtid " + QString::number(eventID) + "\n";
    file.write(str.toLatin1().data());
    str = "nextnumevt " + QString::number(eventOrder) + "\n\n";
    file.write(str.toLatin1().data());
    for (SeqObject o : objectList){
        str = "object " + QString::number(o.GetID()) + " " + EscapeString(o.GetObjName()) + " "  +  QString::number(o.GetClassID()) + " " + o.Coordinates() + "\n";
        file.write(str.toLatin1().data());
    }
    file.write("\n");
    for (SeqEvent evt : eventList){
        str = "event " + QString::number(evt.GetID()) + " " + QString::number(evt.GetEventClass1ID()) + " " + QString::number(evt.GetEventClass2ID()) + " " + QString::number(evt.GetEventUdlType()) + " " + EscapeString(evt.GetEventName()) + " " + QString::number(evt.GetOrder()) +"\n";
        file.write(str.toLatin1().data());
    }
    file.close();
}

void SeqDiagram::LoadDiagram(QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }
    QByteArray data;
    data = file.readLine();
    QStringList params = QString(data).split(" ");
    if(params[0].compare("title") == 0){
        QString title = params[1];
        this->name = UnescapeString(title);
        //this->uuid = params[2];
    }
    else{
        file.close();
        return;
    }
    data = file.readLine();
    params = QString(data).split(" ");
    if(params[0].compare("nextobjid") == 0){
        this->objectID = params[1].toInt();
    }
    else{
        file.close();
        return;
    }
    data = file.readLine();
    params = QString(data).split(" ");
    if(params[0].compare("nextevtid") == 0){
        this->eventID = params[1].toInt();
    }
    else{
        file.close();
        return;
    }
    data = file.readLine();
    params = QString(data).split(" ");
    if(params[0].compare("nextnumevt") == 0){
        this->eventOrder = params[1].toInt();
    }
    else{
        file.close();
        return;
    }
    baseY = 0;
    while(!file.atEnd()){
        data = file.readLine();
        if(data.startsWith("object")){
            params = QString(data).split(" ");
            if(params.length() != 8){
                file.close();
                return;
            }
            int id = params[1].toInt();
            int idt = params[3].toInt();
            int x = params[4].toInt();
            int y = params[5].toInt();
            int width = params[6].toInt();
            int height = params[7].toInt();
            SeqObject* o = AddObject(UnescapeString(params[2]), id, idt);
            o->SetPositionCreate(x, y);
            o->SetSize(width, height);
            if(o->surSY() == 100 && o->surSY() + o->surVY()/2 > baseY){
                baseY = o->surSY() + o->surVY()/2;
            }
        }
        else if(data.startsWith("event")){
            params = QString(data).split(" ");
            if(params.length() != 7){
                file.close();
                return;
            }
            int id = params[1].toInt();
            int o1 = params[2].toInt();
            int o2 = params[3].toInt();
            int typ = params[4].toInt();
            int poradie = params[6].toInt();
            AddEvent(o1, o2, (EventType)typ, UnescapeString(params[5]), id, poradie, baseY);
        }
    }
}

QString SeqDiagram::EscapeString(QString src){
    if(src.isEmpty()){
        return "#EMPTY#";
    }
    QString dst = src.replace(" ", "#SPACE#");
    return dst;
}

QString SeqDiagram::UnescapeString(QString src){
    if(src.compare(("#EMPTY#")) == 0){
        return "";
    }
    QString dst = src.replace("#SPACE#", " ");
    return dst;
}
