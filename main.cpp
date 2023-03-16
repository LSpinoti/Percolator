#include "mainwindow.h"
#include <QApplication>

#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	w.show();
	w.setFixedSize(800, 560);

	return a.exec();
}
