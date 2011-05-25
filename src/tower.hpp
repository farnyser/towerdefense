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
	struct Attribute 
	{
		int level;
		int cost;
		int sellprice;
		float range;
		float power;
		float firerate;
		float bulletSpeed;
	};

protected:
	Attribute attr;
	QList<int> cost;
	int timeUntilNextFire;


public:
	Attribute getAttribute() const;
	Attribute getUpgradedAttribute() const;
	int upgrade();
	int sell();
	void action();

protected:
	Tower(lo21* g,QList<QPixmap> p);
	virtual Attribute computeAttribute(int level) const = 0;
};

class WaterGun: public Tower
{
public:
	WaterGun(lo21* g);
	void action();
protected:
	Tower::Attribute computeAttribute(int level) const;
};

class Slingshot: public Tower
{
public:
	Slingshot(lo21* g);
	void action();
protected:
	Tower::Attribute computeAttribute(int level) const;
};

class PaintBall: public Tower
{
public:
	PaintBall(lo21* g);
	void action();
protected:
	Tower::Attribute computeAttribute(int level) const;
};

class PetanquePlayer: public Tower
{
public:
	PetanquePlayer(lo21* g);
	void action();
protected:
	Tower::Attribute computeAttribute(int level) const;
};

class Musician: public Tower
{

};

#endif /* end of include guard: LO21_TOWER */
