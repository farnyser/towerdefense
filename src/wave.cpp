#include "wave.hpp"
#include "factory.hpp"

Wave::Wave(QString comment,QString enemyType, float size, int amount, int interval)
:comment(comment),size(size),amount(amount),interval(interval), ticksLeftBeforeNextEnnemis(interval)
{
	if(enemyType == "fourmi")
		this->enemyType = Enemy::ANT;
	else if(enemyType == "cafard")
		this->enemyType = Enemy::BUG;
	else if(enemyType == "guepe")
		this->enemyType = Enemy::WASP;
	else if(enemyType == "moustique")
		this->enemyType = Enemy::MOSQUITO;
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

	return Factory::getEnemy(enemyType, game, size);
}

