#ifndef CLSDGRWIDGET_H
#define CLSDGRWIDGET_H

#include <QWidget>
#include <QPainter>
#include "QMouseEvent"
#include "diagram_class.h"

class ClsDiagramWidget : public QWidget
{
public:
    ClsDiagramWidget();

    void CreateNewClsDiagram(QString diagramName);
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int sx;
    int sy;
    int vx;
    int vy;
    bool dragging;
    bool vrohu;
    bool vnutri;
    int mousex;
    int mousey;
    DiagramClass* clsDiagram;
};


#endif // CLSDGRWIDGET_H
