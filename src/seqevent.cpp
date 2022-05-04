#include "seqevent.h"
#include "seqobject.h"

SeqEvent::SeqEvent(int t1, int t2, TypUdalosti typ, QString nazov, int id, int order)
{
    this->id = id;
    this->t1 = t1;
    this->t2 = t2;
    this->typ = typ;
    this->nazov = nazov;
    this->order = order;
}
int SeqEvent::ID(){
        return id;
    }

    /** Získanie názvu udalosti
     * @return Reťazec reprezentujúci názov
     */
QString SeqEvent::UdlNazov(){
        return nazov;
    }

int SeqEvent::Order(){
        return order;
    }

void SeqEvent::NastavPoradie(int order){
        this->order = order;
    }

void SeqEvent::ZmenaUldNazov(QString novyNazov){
        nazov = novyNazov;
    }

int SeqEvent::UdlTrieda1ID(){
        return t1;
    }

int SeqEvent::UdlTrieda2ID(){
        return t2;
    }

QString SeqEvent::UdlTypStr(){
        return QString::number(typ);
    }

TypUdalosti SeqEvent::UdlTyp(){
        return typ;
    }
