#include "seqdiagramwidget.h"
#include "addobjectdialog.h"
#include <QFontMetrics>
#include <QMenu>

SeqDiagramWidget::SeqDiagramWidget(QWidget *parent)
    : QWidget{parent}
{
    sDiagram = new SeqDiagram("tata", new DiagramTried());
    sDiagram->PridajObjekt("o1", 0, 1);
    sDiagram->NajdiObjekt(1)->NastavPoziciu(300);
    sDiagram->PridajObjekt("o2", 0, 1);
    NajdiZakladnu();
    sDiagram->PridajUdalost(1, 2, TypUdalosti::SYNCHRONNA_SPRAVA, "mama", 0, 0, zakladnaY);
    dragging=false;
    setMouseTracking(true);
}

void SeqDiagramWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.drawEllipse(100, 100, 50, 50);
    QList<SeqObject> zozObjekt = sDiagram->ZoznamObjektov();
    for(int i = 0; i<zozObjekt.size(); i++){
        DrawObject(&painter, zozObjekt[i]);

    }
    QList<SeqEvent> zozUdalost = sDiagram->ZoznamUdalosti();
    for(int i = 0; i<zozUdalost.size(); i++){
        DrawEvent(&painter, zozUdalost[i]);
    }
}

QString FormatString(QString src, QFontMetrics metrics, int maxX){
        QString dst = src;
        QSize size = metrics.size(Qt::TextSingleLine, dst);
        while(size.width() > maxX){
            dst = dst.left(dst.length()-1);
            size = metrics.size(Qt::TextSingleLine, dst);
        }
        return dst;
    }

void SeqDiagramWidget::DrawObject(QPainter* painter, SeqObject o){
    int px = o.surSX() - o.surVX()/2;
    int py = o.surSY() - o.surVY()/2;
    int maxY = py + o.surVY();
    painter->drawRect(o.surSX()-o.surVX()/2, o.surSY()-o.surVY()/2, o.surVX(), o.surVY());
    QFontMetrics fm = painter->fontMetrics();
    int hgt = fm.height();
    painter->drawText(px+5, py+hgt, FormatString(o.ObjNazov(), fm, o.surVX()-10));
    if(py+2*hgt+5 < maxY){
        painter->drawText(px+5, py+2*hgt, FormatString("<<"+o.ObjTyp()+">>", fm, o.surVX()-10));
    }
    QPen pen;
    QPen oldPen = painter->pen();
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->drawLine(o.surSX(), o.surSY()+o.surVY()/2, o.surSX(), this->size().height()-50);
    painter->setPen(oldPen);
}

