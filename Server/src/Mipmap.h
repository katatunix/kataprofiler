#pragma once

#include "glDefine.h"

class Mipmap
{
public:
	static Mipmap* create_glTexImage2D(GLint internalformat, GLsizei width, GLsizei height, GLint border,
		GLenum format, GLenum type, const GLvoid* pixels, int unpackAlignment);

	static Mipmap* create_glCompressedTexImage2D(GLenum internalformat, GLsizei width, GLsizei height, GLint border,
		GLsizei imageSize, const GLvoid* data);

	static Mipmap* create_glTexStorage2D(GLenum internalformat, GLsizei width, GLsizei height);

	static Mipmap* create_glCopyTexImage2D(GLenum internalformat, GLsizei width, GLsizei height, GLint border, const char* rgba);

	Mipmap* on_glTexSubImage2D(GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type,
		const GLvoid* pixels, int unpackAlignment);

	Mipmap* on_glCompressedTexSubImage2D(GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
		GLenum format, GLsizei imageSize, const GLvoid* data);

	Mipmap* on_glCopyTexSubImage2D(GLint xoffset, GLint yoffset,
		GLsizei width, GLsizei height, const char* rgba);

	void copyRenderingRgba(int width, int height, const char* pixels);

	int getWidth();
	int getHeight();
	GLenum getFormat();
	GLenum getType();
	const char* getPixels();

	int getImageSize();
	bool isCompressed();
	bool isRawRgba();
	bool isRawRgb();

	~Mipmap();

private:
	static bool isValidWidthHeight(int width, int height);
	static bool isValidBorder(int border);
	static bool isValidFormatAndType(GLenum format, GLenum type);
	static bool isValidCompressedFormat(GLenum internalformat);
	static int getAlignedRowLen(int from, int unpackAlignment);

	Mipmap(int width, int height, GLenum format, GLenum type);

	void upload(const char* src, int unpackAlignment);
	int getBitsPerPixel();
	void copySubMipmap(Mipmap* mip, int xoffset, int yoffset);

	int m_width, m_height;
	GLenum m_format, m_type;
	char* m_pixels;
};
