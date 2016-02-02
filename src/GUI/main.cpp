#include "SETestKCL_GUI.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	SETestKCL_GUI w;
	w.show();

	return a.exec();
}