#include "seqobject.h"

SeqObject::SeqObject(QString nazov, QString typ, int id, int idTriedy)
{
    this->id = id;
    this->nazov = nazov;
    this->typ = typ;
    this->idTriedy = idTriedy;
    this->sx = 100;
    this->sy = 100;
    this->vx = 100;
    this->vy = 50;
}

void SeqObject::NastavPoziciu(int px){
      sx = px;
  }

void SeqObject::UpravPoziciu(int offX){
      sx = sx + offX;
  }

void SeqObject::NastavPoziciuCreate(int px, int py){
      sx = px;
      sy = py;
  }

void SeqObject::NastavVelkost(int sirka, int vyska){
      vx = sirka;
      vy = vyska;
  }

void SeqObject::UpravVelkost(int offX, int offY){
      if(vx+offX > 50){
          vx = vx + offX;
      }
      if(vy+offY > 50){
          vy = vy + offY;
      }
  }

int SeqObject::surSX(){
      return sx;
  }

int SeqObject::surSY(){
      return sy;
  }

int SeqObject::surVX(){
      return vx;
  }
int SeqObject::surVY(){
      return vy;
  }

QString SeqObject::Suradnice(){
      return QString::number(sx) + " " + QString::number(sy) + " " + QString::number(vx) + " " + QString::number(vy);
  }

QString SeqObject::ObjNazov(){
      return nazov;
  }

int SeqObject::IDTriedy(){
      return idTriedy;
  }

void SeqObject::ZmenaObjNazvu(QString novyNazov){
      nazov = novyNazov;
  }

QString SeqObject::ObjTyp(){
      return typ;
  }

void SeqObject::ZmenaObjTypu(QString novyTyp){
      typ = novyTyp;
  }

int SeqObject::ID(){
      return id;
  }
