#include "seqdiagramwidget.h"
#include "addobjectdialog.h"
#include "addeventdialog.h"
#include "editobjectdialog.h"
#include "qmessagebox.h"
#include "editmessagedialog.h"
#include <QFontMetrics>
#include <QMenu>
#include <QtMath>

SeqDiagramWidget::SeqDiagramWidget(QWidget *parent)
    : QWidget{parent}
{    
    dragging=false;
    setMouseTracking(true);
    sDiagram = NULL;
    QList<QString> list = {"SYNCHRONNA_SPRAVA", "ASYNCHRONNA_SPRAVA", "NAVRAT_SPRAVY", "TVORBA_OBJEKTU", "ZANIK_OBJEKTU"};
    evtTypes = list;
}

SeqDiagramWidget::~SeqDiagramWidget(){
    if(sDiagram != NULL){
        delete sDiagram;
    }
}

void SeqDiagramWidget::CreateNewSeqDiagram(QString name, DiagramClass* classD){
    this->classD = classD;
    sDiagram = new SeqDiagram(name, classD);
}

SeqDiagram* SeqDiagramWidget::GetDiagram(){
    return sDiagram;
}

void SeqDiagramWidget::LoadSeqDiagram(QString filename, DiagramClass* classD){
    this->classD = classD;
    sDiagram = new SeqDiagram("test", classD);
    sDiagram->LoadDiagram(filename);
    FindBase();
    repaint();
}

void SeqDiagramWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QList<SeqObject> objectList = sDiagram->GetObjectList();
    for(int i = 0; i<objectList.size(); i++){
        DrawObject(&painter, objectList[i]);
        DrawActive(&painter, objectList[i].surSX(), objectList[i].GetID());

    }
    QList<SeqEvent> zozUdalost = sDiagram->GetEventList();
    for(int i = 0; i<zozUdalost.size(); i++){
        DrawEvent(&painter, zozUdalost[i]);
    }
}

QString SeqDiagramWidget::FormatString(QString src, QFontMetrics metrics, int maxX){
    QString dst = src;
    QSize size = metrics.size(Qt::TextSingleLine, dst);
    while(size.width() > maxX){
        dst = dst.left(dst.length()-1);
        size = metrics.size(Qt::TextSingleLine, dst);
    }
    return dst;
}

int SeqDiagramWidget::FindActivation(int objID, int from){
    QList<SeqEvent> zozUdalost = sDiagram->GetEventList();
    for(int i = 0; i < zozUdalost.size(); i++){
        SeqEvent* u = sDiagram->FindEventOrder(i+1);
        if(u->GetEventClass1ID() == objID && u->GetEventUdlType() == EventType::ACTIVATION){
            if(u->GetOrder() > from){
                return u->GetOrder();
            }
        }
    }
    return 0;
}

int SeqDiagramWidget::FindDeactivation(int objID, int from){
    QList<SeqEvent> zozUdalost = sDiagram->GetEventList();
    for(int i = 0; i < zozUdalost.size(); i++){
        SeqEvent* u = sDiagram->FindEventOrder(i+1);
        if(u->GetEventClass1ID() == objID && u->GetEventUdlType() == EventType::DEACTIVATION){
            if(u->GetOrder() > from){
                return u->GetOrder();
            }
        }
    }
    return 0;
}

void SeqDiagramWidget::DrawActive(QPainter* painter, int sx, int objID){
    int por1 = FindActivation(objID, 0);
    while(por1 != 0){
        int por2 = FindDeactivation(objID, por1);
        if(por2 == 0){
            return;
        }
        QBrush defBrush = painter->brush();
        painter->setBrush(Qt::black);
        if(classD->getClass(sDiagram->FindObject(objID)->GetClassID()) == NULL){
            painter->setBrush(Qt::red);
        }
        painter->drawRect(sx - 5, baseY+por1*50, 10, (por2 - por1)*50);
        por1 = FindActivation(objID, por2);
        painter->setBrush(defBrush);
    }
}

