#ifndef lo21_H
#define lo21_H

#include <QtGui>
#include <QGraphicsView>

#include "object.hpp"
#include "tower.hpp"
#include "enemy.hpp"
#include "dock.hpp"
#include "gamescene.hpp"

class lo21 : public QMainWindow
{
	Q_OBJECT
public:
	lo21();
	virtual ~lo21();

private:
	QGraphicsView view;
	GameScene scene;
	QTimer timer;
	Dock dock;

private slots:
	void update();
};

#endif // lo21_H

