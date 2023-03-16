#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <ctime>
#include <cstdlib>

#define BOX_HEIGHT	540
#define BOX_WIDTH	690
#define X_OFFSET	10
#define Y_OFFSET	10

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void setPerc(double value) {
		perc = value;
		update();
	}

	void paintEvent(QPaintEvent *) {
		QPainter p(this);

		for (int i = 0; i < BOX_HEIGHT; ++i) {
			memcpy(pixels[i], root_pixels[i], BOX_WIDTH * sizeof(unsigned int));
		}

		p.setPen(QColor((pixels[0][0] >> 16) & 0xFF, (pixels[0][0] >> 8) & 0xFF, pixels[0][0] & 0xFF, 0xFF));
		p.drawPoint(X_OFFSET, Y_OFFSET);

		int i = 0;
		while (i < 2) {
			for (int y = 0; y < BOX_HEIGHT; ++y) {
				for (int x = 0; x < BOX_WIDTH; ++x) {
					if (perc >= hlinks[y][x]) {
						pixels[y][x + 1] = pixels[y][x];
					}
					if (perc >= vlinks[y][x]) {
						pixels[y + 1][x] = pixels[y][x];
					}
				}
			}

			for (int y = BOX_HEIGHT - 1; y > 0; --y) {
				for (int x = BOX_WIDTH - 1; x > 0; --x) {
					if (perc >= hlinks[y][x-1]) {
						pixels[y][x] = pixels[y][x-1];
					}

					if (perc >= vlinks[y-1][x]) {
						pixels[y][x] = pixels[y-1][x];
					}
				}
			}
			++i;
		}

		for (int y = 0; y < BOX_HEIGHT; ++y) {
			for (int x = 0; x < BOX_WIDTH; ++x) {
				p.setPen(QColor((pixels[y][x] >> 16) & 0xFF, (pixels[y][x] >> 8) & 0xFF, pixels[y][x] & 0xFF, 0xFF));
				p.drawPoint(X_OFFSET + x, Y_OFFSET + y);
			}
		}

		p.end();
	}
private:
	double perc = 0.5;

	unsigned int root_pixels[BOX_HEIGHT][BOX_WIDTH];
	unsigned int pixels[BOX_HEIGHT][BOX_WIDTH];

	float hlinks[BOX_HEIGHT][BOX_WIDTH - 1];
	float vlinks[BOX_HEIGHT - 1][BOX_WIDTH];

	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
