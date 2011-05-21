#include "enemy.hpp"
#include "ressources.hpp"
#include "tile.hpp"
#include "lo21.hpp"
#include <cmath>
#include <QDebug>
#include <QPoint>

Enemy::Enemy(lo21* game, int arg_size, QList<QPixmap> pixmaps, int interval)
 : 
  Object(game, pixmaps, interval), 
  size(arg_size),
  scale(0.1 + arg_size / 20.0),
  wantedRotation(0)
{
	// resize
	setScale(scale);

	// remember current vector
	this->lastVector = game->getStart()->getVector().second - game->getStart()->getVector().first;

	// compute rotation
	qreal angle = 90 - std::atan(lastVector.x() / lastVector.y()) * 360.0 / (2*3.14957);
	
	// set initial orientation
	this->setRotation(angle);

	// set position to the middle of the start tile
	this->setPos(game->getStart()->getCenterPos() - getCenterPos());
}

/// \brief Move the enemy along the path
void Enemy::action()
{
	float x = this->getCenterPos().x();
	float y = this->getCenterPos().y();

	const Tile* tile = this->game->getTile(x,y);

	if ( tile != NULL && tile->isEndPoint() )
	{
		delete this;
	}
	else if ( tile != NULL && tile->isWalkable() ) 
	{
		vec2f vector = tile->getVector();
		QPointF vectorP = vector.second - vector.first;
		qreal angle = 90 - std::atan(vectorP.x() / vectorP.y()) * 360.0 / (2*3.14957);
		qreal speed = this->getSpeed() * TILE_SIZE/FREQUENCY;


		// courbe (changement de direction
		if (  (lastVector != vectorP) && (vectorP.x() && vectorP.y()) )
		{

			// precedent mouvement : haut/bas
			if ( lastVector.x() && !lastVector.y() )
			{
				if ( vectorP.y() > 0 )
					wantedRotation = 90 - rotation();
				else
					wantedRotation = -90 - rotation();
			}
			// precedent mouvement : gauche/droite
			if ( !lastVector.x() && lastVector.y() )
			{
				if ( vectorP.x() > 0 )
					wantedRotation = 0 - rotation();
				else
					wantedRotation = 180 - rotation();
			}
		}

		if(wantedRotation)
		{
			float rotationSpeed = this->getSpeed() * 90.0/FREQUENCY;
			float lastWantedRotation=wantedRotation;
			if(wantedRotation<0)
			{
				wantedRotation+=rotationSpeed;
				if(wantedRotation>0)
					wantedRotation=0;
				
				this->angle-=wantedRotation-lastWantedRotation;
			}
			else
			{
				wantedRotation-=rotationSpeed;
				if(wantedRotation<0)
					wantedRotation=0;
				
				this->angle+=lastWantedRotation-wantedRotation;
			}
		}

		// rectiligne
		float dx = speed * vectorP.x() / vectorP.manhattanLength();
		float dy = speed * vectorP.y() / vectorP.manhattanLength();
		
		this->moveBy(dx, dy);
		this->lastVector = vectorP;
		
	}
	else
	{
		qDebug() << "There is no Walkbale Tile there : " << x << " , " << y;
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

Wasp::Wasp(lo21 *g, int size)
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

