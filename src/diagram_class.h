/**
 * @file diagram_class.h
 * @author Martin Kozák
 * @brief file represents class diagram
 * @date 2022-05-10
 *
 */

#ifndef DIAGRAM_CLASS
#define DIAGRAM_CLASS
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <QString>

using namespace std;

#include "d_class_properties.h"

/**
 * @brief The DiagramClass class represents class diagrams
 */
class DiagramClass{

private:
    /**
     * @brief Next relation id
     */
    int next_relation_id;

    /**
     * @brief Next class id
     */
    int next_class_id;

    /**
     * @brief Name of diagram class
     */
    string name;

public:

    vector<Class*> classList;
    vector<Relation*> relationList;

    /**
     * @brief Constructor of diagram class
     * @param name name of diamgram class
     */
    DiagramClass(string name);

    /**
     * @brief Second constructor of diagram class
     */
    DiagramClass();

    /**
     * @brief setNextRelationID sets next_relation_id
     * @param id relation id
     */
    void setNextRelationID(int id);

    /**
     * @brief setNextClassID sets next_class_id
     * @param id relation id
     */
    void setNextClassID(int id);

    /**
     * @brief getNextRelationID increase next_relation_id and returns it
     * @return next_relation_id
     */
    int getNextRelationID();

    /**
     * @brief getNextClassID
     * @return next_class_id increase next_class_id and returns it
     */
    int getNextClassID();

    // classes
    /**
     * @brief Find class by name
     * @param name name of class
     * @return id of class
     */
    int getIdByNameClass(string name);

    /**
     * @brief Appends class to classList
     * @param name class name
     * @param id id of class
     * @param interface interface number
     * @return
     */
    Class *appendClass(string name, int id, int interface);

    /**
     * @brief Destroys class by id
     * @param id id of class to be destroyed
     */
    void destroyClass(int id);

    /**
     * @brief Change attributes of class
     * @param name
     * @param id
     * @param interface
     */
    void changeClass(string name, int id, int interface);

    /**
     * @brief Find class by id
     * @param id if of class
     * @return pointer to class
     */
    Class *getClass(int id);

    //relations
    /**
     * @brief Checks ids of classes of relations
     * @param id_first id of first class
     * @param id_second if of second clas
     * @return
     */
    bool checkRelation(int id_first, int id_second);

    /**
     * @brief Append relation
     * @param id id of relation
     * @param id_first id of first class
     * @param id_second if of second class
     * @param card_first first cardinality
     * @param card_second second cardinality
     * @param rel_type relation type
     * @param name name of relation
     */
    void appendRelation( int id, int id_first, int id_second, string card_first, string card_second, RelationType rel_type, string name);

    /**
     * @brief Destroy relation by ID
     * @param id id of relation
     */
    void destroyRelation(int id);

    /**
     * @brief Changes the attributes of relation
     * @param id id of relation to be changed
     * @param card_first first cardinality
     * @param card_second second cardinality
     * @param rel_type relation type of relation
     * @param name name of relation
     */
    void changeRelation(int id, string card_first, string card_second, RelationType rel_type, string name );

    /**
     * @brief Find relation by id
     * @param id
     * @return returns the pointer to relation
     */
    Relation *getRelation(int id);

    /**
     * @brief Find relation by name
     * @param name name of relation to be found
     * @return id of relation
     */
    int getIdByNameRelation(string name);

    // operations with files
    /**
     * @brief Loads diagram
     * @param filename
     */
    void loadDiagram(string filename);

    /**
     * @brief save diagram
     * @param filename
     */
    void saveDiagram(string filename);

    /**
     * @brief Sets UUID of class diagram
     * @param uuid
     */
    void setUUID(QString uuid);

    /**
     * @brief Converts vector to string
     * @param vector
     * @return string of vector
     */
    string vtos(vector<string> vector);

    /**
     * @brief Escapes string
     * @param src source string
     * @return return escaped string
     */
    QString EscapeString(QString src);

    /**
     * @brief Unescape string
     * @param src source string
     * @return return unescaoed string
     */
    QString UnescapeString(QString src);

    /**
     * @brief Returns name of class diagram
     * @return name
     */
    QString getName();
};

#endif
