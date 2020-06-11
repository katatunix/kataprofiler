#include "GlHelper.h"
#include "Program.h"
#include "log.h"

GlHelper::GlHelper(GlPointers& p) :
	m_pointers(p),
	m_cachedMaxMipLevel(-1)
{
}

int GlHelper::calculateShaderSourceSize(GLsizei count, const GLchar** string, const GLint* length)
{
	int sourceLen = 0;
	if (length)
	{
		for (int i = 0; i < count; i++)
		{
			const int len = length[i] < 0 ? STRLEN(string[i]) : length[i];
			sourceLen += len;
		}
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			sourceLen += STRLEN(string[i]);
		}
	}
	return sourceLen;
}

void GlHelper::copyShaderSource(char* buffer, GLsizei count, const GLchar** string, const GLint* length)
{
	if (length)
	{
		for (int i = 0; i < count; i++)
		{
			const int len = length[i] < 0 ? STRLEN(string[i]) : length[i];
			memcpy(buffer, string[i], len);
			buffer += len;
		}
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			const int len = STRLEN(string[i]);
			memcpy(buffer, string[i], len);
			buffer += len;
		}
	}
}

void GlHelper::getViewport(int& x, int& y, int& width, int& height)
{
	int viewport[4];
	m_pointers.glGetIntegerv(GL_VIEWPORT, viewport);
	x = viewport[0];
	y = viewport[1];
	width = viewport[2];
	height = viewport[3];
}

void GlHelper::readPixels(int x, int y, int width, int height, char* rgba)
{
	if (width <= 0 || height <= 0)
		return;
	int oldPackAlignment = 4;
	m_pointers.glGetIntegerv(GL_PACK_ALIGNMENT, &oldPackAlignment);
	m_pointers.glPixelStorei(GL_PACK_ALIGNMENT, 1);
	m_pointers.glFlush();
	m_pointers.glFinish();
	m_pointers.glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
	m_pointers.glPixelStorei(GL_PACK_ALIGNMENT, oldPackAlignment);
}

char* GlHelper::checkValidModifiedProgram(u32 progId, u32 vsId, u32 fsId,
	const char* vsSourceString, const char* fsSourceString, const Program* pOldProg, Program& testProg)
{
	const int maxLength = 1024;
	char* error = new char[maxLength];
	memset(error, 0, maxLength);

	// Sometimes these gl functions could not be GetProcAddress from the system, so remove
	#if 0
	if (!m_pointers.glIsProgram(progId))
	{

		strcpy(error, "This is not a program id");
		return error;
	}
	if (!m_pointers.glIsShader(vsId))
	{

		strcpy(error, "This is not a vertex shader id");
		return error;
	}
	if (!m_pointers.glIsShader(fsId))
	{
		strcpy(error, "This is not a fragment shader id");
		return error;
	}
	int countShaders;
	m_pointers.glGetProgramiv(progId, GL_ATTACHED_SHADERS, &countShaders);
	if (countShaders != 2)
	{
		strcpy(error, "The number of shader objects attached to this program is not equal to 2");
		return error;
	}
	u32 shaders[2];
	m_pointers.glGetAttachedShaders(progId, 2, NULL, shaders);
	if ((vsId != shaders[0] && vsId != shaders[1]) || (fsId != shaders[0] && fsId != shaders[1]))
	{
		strcpy(error, "The shader objects attached to this program have been changed");
		return error;
	}
	#endif
	//-------------------------------------------------------------------------------
	// Compile shaders
	int compileStatus = 0;

	u32 newVsId = m_pointers.glCreateShader(GL_VERTEX_SHADER);
	m_pointers.glShaderSource(newVsId, 1, &vsSourceString, NULL);
	m_pointers.glCompileShader(newVsId);
	m_pointers.glGetShaderiv(newVsId, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus)
	{
		int length = 0;
		m_pointers.glGetShaderInfoLog(newVsId, maxLength, &length, error);
		if (length <= 0) strcpy(error, "[error]");
		m_pointers.glDeleteShader(newVsId);
		return error;
	}

	u32 newFsId = m_pointers.glCreateShader(GL_FRAGMENT_SHADER);
	m_pointers.glShaderSource(newFsId, 1, &fsSourceString, NULL);
	m_pointers.glCompileShader(newFsId);
	m_pointers.glGetShaderiv(newFsId, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus)
	{
		int length = 0;
		m_pointers.glGetShaderInfoLog(newFsId, maxLength, &length, error);
		if (length <= 0) strcpy(error, "[error]");
		m_pointers.glDeleteShader(newFsId);
		m_pointers.glDeleteShader(newVsId);
		return error;
	}

	//-------------------------------------------------------------------------------
	// Link program

	int linkStatus = 0;
	u32 newProgramId = m_pointers.glCreateProgram();
	m_pointers.glAttachShader(newProgramId, newVsId);
	m_pointers.glAttachShader(newProgramId, newFsId);
	m_pointers.glLinkProgram(newProgramId);
	m_pointers.glGetProgramiv(newProgramId, GL_LINK_STATUS, &linkStatus);

	testProg.setId(newProgramId);

	if (!linkStatus)
	{
		int length = 0;
		m_pointers.glGetProgramInfoLog(newProgramId, maxLength, &length, error);
		if (length <= 0) strcpy(error, "[error]");
		goto my_end;
	}

	testProg.attachVs(newVsId);
	testProg.attachFs(newFsId);
	testProg.link(*this);

	// Note
#if 0
	if (testProg.getAttributesCount() != pOldProg->getAttributesCount())
	{
		strcpy(error, "The attributes count is not the same");
		goto my_end;
	}
#endif

	//-------------------------------------------------------------------------------
	// Everything is ok, free all

	my_end:

	m_pointers.glDeleteProgram(newProgramId);
	m_pointers.glDeleteShader(newFsId);
	m_pointers.glDeleteShader(newVsId);

	if (strlen(error) > 0)
	{
		return error;
	}
	SAFE_DEL_ARRAY(error);
	return NULL;
}

