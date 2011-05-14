#include "lo21.hpp"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>


lo21::lo21() : QMainWindow(0, 0), timer(this), scene(this), view(this), dock(this)
{
	//Init des tableaux
	for (int i = 0 ; i < MAP_SIZE ; i++)
		for (int j = 0 ; j < MAP_SIZE ; j++)
			tileMap[i][j] = NULL;

	//Config par defaut
	frequency = 50.0;

	lives = 10;

	credits = 100; /* valeur inconnue ? */

	loadMap("ressources/map.txt");

	loadWaves("ressources/waves.txt");

	//Ajout de la scene en tant que widget principale
	scene.setSceneRect(0, 0, 700, 700);

	view.setScene(&scene);

	setCentralWidget(&view);

	//Ajout du dock des options de jeu
	dock.setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	dock.setMinimumWidth(200);

	addDockWidget(Qt::RightDockWidgetArea, &dock);

	QList<QPixmap> pxmGrass;

	pxmGrass.push_back(QPixmap("ressources/images/herbe.jpg"));

	Grass *g = new Grass(pxmGrass);

	scene.addItem(g);

	Object *b = new Bug();

	b->setPos(50, 100);

	scene.addItem(b);

	Object *bee = new Bee();

	bee->setPos(150, 150);

	scene.addItem(bee);

	Object *ant = new Ant();

	ant->setPos(250, 350);

	scene.addItem(ant);


	timer.start(1000.0 / frequency);

	connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

lo21::~lo21()
{
}

//
// METHODES
//

void lo21::loadMap(const QString &path)
{
	QFile map(path);
	int x = 0, y = 0;

	if (!map.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox(QMessageBox::Warning, tr("Impossible de charger la carte"), tr("Impossible d'ouvrir le fichier de la carte"));
		return;
	}

	while (!map.atEnd())
	{
		QString line(map.readLine());
		QStringList tiles = line.split(' ', QString::SkipEmptyParts);
		QStringListIterator it(tiles);

		while (it.hasNext())
		{
			switch (it.next().toInt())
			{
			case 0:
				scene.addRect(30*x, 30*y, 30, 30, QPen(Qt::darkGreen), QBrush(Qt::green));
				break;
			case 64:
				scene.addRect(30*x, 30*y, 30, 30, QPen(Qt::darkBlue), QBrush(Qt::blue));
				break;
			default:
				scene.addRect(30*x, 30*y, 30, 30, QPen(Qt::black), QBrush(Qt::yellow));
			}

			x++;
		}

		x = 0;

		y++;
	}
}

void lo21::loadWaves(const QString &path)
{

}

//
// SLOTS
//

void lo21::update()
{
	// foreach Object (on the scene), call advance
	emit scene.advance();
}


#include "lo21.moc"

