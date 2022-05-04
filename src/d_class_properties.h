
#include <iostream>
#include <vector>  
using namespace std;


enum Visibility{
    T_private,
    T_public,
    T_protected,
    T_package
};

enum RelationType{
    T_association,
    T_aggregation,
    T_composition,
    T_generalization
};

class Attribute{
    private:
        int id;
        Visibility visibility;
        string name;
        string type;

    public:
        Attribute(int id, Visibility visibility, string name, string type);

        int getID();

        Visibility getVisibility();
        string getVisibilityStr();
        void changeVisibility(Visibility visibility);

        string getName();
        void changeName(string name);

        string getType();
        void changeType(string type);

};

class Method{
    private:
        Visibility visibility;
        string name;
        string return_type;
        string parameters;
        int id;

    public:
        Method(int id, Visibility visibility, string name, string return_type, string parameters);

        int getID();

        string getName();
        void changeName(string name);
        
        Visibility getVisibility();
        void changeVisibility(Visibility visibility);
        string getVisibilityStr();

        string getReturnType();
        void changeReturnType(string return_type);

        string getParameters();
        void changeParameters(string parameters);
};


class Relation{
    private:
        RelationType rel_type;
        int id;
        int id_first;
        int id_second;
        string card_first;
        string card_second;
        string name;


    public:  

        Relation( int id, int id_first, int id_second, string card_first, string card_second,RelationType rel_type, string name);

        int getID();
        string getName();
        void changeName(string name);

        int getFirstID();
        int getSecondID();

        string getCardFirst();
        string getCardSecond();
        void changeCardFirst(string card);
        void changeCardSecond(string card);


        RelationType getRelType();
        string getRelTypeStr();
        void changeRelType(RelationType rel_type);


};

class Class{
    private:
        string name;
        int id;
        int interface;
        vector<Attribute*> attribVector;
        vector<Method*> methodVector;

    public:
        
        explicit Class(string name, int id, int interface);
        ~Class();

        string getName();
        void changeName(string name);
        
        int getID();
        int getInterface();
        
        vector<Attribute*> getAttribVector();
        vector<Method*> getMethodVector();

        void appendMethod(int id, Visibility visibility, string name, string return_type, string parameters);
        
        void appendAttribute(int id, Visibility visibility, string name, string return_type);

};