void SeqDiagramWidget::DrawEvent(QPainter* painter, SeqEvent evt){
        SeqObject* o1 = sDiagram->NajdiObjekt(evt.UdlTrieda1ID());
        SeqObject* o2 = sDiagram->NajdiObjekt(evt.UdlTrieda2ID());
        int sx1 = o1->surSX();
        int sx2 = o2->surSX();
        int sy = zakladnaY + 50*evt.Order();
        //Color old = g.getColor();
        if(evt.UdlTyp() == TypUdalosti::SYNCHRONNA_SPRAVA){
            painter->drawLine(sx1, sy, sx2, sy);
            double phi = qDegreesToRadians(30);
            int barb = 20;
            if(sx1 > sx2){
                int x3 = sx2 + (int)(barb * qCos(-phi));
                int y3 = sy + (int)(barb * qSin(-phi));
                int x4 = sx2 + (int)(barb * qCos(phi));
                int y4 = sy + (int)(barb * qSin(phi));
                int dx = (sx1 - sx2)/2;
                painter->setBrush(Qt::black);
                QPoint points[3] = {QPoint(x3, y3), QPoint(sx2, sy), QPoint(x4, y4)};
                painter->drawPolygon(points, 3);
                painter->drawText(sx1 - dx - evt.UdlNazov().length()*3, sy - 5, evt.UdlNazov());
            }
            else{
                int x3 = sx2 - (int)(barb * qCos(-phi));
                int y3 = sy - (int)(barb * qSin(-phi));
                int x4 = sx2 - (int)(barb * qCos(phi));
                int y4 = sy - (int)(barb * qSin(phi));
                int dx = (sx2 - sx1)/2;
                painter->setBrush(Qt::black);
                QPoint points[3] = {QPoint(x3, y3), QPoint(sx2, sy), QPoint(x4, y4)};
                painter->drawPolygon(points, 3);
                painter->drawText(sx2 - dx - evt.UdlNazov().length()*3, sy - 5, evt.UdlNazov());
            }
        }
        else if(evt.UdlTyp() == TypUdalosti::ASYNCHRONNA_SPRAVA){
            painter->drawLine(sx1, sy, sx2, sy);
            double phi = qDegreesToRadians(30);
            int barb = 20;
            if(sx1 > sx2){
                int x3 = sx2 + (int)(barb * qCos(-phi));
                int y3 = sy + (int)(barb * qSin(-phi));
                int x4 = sx2 + (int)(barb * qCos(phi));
                int y4 = sy + (int)(barb * qSin(phi));
                int dx = (sx1 - sx2)/2;
                painter->drawLine(x3, y3, sx2, sy);
                painter->drawLine(x4, y4, sx2, sy);
                painter->drawText(sx1 - dx - evt.UdlNazov().length()*3, sy - 5, evt.UdlNazov());
            }
            else{
                int x3 = sx2 - (int)(barb * qCos(-phi));
                int y3 = sy - (int)(barb * qSin(-phi));
                int x4 = sx2 - (int)(barb * qCos(phi));
                int y4 = sy - (int)(barb * qSin(phi));
                int dx = (sx2 - sx1)/2;
                painter->drawLine(x3, y3, sx2, sy);
                painter->drawLine(x4, y4, sx2, sy);
                painter->drawText(sx2 - dx - evt.UdlNazov().length()*3, sy - 5, evt.UdlNazov());
            }
        }
        else if(evt.UdlTyp() == TypUdalosti::NAVRAT_SPRAVY){
            QPen pen;
            QPen oldPen = painter->pen();
            pen.setStyle(Qt::DashLine);
            painter->setPen(pen);
            painter->drawLine(sx1, sy, sx2, sy);
            painter->setPen(oldPen);
            double phi = qDegreesToRadians(30);
            int barb = 20;
            if(sx1 > sx2){
                int x3 = sx2 + (int)(barb * qCos(-phi));
                int y3 = sy + (int)(barb * qSin(-phi));
                int x4 = sx2 + (int)(barb * qCos(phi));
                int y4 = sy + (int)(barb * qSin(phi));
                int dx = (sx1 - sx2)/2;
                painter->drawLine(x3, y3, sx2, sy);
                painter->drawLine(x4, y4, sx2, sy);
                painter->drawText(sx1 - dx - evt.UdlNazov().length()*3, sy - 5, evt.UdlNazov());
            }
            else{
                int x3 = sx2 - (int)(barb * qCos(-phi));
                int y3 = sy - (int)(barb * qSin(-phi));
                int x4 = sx2 - (int)(barb * qCos(phi));
                int y4 = sy - (int)(barb * qSin(phi));
                int dx = (sx2 - sx1)/2;
                painter->drawLine(x3, y3, sx2, sy);
                painter->drawLine(x4, y4, sx2, sy);
                painter->drawText(sx2 - dx - evt.UdlNazov().length()*3, sy - 5, evt.UdlNazov());
            }
        }
        else if(evt.UdlTyp() == TypUdalosti::TVORBA_OBJEKTU){
            double phi = qDegreesToRadians(30);
            int barb = 20;
            if(sx1 > sx2){
                painter->drawLine(sx1, sy, sx2+(o2->surVX()/2), sy);
                int x3 = sx2+(o2->surVX()/2) + (int)(barb * qCos(-phi));
                int y3 = sy + (int)(barb * qSin(-phi));
                int x4 = sx2+(o2->surVX()/2) + (int)(barb * qCos(phi));
                int y4 = sy + (int)(barb * qSin(phi));
                int dx = (sx1 - sx2)/2;
                painter->setBrush(Qt::black);
                QPoint points[3] = {QPoint(x3, y3), QPoint(sx2+(o2->surVX()/2), sy), QPoint(x4, y4)};
                painter->drawPolygon(points, 3);
                painter->drawText(sx1 - dx - evt.UdlNazov().length()*3, sy - 5, evt.UdlNazov());
            }
            else{
                painter->drawLine(sx1, sy, sx2-(o2->surVX()/2), sy);
                int x3 = sx2-(o2->surVX()/2) - (int)(barb * qCos(-phi));
                int y3 = sy - (int)(barb * qSin(-phi));
                int x4 = sx2-(o2->surVX()/2) - (int)(barb * qCos(phi));
                int y4 = sy - (int)(barb * qSin(phi));
                int dx = (sx2 - sx1)/2;
                painter->setBrush(Qt::black);
                QPoint points[3] = {QPoint(x3, y3), QPoint(sx2-(o2->surVX()/2), sy), QPoint(x4, y4)};
                painter->drawPolygon(points, 3);
                painter->drawText(sx2 - dx - evt.UdlNazov().length()*3, sy - 5, evt.UdlNazov());
            }
        }
        else if(evt.UdlTyp() == TypUdalosti::ZANIK_OBJEKTU){
            double phi = qDegreesToRadians(30);
            int barb = 20;
            if(sx1 > sx2){
                painter->drawLine(sx1, sy, sx2+10, sy);
                int x3 = sx2+10 + (int)(barb * qCos(-phi));
                int y3 = sy + (int)(barb * qSin(-phi));
                int x4 = sx2+10 + (int)(barb * qCos(phi));
                int y4 = sy + (int)(barb * qSin(phi));
                int dx = (sx1 - sx2)/2;
                painter->setBrush(Qt::black);
                QPoint points[3] = {QPoint(x3, y3), QPoint(sx2+10, sy), QPoint(x4, y4)};
                painter->drawPolygon(points, 3);
                painter->drawLine(sx2+10, sy+10, sx2-10, sy-10);
                painter->drawLine(sx2+10, sy-10, sx2-10, sy+10);
                painter->drawText(sx1 - dx - evt.UdlNazov().length()*3 - 10, sy - 5, evt.UdlNazov());
            }
            else{
                painter->drawLine(sx1, sy, sx2-10, sy);
                int x3 = sx2-10 - (int)(barb * qCos(-phi));
                int y3 = sy - (int)(barb * qSin(-phi));
                int x4 = sx2-10 - (int)(barb * qCos(phi));
                int y4 = sy - (int)(barb * qSin(phi));
                int dx = (sx2 - sx1)/2;
                painter->setBrush(Qt::black);
                QPoint points[3] = {QPoint(x3, y3), QPoint(sx2-10, sy), QPoint(x4, y4)};
                painter->drawPolygon(points, 3);
                painter->drawLine(sx2+10, sy+10, sx2-10, sy-10);
                painter->drawLine(sx2+10, sy-10, sx2-10, sy+10);
                painter->drawText(sx2 - dx - evt.UdlNazov().length()*3 - 10, sy - 5, evt.UdlNazov());
            }
        }
        else if(evt.UdlTyp() == TypUdalosti::AKTIVACIA){
            painter->setBrush(Qt::black);
            painter->drawEllipse(sx1 - 5, sy - 5, 10, 10);
        }
        else if(evt.UdlTyp() == TypUdalosti::DEAKTIVACIA){
            painter->setBrush(Qt::black);
            painter->drawRect(sx1 - 5, sy - 2, 10, 4);
        }
    }


