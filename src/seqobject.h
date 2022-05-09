#ifndef SEQOBJECT_H
#define SEQOBJECT_H
#include <QString>

/**
 * @brief SeqObject class used to create object.
 */
class SeqObject
{
public:
    /**
     * @brief Constructor
     * @param name Name of the object.
     * @param id ID of the object.
     * @param classID ID of the class.
     */
    SeqObject(QString name, int id, int classID);

    /**
     * @brief Sets position of object.
     * @param px New X coordination.
     */
    void SetPosition(int px);

    /**
     * @brief Moves object.
     * @param offX X coordination offset.
     */
    void ChangePosition(int offX);

    /**
     * @brief Sets position of object when creating one.
     * @param px X coordination.
     * @param py Y coordination.
     */
    void SetPositionCreate(int px, int py);

    /**
     * @brief Sets size of the object.
     * @param width Width.
     * @param height Height.
     */
    void SetSize(int width, int height);

    /**
     * @brief Returns X coordination of the object.
     * @return X coordination.
     */
    int surSX();

    /**
     * @brief Returns Y coordination of the object.
     * @return Y coordination.
     */
    int surSY();

    /**
     * @brief Returns width of the object.
     * @return Width.
     */
    int surVX();

    /**
     * @brief Returns height of the object.
     * @return Height.
     */
    int surVY();

    /**
     * @brief Returns string of the coordinates of the object.
     * @return String of coordinates.
     */
    QString Coordinates();

    /**
     * @brief Returns name of the object.
     * @return String representation of name of the objet.
     */
    QString GetObjName();

    /**
     * @brief Returns ID of the class.
     * @return ID of the class.
     */
    int GetClassID();

    /**
     * @brief Changes name of the object.
     * @param New name of the object.
     */
    void ChangeObjName(QString newName);

    /**
     * @brief Changes type of the object.
     * @param New ID of the class.
     */
    void ChangeObjType(int classID);

    /**
     * @brief Returns ID of the object.
     * @return ID of the object.
     */
    int GetID();

    /**
     * @brief Changes size of the object.
     * @param offX Width offset.
     * @param offY Height offset.
     */
    void ChangeSize(int offX, int offY);

private:
    /**
     * @brief ID of the object.
     */
    int id;

    /**
     * @brief Name of the objact.
     */
    QString name;

    /**
     * @brief ID of the class.
     */
    int classID;

    /**
     * @brief X coordination.
     */
    int sx;

    /**
     * @brief Y coordination.
     */
    int sy;

    /**
     * @brief Width
     */
    int vx;

    /**
     * @brief Height
     */
    int vy;
};

#endif // SEQOBJECT_H
