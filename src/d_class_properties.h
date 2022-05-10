/**
 * @file d_class_properties.h
 * @author Martin Kozák
 * @brief represents diagram class properties: classes, methods and attributes
 * @date 2022-05-10
 * 
 */

#ifndef D_CLASS_PROPERTIES_H
#define D_CLASS_PROPERTIES_H

#include <iostream>
#include <vector>  
#include <QString>
using namespace std;

/**
 * @brief Visibility enum
 */
enum Visibility{
    T_private,
    T_public,
    T_protected,
    T_package
};

/**
 * @brief Relation type enum
 */
enum RelationType{
    T_association,
    T_aggregation,
    T_composition,
    T_generalization
};

/**
 * @brief The Attribute class represents attributes of class
 */
class Attribute{
private:
    /**
     * @brief id attribute id
     */
    int id;

    /**
     * @brief visibility visibility of attribute
     */
    Visibility visibility;

    /**
     * @brief name name of attribute
     */
    string name;

    /**
     * @brief type type of attribute
     */
    string type;

public:
    /**
     * @brief Constructor
     * @param id
     * @param visibility
     * @param name
     * @param type
     */
    Attribute(int id, Visibility visibility, string name, string type);

    /**
     * @brief Returns id of Attribute
     */
    int getID();

    /**
     * @brief  Returns visibility of attribute
     */
    Visibility getVisibility();

    /**
     * @brief Returns visibility converted to string
     */
    string getVisibilityStr();

    /**
     * @brief Changes visibility
     * @param visibility
     */
    void changeVisibility(Visibility visibility);

    /**
     * @brief Returns name of relation
     * @return
     */
    string getName();

    /**
     * @brief Changes name of relation
     * @param name
     */
    void changeName(string name);

    /**
     * @brief Returns attribute type
     */
    string getType();

    /**
     * @brief Changes attribute type
     */
    void changeType(string type);

};

/**
 * @brief The Method class represents method of class
 */
class Method{
private:
    /**
     * @brief visibility of method
     */
    Visibility visibility;
    /**
     * @brief name of method
     */
    string name;
    /**
     * @brief return_type of method
     */
    string return_type;
    /**
     * @brief string of parameters
     */
    string parameters;

    /**
     * @brief id of method
     */
    int id;

public:
    /**
     * @brief vectorParam vector of parameters
     */
    vector<string> vectorParam;

    /**
     * @brief Constructor
     * @param id
     * @param visibility
     * @param name
     * @param return_type
     * @param vectorParam
     */
    Method(int id, Visibility visibility, string name, string return_type,  vector<string> vectorParam);

    /**
     * @brief Returns id of Method
     */
    int getID();

    /**
     * @brief Returns name of Mehtod
     */
    string getName();

    /**
     * @brief Changes name
     */
    void changeName(string name);

    /**
     * @brief Returns visibility of Method
     */
    Visibility getVisibility();

    /**
     * @brief Changes visibility
     * @param visibility
     */
    void changeVisibility(Visibility visibility);

    /**
     * @brief Returns visibility converted to string
     */
    string getVisibilityStr();

    /**
     * @brief Returns type
     * @return
     */
    string getReturnType();

    /**
     * @brief Changes return type
     * @param return_type
     */
    void changeReturnType(string return_type);

    /**
     * @brief Adds parameter to vector of parameters
     * @param new_par
     */
    void addParam(string new_par);

    /**
     * @brief Remove parameter from vector of parameters
     */
    void removeParam(string par);
};

/**
 * @brief The Relation class is
 */
class Relation{
private:
    /**
     * @brief Relation type
     */
    RelationType rel_type;

    /**
     * @brief id id od relation
     */
    int id;

    /**
     * @brief id_first if od first class
     */
    int id_first;

    /**
     * @brief id_second id of second class
     */
    int id_second;

    /**
     * @brief card_first cardinality of first class
     */
    string card_first;

    /**
     * @brief card_second cardinality of second class
     */
    string card_second;

    /**
     * @brief name name of Relation
     */
    string name;


public:

    /**
     * @brief Constructor of relation
     * @param id
     * @param id_first
     * @param id_second
     * @param card_first
     * @param card_second
     * @param rel_type
     * @param name
     */
    Relation( int id, int id_first, int id_second, string card_first, string card_second,RelationType rel_type, string name);

    /**
     * @brief Returns id of Relation´
     * @return
     */
    int getID();

    /**
     * @brief Returns name of Relation
     * @return
     */
    string getName();

    /**
     * @brief Changes name of class
     * @param name
     */
    void changeName(string name);

    /**
     * @brief Returns first class id
     */
    int getFirstID();

    /**
     * @brief  Returns second class id
     */
    int getSecondID();

    /**
     * @brief Returns first cardinality
     */
    string getCardFirst();

    /**
     * @brief Returns second cardinality
     */
    string getCardSecond();

    /**
     * @brief Changes cardinality of first class
     * @param card
     */
    void changeCardFirst(string card);

