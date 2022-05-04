
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

void DiagramClass::appendClass(string name, int id, int interface){

    Class *cls = new Class(name, id, 0);

    classList.push_back(cls);

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

void DiagramClass::changeClass(string name, int id){

    for (auto *cls : classList){
        if (cls->getID() == id){
            cls->changeName(name);       
            return;
        }   
    }
}

Class *DiagramClass::getClass(int id){
    Class *cls = nullptr;

    for (auto *cls : classList){
        if (cls->getID() == id){
            return cls;
        }   
    }
}


void DiagramClass::appendRelation( int id, int id_first, int id_second, string card_first, string card_second, RelationType rel_type, string name){

    Relation *rel = new Relation( id, id_first,id_second,card_first,card_second, rel_type,name);

    relationList.push_back(rel);
}

void DiagramClass::destroyRelation(int id){
    int i = 0;

    for (auto *rel : relationList){
        if (rel->getID() == id){
            delete rel;
            classList.erase(classList.begin()+i);       
            return;
        }
        i++;
    }
}

Relation *DiagramClass::getRelation(int id){
    Relation *rel = nullptr;

    for (auto *rel : relationList){
        if (rel->getID() == id){
            return rel;
        }   
    }
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

void vtos(string *str, vector<string> vector) {
    for( auto s : vector){
        str->append(s);
        str->append(" ");
    }
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
            
            // coordinates

        } else if (lineVector.at(0) == "method"){
            int id = stoi(lineVector.at(1));
            Visibility visibility = static_cast<Visibility>( stoi(lineVector.at(2)));
            string name = lineVector.at(3);
            string return_type = lineVector.at(4);
            string params;

            vector<string> param_vec(lineVector.begin() + 5,lineVector.end());
            vtos(&params, param_vec);

            Class *cls = this->getClass(class_id); 
            
            cls->appendMethod(id, visibility, name, return_type, params);

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
            buffer << "method " << met->getID() << " " << static_cast<int>(met->getVisibility()) << " ";
            buffer << met->getName() << " " << met->getReturnType() << " " << met->getParameters() << endl;
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
/**
int main(){
    
    DiagramClass dg;

    dg.loadDiagram("d5.txt");
    dg.print();
    dg.saveDiagram("d5_text.txt");
}
*/