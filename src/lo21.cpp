#include "lo21.hpp"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>

#include "ressources.hpp"

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


	Tile *t;

	Object *b = new Bug(this);
	b->setPos(50, 100);
	scene.addItem(b);


	Object *bee = new Bee(this);
	bee->setPos(150, 150);
	scene.addItem(bee);

	Object *ant = new Ant(this);
	ant->setPos(250, 350);
	scene.addItem(ant);

	timer.start(1000.0 / frequency);
	connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
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
			QString itn = it.next();
			int value = itn.toInt();

			// end of map (not integer) should be ignored
			if (x < MAP_SIZE and y < MAP_SIZE)
			{
				if ( value == 0 )
				{
					tileMap[x][y] = new Grass(this);
					tileMap[x][y]->setPos(TILE_SIZE*x, TILE_SIZE*y);
					scene.addItem(tileMap[x][y]);
				}
				else if ( value == 64 )
				{
					tileMap[x][y] = new Mud(this);
					tileMap[x][y]->setPos(TILE_SIZE*x, TILE_SIZE*y);
					scene.addItem(tileMap[x][y]);
				}
				else
				{
					Road *r = new Road(this);
					tileMap[x][y] = r;
					tileMap[x][y]->setPos(TILE_SIZE*x, TILE_SIZE*y);
					scene.addItem(tileMap[x][y]);

					vec2i vector;
					vector.first.setX(0);
					vector.first.setY(0);
					vector.second.setX(0);
					vector.second.setY(0);
	
					if ( value == 32 ) 
					{
						r->setEnd();
					}
					else
					{
						if ( value & 16 )
							r->setStart();

						if ( value & 1 )
							vector.second.setY(1);
						else if ( value & 2 )
							vector.first.setY(1);
						if ( value & 4 )
							vector.second.setX(1);
						else if ( value & 8 )
							vector.first.setX(1);
					
						r->setVector(vector);
					}
				}

				x++;
			}
		}

		x = 0;
		y++;
	}
}

void lo21::loadWaves(const QString &path)
{

}

const Tile * lo21::getTile(int x, int y) const
{
	int xi = x % TILE_SIZE;
	int yi = y % TILE_SIZE;

	if ( xi < MAP_SIZE && yi < MAP_SIZE )
		return tileMap[xi][yi];
	else
		return NULL;
}

#include "lo21.moc"

