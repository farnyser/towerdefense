#ifndef LO21_TILE_HPP
#define LO21_TILE_HPP

#include <QGraphicsItem>

class Tower;
typedef QPair<QPoint, QPoint> vec2i;

class Tile : public QGraphicsItem
{
private:
	QPixmap pixmap;

protected:
	Tile(QPixmap p);

public:
	virtual bool isBuildable() const = 0;
	virtual bool isWalkable() const = 0;
};

class Grass : public Tile
{
public:
	Grass(QPixmap p);
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
public:
	bool isBuildable() const;
	bool isWalkable() const;
	bool isStartPoint() const;
	bool isEndPoint() const;
	const vec2i getVector() const;
};

#endif /* end of include guard: LO21_TILE_HPP */
