#include "object.hpp"
#include <iostream>

Object::Object(QGraphicsItem *parent)
	: QGraphicsItem(parent)
{
	this->frameInterval = 10;
	this->currentFrame = 0;

	// chargement des images
	// dans les classes filles
	
	// pour le test
	this->animatedPixmap.push_back(QPixmap("ressources/images/cafard1.png"));
	this->animatedPixmap.push_back(QPixmap("ressources/images/cafard2.png"));
	this->animatedPixmap.push_back(QPixmap("ressources/images/cafard3.png"));
}

void Object::paint(QPainter* p,const QStyleOptionGraphicsItem* option,QWidget* widget)
{
	if ( this->animatedPixmap.size() )
	{
		p->drawPixmap(0,0,this->animatedPixmap[(this->currentFrame-this->currentFrame%this->frameInterval)/this->frameInterval]);
	}
	else
	{
		p->setBrush(Qt::blue);
		p->drawRoundedRect(0,0,40,40,5,5);
	}
}

QRectF Object::boundingRect() const
{
	if ( this->animatedPixmap.size() )
	{
		return this->animatedPixmap[(this->currentFrame-this->currentFrame%this->frameInterval)/this->frameInterval].rect();
	}
	else
	{
		return QRect(0,0,40,40);
	}
}

void Object::advance(int phase)
{
	if (phase == 0) 
		return; 

	// ce test est necessaire car A % 0 
	// entraine une floatting point exception
	if ( this->animatedPixmap.size() )
	{
		this->currentFrame++;
		this->currentFrame %= (this->animatedPixmap.size() * this->frameInterval);

		if ( this->currentFrame % this->frameInterval == 0 )
			this->update();
	}
}
