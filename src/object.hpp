#ifndef LO21_OBJECT
#define LO21_OBJECT

#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include "config.hpp"

const float RAD_DEG = 360.0 / (2 * 3.14);
const float DEG_RAD = 1.0 / RAD_DEG;

class lo21;

class Object: public QGraphicsItem
{
public:
	Object(lo21* g, QList<QPixmap> p, int interval = 10, QGraphicsItem *parent = 0);

	void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget);
	QRectF boundingRect() const;
	
	QPoint getCenterPos() const;
	QPointF getHalfSize() const;

protected:
	lo21* game;
	virtual void action() = 0;
	qreal angle;

private:
	QList<QPixmap> animatedPixmap;
	int frameInterval, currentFrame;
	int pixHeight,pixWidth;
	void incCurrentFrame();
	int getCurrentFrame() const;
	void advance(int phase);
};

#endif /* end of include guard: LO21_OBJECT */

