#ifndef LO21_HPP
#define LO21_HPP

#include <QMainWindow>
#include <QGraphicsView>

#include "dock.hpp"
#include "wave.hpp"
#include "gamescene.hpp"
#include "tower.hpp"
#include "config.hpp"


class Tile;
class Enemy;
class GameScene;
class QGraphicsItem;

class lo21 : public QMainWindow
{
Q_OBJECT
public:
	lo21();
	virtual ~lo21();

public:
	void loadMap(const QString &path);
	void loadWaves(const QString path);
	const Enemy* getClosestEnemy(int x, int y, unsigned int range, int agtype) const;
	const Tile* getTile(int x, int y) const;
	const Tile* getStart() const;
	void removeObject(Enemy* o);
	void addObject(Enemy* o);
	void removeObject(QGraphicsItem* o);
	void addObject(Object* o);
	void addCredit(int c);
	void subLive(int l);
	void selectTile(Tile *t = NULL);
	bool isEnemy(const void *o) const;

private:
	 Tile* getTile(int x, int y);
	 void updateDock();

private:
	// configuration
	int lives;
	int credits;

	// 0 -> en jeu
	// 1 -> en pause
	// 2 -> fin
	enum State {GAME_RUN, GAME_STOP, GAME_END} state;

	// widgets et objets
	QGraphicsView view;
	GameScene scene;
	QTimer timer;
	Dock dock;
	
	Tower::Type selectedTower;
	
	QList<Enemy*> enemyList;

	Tile *tileMap[MAP_SIZE][MAP_SIZE];
	Tile *start;
	Tile *selectedTile;
	
	QList<Wave> waves;
	int timeUntilNextWave;

	QList<QGraphicsItem*> deleteLaters;
	
private slots:
	void updateGame();
	
public slots:
	void newGame();
	void launchWave();
	void toggleState();
	void selectTowerWater();
	void selectTowerRock();
	void selectTowerPaint();
	void selectTowerPetanque();
	void upgradeTower();
	void sellTower();
	void clickOnScene(int x,int y);
	
signals:
	void advance_scene();
};

#endif // LO21_HPP

