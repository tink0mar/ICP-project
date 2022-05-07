
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <QString>

using namespace std;

#include "d_class_properties.h"

class DiagramClass{
    private:
        int next_relation_id;
        int next_class_id;
        string name;
        QString uuid;

    public:
        vector<Class*> classList;
        vector<Relation*> relationList;

        DiagramClass(string name);
        DiagramClass();

        // classes
        int getIdByNameClass(string name);
        Class *appendClass(string name, int id, int interface);
        void destroyClass(int id);
        void changeClass(string name, int id, int interface);
        Class *getClass(int id);

        //relations
        bool checkRelation(int id_first, int id_second);
        void appendRelation( int id, int id_first, int id_second, string card_first, string card_second, RelationType rel_type, string name);
        void destroyRelation(int id);
        void changeRelation(int id, string card_first, string card_second, RelationType rel_type, string name );
        Relation *getRelation(int id);
        int getIdByNameRelation(string name);

        // operations with files
        void loadDiagram(string filename);
        void saveDiagram(string filename);

        void setUUID(QString uuid);
        string vtos(vector<string> vector);
        void print();
};


