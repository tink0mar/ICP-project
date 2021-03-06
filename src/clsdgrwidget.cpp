#include "clsdgrwidget.h"
#include <QUuid>
#include <iostream>
#include <QString>
#include <QSignalMapper>
#include <QtMath>

ClsDiagramWidget::ClsDiagramWidget(QWidget *parent)
    : QWidget{parent}
{
    dragging=false;
    fprintf(stderr, "tu\n");
    setMouseTracking(true);
}

void ClsDiagramWidget::CreateNewClsDiagram(QString diagramName){

        QString uuid = QUuid::createUuid().toString();

        clsDiagram = new DiagramClass(diagramName.toStdString());

        clsDiagram->appendClass("test1", incNextClassID(), 0);
        clsDiagram->appendClass("test2", incNextClassID(), 0);
        Class* cls = clsDiagram->getClass(0);
        cls->setPosition(250, 100);

        vector<string> vecParam;
        vecParam.push_back("boo");

        cls->appendMethod(cls->getNextAttribID(), Visibility::T_public, "foo", "foo_ret", vecParam);
        cls->appendAttribute(cls->getNextMethodID(), Visibility::T_private, "goo", "int");

        repaint();
}

void ClsDiagramWidget::LoadClsDiagram(QString filename){
    QStringList elements = filename.split('.');
    clsDiagram = new DiagramClass(elements.at(0).toStdString());
    clsDiagram->loadDiagram(filename.toStdString());
    next_class_id = clsDiagram->getNextClassID();
    next_class_id = clsDiagram->getNextRelationID();
    repaint();
}

DiagramClass* ClsDiagramWidget::getDiagramCls(){
    return clsDiagram;
}

int ClsDiagramWidget::getNextClassID(){
    return next_class_id;
}

int ClsDiagramWidget::getNextRelID(){
    return next_relation_id++;
}

int ClsDiagramWidget::incNextRelID(){
    return next_relation_id++;
}

int ClsDiagramWidget::incNextClassID(){
    return next_class_id++;
}

int ClsDiagramWidget::findInside(int mx, int my){
    for (auto *cls : clsDiagram->classList){
        if (mx >= cls->x && mx <= cls->x + cls->width && my >= cls->y && my <= cls->y + cls->height){
            return cls->getID();
        }
    }
    return -1;
}

int ClsDiagramWidget::findIncorner(int mx, int my){
    for (auto *cls : clsDiagram->classList){
        if (mx >= cls->x + cls->width - 5 && mx <= cls->x + cls->width + 5 && my >= cls->y + cls->height -5 && my <= cls->y + cls->height + 5){
            return cls->getID();
        }
    }
    return -1;
}

int ClsDiagramWidget::str_off(string str){
    int w = str.size()/2 *9;
    return w;
}

int ClsDiagramWidget::getMaxWidth(Class *cls, string name){
    int width = str_off(name);

    for (auto att : cls->attribVector){
        string str = att->getVisibilityStr() + " " + att->getName() + " : " + att->getType();
        width = str_off(str) > width ? str_off(str) : width;
    }

    for (auto met : cls->methodVector){
        string params = clsDiagram->vtos(met->vectorParam);
        string str = met->getVisibilityStr() + " " + met->getName() + " (" + params + ") " + met->getReturnType();
        width = str_off(str) > width ? str_off(str) : width;
    }

    return width;
}

void ClsDiagramWidget::resizeClassWidth(Class *cls, int text_len){

    if (cls->width/2 < 15 + text_len){
        cls->changeSize(text_len*2+30-cls->width,0);
    }

}

void ClsDiagramWidget::resizeClassHeight(Class *cls, int height){

    if (height > cls->height){
        cls->changeSize(0, height - cls->height);
    }
}

void ClsDiagramWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for(auto *c : clsDiagram->classList){
        //Dorobit kreslenie
        string name;
        if (c->getInterface() == 0){
            name = c->getName();
        }else {
            name = "<<interface>>" + c->getName();
        }
        resizeClassWidth(c, getMaxWidth(c, name));
        resizeClassHeight(c, 37+c->attribVector.size()*15 + c->methodVector.size()*15);

        painter.drawText(c->x + c->width/2 - str_off(name), c->y + 16, QString::fromStdString(name));
        painter.drawLine(c->x, c->y+20, c->x + c->width, c->y + 20);

        int line_height = 37;
        for (auto att : c->attribVector){
            string str = att->getVisibilityStr() + " " + att->getName() + " : " + att->getType();

            resizeClassWidth(c, str_off(str));
            painter.drawText(c->x + 15, c->y + line_height, QString::fromStdString(str));
            line_height += 15;
        }

        if (c->attribVector.size()!=0){
            painter.drawLine(c->x, c->y+line_height - 10, c->x + c->width, c->y+line_height - 10);
        }

        line_height += 5; // space between line and text
        for (auto met : c->methodVector){
            string str = met->getVisibilityStr() + " " + met->getName() + " (" + clsDiagram->vtos(met->vectorParam) + ") " + met->getReturnType();

            resizeClassWidth(c, str_off(str));
            painter.drawText(c->x + 15, c->y + line_height, QString::fromStdString(str));
            line_height += 15;
        }

        for (auto rel : clsDiagram->relationList){
            cerr << rel->getName() << endl;
        }

        painter.drawRect(c->x,c->y,c->width,c->height);
    }

    for (auto *rel : clsDiagram->relationList){
        Class *c1 = clsDiagram->getClass(rel->getFirstID());
        Class *c2 = clsDiagram->getClass(rel->getSecondID());
        int x_1 = c1->x + c1->width/2;
        int y_1 = c1->y + c1->height/2;
        int x_2 = c2->x + c2->width/2;
        int y_2 = c2->y + c2->height/2;
        int x1, y1, x2, y2;


        if(y_1 - c1->height/2 > y_2){
            y1 = y_1 - c1->height/2;
            x1 = x_1;
        }
        else if(y_1 + c1->height/2 < y_2){
            y1 = y_1 + c1->height/2;
            x1 = x_1;
        }
        else{
            y1 = y_1;
            x1 = x_1 < x_2 ? x_1 + c1->width/2 : x_1 - c1->width/2;
        }


        if(y_2 - c2->height/2 > y_1){
            y2 = y_2 - c2->height/2;
            x2 = x_2;
        }
        else if(y_2 + c2->height/2 < y_1){
            y2 = y_2 + c2->height/2;
            x2 = x_2;
        }
        else{
            y2 = y_2;
            x2 = x_2 < x_1 ? x_2 + c2->width/2 : x_2 - c2->width/2;
        }


        painter.drawLine(x1, y1, x2, y2);

        double dy = y2 - y1;
        double dx = x2 - x1;
        double phi = qDegreesToRadians(30.0);
        double tphi = qDegreesToRadians(10.0);
        int prepon = 20;
        qreal theta = qAtan2(dy, dx);        
        int x3 = x2 - (int)(prepon * qCos(theta + phi));
        int y3 = y2 - (int)(prepon * qSin(theta + phi));
        int x4 = x2 - (int)(prepon * qCos(theta - phi));
        int y4 = y2 - (int)(prepon * qSin(theta - phi));
        int x5 = x2 - (int)(prepon * 2 * qCos(theta));
        int y5 = y2 - (int)(prepon * 2 * qSin(theta));

        QVector<QPoint> diamond = {QPoint(x3, y3), QPoint(x2, y2), QPoint(x4, y4),QPoint(x5, y5)};
        QVector<QPoint> triangle = {QPoint(x3, y3), QPoint(x2, y2), QPoint(x4, y4)};
        int tx1;
        int ty1;
        int tx2;
        int ty2;

        if(rel->getRelType() == T_generalization){
            QPolygon pol(triangle);
            QBrush brush(Qt::white);
            QPainterPath path;
            path.addPolygon(pol);
            painter.drawPolygon(pol);
            painter.fillPath(path, brush);
        }
        else if(rel->getRelType() == T_composition){
            QPolygon pol(diamond);
            QBrush brush(Qt::black);
            QPainterPath path;
            path.addPolygon(pol);
            painter.drawPolygon(pol);
            painter.fillPath(path, brush);

        }
        else if(rel->getRelType() == T_aggregation){
            QPolygon pol(diamond);
            QBrush brush(Qt::white);
            QPainterPath path;
            path.addPolygon(pol);
            painter.drawPolygon(pol);
            painter.fillPath(path, brush);

        }


        if(x_1 < x_2){
            dy = y1 - y2;
            dx = x1 - x2;
            theta = qAtan2(dy, dx);
            if(y_1 - c1->height/2 > y_2){
                tx1 = x1 - (int)(30 * qCos(theta - tphi)) - rel->getCardFirst().length()*3 - 25;
                ty1 = y1 - 5;
                 painter.drawText( tx1, ty1, QString::fromStdString(rel->getCardFirst()));
                if(dx < 0){
                    dx = -dx;
                }
                if(dy < 0){
                    dy = -dy;
                }
                painter.drawText((int)(x1 + dx/2 - rel->getName().length()*5 - 25), (int)(y1 - dy/2), QString::fromStdString(rel->getName()));
            }
            else if(x_1 + c1->height/2 < y_2){
                tx1 = x1 - (int)(30 * qCos(theta + tphi)) - rel->getCardFirst().length()*3 - 25;
                ty1 = y1 + 15;
                painter.drawText( tx1, ty1, QString::fromStdString(rel->getCardFirst()));

                if(dx < 0){
                    dx = -dx;
                }
                if(dy < 0){
                    dy = -dy;
                }
                painter.drawText( (int)(x1 + dx/2 - rel->getName().length()*6 - 20), (int)(y1 + dy/2 + 5), QString::fromStdString(rel->getName()));
            }
            else {
                tx1 = x1 + 5 + rel->getCardFirst().length();
                ty1 = y1 - (int)(30 * qSin(theta - tphi)) - 10;
                painter.drawText(tx1, ty1, QString::fromStdString(rel->getCardFirst()));
                if(dx < 0){
                    dx = -dx;
                }
                if(dy < 0){
                    dy = -dy;
                }
                if(y_1 > y_2){
                    painter.drawText( (int)(x1 + dx/2 - rel->getName().length()*3), (int)(y1 - dy/2 + rel->getName().length()*3) - 15, QString::fromStdString(rel->getName()));

                }
                else{
                    painter.drawText( (int)(x1 + dx/2 - rel->getName().length()*3), (int)(y1 + dy/2 - rel->getName().length()*3) + 15, QString::fromStdString(rel->getName()));

                }
            }
        }
        else{
            dy = y1 - y2;
            dx = x1 - x2;
            theta = qAtan2(dy, dx);
            if(y_1 - c1->height/2 > y_2){
                tx1 = x1 - (int)(30 * qCos(theta - tphi)) + rel->getCardFirst().length() + 15;
                ty1 = y1 - 5;
                painter.drawText( tx1, ty1, QString::fromStdString(rel->getCardFirst()));
                if(dx < 0){
                    dx = -dx;
                }
                if(dy < 0){
                    dy = -dy;
                }
                painter.drawText( (int)(x1 - dx/2 + rel->getName().length()), (int)(y1 - dy/2), QString::fromStdString(rel->getName()));

            }
            else if(y_1 + c1->height/2 < y_2){
                tx1 = x1 - (int)(30 * qCos(theta - tphi)) + rel->getCardFirst().length() + 15;
                ty1 = y1 + 15;
                painter.drawText(  tx1, ty1, QString::fromStdString(rel->getCardFirst()));

                if(dx < 0){
                    dx = -dx;
                }
                if(dy < 0){
                    dy = -dy;
                }
                painter.drawText((int)(x1 - dx/2 + rel->getName().length() + 10), (int)(y1 + dy/2 + 5), QString::fromStdString(rel->getName()));
            }
            else{
                tx1 = x1 - 25 - rel->getCardFirst().length();
                ty1 = y1 - (int)(30 * qSin(theta - tphi)) - 25;
                painter.drawText(tx1, ty1, QString::fromStdString(rel->getCardFirst()));
                if(dx < 0){
                    dx = -dx;
                }
                if(dy < 0){
                    dy = -dy;
                }
                if(y_1 > y_2){
                    painter.drawText((int)(x1 - dx/2 - rel->getName().length()*3), (int)(y1 - dy/2 + rel->getName().length()*3) - 15, QString::fromStdString(rel->getName()));

                }
                else{
                    painter.drawText((int)(x1 - dx/2 - rel->getName().length()*3), (int)(y1 + dy/2 - rel->getName().length()*3) + 20, QString::fromStdString(rel->getName()));
                }
            }
        }
        if(x_1 > x_2){
            dy = y2 - y1;
            dx = x2 - x1;
            theta = qAtan2(dy, dx);
            if(y_2 - c2->height/2 > y_1){
                tx2 = x2 - (int)(30 * qCos(theta - tphi)) - rel->getCardSecond().length()*3 - 35;
                ty2 = y2 - 5;
                 painter.drawText(tx2, ty2, QString::fromStdString(rel->getCardSecond()));

            }
            else if(y_2 + c2->height/2 < y_1){
                tx2 = x2 - (int)(30 * qCos(theta + tphi)) - rel->getCardSecond().length()*3 - 35;
                ty2 = y2 + 15;
                painter.drawText(tx2, ty2, QString::fromStdString(rel->getCardSecond()));

            }
            else{
                tx2 = x2 + 5 + rel->getCardSecond().length();
                ty2 = y2 - (int)(30 * qSin(theta - tphi)) - 20;
                painter.drawText(tx2, ty2, QString::fromStdString(rel->getCardSecond()));
            }
        }
        else{
            dy = y2 - y1;
            dx = x2 - x1;
            theta = qAtan2(dy, dx);
            if(y_2 - c2->height/2 > y_1){
                tx2 = x2 - (int)(30 * qCos(theta - tphi)) + rel->getCardSecond().length() + 25;
                ty2 = y2 - 5;
                painter.drawText(tx2, ty2, QString::fromStdString(rel->getCardSecond()));

            }
            else if(y_2 + c2->height/2 < y_1){
                tx2 = x2 - (int)(30 * qCos(theta - tphi)) + rel->getCardFirst().length() + 25;
                ty2 = y2 + 15;
                painter.drawText(tx2, ty2, QString::fromStdString(rel->getCardSecond()));

            }
            else{
                tx2 = x2 - 25 - rel->getCardFirst().length();
                ty2 = y2 - (int)(30 * qSin(theta - tphi)) - 25;
                painter.drawText(tx2, ty2, QString::fromStdString(rel->getCardSecond()));

            }
        }

    }

}


