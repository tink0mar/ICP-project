#ifndef D_CLASS_PROPERTIES_H
#define D_CLASS_PROPERTIES_H

#include <iostream>
#include <vector>  
#include <QString>
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
        vector<string> vectorParam;

        Method(int id, Visibility visibility, string name, string return_type,  vector<string> vectorParam);

        int getID();

        string getName();
        void changeName(string name);

        Visibility getVisibility();
        void changeVisibility(Visibility visibility);
        string getVisibilityStr();

        string getReturnType();
        void changeReturnType(string return_type);

        void addParam(string new_par);
        void removeParam(string par);
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
        int min_height = 60;
        int min_width = 60;

    public:
        int x;
        int y;
        int width;
        int height;

        vector<Attribute*> attribVector;
        vector<Method*> methodVector;

        explicit Class(string name, int id, int interface);
        ~Class();

        string getName();
        void changeName(string name);


        int getID();
        int getInterface();
        void changeInterface(int interface);

        static Visibility strToVisbility(string str);
        static RelationType strToRelation(string str);

        vector<Attribute*> getAttribVector();
        vector<Method*> getMethodVector();

        void appendMethod(int id, Visibility visibility, string name, string return_type, vector<string> vectorParam);
        void removeMethod(int id);
        void changeMethod(int id, Visibility visibility, string name, string return_type);
        void changeParams(int id, vector<string> params);
        int getIdByNameMethod(string name);
        Method *getMethod(int id);

        void appendAttribute(int id, Visibility visibility, string name, string type);
        void removeAttribute(int id);
        void changeAttribute(int id, Visibility visibility, string name, string type);
        int getIdByNameAttribute(string name);
        Attribute *getAttribute(int id);

        // positions
        void setMinHeight(int height);
        void setMinWidth(int width);
        void setPosition(int x, int y);
        void changePosition(int off_x, int off_y);
        void setSize(int width, int height);
        void changeSize(int off_width, int off_height);

};
#endif
