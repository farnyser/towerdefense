#ifndef LO21_HPP
#define LO21_HPP

#include <QtGui>
#include <QGraphicsView>

#include "object.hpp"
#include "tower.hpp"
#include "enemy.hpp"
#include "tile.hpp"
#include "dock.hpp"
#include "gamescene.hpp"
#include "wave.hpp"

#define MAP_SIZE 16
#define TILE_SIZE 30

class lo21 : public QMainWindow
{
Q_OBJECT
public:
	lo21();
	virtual ~lo21();

public:
	void loadMap(const QString &path);
	void loadWaves(const QString &path);
	const Tile* getTile(int x, int y) const;
	const Tile* getStart() const;

private:
	// configuration
	float frequency;
	int lives;
	int credits;
	
	// widgets et objets
	QGraphicsView view;
	GameScene scene;
	QTimer timer;
	Dock dock;

	Tile* tileMap[MAP_SIZE][MAP_SIZE];
	Tile *start;
	
	QList<Wave> waves;
	
private slots:
	void updateGame();
	
signals:
	void advance_scene();
};

#endif // LO21_HPP

