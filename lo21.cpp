#include "lo21.hpp"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>

lo21::lo21(): QMainWindow(0,0), scene(0, 0, 640, 440),view(this)
{
   view.setScene(&scene);
   setCentralWidget( &view );
   
   Object b;
   scene.addItem(&b);
   scene.advance();
}

lo21::~lo21()
{}




#include "lo21.moc"
