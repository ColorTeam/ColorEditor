#include "Editor.h"

Editor::Editor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void Editor::onActionNewTriggered() {
	newdialog.show();
}
