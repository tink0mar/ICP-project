
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


Method::Method( int id, Visibility visibility, string name, string return_type, string parameters){
    this->visibility = visibility;
    this->name = name;
    this->id = id;
    this->return_type = return_type;
    this->parameters = parameters;
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


string Method::getParameters() {
    return parameters;
}


void Method::changeParameters(string parameters){
    this->parameters = parameters;
}


/** class Class */

Class::Class(string new_name, int id, int interface){
    this->name = new_name;
    this->id = id;
    this->interface = interface;

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


vector<Attribute*> Class::getAttribVector(){
    return attribVector;
}

vector<Method*> Class::getMethodVector(){
    return methodVector;
}

void Class::appendMethod(int id, Visibility visibility, string name, string return_type, string parameters){
    
    Method *met = new Method(id, visibility, name, return_type, parameters);

    methodVector.push_back(met);
}

void Class::appendAttribute(int id, Visibility visibility, string name, string return_type){

    Attribute *att = new Attribute(id, visibility, name, return_type);

    attribVector.push_back(att);
}

/** class Relation**/

Relation::Relation( int id, int id_first, int id_second, string card_first, string card_second, RelationType rel_type, string name){

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
}

void Relation::changeRelType(RelationType rel){
    this->rel_type = rel;
}