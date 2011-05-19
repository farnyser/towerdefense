#ifndef LO21_TOWER
#define LO21_TOWER

#include "object.hpp"

enum TowerType
{
	WATERGUN,
	SLINGSHOT,
	PAINTBALL,
	PETANQUEPLAYER,
	NONE
};

class Tower: public Object
{
private:
	int level;
};

class WaterGun: public Tower
{

};

class Slingshot: public Tower
{

};

class PaintBall: public Tower
{

};

class PetanquePlayer: public Tower
{

};

class Musician: public Tower
{

};

#endif /* end of include guard: LO21_TOWER */
