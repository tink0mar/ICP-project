#ifndef SEQEVENT_H
#define SEQEVENT_H
#include <QString>

enum TypUdalosti {
    SYNCHRONNA_SPRAVA,
    ASYNCHRONNA_SPRAVA,
    NAVRAT_SPRAVY,
    TVORBA_OBJEKTU,
    ZANIK_OBJEKTU,
    AKTIVACIA,
    DEAKTIVACIA
};

class SeqEvent
{
public:
    SeqEvent(int t1, int t2, TypUdalosti typ, QString nazov, int id, int order);
    int ID();
    QString UdlNazov();
    int Order();
    void NastavPoradie(int order);
    void ZmenaUldNazov(QString novyNazov);
    int UdlTrieda1ID();
    int UdlTrieda2ID();
    TypUdalosti UdlTyp();
    void ZmenaUldTypu(int novyTyp);
    QString UdlTypStr();
private:
    int id;
    int t1;
    int t2;
    TypUdalosti typ;
    QString nazov;
    int order;
};

#endif // SEQEVENT_H
