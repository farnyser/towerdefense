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

bool Tile::isWalkable() const
{
	return false;
}

bool Tile::isBuildable() const
{
	return false;
}

bool Tile::isStartPoint() const
{
	return false;
}

bool Tile::isEndPoint() const
{
	return false;
}

const vec2f Tile::getVector() const
{
	vec2f vector;
	return vector;
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

//
// Mud
//

Mud::Mud(lo21 *g)
 : Tile(g, Ressources::getAnimatedPixmap("mud"), Ressources::getAnimatedInterval("mud"))
{
}

//
// Road
//

Road::Road(lo21* game)
 : Tile(game, Ressources::getAnimatedPixmap("road"), Ressources::getAnimatedInterval("road"))
{
	this->startpoint = false;
	this->endpoint = false;
}

void Road::setStart()
{
	this->endpoint = false;
	this->startpoint = true;
}

void Road::setEnd()
{
	this->startpoint = false;
	this->endpoint = true;
}

void Road::setVector(vec2f vector)
{
	this->vector = vector;
}

bool Road::isWalkable() const
{
	return true;
}

bool Road::isStartPoint() const
{
	return this->startpoint;
}

bool Road::isEndPoint() const
{
	return this->endpoint;
}

const vec2f Road::getVector() const
{
	return this->vector;
}

