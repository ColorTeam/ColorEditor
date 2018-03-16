#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Editor.h"
#include "NewDialog.h"

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor(QWidget *parent = Q_NULLPTR);

public slots:
	void onActionNewTriggered();

private:
	Ui::EditorClass ui;
	NewDialog newdialog;
};