void SeqDiagramWidget::DrawObject(QPainter* painter, SeqObject o){
    int px = o.surSX() - o.surVX()/2;
    int py = o.surSY() - o.surVY()/2;
    int maxY = py + o.surVY();
    QBrush defBrush = painter->brush();
    Class* c = classD->getClass(o.GetClassID());
    QString type = "unknown";
    if(c != NULL){
        type = QString::fromStdString(c->getName());
    }
    else{
        painter->setBrush(Qt::red);
    }
    painter->drawRect(o.surSX()-o.surVX()/2, o.surSY()-o.surVY()/2, o.surVX(), o.surVY());
    QFontMetrics fm = painter->fontMetrics();
    int hgt = fm.height();
    QPen pen;
    QPen oldPen = painter->pen();
    painter->drawText(px+5, py+hgt, FormatString(o.GetObjName(), fm, o.surVX()-10));
    if(py+2*hgt+5 < maxY){
        painter->drawText(px+5, py+2*hgt, FormatString("<<"+type+">>", fm, o.surVX()-10));
    }
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->drawLine(o.surSX(), o.surSY()+o.surVY()/2, o.surSX(), this->size().height()-50);
    painter->setPen(oldPen);
    painter->setBrush(defBrush);
}

void SeqDiagramWidget::DrawEvent(QPainter* painter, SeqEvent evt){
    SeqObject* o1 = sDiagram->FindObject(evt.GetEventClass1ID());
    SeqObject* o2 = sDiagram->FindObject(evt.GetEventClass2ID());
    int sx1 = o1->surSX();
    int sx2 = o2->surSX();
    int sy = baseY + 50*evt.GetOrder();
    QBrush defBrush = painter->brush();
    int nekonzistencia = 1;
    QPen pen;
    pen.setBrush(Qt::black);
    if(classD->getClass(o2->GetClassID()) != NULL && (evt.GetEventUdlType() == EventType::SYNCHRONOUS_MESSAGE || evt.GetEventUdlType() == EventType::ASYNCHRONOUS_MESSAGE)){
        vector<Method*> methodList = classD->getClass(o2->GetClassID())->methodVector;
        for(unsigned int i = 0; i < methodList.size(); i++){
            if(evt.GetEventName().startsWith(QString::fromStdString(methodList[i]->getName()))){
                nekonzistencia = 0;
            }
        }
    }
    if(evt.GetEventUdlType() == EventType::CREATE_OBJECT || evt.GetEventUdlType() == EventType::DESTROY_OBJECT || evt.GetEventUdlType() == EventType::RETURN_MESSAGE){
        nekonzistencia = 0;
    }
    if((evt.GetEventUdlType() == EventType::ACTIVATION || evt.GetEventUdlType() == EventType::DEACTIVATION) && classD->getClass(o2->GetClassID()) != NULL){
        nekonzistencia = 0;
    }
    if(nekonzistencia == 1){
        painter->setBrush(Qt::red);
        pen.setBrush(Qt::red);
    }
    painter->setPen(pen);
    if(evt.GetEventUdlType() == EventType::SYNCHRONOUS_MESSAGE){
        painter->drawLine(sx1, sy, sx2, sy);
        double phi = qDegreesToRadians(30.0);
        int barb = 20;
        if(sx1 > sx2){
            int x3 = sx2 + (int)(barb * qCos(-phi));
            int y3 = sy + (int)(barb * qSin(-phi));
            int x4 = sx2 + (int)(barb * qCos(phi));
            int y4 = sy + (int)(barb * qSin(phi));
            int dx = (sx1 - sx2)/2;
            if(nekonzistencia == 0){
                painter->setBrush(Qt::black);
            }
            QPoint points[3] = {QPoint(x3, y3), QPoint(sx2, sy), QPoint(x4, y4)};
            painter->drawPolygon(points, 3);
            painter->drawText(sx1 - dx - evt.GetEventName().length()*3, sy - 5, evt.GetEventName());
        }
        else{
            int x3 = sx2 - (int)(barb * qCos(-phi));
            int y3 = sy - (int)(barb * qSin(-phi));
            int x4 = sx2 - (int)(barb * qCos(phi));
            int y4 = sy - (int)(barb * qSin(phi));
            int dx = (sx2 - sx1)/2;
            if(nekonzistencia == 0){
                painter->setBrush(Qt::black);
            }
            QPoint points[3] = {QPoint(x3, y3), QPoint(sx2, sy), QPoint(x4, y4)};
            painter->drawPolygon(points, 3);
            painter->drawText(sx2 - dx - evt.GetEventName().length()*3, sy - 5, evt.GetEventName());
        }
    }
    else if(evt.GetEventUdlType() == EventType::ASYNCHRONOUS_MESSAGE){
        painter->drawLine(sx1, sy, sx2, sy);
        double phi = qDegreesToRadians(30.0);
        int barb = 20;
        if(sx1 > sx2){
            int x3 = sx2 + (int)(barb * qCos(-phi));
            int y3 = sy + (int)(barb * qSin(-phi));
            int x4 = sx2 + (int)(barb * qCos(phi));
            int y4 = sy + (int)(barb * qSin(phi));
            int dx = (sx1 - sx2)/2;
            painter->drawLine(x3, y3, sx2, sy);
            painter->drawLine(x4, y4, sx2, sy);
            painter->drawText(sx1 - dx - evt.GetEventName().length()*3, sy - 5, evt.GetEventName());
        }
        else{
            int x3 = sx2 - (int)(barb * qCos(-phi));
            int y3 = sy - (int)(barb * qSin(-phi));
            int x4 = sx2 - (int)(barb * qCos(phi));
            int y4 = sy - (int)(barb * qSin(phi));
            int dx = (sx2 - sx1)/2;
            painter->drawLine(x3, y3, sx2, sy);
            painter->drawLine(x4, y4, sx2, sy);
            painter->drawText(sx2 - dx - evt.GetEventName().length()*3, sy - 5, evt.GetEventName());
        }
    }
    else if(evt.GetEventUdlType() == EventType::RETURN_MESSAGE){
        QPen pen;
        QPen oldPen = painter->pen();
        pen.setStyle(Qt::DashLine);
        if(nekonzistencia == 1){
            pen.setBrush(Qt::red);
        }
        painter->setPen(pen);
        painter->drawLine(sx1, sy, sx2, sy);
        painter->setPen(oldPen);
        double phi = qDegreesToRadians(30.0);
        int barb = 20;
        if(sx1 > sx2){
            int x3 = sx2 + (int)(barb * qCos(-phi));
            int y3 = sy + (int)(barb * qSin(-phi));
            int x4 = sx2 + (int)(barb * qCos(phi));
            int y4 = sy + (int)(barb * qSin(phi));
            int dx = (sx1 - sx2)/2;
            painter->drawLine(x3, y3, sx2, sy);
            painter->drawLine(x4, y4, sx2, sy);
            painter->drawText(sx1 - dx - evt.GetEventName().length()*3, sy - 5, evt.GetEventName());
        }
        else{
            int x3 = sx2 - (int)(barb * qCos(-phi));
            int y3 = sy - (int)(barb * qSin(-phi));
            int x4 = sx2 - (int)(barb * qCos(phi));
            int y4 = sy - (int)(barb * qSin(phi));
            int dx = (sx2 - sx1)/2;
            painter->drawLine(x3, y3, sx2, sy);
            painter->drawLine(x4, y4, sx2, sy);
            painter->drawText(sx2 - dx - evt.GetEventName().length()*3, sy - 5, evt.GetEventName());
        }
    }
    else if(evt.GetEventUdlType() == EventType::CREATE_OBJECT){
        double phi = qDegreesToRadians(30.0);
        int barb = 20;
        if(sx1 > sx2){
            painter->drawLine(sx1, sy, sx2+(o2->surVX()/2), sy);
            int x3 = sx2+(o2->surVX()/2) + (int)(barb * qCos(-phi));
            int y3 = sy + (int)(barb * qSin(-phi));
            int x4 = sx2+(o2->surVX()/2) + (int)(barb * qCos(phi));
            int y4 = sy + (int)(barb * qSin(phi));
            int dx = (sx1 - sx2)/2;
            if(nekonzistencia == 0){
                painter->setBrush(Qt::black);
            }
            QPoint points[3] = {QPoint(x3, y3), QPoint(sx2+(o2->surVX()/2), sy), QPoint(x4, y4)};
            painter->drawPolygon(points, 3);
            painter->drawText(sx1 - dx - evt.GetEventName().length()*3, sy - 5, evt.GetEventName());
        }
        else{
            painter->drawLine(sx1, sy, sx2-(o2->surVX()/2), sy);
            int x3 = sx2-(o2->surVX()/2) - (int)(barb * qCos(-phi));
            int y3 = sy - (int)(barb * qSin(-phi));
            int x4 = sx2-(o2->surVX()/2) - (int)(barb * qCos(phi));
            int y4 = sy - (int)(barb * qSin(phi));
            int dx = (sx2 - sx1)/2;
            if(nekonzistencia == 0){
                painter->setBrush(Qt::black);
            }
            QPoint points[3] = {QPoint(x3, y3), QPoint(sx2-(o2->surVX()/2), sy), QPoint(x4, y4)};
            painter->drawPolygon(points, 3);
            painter->drawText(sx2 - dx - evt.GetEventName().length()*3, sy - 5, evt.GetEventName());
        }
    }
    else if(evt.GetEventUdlType() == EventType::DESTROY_OBJECT){
        double phi = qDegreesToRadians(30.0);
        int barb = 20;
        if(sx1 > sx2){
            painter->drawLine(sx1, sy, sx2+10, sy);
            int x3 = sx2+10 + (int)(barb * qCos(-phi));
            int y3 = sy + (int)(barb * qSin(-phi));
            int x4 = sx2+10 + (int)(barb * qCos(phi));
            int y4 = sy + (int)(barb * qSin(phi));
            int dx = (sx1 - sx2)/2;
            if(nekonzistencia == 0){
                painter->setBrush(Qt::black);
            }
            QPoint points[3] = {QPoint(x3, y3), QPoint(sx2+10, sy), QPoint(x4, y4)};
            painter->drawPolygon(points, 3);
            painter->drawLine(sx2+10, sy+10, sx2-10, sy-10);
            painter->drawLine(sx2+10, sy-10, sx2-10, sy+10);
            painter->drawText(sx1 - dx - evt.GetEventName().length()*3 - 10, sy - 5, evt.GetEventName());
        }
        else{
            painter->drawLine(sx1, sy, sx2-10, sy);
            int x3 = sx2-10 - (int)(barb * qCos(-phi));
            int y3 = sy - (int)(barb * qSin(-phi));
            int x4 = sx2-10 - (int)(barb * qCos(phi));
            int y4 = sy - (int)(barb * qSin(phi));
            int dx = (sx2 - sx1)/2;
            if(nekonzistencia == 0){
                painter->setBrush(Qt::black);
            }
            QPoint points[3] = {QPoint(x3, y3), QPoint(sx2-10, sy), QPoint(x4, y4)};
            painter->drawPolygon(points, 3);
            painter->drawLine(sx2+10, sy+10, sx2-10, sy-10);
            painter->drawLine(sx2+10, sy-10, sx2-10, sy+10);
            painter->drawText(sx2 - dx - evt.GetEventName().length()*3 - 10, sy - 5, evt.GetEventName());
        }
    }
    else if(evt.GetEventUdlType() == EventType::ACTIVATION){
        if(nekonzistencia == 0){
            painter->setBrush(Qt::black);
        }
        painter->drawEllipse(sx1 - 5, sy - 5, 10, 10);
    }
    else if(evt.GetEventUdlType() == EventType::DEACTIVATION){
        if(nekonzistencia == 0){
            painter->setBrush(Qt::black);
        }
        painter->drawRect(sx1 - 5, sy - 2, 10, 4);
    }
    painter->setBrush(defBrush);
}


