#ifndef SEQOBJECT_H
#define SEQOBJECT_H
#include <QString>

class SeqObject
{
public:
    SeqObject(QString name, int id, int classID);
    void SetPosition(int px);
    void ChangePosition(int offX);
    void SetPositionCreate(int px, int py);
    void SetSize(int width, int height);
    int surSX();
    int surSY();
    int surVX();
    int surVY();
    QString Coordinates();
    QString GetObjName();
    int GetClassID();
    void ChangeObjName(QString newName);
    int GetObjType();
    void ChangeObjType(int classID);
    int GetID();
    void ChangeSize(int offX, int offY);
private:
    int id;
    QString name;
    int classID;
    int sx;
    int sy;
    int vx;
    int vy;
};

#endif // SEQOBJECT_H
