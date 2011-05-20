#ifndef LO21_TOWER
#define LO21_TOWER

#include "object.hpp"
#include "ressources.hpp"

class Tower: public Object
{
public:
	enum Type 
	{
		NONE,
		WATERGUN,
		SLINGSHOT,
		PAINTBALL,
		PETANQUEPLAYER,
	};
private:
	int level;
protected:
	Tower(lo21* g,QList<QPixmap> p);
};

class WaterGun: public Tower
{
public:
	WaterGun(lo21* g);
	void action();
};

class Slingshot: public Tower
{
public:
	Slingshot(lo21* g);
	void action();
};

class PaintBall: public Tower
{
public:
	PaintBall(lo21* g);
	void action();
};

class PetanquePlayer: public Tower
{
public:
	PetanquePlayer(lo21* g);
	void action();
};

class Musician: public Tower
{

};

#endif /* end of include guard: LO21_TOWER */
