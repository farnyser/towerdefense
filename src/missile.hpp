#ifndef MISSILE_HPP
#define MISSILE_HPP

#include "ressources.hpp"
#include "lo21.hpp"
#include "object.hpp"
#include "tile.hpp"


class Missile : public Object
{
private:
	QPointF vec;
	float velocity;
	float size;
	float force;
protected:
    Missile(lo21* g, int size,QList< QPixmap > p, int interval,QPoint pos,QPointF vec,float velocity,float force);
	virtual void action();
};

class AngryBird:public Missile
{
public:
	AngryBird(lo21* g,int size,QPoint pos,QPointF vec);
protected:
};

#endif // MISSILE_HPP
