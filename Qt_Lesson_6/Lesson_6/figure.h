#ifndef FIGURE_H
#define FIGURE_H

#include <QBrush>
#include <QPoint>
#include <QPointF>
#include <QObject>
#include <QCursor>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)

public:
    explicit Figure(QPointF p, QObject *parent = nullptr);
    void setBrush(QBrush brush) {this->brush = brush; emit reDraw();}

signals:
    void reDraw();

private:
    QBrush brush;
    QPointF m_point;
    enum figureType{RECTANGLE, ELLIPS, STAR};
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    figureType m_figureType;
    QRectF boundingRect() const override;

};

#endif // FIGURE_H
