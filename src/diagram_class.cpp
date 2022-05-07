
#include "diagram_class.h"
#include <iostream>
using namespace std;

DiagramClass::DiagramClass(string name){

    this->name = name;
    next_class_id = 1;
    next_relation_id = 1;

}

DiagramClass::DiagramClass(){

}

void DiagramClass::setUUID(QString uuid){
    this->uuid = uuid;
}

int DiagramClass::getIdByNameClass(string name){
    for (auto *cls : classList){
        if (cls->getName() == name){
            return cls->getID();
        }
    }
    return -1;
}

int DiagramClass::getIdByNameRelation(string name){
    for (auto *rel : relationList){
        if (rel->getName() == name){
            return rel->getID();
        }
    }
    return -1;
}

Class *DiagramClass::appendClass(string name, int id, int interface){

    Class *cls = new Class(name, id, interface);

    classList.push_back(cls);
    return cls;
}

void DiagramClass::destroyClass(int id){
    int i = 0;

    for (auto *cls : classList){
        if (cls->getID() == id){
            delete cls;
            classList.erase(classList.begin()+i);       
            return;
        }
        i++;
    }
}

void DiagramClass::changeClass(string name, int id, int interface){

    for (auto *cls : classList){
        if (cls->getID() == id){
            cls->changeName(name);
            cls->changeInterface(interface);
            return;
        }   
    }
}

Class *DiagramClass::getClass(int id){
    for (auto *cls : classList){
        if (cls->getID() == id){
            return cls;
        }   
    }
    return nullptr;
}


bool DiagramClass::checkRelation(int id_first, int id_second){
    bool flag = true;

    if (id_first == id_second){
        return false;
    }

    for (auto *rel: relationList){
        int id_first_cls = rel->getFirstID();
        int id_second_cls = rel->getSecondID();
        if ((id_first_cls == id_first && id_second_cls == id_second) ||
            (id_second_cls == id_first && id_first_cls == id_second)){
                    flag = false;
            }
    }
    return flag;
}

void DiagramClass::appendRelation( int id, int id_first, int id_second, string card_first, string card_second, RelationType rel_type, string name){

    Relation *rel = new Relation( id, id_first,id_second,card_first,card_second, rel_type,name);
    cerr << rel->getID() << "sad" << endl;
    relationList.push_back(rel);
    cerr << "tu";
    for (auto *rel : relationList){
        cerr << rel->getID()<< "sad" << endl;
    }
    cerr << "bu";
}

void DiagramClass::destroyRelation(int id){
    int i = 0;
    for (auto *rel : relationList){
        if (rel->getID() == id){
            delete rel;
            relationList.erase(relationList.begin()+i);
            return;
        }
        i++;
    }
}

void DiagramClass::changeRelation(int id, string card_first, string card_second, RelationType rel_type, string name ){
    for (auto *rel : relationList){
        if (rel->getID() == id){
            rel->changeCardFirst(card_first);
            rel->changeCardSecond(card_second);
            rel->changeRelType(rel_type);
            rel->changeName(name);
        }
    }
}

Relation *DiagramClass::getRelation(int id){
    for (auto *rel : relationList){
        if (rel->getID() == id){
            return rel;
        }   
    }
    return nullptr;
}

void split_string(string str, vector<string> *vec){
    vec->clear();

    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(' ', end)) != string::npos)
    {
        end = str.find(' ', start);
        vec->push_back(str.substr(start, end - start));
    }

}

string DiagramClass::vtos(vector<string> vector) {
    string str = "";
    for( auto s : vector){
        str.append(s);
        str.append(" ");
    }
    return str;
}

