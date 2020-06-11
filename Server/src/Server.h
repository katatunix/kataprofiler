#pragma once

#include "glDefine.h"
#include "Message.h"
#include "Program.h"
#include "Shader.h"
#include "Texture.h"
#include "Vbo.h"
#include "VertexAttribData.h"
#include "Messenger.h"
#include "thread/Mutex.h"
#include "CaptureOption.h"
#include "GlHelper.h"

class Server
{
public:
	Server(GlHelper glHelper);
	~Server();

	bool isBusy();
	void enterPreCapture();
	void enterModifyingProgram();

	void onRequestCapture(Messenger m, CaptureOption co);
	void onRequestModifyProgram(Messenger m);

	//========================================================================================
	void on_glActiveTexture(GLenum texture);
	void on_glAttachShader(GLuint program, GLuint shader);
	void on_glBindAttribLocation(GLuint program, GLuint index, const GLchar* name);
	void on_glBindBuffer(GLenum target, GLuint buffer);
	void on_glBindFramebuffer(GLenum target, GLuint framebuffer);
	void on_glBindRenderbuffer(GLenum target, GLuint renderbuffer);
	void on_glBindTexture(GLenum target, GLuint texture);
	void on_glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	void on_glBlendEquation(GLenum mode);
	void on_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
	void on_glBlendFunc(GLenum sfactor, GLenum dfactor);
	void on_glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
	void on_glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
	void on_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
	void on_glCheckFramebufferStatus(GLenum target, GLenum result);
	void on_glClear(GLbitfield mask);
	void on_glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	void on_glClearDepthf(GLclampf depth);
	void on_glClearStencil(GLint s);
	void on_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void on_glCompileShader(GLuint shader);
	void on_glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
	void on_glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
	void on_glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
	void on_glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	void on_glCreateProgram(GLuint result);
	void on_glCreateShader(GLenum type, GLuint result);
	void on_glCullFace(GLenum mode);
	void on_glDeleteBuffers(GLsizei n, const GLuint* buffers);
	void on_glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers);
	void on_glDeleteProgram(GLuint program);
	void on_glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers);
	void on_glDeleteShader(GLuint shader);
	void on_glDeleteTextures(GLsizei n, const GLuint* textures);
	void on_glDepthFunc(GLenum func);
	void on_glDepthMask(GLboolean flag);
	void on_glDepthRangef(GLclampf zNear, GLclampf zFar);
	void on_glDetachShader(GLuint program, GLuint shader);
	void on_glDisable(GLenum cap);
	void on_glDisableVertexAttribArray(GLuint index);
	void on_glDrawArrays(GLenum mode, GLint first, GLsizei count);
	void on_glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
	void on_glEnable(GLenum cap);
	void on_glEnableVertexAttribArray(GLuint index);
	void on_glFinish(void);
	void on_glFlush(void);
	void on_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
	void on_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	void on_glFrontFace(GLenum mode);
	void on_glGenBuffers(GLsizei n, GLuint* buffers);
	void on_glGenerateMipmap(GLenum target);
	void on_glGenFramebuffers(GLsizei n, GLuint* framebuffers);
	void on_glGenRenderbuffers(GLsizei n, GLuint* renderbuffers);
	void on_glGenTextures(GLsizei n, GLuint* textures);
	void on_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	void on_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	void on_glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
	void on_glGetAttribLocation(GLuint program, const GLchar* name, GLint result);
	void on_glGetBooleanv(GLenum pname, GLboolean* params);
	void on_glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params);
	void on_glGetError(GLenum result);
	void on_glGetFloatv(GLenum pname, GLfloat* params);
	void on_glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params);
	void on_glGetIntegerv(GLenum pname, GLint* params);
	void on_glGetProgramiv(GLuint program, GLenum pname, GLint* params);
	void on_glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
	void on_glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params);
	void on_glGetShaderiv(GLuint shader, GLenum pname, GLint* params);
	void on_glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
	void on_glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
	void on_glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);
	void on_glGetString(GLenum name, const GLubyte* result);
	void on_glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params);
	void on_glGetTexParameteriv(GLenum target, GLenum pname, GLint* params);
	void on_glGetUniformfv(GLuint program, GLint location, GLfloat* params);
	void on_glGetUniformiv(GLuint program, GLint location, GLint* params);
	void on_glGetUniformLocation(GLuint program, const GLchar* name, GLint result);
	void on_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params);
	void on_glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params);
	void on_glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer);
	void on_glHint(GLenum target, GLenum mode);
	void on_glIsBuffer(GLuint buffer, GLboolean result);
	void on_glIsEnabled(GLenum cap, GLboolean result);
	void on_glIsFramebuffer(GLuint framebuffer, GLboolean result);
	void on_glIsProgram(GLuint program, GLboolean result);
	void on_glIsRenderbuffer(GLuint renderbuffer, GLboolean result);
	void on_glIsShader(GLuint shader, GLboolean result);
	void on_glIsTexture(GLuint texture, GLboolean result);
	void on_glLineWidth(GLfloat width);
	void on_glLinkProgram(GLuint program);
	void on_glPixelStorei(GLenum pname, GLint param);
	void on_glPolygonOffset(GLfloat factor, GLfloat units);
	void on_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
	void on_glReleaseShaderCompiler(void);
	void on_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
	void on_glSampleCoverage(GLclampf value, GLboolean invert);
	void on_glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
	void on_glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length);
	void on_glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
	void on_glStencilFunc(GLenum func, GLint ref, GLuint mask);
	void on_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
	void on_glStencilMask(GLuint mask);
	void on_glStencilMaskSeparate(GLenum face, GLuint mask);
	void on_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass);
	void on_glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
	void on_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
	void on_glTexParameterf(GLenum target, GLenum pname, GLfloat param);
	void on_glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params);
	void on_glTexParameteri(GLenum target, GLenum pname, GLint param);
	void on_glTexParameteriv(GLenum target, GLenum pname, const GLint* params);
	void on_glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
	void on_glUniform1f(GLint location, GLfloat x);
	void on_glUniform1fv(GLint location, GLsizei count, const GLfloat* v);
	void on_glUniform1i(GLint location, GLint x);
	void on_glUniform1iv(GLint location, GLsizei count, const GLint* v);
	void on_glUniform2f(GLint location, GLfloat x, GLfloat y);
	void on_glUniform2fv(GLint location, GLsizei count, const GLfloat* v);
	void on_glUniform2i(GLint location, GLint x, GLint y);
	void on_glUniform2iv(GLint location, GLsizei count, const GLint* v);
	void on_glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z);
	void on_glUniform3fv(GLint location, GLsizei count, const GLfloat* v);
	void on_glUniform3i(GLint location, GLint x, GLint y, GLint z);
	void on_glUniform3iv(GLint location, GLsizei count, const GLint* v);
	void on_glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void on_glUniform4fv(GLint location, GLsizei count, const GLfloat* v);
	void on_glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w);
	void on_glUniform4iv(GLint location, GLsizei count, const GLint* v);
	void on_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	void on_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	void on_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	void on_glUseProgram(GLuint program);
	void on_glValidateProgram(GLuint program);
	void on_glVertexAttrib1f(GLuint indx, GLfloat x);
	void on_glVertexAttrib1fv(GLuint indx, const GLfloat* values);
	void on_glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y);
	void on_glVertexAttrib2fv(GLuint indx, const GLfloat* values);
	void on_glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z);
	void on_glVertexAttrib3fv(GLuint indx, const GLfloat* values);
	void on_glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void on_glVertexAttrib4fv(GLuint indx, const GLfloat* values);
	void on_glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
	void on_glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
	// Extensions
	void on_glMapBufferOES(GLenum target, GLenum access, void* ptr);
	void on_glUnmapBufferOES(GLenum target);
	// OpenGL ES 3.0
	void on_glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
	//=======================================================================================

	void onSwapBuffers();

