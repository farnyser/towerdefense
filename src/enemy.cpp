#include "enemy.hpp"
#include "ressources.hpp"
#include "tile.hpp"
#include "lo21.hpp"
#include <cmath>
#include <QDebug>
#include <QPoint>

Enemy::Enemy(lo21* g, QList<QPixmap> p, int interval)
 : Object(g, p, interval) 
{
	// scale depend on the Enemy's size
	this->setScale(0.3);
}

/// \brief Move the enemy along the path
void Enemy::advance()
{
	float x = this->pos().x();
	float y = this->pos().y();

	const Tile* tile = this->game->getTile(x,y);
	
	if ( tile != NULL && tile->isEndPoint() )
	{
		delete this;
	}
	else if ( tile != NULL && tile->isWalkable() ) 
	{
		vec2f vector = tile->getVector();	
		QPointF vectorP = vector.second - vector.first;
		qreal angle;

		x += vectorP.x() / vectorP.manhattanLength();
		y += vectorP.y() / vectorP.manhattanLength();
		angle = 90 - std::atan(vectorP.x() / vectorP.y()) * 360.0 / (2*3.14957);

		this->setPos(x, y);	
		qDebug() << "new pos : " << this->pos();
		qDebug() << "origin point : " << this->transformOriginPoint();
		qDebug() << "vector : " << vector;

		if ( angle != this->rotation() )
		{
			// this->setTransformOriginPoint(this->getCenterPos());
			this->setRotation(1.0/3.0*angle+2.0/3.0*this->rotation());
		}
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
