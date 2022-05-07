#ifndef SEQDIAGRAM_H
#define SEQDIAGRAM_H
#include "seqobject.h"
#include "seqevent.h"
#include "diagram_class.h"
#include <QString>
#include <QList>

class SeqDiagram
{
public:
    SeqDiagram(QString nazov, DiagramClass* dTried);
    void SetUUID(QString uuid);
    void SetBase(int zakladnaY);
    QString SetUUID();
    QList<SeqObject> GetObjectList();
    QList<SeqEvent> GetEventList();
    SeqObject* FindObject(int id);
    SeqEvent *FindEvent(int id);
    SeqEvent *FindEventOrder(int order);
    SeqObject* AddObject(QString nazov, int id, int idTriedy);
    void EditObject(QString novyNazov, int classID, int id);
    void PridajUdalost(int o1, int o2, EventType typ, QString popis, int id, int order, int zakladnaY);
    void EditEvent(QString novyPopis, int id);
    void MoveDown(int id);
    void MoveUp(int id);
    void DeleteEvent(int id);
    QString GetName();
    void DeleteObject(int id);
    QString EscapeString(QString src);
    QString UnescapeString(QString src);
    void SaveDiagram(QString filename);
    void LoadDiagram(QString filename);
private:
    int eventID;
    int objectID;
    int eventOrder;
    QString name;
    QList<SeqObject> objectList;
    QList<SeqEvent> eventList;
    DiagramClass* classD;
    QString uuid;
    int baseY;
};

#endif // SEQDIAGRAM_H
