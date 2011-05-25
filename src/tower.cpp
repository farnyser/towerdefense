#include "tower.hpp"
#include <cmath>
#include "missile.hpp"

//
// Tower
//

Tower::Tower(lo21* game, QList< QPixmap > pixmaps)
 : 
  Object(game, pixmaps), 
  timeUntilNextFire(0)
{
}

Tower::Attribute Tower::getAttribute() const
{
	return this->attr;
}

Tower::Attribute Tower::getUpgradedAttribute() const
{
	return this->computeAttribute(this->attr.level+1);
}

int Tower::upgrade()
{
	this->attr = computeAttribute(this->attr.level+1);
	return this->attr.cost;
}

int Tower::sell()
{
	return this->attr.sellprice;
}

void Tower::action()
{
	// remise a '0' du compteur
	if (timeUntilNextFire == -1 )
		timeUntilNextFire = FREQUENCY / this->attr.firerate;

	//si il faut attendre, attendre ...
	if (timeUntilNextFire >= 1)
		timeUntilNextFire--;
	//else if ( /*il y a un enemy a porte de tir */)
		//fire()	
}

//
// WaterGun
//

WaterGun::WaterGun(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("watergun"))
{
	this->attr = this->computeAttribute(1);
}

void WaterGun::action()
{
	Tower::action();


	// doit s'orienter vers l'enemy cible, pas tourner en rond
	angle += 0.5;

	if (timeUntilNextFire == 0)
	{
		QPointF myPos = scenePos() + getCenterPos();
		const Enemy *target = this->game->getClosestEnemy(myPos.x(), myPos.y());
		
		qDebug() << myPos;

		if (target != NULL)
		{
			// vector
			QPointF vector = target->getCenterPos() - myPos;
			
			// compute distance
			int distance_q = vector.x()*vector.x() + vector.y()*vector.y();	
			int range_q = this->attr.range * TILE_SIZE;
			range_q *= range_q;

			if (distance_q <= range_q) 
			{
				game->addObject(new AngryBird(game,1,myPos,vector));
				timeUntilNextFire = -1;
			}
		}
	}

	update();
}

Tower::Attribute WaterGun::computeAttribute(int level) const
{
	Attribute attr;

	if (level == 1) attr.cost = 8;
	else if (level == 2) attr.cost = 20;
	else if (level == 3) attr.cost = 45;
	else attr.cost = 0;

	attr.sellprice = attr.cost / 2;
	for (int i = level-1 ; i > 0 ; i--)
		attr.sellprice += this->computeAttribute(i).cost / 2;

	attr.level = level;
	attr.range = 2 + level/2.0;
	attr.power = 5 * std::pow(level, 1.5);
	attr.firerate = 4 + level/2.0;
	attr.bulletSpeed = 40;

	return attr;
}

Slingshot::Slingshot(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("slingshot"))
{
	this->attr = this->computeAttribute(1);
}

void Slingshot::action()
{
}

Tower::Attribute Slingshot::computeAttribute(int level) const
{
	Attribute attr;

	if (level == 1) attr.cost = 12;
	else if (level == 2) attr.cost = 25;
	else if (level == 3) attr.cost = 60;
	else attr.cost = 0;

	attr.sellprice = attr.cost / 2;
	for (int i = level-1 ; i > 0 ; i--)
		attr.sellprice += this->computeAttribute(i).cost / 2;


	attr.level = level;
	attr.range = 3 + level/2.0;
	attr.power = 10 * std::pow(level, 1.5);
	attr.firerate = 1;
	attr.bulletSpeed = 25;

	return attr;
}

PetanquePlayer::PetanquePlayer(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("petanque"))
{
	this->attr = this->computeAttribute(1);
}

void PetanquePlayer::action()
{
}

Tower::Attribute PetanquePlayer::computeAttribute(int level) const
{
	Attribute attr;

	if (level == 1) attr.cost = 15;
	else if (level == 2) attr.cost = 40;
	else if (level == 3) attr.cost = 80;
	else attr.cost = 0;

	attr.sellprice = attr.cost / 2;
	for (int i = level-1 ; i > 0 ; i--)
		attr.sellprice += this->computeAttribute(i).cost / 2;


	attr.level = level;
	attr.range = 3 + level/2.0;
	attr.power = 10 * std::pow(level, 1.5);
	attr.firerate = 1;
	attr.bulletSpeed = 25;

	return attr;
}

PaintBall::PaintBall(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("paintball"))
{
	this->attr = this->computeAttribute(1);
}

void PaintBall::action()
{
}

Tower::Attribute PaintBall::computeAttribute(int level) const
{
	Attribute attr;

	if (level == 1) attr.cost = 12;
	else if (level == 2) attr.cost = 25;
	else if (level == 3) attr.cost = 60;
	else attr.cost = 0;

	attr.sellprice = attr.cost / 2;
	for (int i = level-1 ; i > 0 ; i--)
		attr.sellprice += this->computeAttribute(i).cost / 2;


	attr.level = level;
	attr.range = 4 + level/2.0;
	attr.power = 4 * std::pow(level, 1.5);
	attr.firerate = 2;
	attr.bulletSpeed = 30;

	return attr;
}