void SeqDiagramWidget::FindBase(){
    baseY = 0;
    QList<SeqObject> objs = sDiagram->GetObjectList();
    for(SeqObject o : objs){
        if(o.surSY() == 100 && o.surSY() + o.surVY()/2 > baseY){
            baseY = o.surSY() + o.surVY()/2;
        }
    }
    sDiagram->SetBase(baseY);
}

int SeqDiagramWidget::AboveObject(int kX, int kY){
    QList<SeqObject> zozObjekt = sDiagram->GetObjectList();
    for (SeqObject o : zozObjekt){
        if(kX >= o.surSX()-o.surVX()/2 && kX <= o.surSX()+o.surVX()/2 && kY >= o.surSY()-o.surVY()/2 && kY <= o.surSY()+o.surVY()/2){
            return o.GetID();
        }
    }
    return 0;
}

int SeqDiagramWidget::AboveCorner(int kX, int kY){
    QList<SeqObject> zozObjekt = sDiagram->GetObjectList();
    for (SeqObject o : zozObjekt){
        if(kX >= o.surSX()+o.surVX()/2-5 && kX <= o.surSX()+o.surVX()/2+5 && kY >= o.surSY()+o.surVY()/2-5 && kY <= o.surSY()+o.surVY()/2+5){
            return o.GetID();
        }
    }
    return 0;
}

