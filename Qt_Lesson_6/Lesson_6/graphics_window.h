#ifndef GRAPHICSWINDOW_H
#define GRAPHICSWINDOW_H

#include <QDebug>
#include <QWidget>
#include <QVector>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "figure.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = 0);
    ~GraphicsScene();

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    private:

};

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    MyGraphicsView(QWidget *parent = nullptr);
   ~MyGraphicsView();

private:
    GraphicsScene *scene{nullptr};
    Figure *figure;

private Q_SLOTS:
    void reDraw();
    //QVector<*Figure> vecOfFigures;
};

#endif // GRAPHICSWINDOW_H
