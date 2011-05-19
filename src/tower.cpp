#include "tower.hpp"


Tower::Tower(lo21* g, QList< QPixmap > p)
:Object(g, p)
{
}

WaterGun::WaterGun(lo21* g)
:Tower(g,Ressources::getAnimatedPixmap("watergun"))
{	
}

void WaterGun::advance()
{
}