void ClsDiagramWidget::mouseMoveEvent(QMouseEvent *event)
{
    int mx=event->x();
    int my=event->y();
    if(dragging){
        if(incorner_id >= 0){
            int off_x = (mx-mousex);
            int off_y = (my-mousey);
            mousex=mx;
            mousey=my;
            clsDiagram->getClass(incorner_id)->changeSize(off_x, off_y);
            repaint();
        } else if(inside_id >= 0){
            int off_x = (mx-mousex);
            int off_y = (my-mousey);
            mousex=mx;
            mousey=my;
            clsDiagram->getClass(inside_id)->changePosition(off_x, off_y);
            repaint();
        }
    } else {
        incorner_id = findIncorner(mx, my) ;
        inside_id = findInside(mx, my);

        if (incorner_id >= 0){
            setCursor(Qt::SizeFDiagCursor);
        } else if (inside_id >= 0) {
            setCursor(Qt::SizeAllCursor);
        } else {
            setCursor(Qt::ArrowCursor);
        }

    }
    event->accept();
}

void ClsDiagramWidget::mousePressEvent(QMouseEvent *event)
{
    int mx=event->x();
    int my=event->y();
    if(event->button()==Qt::LeftButton){
        dragging=true;
        mousex=mx;
        mousey=my;
    } else if (event->button()==Qt::RightButton){
        dragging=false;
    }

    event->accept();
}

