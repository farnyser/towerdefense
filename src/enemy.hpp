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
//advance()

class Ant: public Enemy
{
public:
	Ant(lo21*, int size);
	virtual ~Ant() { };
};

class Bug: public Enemy
{
public:
	Bug(lo21*, int size);
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
public:
	Mosquito(lo21*,int size);
protected:
	int getSpeed();
	int getSize();
};

#endif /* end of include guard: LO21_ENEMY_HPP */
