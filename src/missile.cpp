#include "missile.hpp"


Missile::Missile(lo21* g, int size, QList< QPixmap > p, int interval, QPoint pos, QPointF vec, float velocity, float force)
:Object(g, p, interval),force(force),size(size),vec(vec),velocity(velocity)
{
setScale(size);
this->setPos(pos);
}


void Missile::action()
{	
	float x=this->x();
	float y=this->y();
	if(x>MAP_SIZE*TILE_SIZE || y>MAP_SIZE*TILE_SIZE || x<-20  ||y<-20)
	{
		delete this;
	}
	else
	{
		x+=vec.x()*velocity;
		y+=vec.y()*velocity;
		this->setPos(QPointF(x,y));
		this->update();
	}
}

AngryBird::AngryBird(lo21* g, int size, QPoint pos, QPointF vec)
:Missile(g, size,Ressources::getAnimatedPixmap("angrybird"),Ressources::getAnimatedInterval("angrybird"),pos,vec, 0.8,1)
{

}