void ClsDiagramWidget::mouseReleaseEvent(QMouseEvent *event){
    mousex = event->x();;
    mousey = event->y();
    if(event->button()==Qt::LeftButton){
        dragging=false;
    } else if (event->button() == Qt::RightButton){

        if(incorner_id == -1 && inside_id == -1){
            PopUpMenuWidget(event->x(), event->y());
        } else if (inside_id >= 0){
            PopUpClassWidget(inside_id, mousex, mousey);
        }
    }
    event->accept();
}

void ClsDiagramWidget::PopUpClassWidget(int id, int x, int y){
    QPoint pos(x,y);
    QMenu menu;
    object_id = id;

    menu.addAction("Remove class", this, SLOT(RemoveClass()));
    menu.addAction("Change class", this, SLOT(ChangeClass()));
    menu.addSeparator();
    menu.addAction("Add attribute", this, SLOT(AddAttribute()));
    menu.addAction("Change attribute", this, SLOT(ChangeAttribute()));
    menu.addAction("Remove attribute", this, SLOT(RemoveAttribute()));
    menu.addSeparator();
    menu.addAction("Add method", this, SLOT(AddMethod()));
    menu.addAction("Change method", this, SLOT(ChangeMethod()));
    menu.addAction("Remove method", this, SLOT(RemoveMethod()));
    menu.addAction("Add parameter to method", this, SLOT(addParameter()));
    menu.addAction("Remove parameter from method", this, SLOT(removeParameter()));

    QAction* act = menu.exec(mapToGlobal(pos));
}

