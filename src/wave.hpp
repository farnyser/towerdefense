#ifndef LO21_WAVE_HPP
#define LO21_WAVE_HPP
#include <QtCore>
#include "enemy.hpp"

class Wave
{

public:
	Wave(QString enemyType,float size, int amount, int interval);
	//Avance d'une unité de temps et renvoie vrai si un insecte doit etre crée.
	bool tick();
	Enemy* getEnemy(lo21* game);
	bool end();
private:
	EnemyType enemyType;
	float size;
	int amount;
	int interval;
	
	int ticksLeftBeforeNextEnnemis;
};

#endif // LO21_WAVE_HPP