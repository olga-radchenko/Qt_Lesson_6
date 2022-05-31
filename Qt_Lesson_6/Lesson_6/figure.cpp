#include "figure.h"
#include <QDebug>
#include<QWidget>

Figure::Figure(QPointF p, QObject *parent) : QObject(parent), QGraphicsItem()
{
    brush.setColor(Qt::BrushStyle::SolidPattern);
    m_figureType = figureType::RECTANGLE;
    m_point = p;
    setPos(p);
}
void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(brush);
    if (m_figureType == figureType::RECTANGLE) {m_figureType = figureType::ELLIPS; painter->drawRect(m_point.x(), m_point.y(), 200, 100);}
    if (m_figureType == figureType::ELLIPS){m_figureType = figureType::RECTANGLE; painter->drawRect(m_point.x(), m_point.y(), 200, 100);}

}

QRectF Figure::boundingRect() const
{
    return QRectF(m_point.x(), m_point.y(), 200, 100);
}