void DiagramClass::loadDiagram(string filename){
    ifstream buffer(filename);
    string line;
    vector<string> lineVector;
    int class_id;
    
    getline (buffer, line);
    split_string(line, &lineVector);
    
    if (lineVector.at(0) == "title"){
        
        this->name = lineVector.at(1);
    } else {
        fprintf(stderr, "ERROR");
    }

    getline (buffer, line);
    split_string(line, &lineVector);
    
    if (lineVector.at(0) == "nextclassid"){
        this->next_class_id = stoi(lineVector.at(1));
    } else {
        fprintf(stderr, "ERROR");
    }

    getline (buffer, line);
    split_string(line, &lineVector);
    
    if (lineVector.at(0) == "nextrelationid"){
        this->next_relation_id = stoi(lineVector.at(1));
    } else {
        fprintf(stderr, "ERROR");
    }


    while (getline (buffer, line)) {
        split_string(line, &lineVector);
        
        if (lineVector.size() == 0){
            continue;
        } else if (lineVector.at(0) == "class"){
            class_id = stoi(lineVector.at(1));
            string name = lineVector.at(2);
            int interface = stoi(lineVector.at(3));
            int x = stoi(lineVector.at(4));
            int y = stoi(lineVector.at(5));
            int width = stoi(lineVector.at(6));
            int height = stoi(lineVector.at(7));
    
            this->appendClass(name, class_id, interface);
            Class *cls = this->getClass(class_id);
            cls->setPosition(x, y);
            cls->setSize(width, height);

        } else if (lineVector.at(0) == "method"){
            int id = stoi(lineVector.at(1));
            Visibility visibility = static_cast<Visibility>( stoi(lineVector.at(2)));
            string name = lineVector.at(3);
            string return_type = lineVector.at(4);

            vector<string> param_vec(lineVector.begin() + 5,lineVector.end());

            Class *cls = this->getClass(class_id); 
            
            cls->appendMethod(id, visibility, name, return_type, param_vec);

        } else if (lineVector.at(0) == "attribute"){
            int id = stoi(lineVector.at(1));
            Visibility visibility = static_cast<Visibility>( stoi(lineVector.at(2)));
            cout << lineVector.at(2) << "tu" << endl;
            string name = lineVector.at(3);
            string return_type = lineVector.at(4);

            Class *cls = this->getClass(class_id); 

            cls->appendAttribute(id, visibility, name, return_type);

        } else if (lineVector.at(0) == "relation"){
            int id = stoi(lineVector.at(1));
            int id_first = stoi(lineVector.at(2));
            int id_second = stoi(lineVector.at(3));
            string card_first = lineVector.at(4);
            string card_second = lineVector.at(5);
            RelationType rel_type = static_cast<RelationType>( stoi(lineVector.at(2)));
            string name = lineVector.at(6);

            this->appendRelation(id, id_first,id_second,card_first,card_second, rel_type,name);

        }
    }
    buffer.close();
}


void DiagramClass::saveDiagram(string filename){
    ofstream buffer(filename);

    buffer << "title " << this->name << endl;
    buffer << "nextclassid " << this->next_class_id << endl;
    buffer << "nextrelationid " << this->next_relation_id << endl << endl;

    for (auto cls: classList) {
        buffer << "class " << cls->getID() << " " << cls->getName() << " " << cls->getInterface() << " ";
        buffer << endl;
        
        for(auto atr : cls->getAttribVector()){
            buffer << "attribute " << atr->getID() << " " << static_cast<int>(atr->getVisibility()) << " " << atr->getName(); 
            buffer << " " << atr->getType() << endl;
        }
                
        for(auto met : cls->getMethodVector()){
            string params = vtos(met->vectorParam);
            buffer << "method " << met->getID() << " " << static_cast<int>(met->getVisibility()) << " ";
            buffer << met->getName() << " " << met->getReturnType() << " " << params << endl;
        }

        buffer << endl;
    }

    for (auto rel: relationList){
        buffer << "relation " << rel->getID() << " " << rel->getFirstID() << " " + rel->getSecondID() << " ";
        buffer << rel->getCardFirst() << " " << rel->getCardSecond() << " " << rel->getRelType() << " ";
        buffer << rel->getName() << endl;
    }

}

void DiagramClass::print(){

    for (auto i: classList){
        cout << i->getName() << " ";
    }

}