int SeqDiagramWidget::EventUnderCursor(int kX, int kY){
    eventID = 0;
    QList<SeqEvent> eventList = sDiagram->GetEventList();
    for(SeqEvent evt : eventList){
        SeqObject* o1 = sDiagram->FindObject(evt.GetEventClass1ID());
        SeqObject* o2 = sDiagram->FindObject(evt.GetEventClass2ID());
        int sx1 = o1->surSX();
        int sx2 = o2->surSX();
        int sy = baseY + 50*evt.GetOrder();
        if(kX >= sx1-5 && kX <= sx2+5 && kY >= sy-10 && kY <= sy+10){
            return evt.GetID();
        }
        if(kX >= sx2-5 && kX <= sx1+5 && kY >= sy-10 && kY <= sy+10){
            return evt.GetID();
        }
    }
    return 0;
}

void SeqDiagramWidget::AddObject(){
    AddObjectDialog dlg;
    QStringList clsList;
    for(Class* c : classD->classList){
        clsList.append(QString::fromStdString(c->getName()));
    }
    dlg.SetClasses(clsList);
    if(dlg.exec() == QDialog::Accepted){
        int id = clsList.indexOf(dlg.GetType());
        int classID = classD->classList[id]->getID();
        SeqObject* o = sDiagram->AddObject(dlg.GetName(), 0, classID);
        o->SetPosition(clickx);
        FindBase();
        repaint();
    }
}

