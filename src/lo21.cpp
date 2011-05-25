#include "lo21.hpp"

#include <QDebug>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QMessageBox>
#include <QGLFormat>
#include <cmath>

#include "ressources.hpp"
#include "tile.hpp"
#include "enemy.hpp"
#include "tower.hpp"
#include "factory.hpp"
#include "missile.hpp"

lo21::lo21()
 : QMainWindow(0, 0), timer(this), scene(this), view(this), dock(this), timeUntilNextWave(-1),selectedTower(Tower::NONE)
{
    //Init des tableaux
    for (int i = 0 ; i < MAP_SIZE ; i++)
        for (int j = 0 ; j < MAP_SIZE ; j++)
            tileMap[i][j] = NULL;

    //Config par defaut
    lives = 10;
    credits = 100; /* valeur inconnue ? */

    loadMap("ressources/map.txt");
    loadWaves("ressources/waves.txt");

    //Ajout de la scene en tant que widget principale
    //scene.setSceneRect(0, 0, 300, 300);
    view.setScene(&scene);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	setCentralWidget(&view);

    //Ajout du dock des options de jeu
    dock.setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, &dock);
    dock.ui->lcdNumber->display(credits);
    dock.ui->lcdNumber_2->display(lives);

    for ( int i = 0 ; i < MAP_SIZE ; i++ )
        for ( int j = 0 ; j < MAP_SIZE ; j++ )
            if ( tileMap[i][j] != NULL && tileMap[i][j]->isStartPoint() )
                start = tileMap[i][j];


    timer.start(1000.0/FREQUENCY);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    connect(this, SIGNAL(advance_scene()),&scene,SLOT(advance()));

    connect(dock.ui->launchWave,SIGNAL(clicked()),this,SLOT(launchWave()));
    connect(dock.ui->SelectWater,SIGNAL(clicked()),this,SLOT(selectTowerWater()));
    connect(dock.ui->SelectRock,SIGNAL(clicked()),this,SLOT(selectTowerRock()));
    connect(dock.ui->SelectPaint,SIGNAL(clicked()),this,SLOT(selectTowerPaint()));
    connect(dock.ui->SelectPetanque,SIGNAL(clicked()),this,SLOT(selectTowerPetanque()));
    connect(dock.ui->Upgrade,SIGNAL(clicked()),this,SLOT(upgradeTower()));
    connect(dock.ui->Sell,SIGNAL(clicked()),this,SLOT(sellTower()));

    connect(&scene,SIGNAL(clickOnScene(int,int)),this,SLOT(clickOnScene(int,int)));
}

void lo21::addCredit(int c)
{
	credits+=c;
	dock.ui->lcdNumber->display(credits);
}

void lo21::subLive(int l)
{
	lives-=l;
	dock.ui->lcdNumber_2->display(lives);
	if(lives<=0)
	{
		QMessageBox(QMessageBox::Warning,tr("Perdu"),
				tr("Vous etes une merde")).exec();
	}
}



void lo21::addObject(Object* o)
{
	scene.addItem(o);
}

void lo21::addObject(Enemy *o)
{
	this->addObject((Object*)o);
	this->enemyList.push_back(o);
}

void lo21::removeObject(Object* o)
{
	qDebug() << "removeObject called"; 
	
	if (o != NULL)
	{
		scene.removeItem(o);
		// delete o;
	}
}

void lo21::removeObject(Enemy *o)
{
	this->enemyList.removeOne(o);
	this->removeObject((Object*)o);
}

bool lo21::isEnemy(void *o) const
{
	for ( int i = 0 ; i < enemyList.size() ; i++ )
		if ( enemyList[i] == o ) 
			return true;
	
	return false;
}

const Enemy* lo21::getClosestEnemy(int x, int y) const
{
	Enemy *e = NULL;
	
	for ( unsigned int distance = -1, i = 0 ; i < enemyList.size() ; i++ )
	{
		unsigned int tmp = (enemyList[i]->getCenterPos() - QPoint(x,y)).manhattanLength(); 
		
		if ( tmp < distance )
		{
			e = enemyList[i];
			distance = tmp;
		}
	}

	return e;
}

void lo21::selectTowerPaint()
{
    if (selectedTower == Tower::PAINTBALL)
	{
		selectedTower = Tower::NONE;
		dock.ui->SelectPaint->setPalette( dock.ui->SelectPetanque->palette() );
        return;
	}

    QPalette p=dock.ui->SelectPaint->palette();
    dock.ui->SelectPaint->setPalette(QPalette(Qt::red));
    dock.ui->SelectRock->setPalette(p);
    dock.ui->SelectWater->setPalette(p);
    dock.ui->SelectPetanque->setPalette(p);
    selectedTower = Tower::PAINTBALL;
}

void lo21::selectTowerPetanque()
{
    if (selectedTower == Tower::PETANQUEPLAYER)
	{
		selectedTower = Tower::NONE;
		dock.ui->SelectPetanque->setPalette( dock.ui->SelectPaint->palette() );
        return;
	}

    QPalette p=dock.ui->SelectPetanque->palette();
    dock.ui->SelectPaint->setPalette(p);
    dock.ui->SelectRock->setPalette(p);
    dock.ui->SelectWater->setPalette(p);
    dock.ui->SelectPetanque->setPalette(QPalette(Qt::red));
    selectedTower = Tower::PETANQUEPLAYER;

}
void lo21::selectTowerRock()
{
    if (selectedTower == Tower::SLINGSHOT)
	{
		selectedTower = Tower::NONE;
		dock.ui->SelectRock->setPalette( dock.ui->SelectPaint->palette() );
        return;
	}

    QPalette p=dock.ui->SelectRock->palette();
    dock.ui->SelectPaint->setPalette(p);
    dock.ui->SelectRock->setPalette(QPalette(Qt::red));
    dock.ui->SelectWater->setPalette(p);
    dock.ui->SelectPetanque->setPalette(p);
    selectedTower = Tower::SLINGSHOT;
}

