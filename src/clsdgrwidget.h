#ifndef CLSDGRWIDGET_H
#define CLSDGRWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QtMath>

#include "diagram_class.h"
#include "addclassdialog.h"
#include "addobjectdialog.h"
#include "addattributedialog.h"
#include "addrelationdialog.h"
#include "changerelationdialog.h"

class ClsDiagramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClsDiagramWidget(QWidget *parent = nullptr);

    void CreateNewClsDiagram(QString diagramName);
    int findInside(int mx, int my);
    int findIncorner(int mx, int my);
    void resizeClassWidth(Class *cls, int text_len);
    int str_off(string str);
    int getMaxWidth(Class *cls, string name);
    void resizeClassHeight(Class *cls, int height);
    void PopUpMenuWidget(int x, int y);
    void PopUpClassWidget(int id, int x, int y);

    int getNextClassID();
    int getNextRelID();
    int getNextMethodID();
    int getNextAttributeID();

    QMessageBox alertDialog;

private slots:
    void AddClass();
    void RemoveClass();
    void ChangeClass();

    void AddAttribute();
    void ChangeAttribute();
    void RemoveAttribute();

    void AddMethod();
    void ChangeMethod();
    void addParameter();
    void removeParameter();
    void RemoveMethod();

    void AddRelation();
    void ChangeRelation();
    void RemoveRelation();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int object_id;

    int next_class_id=0;
    int next_relation_id=0;
    int next_method_id=0;
    int next_attribute_id=0;

    bool dragging;
    int incorner_id;
    int inside_id;
    int mousex;
    int mousey;
    DiagramClass* clsDiagram;
};


#endif // CLSDGRWIDGET_H
