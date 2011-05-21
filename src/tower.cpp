#include "tower.hpp"


Tower::Tower(lo21* g, QList< QPixmap > p)
:Object(g, p)
{
}

int Tower::getCost() const
{
	return this->cost;
}

WaterGun::WaterGun(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("watergun"))
{
	this->level = 1;
	this->cost = 8;
	this->range = 2.5;
	this->power = 5;
	this->firerate = 3.5;
	this->bulletSpeed = 40;
}

void WaterGun::action()
{
}

Slingshot::Slingshot(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("slingshot"))
{
	this->level = 1;
	this->cost = 12;
	this->range = 3.5;
	this->power = 10;
	this->firerate = 1;
	this->bulletSpeed = 25;
}

void Slingshot::action()
{
}

PetanquePlayer::PetanquePlayer(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("petanque"))
{
	this->level = 1;
	this->cost = 15;
	this->range = 4;
	this->power = 15;
	this->firerate = 0.5;
	this->bulletSpeed = 20;
}

void PetanquePlayer::action()
{
}

PaintBall::PaintBall(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("paintball"))
{
	this->level = 1;
	this->cost = 12;
	this->range = 4.5;
	this->power = 4;
	this->firerate = 2;
	this->bulletSpeed = 30;
}

void PaintBall::action()
{
}

