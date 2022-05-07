
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

QString DiagramClass::getName(){
    return QString::fromStdString(name);
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
        
        this->name = UnescapeString(QString::fromStdString(lineVector.at(1))).toStdString();
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
            string name = UnescapeString(QString::fromStdString(lineVector.at(2))).toStdString();
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
            string name = UnescapeString(QString::fromStdString(lineVector.at(3))).toStdString();
            string return_type = UnescapeString(QString::fromStdString(lineVector.at(4))).toStdString();

            vector<string> param_vec(lineVector.begin() + 5,lineVector.end());
            //param_vec = UnescapeString(QString::fromStdString(param_vec)).toStdString();

            Class *cls = this->getClass(class_id);
            
            cls->appendMethod(id, visibility, name, return_type, param_vec);

        } else if (lineVector.at(0) == "attribute"){
            int id = stoi(lineVector.at(1));
            Visibility visibility = static_cast<Visibility>( stoi(lineVector.at(2)));
            cout << lineVector.at(2) << "tu" << endl;
            string name = UnescapeString(QString::fromStdString(lineVector.at(3))).toStdString();
            string return_type = UnescapeString(QString::fromStdString(lineVector.at(4))).toStdString();

            Class *cls = this->getClass(class_id);

            cls->appendAttribute(id, visibility, name, return_type);

        } else if (lineVector.at(0) == "relation"){
            int id = stoi(lineVector.at(1));
            int id_first = stoi(lineVector.at(2));
            int id_second = stoi(lineVector.at(3));
            string card_first = UnescapeString(QString::fromStdString(lineVector.at(4))).toStdString();
            string card_second = UnescapeString(QString::fromStdString(lineVector.at(5))).toStdString();
            RelationType rel_type = static_cast<RelationType>( stoi(lineVector.at(2)));
            string name = UnescapeString(QString::fromStdString(lineVector.at(6))).toStdString();

            this->appendRelation(id, id_first,id_second,card_first,card_second, rel_type,name);

        }
    }
    buffer.close();
}

QString DiagramClass::EscapeString(QString src){
    if(src.isEmpty()){
        return "#EMPTY#";
    }
    QString dst = src.replace(" ", "#SPACE#");
    return dst;
}

QString DiagramClass::UnescapeString(QString src){
    if(src.compare(("#EMPTY#")) == 0){
        return "";
    }
    QString dst = src.replace("#SPACE#", " ");
    return dst;
}

void DiagramClass::saveDiagram(string filename){
    ofstream buffer(filename);

    buffer << "title " << EscapeString(QString::fromStdString(this->name)).toStdString() << endl;
    buffer << "nextclassid " << this->next_class_id << endl;
    buffer << "nextrelationid " << this->next_relation_id << endl << endl;

    for (auto cls: classList) {
        buffer << "class " << cls->getID() << " " << EscapeString(QString::fromStdString(cls->getName())).toStdString() << " " << cls->getInterface() << " ";
        buffer << cls->x << " " << cls->y << " " << cls->width << " " << cls->height << " " <<  endl;
        
        for(auto atr : cls->getAttribVector()){
            buffer << "attribute " << atr->getID() << " " << static_cast<int>(atr->getVisibility()) << " " << EscapeString(QString::fromStdString(atr->getName())).toStdString();
            buffer << " " << EscapeString(QString::fromStdString(atr->getType())).toStdString() << endl;
        }

        for(auto met : cls->getMethodVector()){
            string params = vtos(met->vectorParam);
            buffer << "method " << met->getID() << " " << static_cast<int>(met->getVisibility()) << " ";
            buffer << EscapeString(QString::fromStdString(met->getName())).toStdString() << " " << EscapeString(QString::fromStdString(met->getReturnType())).toStdString() << " " << params << endl;
        }

        buffer << endl;
    }

    for (auto rel: relationList){
        buffer << "relation " << rel->getID() << " " << rel->getFirstID() << " " << rel->getSecondID() << " ";
        buffer << EscapeString(QString::fromStdString(rel->getCardFirst())).toStdString() << " " << EscapeString(QString::fromStdString(rel->getCardSecond())).toStdString() << " " << (int)rel->getRelType() << " ";
        buffer << EscapeString(QString::fromStdString(rel->getName())).toStdString() << endl;
    }

}

void DiagramClass::print(){

    for (auto i: classList){
        cout << i->getName() << " ";
    }

}