void ClsDiagramWidget::RemoveClass(){
    clsDiagram->destroyClass(object_id);
    repaint();
}

void ClsDiagramWidget::ChangeClass(){
    BasicDialog dlg;
    dlg.changeName(QString("Change Class name"));
    dlg.changeLabel(QString("New name"));
    dlg.removeComboBox();


    Class *cls = clsDiagram->getClass(object_id);
    if (cls->getInterface() == 1){
        dlg.setCheckBox();
    }

    if(dlg.exec() == QDialog::Accepted){
        QString q_name = dlg.getLineEditConent();
        string name = q_name.toStdString();
        clsDiagram->changeClass(name, object_id, dlg.getInterface());
        repaint();
    }

}

void ClsDiagramWidget::AddAttribute(){
    AddAttributeDialog dlg;
    dlg.changeName(QString("Add Attribute"));

    if(dlg.exec() == QDialog::Accepted){
        Class *cls = clsDiagram->getClass(object_id);
        string mod = dlg.getComboBoxContent().toStdString();
        QString type = dlg.getLineEditType();
        QString name = dlg.getLineEditName();

        Visibility vis = cls->strToVisbility(mod);

        cls->appendAttribute(cls->getNextAttribID(), vis, name.toStdString(), type.toStdString());
        repaint();
    }
}

void ClsDiagramWidget::ChangeAttribute(){
   BasicDialog dlg_cls;
    dlg_cls.changeName(QString("Change Attribute"));
    dlg_cls.removeCheckBox();
    dlg_cls.removeLineEdit();
    Class *cls = clsDiagram->getClass(object_id);

    if (cls->attribVector.size() == 0){
        return;
    }

    int att_id;

    for (auto att: cls->attribVector){
        dlg_cls.addItemComboBox(QString::fromStdString(att->getName()));
    }

    if (cls->attribVector.size() == 0){
        QMessageBox::warning(this, "WARNING", "There is no attribute in class");
        return;
    }

    if(dlg_cls.exec() == QDialog::Accepted){
        att_id = cls->getIdByNameAttribute(dlg_cls.getComboBoxContent().toStdString());
    } else {
        return;
    }

    AddAttributeDialog dlg_att;

    Attribute *att = cls->getAttribute(att_id);

    dlg_att.changeName(QString("Change Attribute"));
    dlg_att.changeLineEdit1(QString::fromStdString(att->getName()));
    dlg_att.changeLineEdit2(QString::fromStdString(att->getType()));
    dlg_att.changeComboBox(QString::fromStdString(att->getVisibilityStr()));

    if(dlg_att.exec() == QDialog::Accepted){
        string mod = dlg_att.getComboBoxContent().toStdString();
        QString new_type = dlg_att.getLineEditType();
        QString new_name = dlg_att.getLineEditName();

        Visibility vis = cls->strToVisbility(mod);

        cls->changeAttribute(att_id, vis, new_name.toStdString(), new_type.toStdString());
        repaint();
    }
}

