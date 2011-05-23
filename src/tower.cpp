#include "tower.hpp"
#include <cmath>
#include "missile.hpp"

Tower::Tower(lo21* g, QList< QPixmap > p)
:Object(g, p),timeUntilNextFire(0)
{
	//this->setFlag(QGraphicsItem::ItemIsSelectable);
}

Tower::Attribute Tower::getAttribute() const
{
	return this->attr;
}

Tower::Attribute Tower::getUpgradedAttribute() const
{
	return this->computeAttribute(this->attr.level+1);
}

WaterGun::WaterGun(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("watergun"))
{
	this->attr = this->computeAttribute(1);
}

void WaterGun::action()
{
	angle+=0.5;
	if(timeUntilNextFire>0)
		timeUntilNextFire--;
	else
	{
		timeUntilNextFire=20;
		game->addObject(new AngryBird(game,1,scenePos()+this->getHalfSize()/2,QPointF(cos(angle/360.0*2*3.1415927),sin(angle/360.0*2*3.1415927))));
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

	attr.level = level;
	attr.range = 2 + level/2.0;
	attr.power = 5 * std::pow(level, 1.5);
	attr.firerate = 4 - level/2.0;
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

	attr.level = level;
	attr.range = 4 + level/2.0;
	attr.power = 4 * std::pow(level, 1.5);
	attr.firerate = 2;
	attr.bulletSpeed = 30;

	return attr;
}