void lo21::selectTowerWater()
{
    if (selectedTower == Tower::WATERGUN)
	{
		selectedTower = Tower::NONE;
		dock.ui->SelectWater->setPalette( dock.ui->SelectPetanque->palette() );
        return;
	}

    QPalette p=dock.ui->SelectWater->palette();
    dock.ui->SelectPaint->setPalette(p);
    dock.ui->SelectRock->setPalette(p);
    dock.ui->SelectWater->setPalette(QPalette(Qt::red));
    dock.ui->SelectPetanque->setPalette(p);
    selectedTower = Tower::WATERGUN;
}

void lo21::upgradeTower()
{
	if (selectedTile != NULL)
	{
		Tower *tw = selectedTile->getTower();
		
		if (tw->getUpgradedAttribute().cost <= this->credits)
		{
			this->credits -= tw->getUpgradedAttribute().cost;
			dock.ui->lcdNumber->display(this->credits);
			tw->upgrade();
			selectTile(selectedTile);
		}
	}
}

void lo21::sellTower()
{
	if (selectedTile != NULL && selectedTile->getTower() != NULL)
	{
		this->credits += selectedTile->getTower()->sell();
		dock.ui->lcdNumber->display(this->credits);
		
		selectedTile->deleteTower();
		selectTile();
	}
}

void lo21::clickOnScene(int x, int y)
{
	Tile *t = this->getTile(x,y);

	// construction d'une tour
	if (selectedTower != Tower::NONE && t != NULL) 
	{
		Tower *tw = Factory::getTower(selectedTower,this);
		
		if (tw == NULL)
		{
			qDebug() << "erreur a la creation de la tour";
			this->selectTile(NULL);
		}
		else if (tw->getAttribute().cost > this->credits)
		{
			QMessageBox(QMessageBox::Warning,tr("Plus de credits"),
				tr("Vous n'avez pas assez de credits pour acheter cette tour")).exec();
			this->selectTile(NULL);
			delete tw;
		}
		else if (!t->buildTower(tw))
		{
			QMessageBox(QMessageBox::Warning,tr("Impossible de construire ici"),
				tr("Vous ne pouvez pas construire une tour a cet endroit")).exec();
			this->selectTile(NULL);
			delete tw;
		}
		else
		{
			this->credits -= tw->getAttribute().cost;
			dock.ui->lcdNumber->display(this->credits);
			this->selectTile(t);
		}
	}
	// selection d'un tile
	else
	{
		this->selectTile(t);
	}
}

void lo21::selectTile(Tile *t)
{
	this->selectedTile = t;

	if (t == NULL or t->getTower() == NULL)
	{
		this->dock.ui->groupBox_2->setEnabled(false);
		this->dock.ui->label_edition->setText("pas de selection");
	}
	else
	{
		// affichage
		this->dock.ui->groupBox_2->setEnabled(true);
		this->dock.ui->Upgrade->setEnabled((selectedTile->getTower()->getUpgradedAttribute().cost <= this->credits));

		// mise a jour label
		this->dock.ui->label_edition->setText(
			"prix amelioration: " + QString::number(t->getTower()->getUpgradedAttribute().cost) +"<br />"
			+ "prix de vente: " + QString::number(t->getTower()->getAttribute().sellprice)
			);
	}
}

const Tile* lo21::getStart() const
{
    return start;
}


void lo21::updateGame()
{
    if (!waves.empty())
    {
        //Si la vague en cours est vide, on passe à la suivante.
        if (waves.first().end())
        {
            waves.pop_front();
            timeUntilNextWave=TIME_BETWEEN_WAVES*FREQUENCY;
        }

        if (timeUntilNextWave==0)
        {
            dock.ui->waveComment->setText(waves.first().getComment());
            if (waves.first().tick())
            {
                Enemy *e = waves.first().getEnemy(this);
                this->addObject(e);
            }
        }
        else if (timeUntilNextWave>0)
            timeUntilNextWave--;
    }

    emit advance_scene();
}

void lo21::launchWave()
{
    timeUntilNextWave=0;
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
        QMessageBox(QMessageBox::Warning, tr("Impossible de charger la carte"), tr("Impossible d'ouvrir le fichier de la carte")).exec();
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
				else if ( value == 32 )
				{
				    tileMap[x][y] = new Goal(this);
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

                    if ( value & 16 )
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

void lo21::loadWaves(const QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox(QMessageBox::Warning, tr("Impossible de charger les vagues"), tr("Impossible d'ouvrir le fichier des vagues")).exec();
        return;
    }

    while (!file.atEnd())
    {
        QString rawLine=file.readLine();
        QStringList line = rawLine.split(';', QString::SkipEmptyParts);
        QString comment=line.first();

        line.pop_front(); //On vire le commentaire de debut
        QStringListIterator itLine(line);

        while (itLine.hasNext())
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
    int xi = (x - (x % TILE_SIZE)) / TILE_SIZE;
    int yi = (y - (y % TILE_SIZE)) / TILE_SIZE;

    if ( xi < MAP_SIZE && yi < MAP_SIZE )
        return tileMap[xi][yi];
    else
        return NULL;
}

Tile* lo21::getTile(int x, int y)
{
    int xi = (x - (x % TILE_SIZE)) / TILE_SIZE;
    int yi = (y - (y % TILE_SIZE)) / TILE_SIZE;

    if ( xi < MAP_SIZE && yi < MAP_SIZE )
        return tileMap[xi][yi];
    else
        return NULL;
}

#include "lo21.moc"

