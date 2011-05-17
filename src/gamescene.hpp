#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include <qt4/QtGui/qgraphicsscene.h>


class GameScene : public QGraphicsScene
{

public:
	GameScene(QObject* parent = 0);
	virtual ~GameScene();
};

#endif // GAMESCENE_HPP



