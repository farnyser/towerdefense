#ifndef LO21_ENEMY_HPP
#define LO21_ENEMY_HPP

#include "object.hpp"

class Enemy: public Object
{
protected:
	float hp;
	int size;
	Enemy(lo21* g, QList<QPixmap> p, int interval);
protected:
	virtual int getSpeed() = 0;
	virtual void advance();
};

class Ant: public Enemy
{
public:
	Ant(lo21*);
protected:
	int getSpeed();
};

class Bug: public Enemy
{
public:
	Bug(lo21*);
protected:
	int getSpeed();
};

class Bee: public Enemy
{
public:
	Bee(lo21*);
protected:
	int getSpeed();
};

class Mosquito: public Enemy
{
public:
	Mosquito(lo21*);
protected:
	int getSpeed();
};

#endif /* end of include guard: LO21_ENEMY_HPP */