void SeqDiagramWidget::EditObject(){
    EditObjectDialog dlg;
    QStringList clsList;
    SeqObject* o = sDiagram->FindObject(insideObjectID);
    int index = -1;
    for(unsigned int i = 0; i < classD->classList.size(); i++){
        Class* c = classD->classList[i];
        clsList.append(QString::fromStdString(c->getName()));
        if(c->getID() == o->GetClassID()){
            index = i;
        }
    }
    dlg.SetClasses(clsList);
    dlg.SetName(o->GetObjName());
    if(index >= 0){
        dlg.SetType(index);
    }
    if(dlg.exec() == QDialog::Accepted){
        int id = clsList.indexOf(dlg.GetType());
        int classID = classD->classList[id]->getID();
        sDiagram->EditObject(dlg.GetName(), classID, insideObjectID);
        repaint();
    }
}

void SeqDiagramWidget::AddEvent(){
    AddEventDialog dlg;
    QStringList objList;
    QList<SeqObject> zozObjekt = sDiagram->GetObjectList();
    for (SeqObject o : zozObjekt){
        Class* c = classD->getClass(o.GetClassID());
        QString type = "Unknown";
        if(c != NULL){
            type = QString::fromStdString(c->getName());
        }
        QString str = QString("%1:%2").arg(o.GetObjName(),type);
        objList.append(str);
    }
    dlg.SetTypes(evtTypes);
    dlg.SetObjects(objList);
    if(dlg.exec() == QDialog::Accepted){
        int o1 = dlg.GetObj1();
        int o2 = dlg.GetObj2();
        if(o1 == o2){
            QMessageBox::warning(this, "WARNING", "Reflexive message not allowed");
        }
        else{
            QString msg = dlg.GetMsg();
            int type = dlg.GetType();
            sDiagram->AddEvent(zozObjekt[o1].GetID(), zozObjekt[o2].GetID(), (EventType)type, msg, 0, 0, baseY);
            repaint();
        }
    }
}

