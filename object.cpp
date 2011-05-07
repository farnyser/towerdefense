#include "object.hpp"

Object::Object(QGraphicsItem *parent)
	: QGraphicsItem(parent)
{
}

void Object::paint(QPainter* p,const QStyleOptionGraphicsItem* option,QWidget* widget)
{
	p->setBrush(Qt::blue);
	p->drawRoundedRect(0,0,40,40,5,5);
}

QRectF Object::boundingRect() const
{
	return QRect(0,0,40,40);
}

