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

#define MAP_SIZE 16
#define TILE_SIZE 30

class lo21 : public QMainWindow
{
Q_OBJECT
public:
	lo21();
	virtual ~lo21();

private:
	void loadMap(const QString &path);
	void loadWaves(const QString &path);

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

private slots:
	void update();
};

#endif // LO21_HPP

