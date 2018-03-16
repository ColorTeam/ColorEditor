#include "openglwindow.h"  
#include <cstdio>

openglwindow::openglwindow(QWidget *parent)
	:QOpenGLWidget(parent)
{
	//����OpenGL�İ汾��Ϣ  
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
	//��ʼ��OpenGL����  
	initializeOpenGLFunctions();

	//����ȫ�ֱ���  
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void openglwindow::paintGL()
{
	//������Ļ  
	glClear(GL_COLOR_BUFFER_BIT);
}

void openglwindow::resizeGL(int width, int height)
{
	//δʹ��  
	Q_UNUSED(width);
	Q_UNUSED(height);
}

void openglwindow::setStartX(int x) {
	ViewStartX = x;	
#ifdef _DEBUG
	printf("StartX: %d\n", ViewStartX);
#endif
}