int GlHelper::getSize(GLenum type)
{
	switch (type)
	{
	case GL_BYTE:
	case GL_UNSIGNED_BYTE:
		return 1;
	case GL_SHORT:
	case GL_UNSIGNED_SHORT:
		return 2;
	case GL_INT:
	case GL_UNSIGNED_INT:
	case GL_FLOAT:
	case GL_FIXED:
		return 4;
	}
	LOGE("[%s] Should not go here", __FUNCTION__);
	return 0;
}

int GlHelper::get(GLenum param)
{
	int result = 0;
	m_pointers.glGetIntegerv(param, &result);
	return result;
}

u32 GlHelper::get_TEXTURE_BINDING(GLenum target)
{
	return target == GL_TEXTURE_2D ? get_TEXTURE_BINDING_2D() : get_TEXTURE_BINDING_CUBE_MAP();
}

u32 GlHelper::get_TEXTURE_BINDING_2D()
{
	return (u32)get(GL_TEXTURE_BINDING_2D);
}

u32 GlHelper::get_TEXTURE_BINDING_CUBE_MAP()
{
	return (u32)get(GL_TEXTURE_BINDING_CUBE_MAP);
}

u32 GlHelper::get_CURRENT_PROGRAM()
{
	return (u32)get(GL_CURRENT_PROGRAM);
}

u8 GlHelper::get_ACTIVE_TEXTURE() // From 0 to 31
{
	return (u8)(get(GL_ACTIVE_TEXTURE) - GL_TEXTURE0);
}

u32 GlHelper::get_ARRAY_BUFFER_BINDING()
{
	return (u32)get(GL_ARRAY_BUFFER_BINDING);
}

u32 GlHelper::get_ELEMENT_ARRAY_BUFFER_BINDING()
{
	return (u32)get(GL_ELEMENT_ARRAY_BUFFER_BINDING);
}

u32 GlHelper::get_BUFFER_BINDING(u32 target)
{
	return target == GL_ARRAY_BUFFER ?
		get_ARRAY_BUFFER_BINDING() :
		get_ELEMENT_ARRAY_BUFFER_BINDING();
}

