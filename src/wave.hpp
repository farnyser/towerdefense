#ifndef LO21_WAVE_HPP
#define LO21_WAVE_HPP
#include <QtCore>
#include "enemy.hpp"

class Wave
{

public:
	Wave(QString comment,QString enemyType,float size, int amount, int interval, bool withPause);
	//Avance d'une unité de temps et renvoie vrai si un insecte doit etre crée.
	bool tick();
	Enemy* getEnemy(lo21* game);
	bool end() const;
	const QString& getComment() const;
	bool isWithPause() const	{return withPause;}
private:
	QString comment;
	Enemy::Type enemyType;
	float size;
	int amount;
	int interval;
	bool withPause;
	
	int ticksLeftBeforeNextEnnemis;
};

#endif // LO21_WAVE_HPP
