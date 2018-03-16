#ifndef GL_HELPER_INCLUDE
#define GL_HELPER_INCLUDE

#include <glew.h>
#include <freeglut.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

extern GLuint VBO;
extern GLuint EBO;

class GLProgram {
public:
	GLProgram() {
		m_programID = 0;
	}
	~GLProgram() {
		DeleteProgram();
	}
	bool CreateProgram() {
		m_programID = glCreateProgram();
		if (m_programID == 0) {
			printf("Error creating shader program\n");
			return false;
		}
		return true;
	}
	GLuint GetUniformLocation(char* name) {
		return glGetUniformLocation(m_programID, name);
	}
	bool DeleteProgram() {
		glDeleteProgram(m_programID);
		m_programID = 0;
		return true;
	}
	bool UseProgram() {
		glUseProgram(m_programID);
		return true;
	}
	bool DisuseProgram() {
		glUseProgram(0);
		return true;
	}
	GLuint GetProgramID() {
		return m_programID;
	}

	bool Compile() {
		GLint Success = 0;
		GLchar ErrorLog[1024] = { 0 };
		glLinkProgram(m_programID);
		glGetProgramiv(m_programID, GL_LINK_STATUS, &Success);
		if (Success == 0) {
			glGetProgramInfoLog(m_programID, sizeof(ErrorLog), NULL, ErrorLog);
			printf("Error linking shader program: '%s'\n", ErrorLog);
			return false;
		}
		// 检查验证在当前的管线状态程序是否可以被执行
		glValidateProgram(m_programID);
		glGetProgramiv(m_programID, GL_VALIDATE_STATUS, &Success);
		if (!Success) {
			glGetProgramInfoLog(m_programID, sizeof(ErrorLog), NULL, ErrorLog);
			printf("Invalid shader program: '%s'\n", ErrorLog);
			return false;
		}
		// 设置到管线声明中来使用上面成功建立的shader程序
		glUseProgram(m_programID);
		return true;
	}

	bool UseShaders(const char *vert_shader, const char *frag_shader) {
		if (m_programID == 0) m_programID = glCreateProgram();

		m_vertex_shaderID = glCreateShader(GL_VERTEX_SHADER);
		m_fragment_shaderID = glCreateShader(GL_FRAGMENT_SHADER);

		if (m_vertex_shaderID == 0 || m_fragment_shaderID == 0) {
			printf("Error creating shader.\n");
			return false;
		}
		glShaderSource(m_vertex_shaderID, 1, (const char**)&vert_shader, NULL);
		glShaderSource(m_fragment_shaderID, 1, (const char**)&frag_shader, NULL);
		glCompileShader(m_vertex_shaderID);// 编译shader对象
		glCompileShader(m_fragment_shaderID);// 编译shader对象


		GLint success;
		glGetShaderiv(m_vertex_shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar InfoLog[1024];
			glGetShaderInfoLog(m_vertex_shaderID, 1024, NULL, InfoLog);
			printf("Error compiling 'vertex shader': '%s'\n", InfoLog);
			return false;
		}
		glGetShaderiv(m_fragment_shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar InfoLog[1024];
			glGetShaderInfoLog(m_fragment_shaderID, 1024, NULL, InfoLog);
			printf("Error compiling 'fragment shader': '%s'\n", InfoLog);
			return false;
		}

		glAttachShader(m_programID, m_vertex_shaderID);
		glAttachShader(m_programID, m_fragment_shaderID);

		return Compile();
	}

	bool UseShaders_file(char *vert_path, char *frag_path);

private:
	GLuint m_programID;
	GLuint m_vertex_shaderID;
	GLuint m_fragment_shaderID;
};

class GLRTT {
	/*
	1. setFrameSize
	2. creatFrameBuffer
	3. creatColorBuffer
	4. creatDepthBuffer
	5. bindFrameBuffer
	6. draw.......
	7. unbindFrameBuffer
	8. getColorData
	using glCheckFramebufferStatus to check the status of present frame buffer.
	*/
public:
	GLRTT() : m_width(0), m_height(0), m_frameBuffer(0u), m_colorBuffer(0u), m_depthBuffer(0u) {}
	~GLRTT() {
		DeleteRTT();
	}
	void CreateRTT(int width, int height, GLuint internalformat, GLuint inputformat = GL_RGB) {
		SetFrameSize(width, height);
		glGenFramebuffers(1, &m_frameBuffer);
		CreateColorBuffer(internalformat, inputformat);
		CreateDepthBuffer();

		/*SetFrameSize(width, height);
		CreatFrameBuffer();
		CreatColorBuffer(internalformat);
		CreatDepthBuffer();*/
	}
	void UseRTT() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
		glViewport(0, 0, m_width, m_height);

		/*
		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		printf("Wrong drawing framebuffer.\n");
		}*/
	}
	void DeleteRTT() {
		if (m_frameBuffer) {
			glDeleteFramebuffers(1, &m_frameBuffer);
			m_frameBuffer = 0u;
		}
		if (m_colorBuffer) {
			glDeleteTextures(1, &m_colorBuffer);
			m_colorBuffer = 0u;
		}
		if (m_depthBuffer) {
			glDeleteRenderbuffers(1, &m_depthBuffer);
			m_depthBuffer = 0u;
		}

	}
	void SetFrameSize(int _width, int _height) {
		m_width = _width;
		m_height = _height;
	}
	void BindFrameBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	}
	void UnbindFrameBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0u);
	}
	void CreateFrameBuffer() {
		glGenFramebuffers(1, &m_frameBuffer);
	}
	//internalFormat, GL_RGBA8
	void CreateColorBuffer(GLuint internalFormat, GLuint inputformat) {
		assert(m_width != 0 && m_height != 0 && m_frameBuffer != 0u);
		//creat color buffer
		glGenTextures(1, &m_colorBuffer);
		glBindTexture(GL_TEXTURE_2D, m_colorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, inputformat, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0u);
		//attach color buffer
		BindFrameBuffer();
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_colorBuffer, 0);
		UnbindFrameBuffer();
	}
	void CreateDepthBuffer() {
		assert(m_width != 0 && m_height != 0 && m_frameBuffer != 0u);
		//creat depth buffer
		glGenRenderbuffers(1, &m_depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0u);
		//attach depth buffer
		BindFrameBuffer();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
		UnbindFrameBuffer();
	}
	//external format
	void GetColorData(GLvoid* pixels, GLenum format, GLenum type) {
		glBindTexture(GL_TEXTURE_2D, m_colorBuffer);
		glGetTexImage(GL_TEXTURE_2D, 0, format, type, pixels);
		glBindTexture(GL_TEXTURE_2D, 0u);
	}
	GLuint GetFrameBuffer() {
		return m_frameBuffer;
	}
	GLuint GetColorBuffer() {
		return m_colorBuffer;
	}
	GLuint GetDepthBuffer() {
		return m_depthBuffer;
	}
	void GetFrameSize(int &_width, int &_height) {
		_width = m_width;
		_height = m_height;
	}
private:
	int            m_width;
	int            m_height;
	GLuint         m_frameBuffer;
	GLuint         m_colorBuffer;
	GLuint         m_depthBuffer;
};

bool GLInit(int argc, char **argv, int width = 480, int height = 320, const char *title = "Title");

#endif //GL_HELPER_INCLUDE