u32 GlHelper::get_FRAMEBUFFER_BINDING()
{
	return (u32)get(GL_FRAMEBUFFER_BINDING);
}

void GlHelper::get_DEPTH_RANGE(float& n, float& f)
{
	float v[2];
	m_pointers.glGetFloatv(GL_DEPTH_RANGE, v);
	n = v[0];
	f = v[1];
}

int GlHelper::get_MAX_COMBINED_TEXTURE_IMAGE_UNITS()
{
	return get(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
}

int GlHelper::get_MAX_TEXTURE_SIZE()
{
	return get(GL_MAX_TEXTURE_SIZE);
}

int GlHelper::getMaxMipLevel()
{
	if (m_cachedMaxMipLevel == -1)
	{
		int texSize = get_MAX_TEXTURE_SIZE();
		m_cachedMaxMipLevel = 0;
		while (texSize > 1)
		{
			texSize = texSize >> 1;
			m_cachedMaxMipLevel++;
		}
	}
	return m_cachedMaxMipLevel;
}

int GlHelper::get_MAX_VERTEX_ATTRIBS()
{
	return get(GL_MAX_VERTEX_ATTRIBS);
}

int GlHelper::get_UNPACK_ALIGNMENT()
{
	return get(GL_UNPACK_ALIGNMENT);
}

void GlHelper::copyProgramUniformsStateToGpu(const Program& dstProg, const Program& srcProg)
{
	int dstCount = dstProg.getUniformsCount();
	int srcCount = srcProg.getUniformsCount();

	for (int i = 0; i < dstCount; i++)
	{
		int k = -1;
		{
			const KPUniform& dstUniform = dstProg.getUniform(i);
			for (int j = 0; j < srcCount; j++)
			{
				const KPUniform& srcUniform = srcProg.getUniform(j);
				if (dstUniform.isTheSamePrototype(srcUniform))
				{
					k = j;
					break;
				}
			}
		}

		if (k == -1) continue;

		const KPUniform& uni = srcProg.getUniform(k);

		switch (uni.m_type)
		{
		case GL_FLOAT:
		{
			int count = uni.m_valueBytesNumber / 4;
			m_pointers.glUniform1fv(uni.m_location, count, (const float*)uni.m_pValuePointer);
			break;
		}
		case GL_FLOAT_VEC2:
		{
			int count = uni.m_valueBytesNumber / 8;
			m_pointers.glUniform2fv(uni.m_location, count, (const float*)uni.m_pValuePointer);
			break;
		}
		case GL_FLOAT_VEC3:
		{
			int count = uni.m_valueBytesNumber / 12;
			m_pointers.glUniform3fv(uni.m_location, count, (const float*)uni.m_pValuePointer);
			break;
		}
		case GL_FLOAT_VEC4:
		{
			int count = uni.m_valueBytesNumber / 16;
			m_pointers.glUniform4fv(uni.m_location, count, (const float*)uni.m_pValuePointer);
			break;
		}
		case GL_INT:
		case GL_SAMPLER_2D:
		case GL_SAMPLER_3D:
		case GL_SAMPLER_CUBE:
		{
			int count = uni.m_valueBytesNumber / 4;
			m_pointers.glUniform1iv(uni.m_location, count, (const int*)uni.m_pValuePointer);
			break;
		}
		case GL_INT_VEC2:
		{
			int count = uni.m_valueBytesNumber / 8;
			m_pointers.glUniform2iv(uni.m_location, count, (const int*)uni.m_pValuePointer);
			break;
		}
		case GL_INT_VEC3:
		{
			int count = uni.m_valueBytesNumber / 12;
			m_pointers.glUniform3iv(uni.m_location, count, (const int*)uni.m_pValuePointer);
			break;
		}
		case GL_INT_VEC4:
		{
			int count = uni.m_valueBytesNumber / 16;
			m_pointers.glUniform4iv(uni.m_location, count, (const int*)uni.m_pValuePointer);
			break;
		}
		case GL_BOOL:
		{
			int count = uni.m_valueBytesNumber / 4;
			m_pointers.glUniform1iv(uni.m_location, count, (const int*)uni.m_pValuePointer);
			break;
		}
		case GL_BOOL_VEC2:
		{
			int count = uni.m_valueBytesNumber / 8;
			m_pointers.glUniform2iv(uni.m_location, count, (const int*)uni.m_pValuePointer);
			break;
		}
		case GL_BOOL_VEC3:
		{
			int count = uni.m_valueBytesNumber / 12;
			m_pointers.glUniform3iv(uni.m_location, count, (const int*)uni.m_pValuePointer);
			break;
		}
		case GL_BOOL_VEC4:
		{
			int count = uni.m_valueBytesNumber / 16;
			m_pointers.glUniform4iv(uni.m_location, count, (const int*)uni.m_pValuePointer);
			break;
		}
		case GL_FLOAT_MAT2:
		{
			const int size = 2;
			const int bytes = size * size * 4;
			int count = uni.m_valueBytesNumber / bytes;
			m_pointers.glUniformMatrix2fv(uni.m_location, count, GL_FALSE, (const float*)uni.m_pValuePointer);
			break;
		}
		case GL_FLOAT_MAT3:
		{
			const int size = 3;
			const int bytes = size * size * 4;
			int count = uni.m_valueBytesNumber / bytes;
			m_pointers.glUniformMatrix3fv(uni.m_location, count, GL_FALSE, (const float*)uni.m_pValuePointer);
			break;
		}
		case GL_FLOAT_MAT4:
		{
			const int size = 4;
			const int bytes = size * size * 4;
			int count = uni.m_valueBytesNumber / bytes;
			m_pointers.glUniformMatrix4fv(uni.m_location, count, GL_FALSE, (const float*)uni.m_pValuePointer);
			break;
		}

		default:
		{
			LOGE("[%s] Should not go here", __FUNCTION__);
			break;
		}
		} // switch (uni.m_type)
	} // for
}

bool GlHelper::isRenderingToTexture(u32& texId, int& mipLevel)
{
	if (get_FRAMEBUFFER_BINDING() == 0) return false;

	GLint params;
	m_pointers.glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &params);

	if (params != GL_TEXTURE) return false;

	m_pointers.glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &params);
	texId = (u32)params; // ***

	m_pointers.glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL, &params);
	mipLevel = params; // ***

	return true;
}

