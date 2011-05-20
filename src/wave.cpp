#include "wave.hpp"


Wave::Wave(QString comment,QString enemyType, float size, int amount, int interval)
:comment(comment),size(size),amount(amount),interval(interval), ticksLeftBeforeNextEnnemis(interval)
{
	if(enemyType == "fourmi")
		this->enemyType = ENEMY::ANT;
	else if(enemyType == "cafard")
		this->enemyType = ENEMY::BUG;
	else if(enemyType == "guepe")
		this->enemyType = ENEMY::WASP;
	else if(enemyType == "moustique")
		this->enemyType = ENEMY::MOSQUITO;
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
		case ENEMY::ANT:
			e = new Ant(game, size);
			break;
		case ENEMY::BUG:
			e = new Bug(game, size);
			break;
		case ENEMY::WASP:
			e = new Wasp(game, size);
			break;
		case ENEMY::MOSQUITO:
			e = new Mosquito(game, size);
			break;
	}
	
	return e;
}

