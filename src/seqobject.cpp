#include "seqobject.h"

SeqObject::SeqObject(QString name, int id, int classID)
{
    this->id = id;
    this->name = name;
    this->classID = classID;
    this->sx = 100;
    this->sy = 100;
    this->vx = 100;
    this->vy = 50;
}

void SeqObject::SetPosition(int px){
    sx = px;
}

void SeqObject::ChangePosition(int offX){
    sx = sx + offX;
}

void SeqObject::SetPositionCreate(int px, int py){
    sx = px;
    sy = py;
}

void SeqObject::SetSize(int width, int height){
    vx = width;
    vy = height;
}

void SeqObject::ChangeSize(int offX, int offY){
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

QString SeqObject::Coordinates(){
    return QString::number(sx) + " " + QString::number(sy) + " " + QString::number(vx) + " " + QString::number(vy);
}

QString SeqObject::GetObjName(){
    return name;
}

int SeqObject::GetClassID(){
    return classID;
}

void SeqObject::ChangeObjName(QString newName){
    name = newName;
}

void SeqObject::ChangeObjType(int classID){
    this->classID = classID;
}

int SeqObject::GetID(){
    return id;
}
