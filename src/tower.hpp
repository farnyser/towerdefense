#ifndef LO21_TOWER
#define LO21_TOWER

#include "object.hpp"
#include "ressources.hpp"

class Tower: public Object
{
private:
	int level;
protected:
	Tower(lo21* g,QList<QPixmap> p);
};

class WaterGun: public Tower
{
public:
	WaterGun(lo21* g);
	void advance();
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
