#ifndef LO21_TILE_HPP
#define LO21_TILE_HPP

#include <QGraphicsItem>
#include "object.hpp"

class Tower;
typedef QPair<QPoint, QPoint> vec2i;

class Tile : public Object 
{
protected:
	Tile(QList<QPixmap> p, int interval = 1);

public:
	virtual bool isBuildable() const = 0;
	virtual bool isWalkable() const = 0;
};

class Grass : public Tile
{
public:
	Grass(QList<QPixmap> p);
	bool isBuildable() const;
	bool isWalkable() const;
private:
	Tower *tower;
};

class Mud : public Tile
{
public:
	bool isBuildable() const;
	bool isWalkable() const;
};

class Road : public Tile
{
protected:
	vec2i vector;
	
public:
	bool isBuildable() const;
	bool isWalkable() const;
	bool isStartPoint() const;
	bool isEndPoint() const;
	const vec2i getVector() const;
};

#endif /* end of include guard: LO21_TILE_HPP */
