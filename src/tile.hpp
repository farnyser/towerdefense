#ifndef LO21_TILE_HPP
#define LO21_TILE_HPP

#include <QGraphicsItem>
#include "object.hpp"

class Tower;
typedef QPair<QPoint, QPoint> vec2i;

class Tile : public Object 
{
protected:
	Tile(lo21* g, QList<QPixmap> p, int interval = 1);

public:
	void advance();
	virtual bool isBuildable() const;
	virtual bool isWalkable() const;
	virtual bool isStartPoint() const;
	virtual bool isEndPoint() const;
	virtual const vec2i getVector() const;
};

class Grass : public Tile
{
public:
	Grass(lo21*);
	bool isBuildable() const;
private:
	Tower *tower;
};

class Mud : public Tile
{
public:
	Mud(lo21*);
};

class Road : public Tile
{
protected:
	vec2i vector;
	bool startpoint;
	bool endpoint;

public:
	Road(lo21*);
	
	void setStart();
	void setEnd();
	void setVector(vec2i);

	bool isWalkable() const;
	bool isStartPoint() const;
	bool isEndPoint() const;
	const vec2i getVector() const;
};

#endif /* end of include guard: LO21_TILE_HPP */
