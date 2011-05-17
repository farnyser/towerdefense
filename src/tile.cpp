#include "tile.hpp"
#include "ressources.hpp"

//
// Tile
//

Tile::Tile(lo21 *g, QList<QPixmap> p, int interval)
 : Object(g, p,interval)
{
}

void Tile::advance()
{
}

//
// Grass
//

Grass::Grass(lo21 *g) 
 : Tile(g, Ressources::getAnimatedPixmap("grass"),Ressources::getAnimatedInterval("grass")), tower(NULL) 
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

Mud::Mud(lo21 *g)
 : Tile(g, Ressources::getAnimatedPixmap("mud"), Ressources::getAnimatedInterval("mud"))
{
}

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