void SeqDiagramWidget::EditMessage(){
    EditMessageDialog dlg(this);
    SeqEvent* evt = sDiagram->FindEvent(eventID);
    SeqObject* obj1 = sDiagram->FindObject(evt->GetEventClass1ID());
    SeqObject* obj2 = sDiagram->FindObject(evt->GetEventClass2ID());
    Class* c1 = classD->getClass(obj1->GetClassID());
    Class* c2 = classD->getClass(obj2->GetClassID());
    QString type = "Unknown";
    if(c1 != NULL){
        type = QString::fromStdString(c1->getName());
    }
    QString str = QString("%1:%2").arg(obj1->GetObjName(),type);
    dlg.SetObj1(str);
    type = "Unknown";
    if(c2 != NULL){
        type = QString::fromStdString(c2->getName());
    }
    str = QString("%1:%2").arg(obj2->GetObjName(),type);
    dlg.SetObj2(str);
    dlg.SetType(evtTypes[evt->GetEventUdlType()]);
    dlg.SetMsg(evt->GetEventName());
    if(dlg.exec() == QDialog::Accepted){
        QString msg = dlg.GetMsg();
        sDiagram->EditEvent(msg, eventID);
        repaint();

    }
}

void SeqDiagramWidget::DeleteEvent(){
    sDiagram->DeleteEvent(eventID);
    repaint();
}

void SeqDiagramWidget::DeleteObject(){
    sDiagram->DeleteObject(insideObjectID);
    repaint();
}

void SeqDiagramWidget::AddActivation(){
    sDiagram->AddEvent(insideObjectID, insideObjectID, EventType::ACTIVATION, "", 0, 0, baseY);
    repaint();
}

void SeqDiagramWidget::AddDeactivation(){
    sDiagram->AddEvent(insideObjectID, insideObjectID, EventType::DEACTIVATION, "", 0, 0, baseY);
    repaint();
}

void SeqDiagramWidget::PopupMenu1(int x, int y){
    QPoint pos(x,y);
    clickx = x;
    QMenu menu(this);
    menu.addAction("Add object",this, SLOT(AddObject()));
    menu.addSeparator();
    menu.addAction("Add event",this, SLOT(AddEvent()));
    QAction* act = menu.exec(mapToGlobal(pos));
    (void)act;
}

