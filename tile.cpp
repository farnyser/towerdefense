#include "tile.hpp"


//
// Tile
//

Tile::Tile(QList<QPixmap> p, int interval)
{
	this->animatedPixmap = p;
	this->frameInterval = interval;
}

//
// Grass
//

Grass::Grass(QList<QPixmap> p) 
 : Tile(p), tower(NULL) 
{
}

bool Grass::isBuildable() const
{
	return (this->tower == NULL);
}

bool Grass::isWalkable() const
{
	return false;
}

//
// Mud
//

bool Mud::isBuildable() const
{
	return false;
}

bool Mud::isWalkable() const
{
	return false;
}

//
// Road
//

bool Road::isBuildable() const
{
	return false;
}

bool Road::isWalkable() const
{
	return true;
}

bool Road::isStartPoint() const
{
	return /*something*/ false;
}

bool Road::isEndPoint() const
{
	return /*something*/ false;
}

const vec2i Road::getVector() const
{
	return this->vector;
}

