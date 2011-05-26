#ifndef MISSILE_HPP
#define MISSILE_HPP

#include "ressources.hpp"
#include "lo21.hpp"
#include "object.hpp"
#include "tile.hpp"


class Missile : public Object
{
private:
	const Enemy *target;
	QPointF vec;
	float velocity;
	float size;
	float force;
protected:
    Missile(lo21* g, int size,QList< QPixmap > p, int interval,QPointF pos, const Enemy *target,float velocity,float force);
	void computeVector();
	virtual void action();
};

class AngryBird:public Missile
{
public:
	AngryBird(lo21* g, int size, QPointF pos, const Enemy *target);
protected:
};

#endif // MISSILE_HPP