private:
	GlHelper m_glHelper;

	enum State
	{
		IDLE = 0,
		PRE_CAPTURE,
		CAPTURING,
		MODIFYING_PROGRAM
	};
	volatile State m_state;

	Program*	getProgram(u32 id);
	Program*	getFreeProgram();

	Shader*		getShader(u32 id);
	Shader*		getFreeShader();

	Texture*	getTexture(u32 id);
	Texture*	getFreeTexture();

	Vbo*		getVbo(u32 id);
	Vbo*		getFreeVbo();

	int calculateVertexAttribDataLength(Program* prog, int vertexCount);

	void makeVertexAttribData(char* buffer, Program* prog,
		bool isDrawElements,
		GLsizei countElements, GLenum type, const GLvoid* indices,
		GLint first, GLsizei countArrays);

	Program* validate_glUniform1234fiv(const char* funcName, int comps, bool isFloat, bool isVector, GLint location, GLsizei count = 0);

	Program* validate_glUniformMatrix(const char* funcName, int size, GLint location, GLsizei count, GLboolean transpose);

	void copyCurrentFboToTexture(char** pixels, int width, int height);

	char* takeRgbaScreenshot(int& width, int& height);
	char* makeBgrScreenshot(char* rgba, int width, int height, int& widthScaled, int& heightScaled, int& imageLen);

	bool sendObjects();
	int sendTexUnits();
	void modifyProgram();

	Message m_msg;
	void makeGLCommandMsg(KPMessageType type);
	
	Mutex m_mutex;

	enum
	{
		MAX_TEXTURES_NUMBER				= 2048,
		MAX_PROGRAMS_NUMBER				= 2048,
		MAX_SHADERS_NUMBER				= 2048,
		MAX_VBOS_NUMBER					= 4096,
		MAX_VERTEX_ATTRIBUTES_NUMBER	= 256
	};

	Texture	m_pTexturesList[MAX_TEXTURES_NUMBER];
	Program	m_pProgramsList[MAX_PROGRAMS_NUMBER];
	Shader	m_pShadersList[MAX_SHADERS_NUMBER];
	Vbo		m_pVbosList[MAX_VBOS_NUMBER];
	VertexAttribData m_vertexAttributes[MAX_VERTEX_ATTRIBUTES_NUMBER];

	Messenger m_messenger;
	CaptureOption m_captureOption;
};
