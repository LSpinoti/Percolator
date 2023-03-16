#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QLayout>
#include <QSlider>

class DoubleSlider : public QSlider {
	Q_OBJECT

public:
	DoubleSlider(QWidget *parent = 0) : QSlider(parent) {
		connect(this, SIGNAL(valueChanged(int)),
			this, SLOT(notifyValueChanged(int)));
	}

signals:
	void doubleValueChanged(double value);

public slots:
	void doubleSetValue(double value) {
		this->setValue(value * 1000.0);
	}

	void notifyValueChanged(int value) {
		double doubleValue = value / 1000.0;
		emit doubleValueChanged(doubleValue);
	}
};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	srand(time(0));

	// Pixels
	for (int i = 0; i < BOX_HEIGHT; ++i) {
		for (int j = 0; j < BOX_WIDTH; ++j) {
			root_pixels[i][j] = rand();
		}
	}

	// Links
	for (int i = 0; i < BOX_HEIGHT; ++i) {
		for (int j = 0; j < BOX_WIDTH - 1; ++j) {
			hlinks[i][j] = (double)rand() / (double)RAND_MAX;
		}
	}
	for (int i = 0; i < BOX_HEIGHT - 1; ++i) {
		for (int j = 0; j < BOX_WIDTH; ++j) {
			vlinks[i][j] = (double)rand() / (double)RAND_MAX;
		}
	}

	ui->setupUi(this);

	// Slider
	DoubleSlider *slider = new DoubleSlider();
	this->layout()->addWidget(slider);
	slider->setMinimum(0);
	slider->setMaximum(1000);
	slider->setValue(500);
	slider->move(430, 15);
	connect(slider, &DoubleSlider::doubleValueChanged, ui->doubleSpinBox, &QDoubleSpinBox::setValue);
	connect(slider, &DoubleSlider::doubleValueChanged, this, &MainWindow::setPerc);
	connect(ui->doubleSpinBox, &QDoubleSpinBox::valueChanged, slider, &DoubleSlider::doubleSetValue);
}

MainWindow::~MainWindow()
{
	delete ui;
}

#include "mainwindow.moc"
