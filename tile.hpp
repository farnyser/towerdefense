#ifndef LO21_TILE_HPP
#define LO21_TILE_HPP

#include <QGraphicsItem>

class Tile : public QGraphicsItem
{
	public:
		virtual bool isBuildable() = 0;
};

class Grass : public Tile
{
};

class Mud : public Tile
{
};

class Road : public Tile
{
};

#endif /* end of include guard: LO21_TILE_HPP */
