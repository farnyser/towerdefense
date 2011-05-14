#ifndef LO21_ENEMY_HPP
#define LO21_ENEMY_HPP

#include "object.hpp"

class Enemy: public Object
{
protected:
	float hp;
	int size;
	Enemy(QList<QPixmap> p, int interval);
};

class Ant: public Enemy
{
public:
	Ant();
};

class Bug: public Enemy
{
public:
	Bug();
};

class Bee: public Enemy
{
public:
	Bee();
};

class Mosquito: public Enemy
{
public:
	Mosquito();
};

#endif /* end of include guard: LO21_ENEMY_HPP */
