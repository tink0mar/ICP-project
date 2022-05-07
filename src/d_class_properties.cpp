
#include "d_class_properties.h"
#include <iostream>
using namespace std;

Attribute::Attribute(int id, Visibility visibility, string name, string type){
    this->id = id;
    this->visibility = visibility;
    this->name = name;
    this-> type = type;
}

int Attribute::getID(){
    return id;
}

Visibility Attribute::getVisibility(){
    return visibility;
}

string Attribute::getVisibilityStr(){

    switch(visibility){

        case T_protected:
            return "#";

        case T_public:
            return "+";

        case T_private:
            return "-";

        case T_package:
            return "~";
    }
    return "?";
}

void Attribute::changeVisibility(Visibility visibility){
    this->visibility = visibility;
}

string Attribute::getName(){
    return name;
}

void Attribute::changeName(string name){
    this->name = name;
}

string Attribute::getType(){
    return type;
}

void Attribute::changeType(string type){
    this->type = type;
}

/** class Method */


Method::Method( int id, Visibility visibility, string name, string return_type, vector<string> vectorParam){
    this->visibility = visibility;
    this->name = name;
    this->id = id;
    this->return_type = return_type;
    this->vectorParam = vectorParam;
}


int Method::getID(){
    return id;
}


string Method::getName(){
    return name;
}


void Method::changeName(string name){
    this->name = name;
}


Visibility Method::getVisibility(){
    return visibility;
}

string Method::getVisibilityStr(){

    switch(visibility){

        case T_protected:
            return "#";

        case T_public:
            return "+";

        case T_private:
            return "-";

        case T_package:
            return "~";
    }
    return string("");
}

void Method::changeVisibility(Visibility visibility){
    this->visibility = visibility;
}


string Method::getReturnType(){
    return return_type;
}


void Method::changeReturnType(string return_type){
    this->return_type = return_type;
}

void Method::addParam(string new_par){
   vectorParam.push_back(new_par);
}

void Method::removeParam(string par){
    int i = 0;
    for (auto p:vectorParam){
        if (p == par){
            vectorParam.erase(vectorParam.begin()+i);
        }
        i++;
    }
}


/** class Class */

Class::Class(string new_name, int id, int interface){
    this->name = new_name;
    this->id = id;
    this->interface = interface;
    this->x = 100;
    this->y = 100;
    this->width = 100;
    this->height = 100;

}

Class::~Class(){

    for (auto i: attribVector){
        delete i;
    }

    for (auto i: methodVector){
        delete i;
    }

}

string Class::getName(){
    return name;
}

void Class::changeName(string name){
    this->name = name;
}

int Class::getID(){
    return id;
}

int Class::getInterface(){
    return interface;
}   

void Class::changeInterface(int interface){
    this->interface = interface;
}

vector<Attribute*> Class::getAttribVector(){
    return attribVector;
}

vector<Method*> Class::getMethodVector(){
    return methodVector;
}

Visibility Class::strToVisbility(string str){

   if (str == "+"){
       return T_public;
   } else if (str == "-"){
       return T_private;
   } else if (str == "~"){
       return T_package;
   } else if (str == "#"){
       return T_protected;
   }
   return T_public;
}

RelationType Class::strToRelation(string str){

    if (str == "aggregation"){
        return T_aggregation;
    } else if (str == "asociation"){
        return T_association;
    } else if (str == "composition"){
        return T_composition;
    } else if (str == "generalization"){
        return T_generalization;
    }
    return T_association;
}

void Class::appendMethod(int id, Visibility visibility, string name, string return_type, vector<string> vectorParam){
    
    Method *met = new Method(id, visibility, name, return_type, vectorParam);

    methodVector.push_back(met);
}

void Class::changeMethod(int id, Visibility visibility, string name, string return_type){
    int i = 0;
    for (auto *met : methodVector){
        if (met->getID() == id){
            met->changeName(name);
            met->changeVisibility(visibility);
            met->changeReturnType(return_type);
            return;
        }
        i++;
    }
}

void Class::removeMethod(int id){
    int i = 0;
    for (auto *met : methodVector){
        if (met->getID() == id){
            delete met;
            methodVector.erase(methodVector.begin()+i);
        }
        i++;
    }
}

void Class::changeParams(int id, vector<string> params){
    for (auto *met : methodVector){
        if (met->getID() == id){
            met->vectorParam = params;
            return;
        }
    }
}

int Class::getIdByNameMethod(string name){

    for (auto *met : methodVector){
        if (met->getName() == name){
            return met->getID();
        }
    }
    return -1;
}

Method *Class::getMethod(int id){
    for (auto met : methodVector){
        if (met->getID() == id){
            return met;
        }
    }
    return nullptr;
}



void Class::appendAttribute(int id, Visibility visibility, string name, string type){

    Attribute *att = new Attribute(id, visibility, name, type);

    attribVector.push_back(att);
}

void Class::changeAttribute(int id, Visibility visibility, string name, string type){
    int i = 0;
    for (auto *att : attribVector){
        if (att->getID() == id){
            att->changeName(name);
            att->changeVisibility(visibility);
            att->changeType(type);
        }

        i++;
    }
}

void Class::removeAttribute(int id){
    int i = 0;
    for (auto *att : attribVector){
        if (att->getID() == id){
            delete att;
            fprintf(stderr, "tu\n");
            attribVector.erase(attribVector.begin()+i);
        }
        i++;
    }
}

int Class::getIdByNameAttribute(string name){
    for (auto *att : attribVector){
        if (att->getName() == name){
            return att->getID();
        }
    }
    return -1;
}

Attribute *Class::getAttribute(int id){
    for (auto att : attribVector){
        if (att->getID() == id){
            return att;
        }
    }
    return nullptr;
}

void Class::setMinWidth(int width){
    this->min_width = width;
}

void Class::setMinHeight(int height){
    this->min_height = height;
}

void Class::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

void Class::changePosition(int off_x, int off_y){
    this->x += off_x;
    this->y += off_y;
}

void Class::setSize(int width, int height){
    this->width = width;
    this->height = height;
}

void Class::changeSize(int off_width, int off_height){
    if(this->width + off_width > min_width){
        this->width += off_width;
    }
    if(this->height + off_height > min_height){
        this->height += off_height;
    }
}

/** class Relation**/

Relation::Relation( int id, int id_first, int id_second, string card_first, string card_second, RelationType rel_type, string name){
    this->name = name;
    this->id = id;
    this->id_first = id_first;
    this->id_second = id_second;
    this->card_first = card_first;
    this->card_second = card_second;

}

int Relation::getID(){
    return id;
}

string Relation::getName(){
    return name;
}

void Relation::changeName(string name){
    this->name = name;
}

int Relation::getFirstID(){
    return id_first;
}

int Relation::getSecondID(){
    return id_second;
}

string Relation::getCardFirst(){
    return card_first;
}

string Relation::getCardSecond(){
    return card_second;
}

void Relation::changeCardFirst(string card){
    this->card_first = card;
}

void Relation::changeCardSecond(string card){
    this->card_second = card;
}

RelationType Relation::getRelType(){
    return rel_type;
}

string Relation::getRelTypeStr(){
    switch(rel_type){

        case T_aggregation:
            return "aggregation";

        case T_association:
            return "asociation";

        case T_composition:
            return "composition";

        case T_generalization:
            return "generalization";
        
    }

    return string("");
}

void Relation::changeRelType(RelationType rel){
    this->rel_type = rel;
}
