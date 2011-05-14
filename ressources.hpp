#ifndef LO21_RESSOURCES_HPP
#define LO21_RESSOURCES_HPP

#include <QList>
#include <QGraphicsItem>


class Ressources 
{
public:
	 static QList<QPixmap> getAnimatedPixmap(QString);
	 static int getAnimatedInterval(QString);

private:
	QMap<QString, QList<QPixmap> > animatedPixmap;
	QMap<QString, int> animatedInterval;
	static Ressources *_singleton;

private:
	Ressources();
	~Ressources();
	static Ressources* getInstance();
};

#endif /* end of include guard: LO21_RESSOURCES_HPP */
