#include "openglwindow.h"  
#include <cstdio>

openglwindow::openglwindow(QWidget *parent)
	:QOpenGLWidget(parent)
{
	//设置OpenGL的版本信息  
	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(3, 3);
	setFormat(format);

	ViewStartX = 0;
}

openglwindow::~openglwindow()
{

}

void openglwindow::initializeGL()
{
	//初始化OpenGL函数  
	initializeOpenGLFunctions();

	//设置全局变量  
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void openglwindow::paintGL()
{
	//清理屏幕  
	glClear(GL_COLOR_BUFFER_BIT);
}

void openglwindow::resizeGL(int width, int height)
{
	//未使用  
	Q_UNUSED(width);
	Q_UNUSED(height);
}

void openglwindow::setStartX(int x) {
	ViewStartX = x;	
#ifdef _DEBUG
	printf("StartX: %d\n", ViewStartX);
#endif
}
