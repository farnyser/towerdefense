#include "missile.hpp"
#include "enemy.hpp"

Missile::Missile(lo21* g, QList< QPixmap > p, int interval, QPointF pos, float velocity, float force, const Enemy *target)
:Object(g, p, interval),
force(force),
velocity(velocity),
target(target)
{
	this->setScale(1.5);
	this->setPos(pos-getCenterPos());
}

void Missile::computeVector()
{
	// verif en cas de suppression
	if (target != NULL && game->isEnemy(target))
	{
		// direction
		vec = target->getCenterPos() - this->getCenterPos();
		
		// vecteur unitaire
		int distance_q = ((vec.x()*vec.x()) + (vec.y()*vec.y()));
		this->vec.setX( (vec.x() < 0 ? -1 : 1) * (vec.x()*vec.x()) / distance_q ); 
		this->vec.setY( (vec.y() < 0 ? -1 : 1) * (vec.y()*vec.y()) / distance_q ); 
	}
	else
	{
		// on conserve le vecteur courant
		// sauf si nul
		if (vec.x() == vec.y() == 0)
			game->removeObject(this);
	}
}

void Missile::action()
{	
	float x = this->x();
	float y = this->y();

	if(x > MAP_SIZE*TILE_SIZE || y > MAP_SIZE*TILE_SIZE || x < -20  ||y < -20)
	{
		game->removeObject(this);
	}
	else
	{
		int trueVelocity = (velocity * TILE_SIZE) / FREQUENCY;
		this->computeVector();

		x += vec.x()*trueVelocity;
		y += vec.y()*trueVelocity;
		this->setPos(QPointF(x,y));
		this->update();
	
		QList<QGraphicsItem *> c=collidingItems(Qt::IntersectsItemShape );
		QListIterator<QGraphicsItem*> it(c);
		while(it.hasNext())
		{
			QGraphicsItem* t=it.next();
			
			if (game->isEnemy(t) /* && t->type inclut dans this->targetType */)
			{
				Enemy *e = dynamic_cast<Enemy*>(t);
				if (e != NULL)
				{
					e->hit(this);
					game->removeObject(this);
					break;
				}
			}

		}
	}
	
}

int Missile::getPower() const
{
	return this->force;
}

AngryBird::AngryBird(lo21* g, QPointF pos, float velocity, float power, const Enemy *target)
:Missile(g,Ressources::getAnimatedPixmap("angrybird"),Ressources::getAnimatedInterval("angrybird"),pos, velocity, power, target)
{

}




