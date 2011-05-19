#ifndef DOCK_HPP
#define DOCK_HPP

#include <qdockwidget.h>
#include "ui_dock.h"

class Dock : public QDockWidget
{
public:
	explicit Dock(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	
private:
	Ui_DockWidget *ui;
};

#endif // DOCK_HPP
