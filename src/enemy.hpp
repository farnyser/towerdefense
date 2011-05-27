#ifndef LO21_ENEMY_HPP
#define LO21_ENEMY_HPP

#include "object.hpp"

class Missile;

class Enemy: public Object
{
public:
	enum Type
	{
		NONE,
		ANT,
		BUG,
		WASP,
		MOSQUITO
	};
    enum AGType
	{
		GROUND = 1 << 1,
		AIR = 1 << 2
	};
public:
	void hit(int damage);
	bool hit(const Missile *m);
	bool canBeHit(int agtype) const;
	virtual ~Enemy() { };

protected:
	float scale;
	float hp;
	float resistance;
	float speed;
	int size;
	AGType agtype;
	
	QPointF lastVector;
	float wantedRotation;

protected:
	Enemy(lo21* g, int size, QList<QPixmap> p, int interval);
	float getScale() const;
	float getSpeed() const;
	float getHeatPoint() const;
	float getResistance() const;
	virtual void action();
};

class Ant: public Enemy
{
public:
	Ant(lo21*, int size);
	virtual ~Ant() { };
};

class Bug: public Enemy
{
public:
	Bug(lo21*, int size, int angle = 0);
	~Bug();
};

class Wasp: public Enemy
{
public:
	Wasp(lo21*, int size);
	virtual ~Wasp();
};

class Mosquito: public Enemy
{
private:
	int state;
public:
	Mosquito(lo21*,int size);
protected:
	virtual void action();
	virtual void hit(int damage);
};

#endif /* end of include guard: LO21_ENEMY_HPP */
