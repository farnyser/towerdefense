#ifndef LO21_OBJECT
#define LO21_OBJECT

#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>

class lo21;

class Object: public QGraphicsItem
{
public:
	Object(lo21* g, QList<QPixmap> p, int interval = 10, QGraphicsItem *parent = 0);

	void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget);
	QRectF boundingRect() const;
	QPointF getCenterPos() const;

protected:
	const lo21* game;
	virtual void advance() = 0;

private:
	QList<QPixmap> animatedPixmap;
	int frameInterval, currentFrame;
	void incCurrentFrame();
	int getCurrentFrame() const;
	void advance(int phase);
};

#endif /* end of include guard: LO21_OBJECT */

