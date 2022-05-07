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
    void FindBase();
    void DrawEvent(QPainter *painter, SeqEvent evt);
    void PopupMenu1(int x, int y);
    QString FormatString(QString src, QFontMetrics metrics, int maxX);
    int FindActivation(int objID, int from);
    int FindDeactivation(int objID, int from);
    void DrawActive(QPainter* painter, int sx, int objID);
    bool InObject(int kX, int kY, SeqObject o);
    void PopupMenu2(int x, int y);
    int EventUnderCursor(int kX, int kY);
    void PopupMenu3(int x, int y);
    void CreateNewSeqDiagram(QString name, DiagramClass *classD);
    SeqDiagram *GetDiagram();
    void LoadSeqDiagram(QString filename, DiagramClass *classD);
public slots:
    void AddObject();
    void AddEvent();
    void EditObject();
    void AddActivation();
    void AddDeactivation();
    void EditMessage();
    void DeleteEvent();
    void DeleteObject();
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    SeqDiagram* sDiagram;
    DiagramClass* classD;
    bool dragging;
    int mousex;
    int mousey;
    int idRohuObjektu;
    int idVnutraObjektu;
    int eventID;
    int baseY;
    int clickx;
    QStringList evtTypes;
};

#endif // SEQDIAGRAMWIDGET_H
