#ifndef LO21_ENEMY_HPP
#define LO21_ENEMY_HPP

#include "object.hpp"


enum EnemyType
{
	ANT,
	BUG,
	BEE,
	MOSQUITO
};

class Enemy: public Object
{
protected:
	float hp;
	int size;

protected:
	Enemy(lo21* g, int size, QList<QPixmap> p, int interval);
	virtual int getSpeed() = 0;
	virtual int getSize() = 0;
	// virtual int getLife() = 0:
	// virtual int getResistance() = 0;
	virtual void advance();
};

class Ant: public Enemy
{
public:
	Ant(lo21*, int size);
protected:
	int getSpeed();
	int getSize();
};

class Bug: public Enemy
{
public:
	Bug(lo21*, int size);
protected:
	int getSpeed();
	int getSize();
};

class Bee: public Enemy
{
public:
	Bee(lo21*, int size);
protected:
	int getSpeed();
	int getSize();
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
