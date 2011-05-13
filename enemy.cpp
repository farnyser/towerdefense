#include "enemy.hpp"

Bug::Bug()
{
	this->frameInterval = 8;
	this->animatedPixmap.push_back(QPixmap("ressources/images/cafard1.png"));
	this->animatedPixmap.push_back(QPixmap("ressources/images/cafard2.png"));
	this->animatedPixmap.push_back(QPixmap("ressources/images/cafard3.png"));
}

Ant::Ant()
{
	this->frameInterval = 8;
	this->animatedPixmap.push_back(QPixmap("ressources/images/fourmi1.png"));
	this->animatedPixmap.push_back(QPixmap("ressources/images/fourmi2.png"));
	this->animatedPixmap.push_back(QPixmap("ressources/images/fourmi3.png"));
}

Bee::Bee()
{
	this->frameInterval = 8;
	this->animatedPixmap.push_back(QPixmap("ressources/images/guepe1.png"));
	this->animatedPixmap.push_back(QPixmap("ressources/images/guepe2.png"));
}

Mosquito::Mosquito()
{
	this->frameInterval = 8;
	this->animatedPixmap.push_back(QPixmap("ressources/images/moustiquevolant1.png"));
	this->animatedPixmap.push_back(QPixmap("ressources/images/moustiquevolant2.png"));
}

