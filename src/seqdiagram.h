#ifndef SEQDIAGRAM_H
#define SEQDIAGRAM_H
#include "seqobject.h"
#include "seqevent.h"
#include <QString>
#include <QList>

class Trieda{
public:
    Trieda(){

    }
    QString Nazov(){
        return "tata";
    }
};

class DiagramTried{
public:
    DiagramTried(){
        t1 = new Trieda();
    }
    Trieda* NajdiTriedu(int id){
        (void)id;
        return t1;
    }
private:
    Trieda* t1;
};

class SeqDiagram
{
public:
    SeqDiagram(QString nazov, DiagramTried* dTried);
    QString Nazov();
    void NastavUUID(QString uuid);
    void NastavZakladnu(int zakladnaY);
    QString UUID();
    QList<SeqObject> ZoznamObjektov();
    QList<SeqEvent> ZoznamUdalosti();
    SeqObject* NajdiObjekt(int id);
    SeqEvent *NajdiUdalost(int id);
    SeqEvent *NajdiUdalostOrder(int order);
    SeqObject* PridajObjekt(QString nazov, int id, int idTriedy);
    void UpravObjekt(QString novyNazov, QString novyTyp, int id);
    void ZrusenieObjektu(int id);
    void PridajUdalost(int o1, int o2, TypUdalosti typ, QString popis, int id, int order, int zakladnaY);
    void UpravUdalost(QString novyPopis, int id);
    void PresunUdalostDole(int id);
    void PresunUdalostHore(int id);
    void ZrusenieUdalosti(int id);
private:
    int idUdalosti;
    int idObjektu;
    int poradUdalosti;
    QString nazov;
    QList<SeqObject> zoznamObjektov;
    QList<SeqEvent> zoznamUdalosti;
    DiagramTried* dTried;
    QString uuid;
    int zakladnaY;
};

#endif // SEQDIAGRAM_H