    /**
     * @brief Changes cardinality of second class
     * @param card
     */
    void changeCardSecond(string card);

    /**
     * @brief Returns relation type
     */
    RelationType getRelType();

    /**
     * @brief Returns converted relation type to string
     */
    string getRelTypeStr();

    /**
     * @brief Changes relation type
     * @param rel_type
     */
    void changeRelType(RelationType rel_type);


};


/**
 * @brief The Class class represents classes of class diagram
 */
class Class{
private:
    /**
     * @brief name name of class
     */
    string name;

    /**
     * @brief id id of class
     */
    int id;

    /**
     * @brief interface interface number
     */
    int interface;

    /**
     * @brief min_height of class block
     */
    int min_height = 60;

    /**
     * @brief min_width of class block
     */
    int min_width = 60;

    /**
     * @brief next_method_id next method id
     */
    int next_method_id = 0;
    /**
     * @brief next_attribute_id next attribute id
     */
    int next_attribute_id = 0;

public:
    /**
     * @brief x position of block
     */
    int x;
    /**
     * @brief y position of block
     */
    int y;

    /**
     * @brief width of block
     */
    int width;

    /**
     * @brief height of block
     */
    int height;

    /**
     * @brief attribVector vector of attributes
     */
    vector<Attribute*> attribVector;

    /**
     * @brief methodVector vector of methods
     */
    vector<Method*> methodVector;

    /**
     * @brief Constructor
     * @param name
     * @param id
     * @param interface
     */
    explicit Class(string name, int id, int interface);
    ~Class();

    /**
     * @brief Returns name of class
     */
    string getName();

    /**
     * @brief Changes name of class
     * @param name new name
     */
    void changeName(string name);

    /**
     * @brief Returns id of clas
     */
    int getID();

    /**
     * @brief Returns interface number
     */
    int getInterface();

    /**
     * @brief Changes interface of class
     * @param interface
     */
    void changeInterface(int interface);

    /**
     * @brief Converts string to Visibility
     * @param str
     * @return
     */
    static Visibility strToVisbility(string str);
    static RelationType strToRelation(string str);

    /**
     * @brief Returns atrribute vector
     * @return
     */
    vector<Attribute*> getAttribVector();

    /**
     * @brief Returns method vector
     * @return
     */
    vector<Method*> getMethodVector();

    /**
     * @brief Returns and increase next method id
     * @return
     */
    int getNextMethodID();

    /**
     * @brief getNextAttribID
     * @return
     */
    int getNextAttribID();

    /**
     * @brief setNextMethodID
     * @param id
     */
    void setNextMethodID(int id);

    /**
     * @brief Sets next attribute id
     * @param id
     */
    void setNextAttribID(int id);

    void appendMethod(int id, Visibility visibility, string name, string return_type, vector<string> vectorParam);
    /**
     * @brief Removes method by id
     * @param id
     */
    void removeMethod(int id);

    /**
     * @brief Changes method by id
     * @param id
     * @param visibility
     * @param name
     * @param return_type
     */
    void changeMethod(int id, Visibility visibility, string name, string return_type);

    /**
     * @brief Changes parameters
     * @param id id of Method
     * @param params new parameters
     */
    void changeParams(int id, vector<string> params);

    /**
     * @brief Return id of Method by name
     * @param name
     * @return returns id
     */
    int getIdByNameMethod(string name);

    /**
     * @brief Find Method by id
     * @param id
     * @return returns Method
     */
    Method *getMethod(int id);

    /**
     * @brief Append attribute to attribList
     * @param id
     * @param visibility
     * @param name
     * @param type
     */
    void appendAttribute(int id, Visibility visibility, string name, string type);

    /**
     * @brief Remove attribute by id
     * @param id
     */
    void removeAttribute(int id);

    /**
     * @brief Changes attributes of Attribute
     * @param id
     * @param visibility
     * @param name
     * @param type
     */
    void changeAttribute(int id, Visibility visibility, string name, string type);

    /**
     * @brief Returns id of attribute found by name
     * @param name
     * @return returns id of attribute
     */
    int getIdByNameAttribute(string name);

    /**
     * @brief Returns pointer to attribute
     * @param id
     * @return returns pointer
     */
    Attribute *getAttribute(int id);

    // positions
    /**
     * @brief Set min height
     * @param height
     */
    void setMinHeight(int height);

    /**
     * @brief Set min width
     * @param width
     */
    void setMinWidth(int width);

    /**
     * @brief Sets position of block
     * @param x
     * @param y
     */
    void setPosition(int x, int y);

    /**
     * @brief Change position
     * @param off_x offset of x
     * @param off_y offset of y
     */
    void changePosition(int off_x, int off_y);

    /**
     * @brief Sets size of window
     * @param width new width
     * @param height new height
     */
    void setSize(int width, int height);

    /**
     * @brief Change size of window
     * @param off_width width offset
     * @param off_height height offset
     */
    void changeSize(int off_width, int off_height);

};
#endif
