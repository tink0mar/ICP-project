
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#include "d_class_properties.h"

class DiagramClass{
    private:
        int next_class_id;
        int next_relation_id;
        string name;

    public:
        vector<Class*> classList;
        vector<Relation*> relationList;

        DiagramClass(string name);
        DiagramClass();

        // classes
        void appendClass(string name, int id, int interface);
        void destroyClass(int id);
        void changeClass(string name, int id);
        Class *getClass(int id);

        //relations
        void appendRelation( int id, int id_first, int id_second, string card_first, string card_second, RelationType rel_type, string name);
        void destroyRelation(int id);
        Relation *getRelation(int id);

        // operations with files
        void loadDiagram(string filename);
        void saveDiagram(string filename);

        
        void print();
};


