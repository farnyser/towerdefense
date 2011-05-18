#include "enemy.hpp"
#include "ressources.hpp"
#include "tile.hpp"
#include "lo21.hpp"
#include <cmath>
#include <QDebug>
#include <QPoint>

Enemy::Enemy(lo21* g, int arg_size, QList<QPixmap> p, int interval)
 : Object(g, p, interval), size(arg_size)
{
	setPos(g->getStart()->pos() + g->getStart()->getCenterPos());
	// setScale(getSize());
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

		x += 3*vectorP.x() / vectorP.manhattanLength();
		y += 3*vectorP.y() / vectorP.manhattanLength();
		angle = 90 - std::atan(vectorP.x() / vectorP.y()) * 360.0 / (2*3.14957);

		this->setPos(x, y);	
		//qDebug() << "new pos : " << this->pos();
		//qDebug() << "origin point : " << this->transformOriginPoint();
		//qDebug() << "vector : " << vector;

		if ( angle != this->rotation() )
		{
			// this->setTransformOriginPoint(this->getCenterPos());
			this->setRotation(1.0/3.0*angle+2.0/3.0*this->rotation());
		}
	}
}

Ant::Ant(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("ant"),Ressources::getAnimatedInterval("ant"))
{
}

int Ant::getSpeed()
{
}

int Ant::getSize()
{
}

Bug::Bug(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("bug"),Ressources::getAnimatedInterval("bug"))
{
}

int Bug::getSpeed()
{
}

int Bug::getSize()
{
}

Bee::Bee(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("bee"),Ressources::getAnimatedInterval("bee"))
{
}

int Bee::getSpeed()
{
}

int Bee::getSize()
{
}

Mosquito::Mosquito(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("mosquito"),Ressources::getAnimatedInterval("mosquito"))
{
}

int Mosquito::getSpeed()
{
}

int Mosquito::getSize()
{
}

