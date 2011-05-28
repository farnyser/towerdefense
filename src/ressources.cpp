#include "ressources.hpp"
#include "lo21.hpp" /* for const */

Ressources *Ressources::_singleton = NULL;

Ressources::Ressources()
{
	QList<QPixmap> bug, ant, bee, mosquito, 
		grass, mud, road, end, 
		watergun, slingshot, petanque, paintball,
		angrybird;

    bug.push_back(QPixmap("ressources/images/cafard1.png"));
	bug.push_back(QPixmap("ressources/images/cafard2.png"));
    bug.push_back(QPixmap("ressources/images/cafard3.png"));
	animatedPixmap["bug"] = bug;
	animatedInterval["bug"] = 8;
		
	ant.push_back(QPixmap("ressources/images/fourmi1.png"));
    ant.push_back(QPixmap("ressources/images/fourmi2.png"));
    ant.push_back(QPixmap("ressources/images/fourmi3.png"));
	animatedPixmap["ant"] = ant;
	animatedInterval["ant"] = 8;

    bee.push_back(QPixmap("ressources/images/guepe1.png"));
    bee.push_back(QPixmap("ressources/images/guepe2.png"));
	animatedPixmap["bee"] = bee;
	animatedInterval["bee"] = 8;

	mosquito.push_back(QPixmap("ressources/images/moustiquevolant1.png"));
    mosquito.push_back(QPixmap("ressources/images/moustiquevolant2.png"));
	animatedPixmap["mosquito"] = mosquito;
	animatedInterval["mosquito"] = 8;

	mud.push_back(QPixmap("ressources/images/boue.png").scaled(TILE_SIZE, TILE_SIZE));
	animatedPixmap["mud"] = mud;
	animatedInterval["mud"] = 1;

	grass.push_back(QPixmap("ressources/images/herbe.jpg").scaled(TILE_SIZE, TILE_SIZE));
	animatedPixmap["grass"] = grass;
	animatedInterval["grass"] = 1;

	road.push_back(QPixmap("ressources/images/sand.png").scaled(TILE_SIZE, TILE_SIZE));
	animatedPixmap["road"] = road;
	animatedInterval["road"] = 1;

	end.push_back(QPixmap("ressources/images/but.png").scaled(TILE_SIZE, TILE_SIZE));
	animatedPixmap["end"] = end;
	animatedInterval["end"] = 1;
	
	watergun.push_back(QPixmap("ressources/images/watergun.png").scaled(TILE_SIZE, TILE_SIZE));
	animatedPixmap["watergun"] = watergun;
	animatedInterval["watergun"] = 1;

	slingshot.push_back(QPixmap("ressources/images/slingshot.png").scaled(TILE_SIZE, TILE_SIZE));
	animatedPixmap["slingshot"] = slingshot;
	animatedInterval["slingshot"] = 1;

	paintball.push_back(QPixmap("ressources/images/paintball.png").scaled(TILE_SIZE, TILE_SIZE));
	animatedPixmap["paintball"] = paintball;
	animatedInterval["paintball"] = 1;

	petanque.push_back(QPixmap("ressources/images/petanque.png").scaled(TILE_SIZE, TILE_SIZE));
	animatedPixmap["petanque"] = petanque;
	animatedInterval["petanque"] = 1;
	
	angrybird.push_back(QPixmap("ressources/images/angrybird.png").scaled(TILE_SIZE/2.0, TILE_SIZE/2.0));
	animatedPixmap["angrybird"] = angrybird;
	animatedInterval["angrybird"] = 1;
}


Ressources* Ressources::getInstance()
{
	if (NULL == _singleton)
		_singleton =  new Ressources;

	return _singleton;
}

QList<QPixmap> Ressources::getAnimatedPixmap(QString name)
{
	Ressources *r = Ressources::getInstance();
	return r->animatedPixmap[name];
}

int Ressources::getAnimatedInterval(QString name)
{
	Ressources *r = Ressources::getInstance();
	return r->animatedInterval[name];
}
