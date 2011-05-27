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
	int agtype;
	const Enemy *target;
public:
	int getPower() const;
	int getAGType() const;

protected:
    Missile(lo21* g, QList< QPixmap > p, int interval, int agtype, QPointF pos, float velocity, float force, const Enemy *target);
	virtual ~Missile(){};

	void computeVector();
	virtual void action();
};

class AngryBird:public Missile
{
public:
	AngryBird(lo21* g, QPointF pos, float velocity, float power, const Enemy *target);
	virtual ~AngryBird() {};
protected:
};

#endif // MISSILE_HPP
