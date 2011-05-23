#ifndef LO21_TILE_HPP
#define LO21_TILE_HPP

#include <QGraphicsItem>
#include "object.hpp"

class Tower;
typedef QPair<QPoint, QPointF> vec2f;

class Tile : public Object 
{
protected:
	Tile(lo21* g, QList<QPixmap> p, int interval = 1);

public:
	void action();
	virtual bool isBuildable() const;
	virtual bool isWalkable() const;
	virtual bool isStartPoint() const;
	virtual bool isEndPoint() const;
	virtual const vec2f getVector() const;
	bool buildTower(Tower *t);
	const Tower* getTower() const;

protected:
	Tower *tower;
};

class Grass : public Tile
{
public:
	Grass(lo21*);
	bool isBuildable() const;
};

class Mud : public Tile
{
public:
	Mud(lo21*);
};

class Road : public Tile
{
protected:
	vec2f vector;
	bool startpoint;

public:
	Road(lo21*);
	
	void setStart();
	void setEnd();
	void setVector(vec2f);

	bool isWalkable() const;
	bool isStartPoint() const;
	const vec2f getVector() const;
};

class Goal : public Tile 
{
public:
	Goal(lo21*);
	bool isEndPoint() const;
	bool isWalkable() const;
};

#endif /* end of include guard: LO21_TILE_HPP */
