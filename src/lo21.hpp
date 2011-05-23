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

class lo21 : public QMainWindow
{
Q_OBJECT
public:
	lo21();
	virtual ~lo21();

public:
	void loadMap(const QString &path);
	void loadWaves(const QString path);
	const Tile* getTile(int x, int y) const;
	const Tile* getStart() const;
	void addObject(Object* o);
	Tile* getTile(int x, int y);

private:
	// configuration
	int lives;
	int credits;
	
	// widgets et objets
	QGraphicsView view;
	GameScene scene;
	QTimer timer;
	Dock dock;
	Tower::Type selectedTower;

	Tile *tileMap[MAP_SIZE][MAP_SIZE];
	Tile *start;
	
	QList<Wave> waves;
	int timeUntilNextWave;
	
private slots:
	void updateGame();
	
public slots:
	void launchWave();
	void selectTowerWater();
	void selectTowerRock();
	void selectTowerPaint();
	void selectTowerPetanque();
	void clickOnScene(int x,int y);
	
signals:
	void advance_scene();
};

#endif // LO21_HPP