void SeqDiagramWidget::NajdiZakladnu(){
        zakladnaY = 0;
        QList<SeqObject> objs = sDiagram->ZoznamObjektov();
        for(SeqObject o : objs){
            if(o.surSY() == 100 && o.surSY() + o.surVY()/2 > zakladnaY){
                zakladnaY = o.surSY() + o.surVY()/2;
            }
        }
        sDiagram->NastavZakladnu(zakladnaY);
    }

int SeqDiagramWidget::VoVnutri(int kX, int kY){
    QList<SeqObject> zozObjekt = sDiagram->ZoznamObjektov();
    for (SeqObject o : zozObjekt){
        if(kX >= o.surSX()-o.surVX()/2 && kX <= o.surSX()+o.surVX()/2 && kY >= o.surSY()-o.surVY()/2 && kY <= o.surSY()+o.surVY()/2){
            return o.ID();
        }
    }
    return 0;
}

int SeqDiagramWidget::VRohu(int kX, int kY){
    QList<SeqObject> zozObjekt = sDiagram->ZoznamObjektov();
    for (SeqObject o : zozObjekt){
        if(kX >= o.surSX()+o.surVX()/2-5 && kX <= o.surSX()+o.surVX()/2+5 && kY >= o.surSY()+o.surVY()/2-5 && kY <= o.surSY()+o.surVY()/2+5){
            return o.ID();
        }
    }
    return 0;
}

void SeqDiagramWidget::AddObject(){
    AddObjectDialog dlg;
    if(dlg.exec() == QDialog::Accepted){
        SeqObject* o = sDiagram->PridajObjekt("o3", 0, 1);
        o->NastavPoziciu(clickx);
        repaint();
    }

}

void SeqDiagramWidget::PopupMenu1(int x, int y){
    QPoint pos(x,y);
    clickx = x;
    QMenu menu;
    menu.addAction("Add object",this, SLOT(AddObject()));
    menu.addSeparator();
    menu.addAction("Add event");
    menu.addAction("Edit event");
    menu.addAction("Delete event");
    QAction* act = menu.exec(mapToGlobal(pos));
}

void SeqDiagramWidget::mouseMoveEvent(QMouseEvent *event)
{
    int mx=event->x();
    int my=event->y();
    if(dragging){
        if(idRohuObjektu > 0){
            int offX = mx - mousex;
            int offY = my - mousey;
            sDiagram->NajdiObjekt(idRohuObjektu)->UpravVelkost(offX, offY);
            mousex=mx;
            mousey=my;
            repaint();

        } else if(idVnutraObjektu > 0){
            int offX = mx - mousex;
            sDiagram->NajdiObjekt(idVnutraObjektu)->UpravPoziciu(offX);
            mousex=mx;
            mousey=my;
            repaint();
        }

    } else {
        idRohuObjektu=VRohu(mx,my);
        idVnutraObjektu=VoVnutri(mx,my);
        if(idRohuObjektu > 0){
            setCursor(Qt::SizeFDiagCursor);
        }
        else if(idVnutraObjektu > 0){
            setCursor(Qt::SizeAllCursor);
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
    //int mx=event->x();
    //int my=event->y();
    if(event->button()==Qt::LeftButton){
        dragging=false;
    }
    if(event->button()==Qt::RightButton){
        if(idRohuObjektu == 0 && idVnutraObjektu == 0){
            PopupMenu1(event->x(), event->y());
        }
    }
    event->accept();
}
