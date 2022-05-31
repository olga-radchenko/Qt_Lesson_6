#include "graphics_window.h"

MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    resize(800, 600);
    scene = new  GraphicsScene(this);
    setScene(scene);
    scene->setSceneRect(0,0,50,50);
    setMouseTracking(true);
    /*
    figure = new Figure(this);
    scene->addItem(figure);*/
}

MyGraphicsView::~MyGraphicsView()
{
    delete this;
}

void MyGraphicsView::reDraw()
{
    scene->update();
    update();
}

//void MyGraphicsView::mousePressEvent(QMouseEvent *event)
//{
//    if(event->buttons() == Qt::LeftButton)
//    {
//        scene->addItem(new Figure(event->scenePos(), this));
//    }
//}

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

GraphicsScene::~GraphicsScene()
{
    qDebug() << "deleted scene";
}


void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

      if (mouseEvent->button() == Qt::LeftButton)
      {
          QPointF pt = mouseEvent->scenePos();
          this->addItem(new Figure(pt, this));
      }
}
