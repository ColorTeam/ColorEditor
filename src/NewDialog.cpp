#include "NewDialog.h"
#include <cstdio>

NewDialog::NewDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	img_width = 0;
	img_height = 0;

	view_width = 1024;
	view_height = 1024;
}

NewDialog::~NewDialog()
{

}

void NewDialog::chooseFile() {
	QString path = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		".",
		tr("Image Files(*.png *.jpg *.jpeg)"));	
	if (!path.isEmpty()) {
		/*QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}*/
		QImage img(path);
		if (img.width() && img.height()) {
			img_width = img.width();
			img_height = img.height();
			onFilePathChange(path);
			onFileWidthChange(QString::number(img_width*view_height/img_height, 10));
		}
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}

void NewDialog::setViewWidth(QString w) {
	view_width = w.toInt();
}

void NewDialog::setViewHeight(QString h) {
	view_height = h.toInt();
}

void NewDialog::pressOK() {
	
}