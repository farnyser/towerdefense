#ifndef LO21_ENEMY_HPP
#define LO21_ENEMY_HPP

#include "object.hpp"

class Enemy: public Object
{
protected:
	float scale;
	float hp;
	float resistance;
	float speed;
	int size;

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

class Wasp: public Enemy
{
public:
	Wasp(lo21*, int size);
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