void GlHelper::activeTexture(int unit)
{
	m_pointers.glActiveTexture(GL_TEXTURE0 + unit);
}

void GlHelper::shaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length)
{
	m_pointers.glShaderSource(shader, count, string, length);
}

void GlHelper::compileShader(GLuint shader)
{
	m_pointers.glCompileShader(shader);
}

void GlHelper::bindAttribLocation(GLuint program, GLuint index, const GLchar* name)
{
	m_pointers.glBindAttribLocation(program, index, name);
}

void GlHelper::linkProgram(GLuint program)
{
	m_pointers.glLinkProgram(program);
}

void GlHelper::useProgram(GLuint program)
{
	m_pointers.glUseProgram(program);
}

void GlHelper::getActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	m_pointers.glGetActiveAttrib(program, index, bufsize, length, size, type, name);
}

GLint GlHelper::getAttribLocation(GLuint program, const GLchar* name)
{
	return m_pointers.glGetAttribLocation(program, name);
}

void GlHelper::getActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	m_pointers.glGetActiveUniform(program, index, bufsize, length, size, type, name);
}

GLint GlHelper::getUniformLocation(GLuint program, const GLchar* name)
{
	return m_pointers.glGetUniformLocation(program, name);
}

int GlHelper::getNumActiveAttributes(GLuint program)
{
	int result;
	m_pointers.glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &result);
	return result;
}

int GlHelper::getNumActiveUniforms(GLuint program)
{
	int result;
	m_pointers.glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &result);
	return result;
}

bool GlHelper::isCurrentFramebufferComplete()
{
	return m_pointers.glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}
