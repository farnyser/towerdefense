#include "enemy.hpp"
#include "ressources.hpp"
#include "tile.hpp"
#include "lo21.hpp"

Enemy::Enemy(lo21* g, QList<QPixmap> p, int interval)
 : Object(g, p, interval) 
{
}

/// \brief Move the enemy along the path
void Enemy::advance()
{
	int x = this->pos().x();
	int y = this->pos().y();
	
	const Tile* tile = this->game->getTile(x,y);
	
	if ( tile != NULL && tile->isWalkable() ) 
	{
		vec2i vector = tile->getVector();	

		x += (vector.second.x() - vector.first.x());
		y += (vector.second.y() - vector.first.y());

		this->setPos(x, y);	
		//this->setRotation(vec2i.angle());
	}
}

Ant::Ant(lo21 *g)
 : Enemy(g, Ressources::getAnimatedPixmap("ant"),Ressources::getAnimatedInterval("ant"))
{
}

int Ant::getSpeed()
{
}

Bug::Bug(lo21 *g)
 : Enemy(g, Ressources::getAnimatedPixmap("bug"),Ressources::getAnimatedInterval("bug"))
{
}

int Bug::getSpeed()
{
}

Bee::Bee(lo21 *g)
 : Enemy(g, Ressources::getAnimatedPixmap("bee"),Ressources::getAnimatedInterval("bee"))
{
}

int Bee::getSpeed()
{
}

Mosquito::Mosquito(lo21 *g)
 : Enemy(g, Ressources::getAnimatedPixmap("mosquito"),Ressources::getAnimatedInterval("mosquito"))
{
}

int Mosquito::getSpeed()
{
}
