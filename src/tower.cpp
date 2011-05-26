#include <cmath>
#include "factory.hpp"
#include "tower.hpp"
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
	else
	{
		QPointF myPos = scenePos() + getCenterPos();
		const Enemy *target = game->getClosestEnemy(myPos.x(), myPos.y(), attr.range * TILE_SIZE);
		
		if (target != NULL)
		{
			game->addObject(Factory::getMissile(this, target, game));
			timeUntilNextFire = -1;
		}
	}
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
	update();
}

Tower::Attribute WaterGun::computeAttribute(int level) const
{
	Attribute attr;
	attr.type = Tower::WATERGUN;

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
	Tower::action();
}

Tower::Attribute Slingshot::computeAttribute(int level) const
{
	Attribute attr;
	attr.type = Tower::SLINGSHOT;

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
	Tower::action();
}

Tower::Attribute PetanquePlayer::computeAttribute(int level) const
{
	Attribute attr;
	attr.type = Tower::PETANQUEPLAYER;

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
	Tower::action();
}

Tower::Attribute PaintBall::computeAttribute(int level) const
{
	Attribute attr;
	attr.type = Tower::PAINTBALL;

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

