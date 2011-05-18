#include "wave.hpp"


Wave::Wave(QString enemyType, float size, int amount, int interval)
:size(size),amount(amount),interval(interval), ticksLeftBeforeNextEnnemis(interval)
{
	if(enemyType=="fourmi")
		this->enemyType=ANT;
	else if(enemyType=="cafard")
		this->enemyType=BUG;
	else if(enemyType=="guepe")
		this->enemyType=BEE;
	else if(enemyType=="moustique")
		this->enemyType=MOSQUITO;
	//else
		//throw Exception("Type d'ennemis non connus");
}

bool Wave::tick()
{
	return !(--ticksLeftBeforeNextEnnemis);
}

bool Wave::end()
{
	return !amount;
}

Enemy* Wave::getEnemy(lo21* game)
{
	if(ticksLeftBeforeNextEnnemis || !amount)
		return NULL;
	
	ticksLeftBeforeNextEnnemis=interval;
	amount--;
	
	Enemy* e;
	
	switch(enemyType)
	{
		case ANT:
			e=new Ant(game);
			break;
		case BUG:
			e= new Bug(game);
			break;
		case BEE:
			e= new Bee(game);
		case MOSQUITO:
			e= new Mosquito(game);
			break;
		default:
			e= NULL;
	}
	
	
	e->setScale(size);
	
	return e;
}

