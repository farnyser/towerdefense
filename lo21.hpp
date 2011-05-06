#ifndef lo21_H
#define lo21_H

#include <QtGui>
#include <QGraphicsView>

#include "object.hpp"

class lo21 : public QMainWindow
{
Q_OBJECT
public:
    lo21();
    virtual ~lo21();
    
private:
  QGraphicsView view;
  QGraphicsScene scene;
};

#endif // lo21_H

