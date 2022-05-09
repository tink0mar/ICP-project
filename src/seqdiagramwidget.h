#ifndef SEQDIAGRAMWIDGET_H
#define SEQDIAGRAMWIDGET_H

#include <QWidget>
#include <QPainter>
#include "QMouseEvent"
#include "seqdiagram.h"
#include "seqevent.h"
#include "seqobject.h"

/**
 * @brief SeqDiagramWidget class used to create a widget for sequence diagram.
 */
class SeqDiagramWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor.
     * @param parent Parent window.
     */
    explicit SeqDiagramWidget(QWidget *parent = nullptr);

    /**
     * @brief Draws object.
     * @param painter Graphic context.
     * @param o Object.
     */
    void DrawObject(QPainter *painter, SeqObject o);

    /**
     * @brief Returns ID of the object, above which the cursor is.
     * @param kX X coordination of cursor.
     * @param kY Y coordination of cursor.
     * @return ID of the object.
     */
    int AboveObject(int kX, int kY);

    /**
     * @brief Returns ID of the object, above which the cursor is.
     * @param kX X coordination of cursor.
     * @param kY Y coordination of cursor.
     * @return ID of the object.
     */
    int AboveCorner(int kX, int kY);

    /**
     * @brief Calculates base.
     */
    void FindBase();

    /**
     * @brief Draws event.
     * @param painter Graphic context.
     * @param evt Event.
     */
    void DrawEvent(QPainter *painter, SeqEvent evt);

    /**
     * @brief Popup menu.
     * @param x X coordination.
     * @param y Y coordination.
     */
    void PopupMenu1(int x, int y);

    /**
     * @brief Shortens string to fit in.
     * @param src Source.
     * @param metrics Metrics.
     * @param maxX Max length.
     * @return Formated string.
     */
    QString FormatString(QString src, QFontMetrics metrics, int maxX);

    /**
     * @brief Returns position of activation.
     * @param objID ID of the object.
     * @param from Order, from which the search begins.
     * @return Order of the activation.
     */
    int FindActivation(int objID, int from);

    /**
     * @brief Returns position of deactivation.
     * @param objID ID of the object.
     * @param from Order, from which the search begins.
     * @return Order of the deactivation.
     */
    int FindDeactivation(int objID, int from);

    /**
     * @brief Draws activation.
     * @param painter Graphic context.
     * @param sx X coordination.
     * @param objID ID of the object.
     */
    void DrawActive(QPainter* painter, int sx, int objID);

    /**
     * @brief Returns, whether cursor is above object.
     * @param kX X coordination of cursor.
     * @param kY Y coordination of cursor.
     * @param o Object.
     * @return
     */
    bool InObject(int kX, int kY, SeqObject o);

    /**
     * @brief Popup menu for object.
     * @param x X coordination.
     * @param y Y coordination.
     */
    void PopupMenu2(int x, int y);

    /**
     * @brief Returns ID of the event under.
     * @param kX X coordination of cursor.
     * @param kY Y coordination of cursor.
     * @return ID of the event.
     */
    int EventUnderCursor(int kX, int kY);

    /**
     * @brief Popup menu for event.
     * @param x X coordination.
     * @param y Y coordination.
     */
    void PopupMenu3(int x, int y);

    /**
     * @brief Creates new sequence diagram.
     * @param name Name of the diagram.
     * @param classD Class diagram.
     */
    void CreateNewSeqDiagram(QString name, DiagramClass *classD);

    /**
     * @brief Returns sequence diagram.
     * @return Sequence diagram.
     */
    SeqDiagram *GetDiagram();

    /**
     * @brief Loads sequence diagram.
     * @param filename Name of the file.
     * @param classD Class diagram.
     */
    void LoadSeqDiagram(QString filename, DiagramClass *classD);

    /**
     * Destructor.
     */
    ~SeqDiagramWidget();

public slots:
    /**
     * @brief Adds object.
     */
    void AddObject();

    /**
     * @brief Adds event.
     */
    void AddEvent();

    /**
     * @brief Edits object.
     */
    void EditObject();

    /**
     * @brief Adds activation.
     */
    void AddActivation();

    /**
     * @brief Adds deactivation.
     */
    void AddDeactivation();

    /**
     * @brief Edits message.
     */
    void EditMessage();

    /**
     * @brief Deletes event.
     */
    void DeleteEvent();

    /**
     * @brief Deletes object.
     */
    void DeleteObject();

protected:
    /**
     * @brief Draws sequence diagram.
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Changes cursor or drags object or event.
     * @param event Event.
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief Reaction to pressing a mouse button.
     * @param event Event.
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief Reaction to releasing a mouse button.
     * @param event Event.
     */
    void mouseReleaseEvent(QMouseEvent *event);

private:
    /**
     * @brief Sequence diagram.
     */
    SeqDiagram* sDiagram;

    /**
     * @brief Class diagram.
     */
    DiagramClass* classD;

    /**
     * @brief Indicator of dragging.
     */
    bool dragging;

    /**
     * @brief X coordination of mouse/cursor.
     */
    int mousex;

    /**
     * @brief Y coordination of mouse/cursor.
     */
    int mousey;

    /**
     * @brief ID of the object.
     */
    int cornerObjectID;

    /**
     * @brief ID of the object.
     */
    int insideObjectID;

    /**
     * @brief ID of the event.
     */
    int eventID;

    /**
     * @brief Base.
     */
    int baseY;

    /**
     * @brief Coordination of click.
     */
    int clickx;

    /**
     * @brief Type of the event.
     */
    QStringList evtTypes;
};

#endif // SEQDIAGRAMWIDGET_H
