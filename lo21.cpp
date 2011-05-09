#include "lo21.hpp"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>

#include "lo21.hpp"

lo21::lo21() : QMainWindow(0, 0), timer(this), scene(0, 0, 640, 440), view(this)
{
	view.setScene(&scene);
	setCentralWidget(&view);

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

