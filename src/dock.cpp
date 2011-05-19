#include "dock.hpp"

Dock::Dock(QWidget* parent, Qt::WindowFlags flags): QDockWidget(tr("Options"),parent, flags),ui(new Ui_DockWidget)
{
	ui->setupUi(this);
}
