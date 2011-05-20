#include "tower.hpp"


Tower::Tower(lo21* g, QList< QPixmap > p)
:Object(g, p)
{
}

WaterGun::WaterGun(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("watergun"))
{	
}

void WaterGun::action()
{
}

Slingshot::Slingshot(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("slingshot"))
{
}

void Slingshot::action()
{
}

PetanquePlayer::PetanquePlayer(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("petanque"))
{
}

void PetanquePlayer::action()
{
}

PaintBall::PaintBall(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("paintball"))
{
}

void PaintBall::action()
{
}

