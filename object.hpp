#include <QGraphicsItem>
#include <QPainter>

class Object: public QGraphicsItem
{
public:
	Object(QGraphicsItem *parent = 0)
		: QGraphicsItem(parent)
	{
	}

    void paint(QPainter* p,const QStyleOptionGraphicsItem* option,QWidget* widget)
    {
		p->setBrush(Qt::blue);
		p->drawRoundedRect(0,0,40,40,5,5);
    }

    QRectF boundingRect() const
    {
		return QRect(0,0,40,40);
    }


private:
    int x,y,a;

    int frameInterval;
    QList<QPixmap> animatedPixmap;

};

class Enemy: public Object
{
private:
    float hp;
    int size;

};

class Tower: public Object
{
private:
    int level;

};

class Ant: public Enemy
{

};

class Bug: public Enemy
{

};

class Bee: public Enemy
{

};

class Mosquito: public Enemy
{

};

class WaterGun: public Tower
{

};

class Slingshot: public Tower
{

};

class PaintBall: public Tower
{

};

class PetanquePlayer: public Tower
{

};

class Musician: public Tower
{

};
