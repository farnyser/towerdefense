#include "lo21.hpp"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>


lo21::lo21() : QMainWindow(0, 0), timer(this), scene(0, 0, 640, 440), view(this), dock(this)
{
	//Ajout de la scene en tant que widget principale
	view.setFixedSize(700, 700);
	view.setScene(&scene);
	setCentralWidget(&view);

	//Ajout du dock des options de jeu
	dock.setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	dock.setMinimumWidth(150);
	addDockWidget(Qt::RightDockWidgetArea, &dock);

	Object *b = new Object();
	b->setPos(50, 100);
	scene.addItem(b);

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


