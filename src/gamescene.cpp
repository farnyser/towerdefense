#include "gamescene.hpp"
#include <QGraphicsSceneMouseEvent>
GameScene::GameScene(QObject* parent): QGraphicsScene(parent)
{

}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	int x = event->scenePos().x();
	int y = event->scenePos().y();

	emit clickOnScene(x,y);
}


GameScene::~GameScene()
{

}

#include "gamescene.moc"
