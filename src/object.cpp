#include <QDebug>
#include "object.hpp"

Object::Object(lo21* g, QList<QPixmap> p, int interval, QGraphicsItem *parent)
 : game(g), QGraphicsItem(parent), animatedPixmap(p), frameInterval(interval)
{
	this->currentFrame = 0;
}

QPointF Object::getCenterPos() const
{
	if ( this->animatedPixmap.size() )
	{
		return QPointF(
			this->animatedPixmap[this->getCurrentFrame()].width() / 2.0,
			this->animatedPixmap[this->getCurrentFrame()].height() / 2.0
		);
	}
	else
	{
		return QPointF(0.0, 0.0);
	}
}

int Object::getCurrentFrame() const
{
	if (this->animatedPixmap.size() > 1)
	{
		// calcul du numero de la frame a afficher
		// exemple : currentFrame = 42, frameInterval = 10
		// affichage de la 5eme frame (0,1,2,3,[4],3,2,1)
		int i = (this->currentFrame-this->currentFrame%this->frameInterval)/this->frameInterval;
		
		// affichage sequence inverse
		// exemple: size = 5, currentFrame = 62, frameInterval = 10 => i = 6
		// et i = 6 - 2 - (6%5) = 4-1 = 3eme image
		// affichage de la 3eme frame (0,1,[2],3,4,3,[2],1)
		if (i >= this->animatedPixmap.size())
			i = this->animatedPixmap.size() - 2 - (i % this->animatedPixmap.size());

		return i;
	}

	return 0;
}

void Object::incCurrentFrame()
{
	// ce test est necessaire car A % 0
	// entraine une floatting point exception
	// de plus, si une seule image, pas besoin de boucler
	if (this->animatedPixmap.size() > 1)
	{
		this->currentFrame++;
		this->currentFrame %= ((this->animatedPixmap.size()*2-2) * this->frameInterval);

		if (this->currentFrame % this->frameInterval == 0)
			this->update();
	}
}

void Object::paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (this->animatedPixmap.size())
		p->drawPixmap(0, 0, this->animatedPixmap[this->getCurrentFrame()]);
}

QRectF Object::boundingRect() const
{
	if (this->animatedPixmap.size())
		return this->animatedPixmap[this->getCurrentFrame()].rect();
	else
		return QRect(0, 0, 1, 1);
}

void Object::advance(int phase)
{
	if (phase == 0)
		return;
	else
	{
		this->incCurrentFrame();
		this->action();
	}
}

