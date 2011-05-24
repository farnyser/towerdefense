#include "missile.hpp"
#include <typeinfo>

Missile::Missile(lo21* g, int size, QList< QPixmap > p, int interval, QPointF pos, QPointF vec, float velocity, float force)
:Object(g, p, interval),force(force),size(size),vec(vec),velocity(velocity)
{
	this->setScale(size);
	this->setPos(pos);
}


void Missile::action()
{	
	float x=this->x();
	float y=this->y();
	if(x>MAP_SIZE*TILE_SIZE || y>MAP_SIZE*TILE_SIZE || x<-20  ||y<-20)
	{
		game->removeObject(this);
	}
	else
	{
		x+=vec.x()*velocity;
		y+=vec.y()*velocity;
		this->setPos(QPointF(x,y));
		this->update();
	
	
	
		QList<QGraphicsItem *> c=collidingItems(Qt::IntersectsItemShape );
		QListIterator<QGraphicsItem*> it(c);
		while(it.hasNext())
		{
			QGraphicsItem* t=it.next();
			//vérifie si l'object dérive de Enemy
			if(typeid(*t).before(typeid(Enemy)))
			{
				((Enemy*) t)->hit(1);
				game->removeObject(this);
				break;
			}

		}
	}
	
}

AngryBird::AngryBird(lo21* g, int size, QPointF pos, QPointF vec)
:Missile(g, size,Ressources::getAnimatedPixmap("angrybird"),Ressources::getAnimatedInterval("angrybird"),pos,vec, 0.8,1)
{

}




