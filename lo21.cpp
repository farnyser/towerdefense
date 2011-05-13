#include "lo21.hpp"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>


lo21::lo21() : QMainWindow(0, 0), timer(this), scene(this), view(this), dock(this)
{
	//Ajout de la scene en tant que widget principale
	scene.setSceneRect(0, 0, 700, 700);
	view.setScene(&scene);
	setCentralWidget(&view);

	//Ajout du dock des options de jeu
	dock.setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	dock.setMinimumWidth(200);
	addDockWidget(Qt::RightDockWidgetArea, &dock);

	Object *b = new Bug();
	b->setPos(50, 100);
	scene.addItem(b);

	Object *bee = new Bee();
	bee->setPos(150, 150);
	scene.addItem(bee);

	Object *ant = new Ant();
	ant->setPos(250, 350);
	scene.addItem(ant);


	timer.start(1000.0 / 50.0);
	connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

lo21::~lo21()
{
}

void lo21::update()
{
	// foreach Object (on the scene), call advance
	emit scene.advance();
}


#include "lo21.moc"

