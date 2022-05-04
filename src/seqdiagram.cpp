#include "seqdiagram.h"
#include "seqevent.h"
#include "seqobject.h"


SeqDiagram::SeqDiagram(QString nazov, DiagramTried *dTried)
{
    idUdalosti = 1;
    idObjektu = 1;
    poradUdalosti = 1;
    this->nazov = nazov;
    zoznamObjektov.clear();
    zoznamUdalosti.clear();
    this->dTried = dTried;
    uuid = "";
    zakladnaY = 0;
}

QString SeqDiagram::Nazov(){
       return nazov;
   }

void SeqDiagram::NastavUUID(QString uuid){
       this->uuid = uuid;
   }

void SeqDiagram::NastavZakladnu(int zakladnaY){
       this->zakladnaY = zakladnaY;
   }

QString SeqDiagram::UUID(){
       return uuid;
   }

QList<SeqObject> SeqDiagram::ZoznamObjektov(){
       return zoznamObjektov;
   }

QList<SeqEvent> SeqDiagram::ZoznamUdalosti(){
       return zoznamUdalosti;
   }

SeqObject* SeqDiagram::NajdiObjekt(int id){

    for( int i=0; i<zoznamObjektov.count(); ++i ){

           if(zoznamObjektov[i].ID() == id){
               return &zoznamObjektov[i];
           }
       }
       return NULL;
   }
SeqEvent* SeqDiagram::NajdiUdalost(int id){
       for( int i=0; i<zoznamUdalosti.count(); ++i ){
           if(zoznamUdalosti[i].ID() == id){
               return &zoznamUdalosti[i];
           }
       }
       return NULL;
   }

SeqEvent* SeqDiagram::NajdiUdalostOrder(int order){
       for( int i=0; i<zoznamUdalosti.count(); ++i ){
           if(zoznamUdalosti[i].Order() == order){
               return &zoznamUdalosti[i];
           }
       }
       return NULL;
   }

SeqObject* SeqDiagram::PridajObjekt(QString nazov, int id, int idTriedy){
        if(id == 0){
            id = idObjektu++;
        }
        if(dTried->NajdiTriedu(idTriedy) != nullptr){
            Trieda* t = dTried->NajdiTriedu(idTriedy);
            SeqObject* obj = new SeqObject(nazov, t->Nazov(), id, idTriedy);
            zoznamObjektov.append(*obj);
            return &zoznamObjektov[zoznamObjektov.count()-1];
        }
        return NULL;
    }

void SeqDiagram::UpravObjekt(QString novyNazov, QString novyTyp, int id){
        for( int i=0; i<zoznamObjektov.count(); ++i ){
            if(zoznamObjektov[i].ID() == id){
                zoznamObjektov[i].ZmenaObjNazvu(novyNazov);
                zoznamObjektov[i].ZmenaObjTypu(novyTyp);
            }
        }
    }

void SeqDiagram::ZrusenieObjektu(int id){
        for( int i=0; i<zoznamObjektov.count(); ++i ){
            if(zoznamObjektov[i].ID() == id){
                for(int j = zoznamUdalosti.size()-1; j >= 0; j--){
                    SeqEvent evt = zoznamUdalosti[j];
                    if(evt.UdlTrieda1ID() == zoznamObjektov[i].ID() || evt.UdlTrieda2ID() == zoznamObjektov[i].ID()){
                        zoznamUdalosti.remove(j);
                    }
                }
                zoznamObjektov.remove(i);
                return;
            }
        }
    }

void SeqDiagram::PridajUdalost(int o1, int o2, TypUdalosti typ, QString popis, int id, int order, int zakladnaY){
        if(id == 0){
            id = idUdalosti++;
        }
        if(order == 0){
            order = poradUdalosti++;
        }
        SeqEvent* evt = new SeqEvent(o1, o2, typ, popis, id, order);
        zoznamUdalosti.append(*evt);
        if(typ == TypUdalosti::TVORBA_OBJEKTU){
            SeqObject* o = NajdiObjekt(o2);
            o->NastavPoziciuCreate(o->surSX(), zakladnaY+order*50);
        }
    }

void SeqDiagram::UpravUdalost(QString novyPopis, int id){
        for( int i=0; i<zoznamUdalosti.count(); ++i ){
            if(zoznamUdalosti[i].ID() == id){
                zoznamUdalosti[i].ZmenaUldNazov(novyPopis);
            }
        }
    }

void SeqDiagram::PresunUdalostDole(int id){
        SeqEvent* evt1 = NajdiUdalost(id);
        if(evt1->Order()+1 == poradUdalosti){
            return;
        }
        SeqEvent* evt2 = NajdiUdalostOrder(evt1->Order()+1);
        evt2->NastavPoradie(evt1->Order());
        evt1->NastavPoradie(evt1->Order()+1);
        if(evt1->UdlTyp() == TypUdalosti::TVORBA_OBJEKTU){
            SeqObject* o = NajdiObjekt(evt1->UdlTrieda2ID());
            o->NastavPoziciuCreate(o->surSX(), evt1->Order()*50+zakladnaY);
        }
        if(evt2->UdlTyp() == TypUdalosti::TVORBA_OBJEKTU){
            SeqObject* o = NajdiObjekt(evt2->UdlTrieda2ID());
            o->NastavPoziciuCreate(o->surSX(), evt2->Order()*50+zakladnaY);
        }
    }

void SeqDiagram::PresunUdalostHore(int id){
        SeqEvent* evt1 = NajdiUdalost(id);
        if(evt1->Order() == 1){
            return;
        }
        SeqEvent* evt2 = NajdiUdalostOrder(evt1->Order()-1);
        evt2->NastavPoradie(evt1->Order());
        evt1->NastavPoradie(evt1->Order()-1);
        if(evt1->UdlTyp() == TypUdalosti::TVORBA_OBJEKTU){
            SeqObject* o = NajdiObjekt(evt1->UdlTrieda2ID());
            o->NastavPoziciuCreate(o->surSX(), evt1->Order()*50+zakladnaY);
        }
        if(evt2->UdlTyp() == TypUdalosti::TVORBA_OBJEKTU){
            SeqObject* o = NajdiObjekt(evt2->UdlTrieda2ID());
            o->NastavPoziciuCreate(o->surSX(), evt2->Order()*50+zakladnaY);
        }
    }



void SeqDiagram::ZrusenieUdalosti(int id){
        for( int i=0; i<zoznamUdalosti.count(); ++i ){
            if(zoznamUdalosti[i].ID() == id){
                zoznamUdalosti.remove(i);
                return;
            }
        }
    }