void ClsDiagramWidget::RemoveAttribute(){
    BasicDialog dlg;
    dlg.changeName(QString("Remove Attribute"));
    dlg.removeCheckBox();
    dlg.removeLineEdit();
    Class *cls = clsDiagram->getClass(object_id);

    for (auto att: cls->attribVector){
        dlg.addItemComboBox(QString::fromStdString(att->getName()));
    }

    if (cls->attribVector.size() == 0){
        QMessageBox::warning(this, "WARNING", "There is no attribute in class");
        return;
    }

    if(dlg.exec() == QDialog::Accepted){
        QString q_name = dlg.getComboBoxContent();
        string name = q_name.toStdString();
        Class *cls = clsDiagram->getClass(object_id);
        int att_id = cls->getIdByNameAttribute(name);
        fprintf(stderr, "%d\n", att_id);
        cls->removeAttribute(att_id);
        repaint();
    }
}

void ClsDiagramWidget::AddMethod(){
    AddAttributeDialog dlg;
    dlg.changeName(QString("Add Method"));
    dlg.changeLabel2(QString("Return Type"));

    if(dlg.exec() == QDialog::Accepted){
        Class *cls = clsDiagram->getClass(object_id);
        string mod = dlg.getComboBoxContent().toStdString();
        QString return_type = dlg.getLineEditType();
        QString name = dlg.getLineEditName();

        Visibility vis = cls->strToVisbility(mod);
        vector<string> vec;

        cls->appendMethod(cls->getNextMethodID(), vis, name.toStdString(), return_type.toStdString(), vec);
        repaint();
    }
}

void ClsDiagramWidget::ChangeMethod(){
    BasicDialog dlg_cls;
    dlg_cls.changeName(QString("Change Method"));
    dlg_cls.removeCheckBox();
    dlg_cls.removeLineEdit();
    Class *cls = clsDiagram->getClass(object_id);

    if (cls->methodVector.size() == 0){
        return;
    }

    int met_id;

    for (auto met: cls->methodVector){
        dlg_cls.addItemComboBox(QString::fromStdString(met->getName()));
    }

    if (cls->methodVector.size() == 0){
        QMessageBox::warning(this, "WARNING", "There is no method in class");
        return;
    }

    if(dlg_cls.exec() == QDialog::Accepted){
        met_id = cls->getIdByNameMethod(dlg_cls.getComboBoxContent().toStdString());
    } else {
        return;
    }

    AddAttributeDialog dlg_met;

    Method *met = cls->getMethod(met_id);

    dlg_met.changeName(QString("Change Method"));
    dlg_met.changeLabel2(QString("Return Type"));
    dlg_met.changeLineEdit1(QString::fromStdString(met->getName()));
    dlg_met.changeLineEdit2(QString::fromStdString(met->getReturnType()));
    dlg_met.changeComboBox(QString::fromStdString(met->getVisibilityStr()));

    if(dlg_met.exec() == QDialog::Accepted){
        string mod = dlg_met.getComboBoxContent().toStdString();
        QString return_type = dlg_met.getLineEditType();
        QString name = dlg_met.getLineEditName();
       cout << name.toStdString();
        Visibility vis = cls->strToVisbility(mod);


        cls->changeMethod(met->getID(), vis, name.toStdString(), return_type.toStdString());
        repaint();
    }


}

