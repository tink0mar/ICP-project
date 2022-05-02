#include "clsdgrwidget.h"


clsdgrWidget::clsdgrWidget()
{
    sx=100;
    sy=100;
    vx=100;
    vy=100;
    dragging=false;
    setMouseTracking(true);
}

void clsdgrWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawRect(sx-vx/2,sy-vy/2,vx,vy);
}

void clsdgrWidget::mouseMoveEvent(QMouseEvent *event)
{
    int mx=event->x();
    int my=event->y();
    if(dragging){
        if(vnutri){
            sx+=(mx-mousex);
            sy+=(my-mousey);
            mousex=mx;
            mousey=my;
            repaint();
        } else if(vrohu){
            vx+=(mx-mousex)*2;
            vy+=(my-mousey)*2;
            mousex=mx;
            mousey=my;
            repaint();
        }

    } else {
        vrohu=false;
        vnutri=false;
        if(mx>sx+vx/2-10 && mx<sx+vx/2+10 && my>sy+vy/2-10 && my<sy+vy/2+10){
            setCursor(Qt::SizeFDiagCursor);
            vrohu=true;
        } else if(mx>sx-vx/2 && mx<sx+vx/2 && my>sy-vy/2 && my<sy+vy/2){
            setCursor(Qt::SizeAllCursor);
            vnutri=true;
        } else {
            setCursor(Qt::ArrowCursor);
        }
    }
    event->accept();
}

void clsdgrWidget::mousePressEvent(QMouseEvent *event)
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

void clsdgrWidget::mouseReleaseEvent(QMouseEvent *event){
    //int mx=event->x();
    //int my=event->y();
    if(event->button()==Qt::LeftButton){
        dragging=false;
    }
    event->accept();
}
