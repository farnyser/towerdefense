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
	// scale = 0.1 + size/10;
	// setScale(scale);
	setPos(g->getStart()->pos() + g->getStart()->getCenterPos());

	qDebug() << "Enemy scale : " << QGraphicsItem::scale();
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

float Enemy::getScale() const
{
	return scale; 
}

float Enemy::getSpeed() const
{
	return this->speed;
}

float Enemy::getResistance() const
{
	return this->resistance;
}

Ant::Ant(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("ant"),Ressources::getAnimatedInterval("ant"))
{
	this->speed = 2 + this->size/2;
	this->hp = 5 * this->size * this->size;
	this->resistance = this->size * this->size;
}

Bug::Bug(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("bug"),Ressources::getAnimatedInterval("bug"))
{
	this->hp = 10 * this->size * this->size;
	this->resistance = 5 * this->size * this->size;
	this->speed = 2;
}

Bee::Bee(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("bee"),Ressources::getAnimatedInterval("bee"))
{
	this->hp = 7 * this->size * this->size;
	this->resistance = 4 * this->size * this->size;
	this->speed = 3;
}

Mosquito::Mosquito(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("mosquito"),Ressources::getAnimatedInterval("mosquito"))
{
	this->hp = 6 * this->size * this->size; 
}

