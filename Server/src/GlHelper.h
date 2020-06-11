#pragma once

#include "GlObject.h"
#include "Message.h"
#include "net/Socket.h"
#include "glDefine.h"
#include "thread/Mutex.h"

class Program;

class GlHelper
{
public:
	GlHelper(GlPointers& p);

	void getViewport(int& x, int& y, int& width, int& height);
	void readPixels(int x, int y, int width, int height, char* rgba);

	int calculateShaderSourceSize(GLsizei count, const GLchar** string, const GLint* length);
	void copyShaderSource(char* buffer, GLsizei count, const GLchar** string, const GLint* length);

	char* checkValidModifiedProgram(u32 prodId, u32 vsId, u32 fsId,
			const char* vsSourceString, const char* fsSourceString, const Program* pOldProg, Program& newProg);

	int getSize(GLenum type);

	u32 get_TEXTURE_BINDING(GLenum target);
	u32 get_TEXTURE_BINDING_2D();
	u32 get_TEXTURE_BINDING_CUBE_MAP();
	u32 get_CURRENT_PROGRAM();
	u8 get_ACTIVE_TEXTURE(); // From 0 to 31

	u32 get_ARRAY_BUFFER_BINDING();
	u32 get_ELEMENT_ARRAY_BUFFER_BINDING();
	u32 get_BUFFER_BINDING(u32 target);

	u32 get_FRAMEBUFFER_BINDING();
	void get_DEPTH_RANGE(float& n, float& f);
	int get_MAX_COMBINED_TEXTURE_IMAGE_UNITS();
	int get_MAX_TEXTURE_SIZE();
	int getMaxMipLevel();
	int get_MAX_VERTEX_ATTRIBS();
	int get_UNPACK_ALIGNMENT();

	void copyProgramUniformsStateToGpu(const Program& dstProg, const Program& srcProg);
	bool isRenderingToTexture(u32& texId, int& mipLevel);;
	
	void activeTexture(int unit);
	void shaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
	void compileShader(GLuint shader);
	void bindAttribLocation(GLuint program, GLuint index, const GLchar* name);

	void linkProgram(GLuint program);
	void useProgram(GLuint program);

	void getActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	GLint getAttribLocation(GLuint program, const GLchar* name);

	void getActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	GLint getUniformLocation(GLuint program, const GLchar* name);
	
	int getNumActiveAttributes(GLuint program);
	int getNumActiveUniforms(GLuint program);

	bool isCurrentFramebufferComplete();
	
private:
	GlPointers& m_pointers;
	int m_cachedMaxMipLevel;
	int get(GLenum param);
};
