#ifndef SEQOBJECT_H
#define SEQOBJECT_H
#include <QString>

class SeqObject
{
public:
    SeqObject(QString nazov, QString typ, int id, int idTriedy);
    void NastavPoziciu(int px);
    void UpravPoziciu(int offX);
    void NastavPoziciuCreate(int px, int py);
    void NastavVelkost(int sirka, int vyska);
    void UpravVelkost(int offX, int offY);
    int surSX();
    int surSY();
    int surVX();
    int surVY();
    QString Suradnice();
    QString ObjNazov();
    int IDTriedy();
    void ZmenaObjNazvu(QString novyNazov);
    QString ObjTyp();
    void ZmenaObjTypu(QString novyTyp);
    int ID();
private:
    int id;
    QString nazov;
    QString typ;
    int idTriedy;
    int sx;
    int sy;
    int vx;
    int vy;
};

#endif // SEQOBJECT_H
