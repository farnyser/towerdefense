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
public:
	int getPower() const;

protected:
    Missile(lo21* g, QList< QPixmap > p, int interval,QPointF pos, float velocity, float force, const Enemy *target);
	void computeVector();
	virtual void action();
};

class AngryBird:public Missile
{
public:
	AngryBird(lo21* g, QPointF pos, float velocity, float power, const Enemy *target);
protected:
};

#endif // MISSILE_HPP
