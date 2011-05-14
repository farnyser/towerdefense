#include "enemy.hpp"
#include "ressources.hpp"

Enemy::Enemy(QList<QPixmap> p, int interval)
 : Object(p, interval) 
{
}

Ant::Ant()
 : Enemy(Ressources::getAnimatedPixmap("ant"),Ressources::getAnimatedInterval("ant"))
{
}

Bug::Bug()
 : Enemy(Ressources::getAnimatedPixmap("bug"),Ressources::getAnimatedInterval("bug"))
{
}

Bee::Bee()
 : Enemy(Ressources::getAnimatedPixmap("bee"),Ressources::getAnimatedInterval("bee"))
{
}

Mosquito::Mosquito()
 : Enemy(Ressources::getAnimatedPixmap("mosquito"),Ressources::getAnimatedInterval("mosquito"))
{
}


