#include "gl_helper.h"

const char* ReadAll(char* filepath) {
	FILE *fp = fopen(filepath, "rb");
	if (!fp) return NULL;
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *content = (char*)malloc(size + 1);
	fread(content, sizeof(char), size, fp);
	content[size] = '\0';
	fclose(fp);
	return (const char*)content;
}

bool GLInit(int argc, char **argv, int width, int height, const char *title) {
	// ��ʼ��GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 

	glutInitWindowSize(width, height);      // ���ڳߴ�
	glutInitWindowPosition(100, 100);  // ����λ��
	glutCreateWindow(title);   // ���ڱ���

							   // ��ʼ��Ⱦ

							   // ���GLEW�Ƿ����������Ҫ��GLUT��ʼ��֮��
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		printf("Error: '%s'\n", glewGetErrorString(res));
		return false;
	}
	return true;
}

bool GLProgram::UseShaders_file(char *vert_path, char *frag_path) {
	const char *vert_shader = ReadAll(vert_path);
	const char *frag_shader = ReadAll(frag_path);

	return UseShaders(vert_shader, frag_shader);
}