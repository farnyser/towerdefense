#include "enemy.hpp"
#include "ressources.hpp"
#include "missile.hpp"
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

	const Tile* tile = ((const lo21*)this->game)->getTile(x,y);

	if ( tile != NULL && tile->isEndPoint() )
	{
		game->subLive(1);
		game->removeObject(this);
		return;
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
				if (vectorP.y() > 0 && vectorP.x() > 0)
					wantedRotation = 90;
				else
					wantedRotation = -90;
			}
			// precedent mouvement : gauche/droite
			if ( !lastVector.x() && lastVector.y() )
			{
				if (vectorP.x() > 0 && vectorP.y() > 0)
					wantedRotation = -90;
				else
					wantedRotation = 90;
			}
		}

		if(wantedRotation)
		{
			float rotationSpeed = this->getSpeed() * 90./FREQUENCY;
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

void Enemy::hit(int damage)
{
	if (damage > resistance)
		hp = hp - (damage-resistance);
	
	if(hp <= 0)
	{
		game->addCredit(1);
		game->removeObject(this);
	}
}

bool Enemy::hit(const Missile *m)
{
	if (m->getAGType() & this->agtype)
	{
		this->hit(m->getPower());
		return true;
	}

	return false;
}


Ant::Ant(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("ant"),Ressources::getAnimatedInterval("ant"))
{
	this->speed = 2 + this->size/2;
	this->hp = 5 * this->size * this->size;
	this->resistance = this->size * this->size;
	this->agtype = GROUND;
}

Bug::Bug(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("bug"),Ressources::getAnimatedInterval("bug"))
{
	this->hp = 10 * this->size * this->size;
	this->resistance = 5 * this->size * this->size;
	this->speed = 2;
	this->agtype = GROUND;
}

Bug::~Bug()
{
	if (this->size > 1)
	{
		Bug *c1 = new Bug(game, this->size - 1);
		Bug *c2 = new Bug(game, this->size - 1);

		c1->setPos(this->getCenterPos() - getCenterPos() + QPointF(2,2));
		c2->setPos(this->getCenterPos() - getCenterPos() - QPointF(2,2));

		game->addObject(c1);
		game->addObject(c2);
	}
}

Wasp::Wasp(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("bee"),Ressources::getAnimatedInterval("bee"))
{
	this->hp = 7 * this->size * this->size;
	this->resistance = 4 * this->size * this->size;
	this->speed = 3;
	this->agtype = AIR;
}

Wasp::~Wasp()
{
	// doit s'ecraser et causer des degats
}

Mosquito::Mosquito(lo21 *g, int size)
 : Enemy(g, size, Ressources::getAnimatedPixmap("mosquito"),Ressources::getAnimatedInterval("mosquito"))
{
	this->hp = 6 * this->size * this->size;

	// attention: resistance & vitesse depend de si il est au sol ou non !!
	// au sol
	this->agtype = GROUND;
	this->speed = 1 + this->size/2.0;
	this->resistance = 15 * this->size;
}

