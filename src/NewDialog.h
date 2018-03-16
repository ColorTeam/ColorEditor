#ifndef NEW_DIALOG_H_INCLUDE
#define NEW_DIALOG_H_INCLUDE

#include <QWidget>
#include <qfiledialog.h>
#include <QMessageBox.h>
#include "ui_NewDialog.h"

class NewDialog : public QWidget
{
	Q_OBJECT

public:
	NewDialog(QWidget *parent = Q_NULLPTR);
	~NewDialog();

	int img_width, img_height;
	int view_width, view_height;

public slots:
	void chooseFile();
	void setViewWidth(QString w);
	void setViewHeight(QString h);
	void pressOK();

signals:
	void onFilePathChange(QString path);
	void onFileWidthChange(QString width);

private:
	Ui::NewDialog ui;
};

#endif //NEW_DIALOG_H_INCLUDE