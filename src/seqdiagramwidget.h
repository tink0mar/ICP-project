#ifndef SEQDIAGRAMWIDGET_H
#define SEQDIAGRAMWIDGET_H

#include <QWidget>
#include <QPainter>
#include "QMouseEvent"

#include "seqdiagram.h"
#include "seqevent.h"
#include "seqobject.h"

class SeqDiagramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SeqDiagramWidget(QWidget *parent = nullptr);

    void DrawObject(QPainter *painter, SeqObject o);
    int VoVnutri(int kX, int kY);
    int VRohu(int kX, int kY);
    void NajdiZakladnu();
    void DrawEvent(QPainter *painter, SeqEvent evt);
    void PopupMenu1(int x, int y);
public slots:
    void AddObject();
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    SeqDiagram* sDiagram;
    DiagramTried* dTried;
    bool dragging;
    int mousex;
    int mousey;
    int idRohuObjektu;
    int idVnutraObjektu;
    int zakladnaY;
    int clickx;
};

#endif // SEQDIAGRAMWIDGET_H
