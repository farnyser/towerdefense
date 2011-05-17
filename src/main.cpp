#include <QtGui/QApplication>
#include "lo21.hpp"


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	lo21 foo;
	foo.show();
	return app.exec();
}
