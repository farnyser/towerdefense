#include "tower.hpp"
#include <cmath>
#include "missile.hpp"

Tower::Tower(lo21* g, QList< QPixmap > p)
:Object(g, p),timeUntilNextFire(0)
{
	this->level = 1;
	//this->setFlag(QGraphicsItem::ItemIsSelectable);
}

Tower::Attribute Tower::getAttribute() const
{
	return this->attr;
}

Tower::Attribute Tower::getUpgradedAttribute() const
{
	return this->computeAttribute(this->level+1);
}

int Tower::getCost() const
{
	if ( level > 0 && level <= this->cost.size() )
		return this->cost[level-1];
	else 
		return -1;
}

int Tower::getUpgradeCost() const
{
	if ( level >= 0 && level < this->cost.size() )
		return this->cost[level];
	else
		return -1;
}

WaterGun::WaterGun(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("watergun"))
{
	this->cost.push_back(8);
	this->cost.push_back(20);
	this->cost.push_back(45);
	this->attr = this->computeAttribute(level);
}

void WaterGun::action()
{
	angle+=0.5;
	if(timeUntilNextFire>0)
		timeUntilNextFire--;
	else
	{
		timeUntilNextFire=20;
		game->addObject(new AngryBird(game,1,scenePos(),QPointF(sin(angle/360.0*2*3.1415927),cos(angle/360.0*2*3.1415927))));
	}
	update();
}

Tower::Attribute WaterGun::computeAttribute(int level) const
{
	Attribute attr;
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
	this->cost.push_back(12);
	this->cost.push_back(25);
	this->cost.push_back(60);
	this->attr = this->computeAttribute(level);
}

void Slingshot::action()
{
}

Tower::Attribute Slingshot::computeAttribute(int level) const
{
	Attribute attr;
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
	this->cost.push_back(15);
	this->cost.push_back(40);
	this->cost.push_back(80);
	this->attr = this->computeAttribute(level);
}

void PetanquePlayer::action()
{
}

Tower::Attribute PetanquePlayer::computeAttribute(int level) const
{
	Attribute attr;
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
	this->cost.push_back(12);
	this->cost.push_back(25);
	this->cost.push_back(60);
	this->attr = this->computeAttribute(level);
}

void PaintBall::action()
{
}

Tower::Attribute PaintBall::computeAttribute(int level) const
{
	Attribute attr;
	attr.level = level;
	attr.range = 4 + level/2.0;
	attr.power = 4 * std::pow(level, 1.5);
	attr.firerate = 2;
	attr.bulletSpeed = 30;
	return attr;
}

