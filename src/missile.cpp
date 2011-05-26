#include "missile.hpp"
#include "enemy.hpp"

Missile::Missile(lo21* g, int size, QList< QPixmap > p, int interval, QPointF pos, const Enemy *target, float velocity, float force)
:Object(g, p, interval),
force(force),
size(size),
velocity(velocity),
target(target)
{
	this->setScale(size);
	this->setPos(pos-getCenterPos());
}

void Missile::computeVector()
{
	// verif en cas de suppression
	if (target != NULL && game->isEnemy(target))
	{
		qDebug() << "y a un vilain !!";

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
		this->computeVector();

		x += vec.x()*velocity;
		y += vec.y()*velocity;
		this->setPos(QPointF(x,y));
		this->update();
	
		QList<QGraphicsItem *> c=collidingItems(Qt::IntersectsItemShape );
		QListIterator<QGraphicsItem*> it(c);
		while(it.hasNext())
		{
			QGraphicsItem* t=it.next();
			//vérifie si l'object dérive de Enemy
			//if(typeid(*t).before(typeid(Enemy)))
			if (game->isEnemy(t))
			{
				Enemy *e = dynamic_cast<Enemy*>(t);
				if (e != NULL)
				{
					e->hit(100);
					game->removeObject(this);
					break;
				}
			}

		}
	}
	
}

AngryBird::AngryBird(lo21* g, int size, QPointF pos, const Enemy *target)
:Missile(g, size,Ressources::getAnimatedPixmap("angrybird"),Ressources::getAnimatedInterval("angrybird"),pos,target, 0.8,1)
{

}




