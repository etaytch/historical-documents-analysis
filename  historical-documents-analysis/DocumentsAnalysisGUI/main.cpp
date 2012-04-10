#include "hdamainframe.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HdaMainFrame w;
	w.show();
	return a.exec();
}