void SeqDiagramWidget::PopupMenu2(int x, int y){
    QPoint pos(x,y);
    clickx = x;
    QMenu menu(this);
    menu.addAction("Edit object",this, SLOT(EditObject()));
    menu.addAction("Delete object",this, SLOT(DeleteObject()));
    menu.addSeparator();
    menu.addAction("Add activation", this, SLOT(AddActivation()));
    menu.addAction("Add deactivation", this, SLOT(AddDeactivation()));
    QAction* act = menu.exec(mapToGlobal(pos));
    (void)act;
}

void SeqDiagramWidget::PopupMenu3(int x, int y){
    QPoint pos(x,y);
    clickx = x;
    QMenu menu(this);
    EventType eT = sDiagram->FindEvent(eventID)->GetEventUdlType();
    if(eT != EventType::ACTIVATION && eT != EventType::DEACTIVATION){
        menu.addAction("Edit message",this, SLOT(EditMessage()));
    }
    menu.addAction("Delete",this, SLOT(DeleteEvent()));
    QAction* act = menu.exec(mapToGlobal(pos));
    (void)act;
}

void SeqDiagramWidget::mouseMoveEvent(QMouseEvent *event)
{
    int mx=event->x();
    int my=event->y();
    if(dragging){
        if(cornerObjectID > 0){
            int offX = mx - mousex;
            int offY = my - mousey;
            sDiagram->FindObject(cornerObjectID)->ChangeSize(offX, offY);
            mousex=mx;
            mousey=my;
            repaint();

        }
        else if(insideObjectID > 0){
            int offX = mx - mousex;
            sDiagram->FindObject(insideObjectID)->ChangePosition(offX);
            mousex=mx;
            mousey=my;
            repaint();
        }
        else if(eventID > 0){
            int offY = my - mousey;
            if(offY > 40){
                sDiagram->MoveDown(eventID);
                mousey = my;
                repaint();
            }
            if(offY < -20){
                sDiagram->MoveUp(eventID);
                mousey = my;
                repaint();
            }
        }

    }
    else {
        cornerObjectID=AboveCorner(mx,my);
        insideObjectID=AboveObject(mx,my);
        eventID = EventUnderCursor(mx, my);
        if(cornerObjectID > 0){
            setCursor(Qt::SizeFDiagCursor);
        }
        else if(insideObjectID > 0){
            setCursor(Qt::SizeAllCursor);
        }
        else if(eventID > 0){
            setCursor(Qt::SizeVerCursor);
        }
        else {
            setCursor(Qt::ArrowCursor);
        }
    }
    event->accept();
}

void SeqDiagramWidget::mousePressEvent(QMouseEvent *event)
{
    int mx=event->x();
    int my=event->y();
    if(event->button()==Qt::LeftButton){
        dragging=true;
        mousex=mx;
        mousey=my;
    }

    event->accept();
}

void SeqDiagramWidget::mouseReleaseEvent(QMouseEvent *event){
    int mx=event->x();
    int my=event->y();
    cornerObjectID=AboveCorner(mx,my);
    insideObjectID=AboveObject(mx,my);
    eventID = EventUnderCursor(mx, my);
    if(cornerObjectID > 0){
        setCursor(Qt::SizeFDiagCursor);
    }
    else if(insideObjectID > 0){
        setCursor(Qt::SizeAllCursor);
    }
    else if(eventID > 0){
        setCursor(Qt::SizeVerCursor);
    }
    else {
        setCursor(Qt::ArrowCursor);
    }
    if(event->button()==Qt::LeftButton){
        dragging=false;
    }
    if(event->button()==Qt::RightButton){
        if(cornerObjectID == 0 && insideObjectID == 0 && eventID == 0){
            PopupMenu1(event->x(), event->y());
        }
        else if(insideObjectID > 0){
            PopupMenu2(event->x(), event->y());
        }
        else if(eventID > 0){
            PopupMenu3(event->x(), event->y());
        }
    }
    event->accept();
}
