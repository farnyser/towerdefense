#ifndef LO21_OBJECT
#define LO21_OBJECT

#include <QGraphicsItem>
#include <QPainter>

class Object: public QGraphicsItem
{
public:
	Object(QGraphicsItem *parent = 0);

	void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget);
	QRectF boundingRect() const;

private:
	int x, y, a;

	int frameInterval, currentFrame;
	QList<QPixmap> animatedPixmap;

	void advance(int phase);
};

#endif /* end of include guard: LO21_OBJECT */

