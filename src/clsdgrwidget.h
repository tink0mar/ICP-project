/**
 * @file clsdgrwidget.h
 * @author Martin Kozák
 * @brief file represents class diagram widget
 * @date 2022-05-10
 *
 */
#ifndef CLSDGRWIDGET_H
#define CLSDGRWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QtMath>

#include "diagram_class.h"
#include "basicdialog.h"
#include "addobjectdialog.h"
#include "addattributedialog.h"
#include "addrelationdialog.h"
#include "changerelationdialog.h"

class ClsDiagramWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     */
    explicit ClsDiagramWidget(QWidget *parent = nullptr);

    /**
     * @brief Creates new class diagram
     * @param diagramName
     */
    void CreateNewClsDiagram(QString diagramName);

    /**
     * @brief Finds where if the mouse is on class
     * @param mx x position of mouse
     * @param my y position of mouse
     * @return
     */
    int findInside(int mx, int my);

    /**
     * @brief Checks the corner
     * @param mx x position of mouse
     * @param my y position of mouse
     * @return
     */
    int findIncorner(int mx, int my);

    /**
     * @brief Resize the class box to length of text
     * @param cls class
     * @param text_len length  of text
     */
    void resizeClassWidth(Class *cls, int text_len);

    /**
     * @brief Counts the space for text
     * @param str string to be counted
     * @return length of string
     */
    int str_off(string str);

    /**
     * @brief Returns max width
     * @param cls pointer to class
     * @param name name of class
     * @return
     */
    int getMaxWidth(Class *cls, string name);

    /**
     * @brief Resize class height
     * @param cls pointer to class
     * @param height height of box
     */
    void resizeClassHeight(Class *cls, int height);

    /**
     * @brief Creates pop up menu widget if outside class
     * @param x x - mouse position
     * @param y y - mouse position
     */
    void PopUpMenuWidget(int x, int y);

    /**
     * @brief Creates pop up widget if inside class
     * @param id id of class
     * @param x position of mouse x
     * @param y positon of mouse y
     */
    void PopUpClassWidget(int id, int x, int y);

    /**
     * @brief Next class id
     */
    int getNextClassID();

    /**
     * @brief Next relation id
     */
    int getNextRelID();

    /**
     * @brief Increase and returns next relation id
     * @return
     */
    int incNextRelID();

    /**
     * @brief Increase and returns next class id
     * @return
     */
    int incNextClassID();

    /**
     * @brief getDiagramCls
     * @return returns class diagram
     */
    DiagramClass *getDiagramCls();

    /**
     * @brief Function loads diagram from file
     * @param filename name of diagram file
     */
    void LoadClsDiagram(QString filename);


private slots:
    /**
     * @brief Adds class
     */
    void AddClass();

    /**
     * @brief Removes class
     */
    void RemoveClass();

    /**
     * @brief Changes class
     */
    void ChangeClass();

    /**
     * @brief Adds attribute
     */
    void AddAttribute();

    /**
     * @brief Changes attribute
     */
    void ChangeAttribute();

    /**
     * @brief Removes attribute
     */
    void RemoveAttribute();

    /**
     * @brief Adds method
     */
    void AddMethod();

    /**
     * @brief Changes method
     */
    void ChangeMethod();

    /**
     * @brief Adds parameter
     */
    void addParameter();

    /**
     * @brief Removes parameter
     */
    void removeParameter();

    /**
     * @brief Removes method
     */
    void RemoveMethod();

    /**
     * @brief Adds relation
     */
    void AddRelation();

    /**
     * @brief Changes relation
     */
    void ChangeRelation();

    /**
     * @brief Removes relation
     */
    void RemoveRelation();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    /**
     * @brief object_id stores the last id of object
     */
    int object_id;

    /**
     * @brief next_class_id next class id
     */
    int next_class_id=0;

    /**
     * @brief next_relation_id next relation id
     */
    int next_relation_id=0;

    /**
     * @brief dragging flag for dragging object with mouse
     */
    bool dragging;

    /**
     * @brief incorner_id id of object when mouse is in corner
     */
    int incorner_id;

    /**
     * @brief inside_id id of object when mouse is inside the class
     */
    int inside_id;

    /**
     * @brief mousex x position of mouse
     */
    int mousex;

    /**
     * @brief mousey y position of mouse
     */
    int mousey;

    /**
     * @brief clsDiagram pointer to class object
     */
    DiagramClass* clsDiagram;
};


#endif // CLSDGRWIDGET_H
