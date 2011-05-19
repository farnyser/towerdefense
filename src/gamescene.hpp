#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include <qt4/QtGui/qgraphicsscene.h>


class GameScene : public QGraphicsScene
{
Q_OBJECT
public:
	GameScene(QObject* parent = 0);
	virtual ~GameScene();
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
signals:
	void clickOnScene(int x,int y);
};

#endif // GAMESCENE_HPP



