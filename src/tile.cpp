#include "tile.hpp"
#include "ressources.hpp"
#include "tower.hpp"

//
// Tile
//

Tile::Tile(lo21 *g, QList<QPixmap> p, int interval)
 : Object(g, p,interval), tower(NULL)
{
	// evite l'appel a paint pour un object sans transformation
	this->setCacheMode(DeviceCoordinateCache);
}

void Tile::action()
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

bool Tile::buildTower(Tower *tw)
{
	if ( isBuildable() && tw != NULL && tower == NULL )
	{
		tower = tw;
		tw->setParentItem(this);
		return true;
	}

	return false;
}

//
// Grass
//

Grass::Grass(lo21 *g) 
 : Tile(g, Ressources::getAnimatedPixmap("grass"),Ressources::getAnimatedInterval("grass")) 
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
}

void Road::setStart()
{
	this->startpoint = true;
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

const vec2f Road::getVector() const
{
	return this->vector;
}

//
// End
//

Goal::Goal(lo21 *game) 
 : Tile(game, Ressources::getAnimatedPixmap("end"), Ressources::getAnimatedInterval("end"))
{
	Grass *grass = new Grass(game);
	grass->setFlags(ItemStacksBehindParent);
	grass->setParentItem(this);
}

bool Goal::isWalkable() const
{
	return true;
}

bool Goal::isEndPoint() const
{
	return true;
}


