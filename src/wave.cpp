#include "wave.hpp"


Wave::Wave(QString comment,QString enemyType, float size, int amount, int interval)
:comment(comment),size(size),amount(amount),interval(interval), ticksLeftBeforeNextEnnemis(interval)
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

const QString& Wave::getComment() const
{
	return comment;
}

bool Wave::tick()
{
	return !(--ticksLeftBeforeNextEnnemis);
}

bool Wave::end() const
{
	return !amount;
}

Enemy* Wave::getEnemy(lo21* game)
{
	if(ticksLeftBeforeNextEnnemis || !amount)
		return NULL;
	
	ticksLeftBeforeNextEnnemis=interval;
	amount--;
	
	Enemy* e = NULL;
	
	switch(enemyType)
	{
		case ANT:
			e = new Ant(game, size);
			break;
		case BUG:
			e = new Bug(game, size);
			break;
		case BEE:
			e = new Bee(game, size);
			break;
		case MOSQUITO:
			e = new Mosquito(game, size);
			break;
	}
	
	return e;
}

