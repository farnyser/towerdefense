#ifndef LO21_ENEMY
#define LO21_ENEMY

#include "object.hpp"

class Enemy: public Object
{
private:
	float hp;
	int size;

};

class Ant: public Enemy
{

};

class Bug: public Enemy
{

};

class Bee: public Enemy
{

};

class Mosquito: public Enemy
{

};

#endif /* end of include guard: LO21_ENEMY */