void ClsDiagramWidget::addParameter(){
    BasicDialog dlg;
    dlg.changeName(QString("Add Parameter to Method"));
    dlg.removeCheckBox();
    dlg.removeLineEdit();
    Class *cls = clsDiagram->getClass(object_id);

    int met_id;

    for (auto met: cls->methodVector){
        dlg.addItemComboBox(QString::fromStdString(met->getName()));
    }

    if (cls->methodVector.size() == 0){
        QMessageBox::warning(this, "WARNING", "There is no method in class");
        return;
    }

    if(dlg.exec() == QDialog::Accepted){

        met_id = cls->getIdByNameMethod(dlg.getComboBoxContent().toStdString());
        repaint();
    }

    BasicDialog dlg_met;
    dlg_met.changeName(QString("Add Parameter to Method"));
    dlg_met.changeLabel(QString("Name"));
    dlg_met.removeCheckBox();
    dlg_met.removeComboBox();

    if(dlg_met.exec() == QDialog::Accepted){
        QString q_name = dlg_met.getLineEditConent();
        Method *met = cls->getMethod(met_id);
        met->addParam(q_name.toStdString());

        repaint();
    }
}

void ClsDiagramWidget::removeParameter(){

    BasicDialog dlg;
    dlg.changeName(QString("Add Parameter to Method"));
    dlg.removeCheckBox();
    dlg.removeLineEdit();
    Class *cls = clsDiagram->getClass(object_id);

    int met_id = -1;

    for (auto met: cls->methodVector){
        dlg.addItemComboBox(QString::fromStdString(met->getName()));
    }

    if (cls->methodVector.size() == 0){
        QMessageBox::warning(this, "WARNING", "There is no method in class");
        return;
    }

    if(dlg.exec() == QDialog::Accepted){
        met_id = cls->getIdByNameMethod(dlg.getComboBoxContent().toStdString());
        repaint();
    } else{
        return;
    }

    BasicDialog dlg_met;
    dlg_met.changeName(QString("Add Parameter to Method"));
    dlg_met.changeLabel(QString("Name"));
    dlg_met.removeCheckBox();
    dlg_met.removeLineEdit();
    Method *met = cls->getMethod(met_id);

    for (auto p: met->vectorParam){
        dlg_met.addItemComboBox(QString::fromStdString(p));
    }

    if (met->vectorParam.size() == 0){
        QMessageBox::warning(this, "WARNING", "There is no paramterer in method");
        return;
    }


    if(dlg_met.exec() == QDialog::Accepted){
        QString q_name = dlg_met.getComboBoxContent();
        met->removeParam(q_name.toStdString());

        repaint();
    }

}

void ClsDiagramWidget::RemoveMethod(){
    BasicDialog dlg;
    dlg.changeName(QString("Remove Method"));
    dlg.removeCheckBox();
    dlg.removeLineEdit();
    Class *cls = clsDiagram->getClass(object_id);

    for (auto met: cls->methodVector){
        dlg.addItemComboBox(QString::fromStdString(met->getName()));
    }

    if (cls->methodVector.size() == 0){
        QMessageBox::warning(this, "WARNING", "There is no method in class");
        return;
    }

    if(dlg.exec() == QDialog::Accepted){
        QString q_name = dlg.getComboBoxContent();
        string name = q_name.toStdString();
        Class *cls = clsDiagram->getClass(object_id);
        int met_id = cls->getIdByNameMethod(name);

        cls->removeMethod(met_id);
        repaint();
    }
}

void ClsDiagramWidget::PopUpMenuWidget(int x, int y){
    QPoint pos(x,y);
    QMenu menu;
    menu.addAction("Add class",this, SLOT(AddClass()));
    menu.addSeparator();
    menu.addAction("Add relation", this, SLOT(AddRelation()));
    menu.addAction("Change relation", this, SLOT(ChangeRelation()));
    menu.addAction("Remove relation", this, SLOT(RemoveRelation()));

    QAction* act = menu.exec(mapToGlobal(pos));
}

