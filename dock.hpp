#ifndef DOCK_HPP
#define DOCK_HPP

#include <qdockwidget.h>


class Dock : public QDockWidget
{
public:
	explicit Dock(QWidget* parent = 0, Qt::WindowFlags flags = 0);
};

#endif // DOCK_HPP
