#pragma once

#include "common.h"
#include "glDefine.h"
#include "GlObject.h"
#include "Mipmap.h"

enum TextureType
{
	TEX_NONE = 0,
	TEX_2D,
	TEX_CUBE_MAP
};

class Texture : public GlObject
{
public:
	Texture();
	Texture(u32 id);
	~Texture();

	void clearData();

	TextureType getTexType();
	void setTexType(TextureType texType);

	Mipmap* on_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border,
		GLenum format, GLenum type, const GLvoid* pixels, int unpackAlignment);

	Mipmap* on_glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height,
		GLint border, GLsizei imageSize, const GLvoid* data);

	Mipmap* on_glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat,
		GLsizei width, GLsizei height, GLint border, const char* rgba);

	bool on_glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);

	Mipmap* on_glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
		GLenum format, GLenum type, const GLvoid* pixels, int unpackAlignment);

	Mipmap* on_glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
		GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);

	Mipmap* on_glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
		GLsizei width, GLsizei height, const char* rgba);

	void copyRenderingRgba(int level, int width, int height, const char* pixels);

	int numMipmaps();
	Message* toMessage();

private:
	enum { MAX_MIPMAP = 32 };
	TextureType m_texType;
	Mipmap* m_mipmaps[MAX_MIPMAP];

	bool existsMipmap(int level);
	bool isValidTarget(GLenum target);
	bool isValidLevel(int level);
};