void ClsDiagramWidget::AddRelation(){
    AddRelationDialog dlg;

    for (auto cls: clsDiagram->classList){
        dlg.addItemComboBox1(QString::fromStdString(cls->getName()));
        dlg.addItemComboBox2(QString::fromStdString(cls->getName()));
    }

    if (dlg.exec() == QDialog::Accepted){
        string name = dlg.getLineEdit1().toStdString();
        string name_first = dlg.getComboBox1().toStdString();
        string name_second = dlg.getComboBox2().toStdString();

        string card_first = dlg.getLineEdit2().toStdString();
        string card_second = dlg.getLineEdit3().toStdString();
        string rel_type = dlg.getComboBox3().toStdString();

        int first_id = clsDiagram->getIdByNameClass(name_first);
        int second_id = clsDiagram->getIdByNameClass(name_second);

        if (!clsDiagram->checkRelation(first_id, second_id)){
            QMessageBox::warning(this, "WARNING", "Bad combination of classes");
            return;
        }

        clsDiagram->appendRelation(incNextRelID(), first_id, second_id, card_first, card_second, Class::strToRelation(rel_type), name);

        repaint();
    }

}

void ClsDiagramWidget::ChangeRelation(){
    BasicDialog dlg;
    dlg.changeName(QString("Change Method"));
    dlg.removeCheckBox();
    dlg.removeLineEdit();

    int rel_id = -1;

    for (auto *rel: clsDiagram->relationList){
        dlg.addItemComboBox(QString::fromStdString(rel->getName()));
    }

    if (clsDiagram->relationList.size() == 0){
        QMessageBox::warning(this, "WARNING", "There is no relation to change");
        return;
    }

    if(dlg.exec() == QDialog::Accepted){
        rel_id = clsDiagram->getIdByNameRelation(dlg.getComboBoxContent().toStdString());
    } else {
        return;
    }


    ChangeRelationDialog dlg_rel;
    Relation *rel = clsDiagram->getRelation(rel_id);

    dlg_rel.changeLineEdit1(QString::fromStdString(rel->getName()));
    dlg_rel.changeLineEdit2(QString::fromStdString(rel->getCardFirst()));
    dlg_rel.changeLineEdit3(QString::fromStdString(rel->getCardSecond()));
    dlg_rel.changeComboBox(QString::fromStdString(rel->getRelTypeStr()));

    if (dlg_rel.exec() == QDialog::Accepted){
        string name = dlg_rel.getLineEdit1().toStdString();
        string card_first = dlg_rel.getLineEdit2().toStdString();
        string card_second = dlg_rel.getLineEdit3().toStdString();
        string rel_type = dlg_rel.getComboBox().toStdString();

        clsDiagram->changeRelation(rel_id, card_first, card_second, Class::strToRelation(rel_type), name);

        repaint();
    }

}

void ClsDiagramWidget::RemoveRelation(){
    BasicDialog dlg;
    dlg.changeName(QString("Remove Method"));
    dlg.removeCheckBox();
    dlg.removeLineEdit();

    int rel_id = -1;

    for (auto rel: clsDiagram->relationList){
        dlg.addItemComboBox(QString::fromStdString(rel->getName()));
    }

    if (clsDiagram->relationList.size() == 0){
        QMessageBox::warning(this, "WARNING", "There is no relation to delete");
        return;
    }

    if(dlg.exec() == QDialog::Accepted){
        rel_id = clsDiagram->getIdByNameRelation(dlg.getComboBoxContent().toStdString());
        clsDiagram->destroyRelation(rel_id);
        repaint();
    }

}

void ClsDiagramWidget::AddClass(){
    BasicDialog dlg;
    dlg.changeName(QString("Add Class"));
    dlg.removeComboBox();

    if(dlg.exec() == QDialog::Accepted){
        QString q_name = dlg.getLineEditConent();
        if (q_name.size() == 0){
            QMessageBox::warning(this, "WARNING", "Empty line edit");
            AddClass();
            return;
        }
        string name = q_name.toStdString();
        Class *cls = clsDiagram->appendClass(name, incNextClassID(), dlg.getInterface());
        cls->setPosition(mousex, mousey);

        repaint();
    }
}


