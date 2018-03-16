#ifndef OPENGL_WINDOW_H_INCLUDE
#define OPENGL_WINDOW_H_INCLUDE

#include <QOpenGLWidget>  
#include <QOpenGLFunctions_3_3_Core>  

class openglwindow : public QOpenGLWidget,
	protected QOpenGLFunctions_3_3_Core
{
	Q_OBJECT

public:
	openglwindow(QWidget *parent = 0);
	~openglwindow();

	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

public slots:
	void setStartX(int);

private:
	int ViewStartX;
};

#endif
