#include "lo21.hpp"

#include <QDebug>
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
	lives = 10;
	credits = 100; /* valeur inconnue ? */
	frequency = 50;

	loadMap("ressources/map.txt");

	//Ajout de la scene en tant que widget principale
	//scene.setSceneRect(0, 0, 300, 300);
	view.setScene(&scene);
	view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setCentralWidget(&view);

	//Ajout du dock des options de jeu
	dock.setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea, &dock);


	for ( int i = 0 ; i < MAP_SIZE ; i++ )
		for ( int j = 0 ; j < MAP_SIZE ; j++ )
			if ( tileMap[i][j] != NULL && tileMap[i][j]->isStartPoint() )
				start = tileMap[i][j];
	

	timer.start(1000.0/frequency);
	connect(&timer, SIGNAL(timeout()), this, SLOT(updateGame()));
	connect(this, SIGNAL(advance_scene()),&scene,SLOT(advance()));
	
	connect(dock.ui->launchWave,SIGNAL(clicked()),this,SLOT(loadWaves()));
}

const Tile* lo21::getStart() const
{
	return start;
}


void lo21::updateGame()
{
	
	if(!waves.empty())
		if(waves.first().end())
			waves.pop_front();
	
	if(!waves.empty())
	{
		dock.ui->waveComment->setText(waves.first().getComment());
		if(waves.first().tick())
		{
			Enemy* e=waves.first().getEnemy(this);
			e->setScale(0.3);
			e->setPos(start->pos() + start->getCenterPos());
			scene.addItem(e);
		}
	}
	
	emit advance_scene();
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
		map.close();
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

					vec2f vector;
					vector.first.setX((value&8)? 1 : 0);
					vector.first.setY((value&1)? 1 : 0);
					vector.second.setX((value&4)? 1 : 0);
					vector.second.setY((value&2)? 1 : 0);
					r->setVector(vector);
					
					if ( value == 32 ) 
						r->setEnd();
					else if ( value & 16 )
						r->setStart();
				}

				x++;
			}
		}

		x = 0;
		y++;
	}
	map.close();
}

void lo21::loadWaves()
{
	QFile file("ressources/waves.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox(QMessageBox::Warning, tr("Impossible de charger les vagues"), tr("Impossible d'ouvrir le fichier des vagues"));
		return;
	}
	
	while (!file.atEnd())
	{
		QString rawLine=file.readLine();
		QStringList line = rawLine.split(';', QString::SkipEmptyParts);
		QString comment=line.first();

		line.pop_front(); //On vire le commentaire de debut 
		QStringListIterator itLine(line);
		
		while(itLine.hasNext())
		{
			QStringList wave=itLine.next().split(':', QString::SkipEmptyParts);
			
				this->waves.push_back(
										Wave(comment,
											wave[0],			//Type d'insect
											wave[1].toFloat(),	//taille
											wave[2].toInt(),	//Nombre
											wave[3].toInt()		//Interval
											)
									);
		}
	
	}
	
	file.close();
}

const Tile* lo21::getTile(int x, int y) const
{
	int xi = x / TILE_SIZE;
	int yi = y / TILE_SIZE;

	if ( xi < MAP_SIZE && yi < MAP_SIZE )
		return tileMap[xi][yi];
	else
		return NULL;
}

#include "lo21.moc"

