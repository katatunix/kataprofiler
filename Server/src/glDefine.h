#pragma once

#include "GLES/gl3.h"

// PVR
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG				0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG              0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG             0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG             0x8C03

// ETC1
#define GL_ETC1_RGB8_OES								0x8D64

// ETC2
#define GL_COMPRESSED_RGB8_ETC2                         0x9274
#define GL_COMPRESSED_RGBA8_ETC2_EAC                    0x9278

// DXT
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT					0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT				0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT				0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT				0x83F3

//================================================================================================================================================================================================

typedef void(GL_APIENTRY *PFN_glActiveTexture)(GLenum texture);
typedef void(GL_APIENTRY *PFN_glAttachShader)(GLuint program, GLuint shader);
typedef void(GL_APIENTRY *PFN_glBindAttribLocation)(GLuint program, GLuint index, const GLchar* name);
typedef void(GL_APIENTRY *PFN_glBindBuffer)(GLenum target, GLuint buffer);
typedef void(GL_APIENTRY *PFN_glBindFramebuffer)(GLenum target, GLuint framebuffer);
typedef void(GL_APIENTRY *PFN_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
typedef void(GL_APIENTRY *PFN_glBindTexture)(GLenum target, GLuint texture);
typedef void(GL_APIENTRY *PFN_glBlendColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void(GL_APIENTRY *PFN_glBlendEquation)(GLenum mode);
typedef void(GL_APIENTRY *PFN_glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);
typedef void(GL_APIENTRY *PFN_glBlendFunc)(GLenum sfactor, GLenum dfactor);
typedef void(GL_APIENTRY *PFN_glBlendFuncSeparate)(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void(GL_APIENTRY *PFN_glBufferData)(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
typedef void(GL_APIENTRY *PFN_glBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
typedef GLenum(GL_APIENTRY *PFN_glCheckFramebufferStatus)(GLenum target);
typedef void(GL_APIENTRY *PFN_glClear)(GLbitfield mask);
typedef void(GL_APIENTRY *PFN_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void(GL_APIENTRY *PFN_glClearDepthf)(GLclampf depth);
typedef void(GL_APIENTRY *PFN_glClearStencil)(GLint s);
typedef void(GL_APIENTRY *PFN_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void(GL_APIENTRY *PFN_glCompileShader)(GLuint shader);
typedef void(GL_APIENTRY *PFN_glCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
typedef void(GL_APIENTRY *PFN_glCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
typedef void(GL_APIENTRY *PFN_glCopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void(GL_APIENTRY *PFN_glCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef GLuint(GL_APIENTRY *PFN_glCreateProgram)(void);
typedef GLuint(GL_APIENTRY *PFN_glCreateShader)(GLenum type);
typedef void(GL_APIENTRY *PFN_glCullFace)(GLenum mode);
typedef void(GL_APIENTRY *PFN_glDeleteBuffers)(GLsizei n, const GLuint* buffers);
typedef void(GL_APIENTRY *PFN_glDeleteFramebuffers)(GLsizei n, const GLuint* framebuffers);
typedef void(GL_APIENTRY *PFN_glDeleteProgram)(GLuint program);
typedef void(GL_APIENTRY *PFN_glDeleteRenderbuffers)(GLsizei n, const GLuint* renderbuffers);
typedef void(GL_APIENTRY *PFN_glDeleteShader)(GLuint shader);
typedef void(GL_APIENTRY *PFN_glDeleteTextures)(GLsizei n, const GLuint* textures);
typedef void(GL_APIENTRY *PFN_glDepthFunc)(GLenum func);
typedef void(GL_APIENTRY *PFN_glDepthMask)(GLboolean flag);
typedef void(GL_APIENTRY *PFN_glDepthRangef)(GLclampf zNear, GLclampf zFar);
typedef void(GL_APIENTRY *PFN_glDetachShader)(GLuint program, GLuint shader);
typedef void(GL_APIENTRY *PFN_glDisable)(GLenum cap);
typedef void(GL_APIENTRY *PFN_glDisableVertexAttribArray)(GLuint index);
typedef void(GL_APIENTRY *PFN_glDrawArrays)(GLenum mode, GLint first, GLsizei count);
typedef void(GL_APIENTRY *PFN_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
typedef void(GL_APIENTRY *PFN_glEnable)(GLenum cap);
typedef void(GL_APIENTRY *PFN_glEnableVertexAttribArray)(GLuint index);
typedef void(GL_APIENTRY *PFN_glFinish)(void);
typedef void(GL_APIENTRY *PFN_glFlush)(void);
typedef void(GL_APIENTRY *PFN_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void(GL_APIENTRY *PFN_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void(GL_APIENTRY *PFN_glFrontFace)(GLenum mode);
typedef void(GL_APIENTRY *PFN_glGenBuffers)(GLsizei n, GLuint* buffers);
typedef void(GL_APIENTRY *PFN_glGenerateMipmap)(GLenum target);
typedef void(GL_APIENTRY *PFN_glGenFramebuffers)(GLsizei n, GLuint* framebuffers);
typedef void(GL_APIENTRY *PFN_glGenRenderbuffers)(GLsizei n, GLuint* renderbuffers);
typedef void(GL_APIENTRY *PFN_glGenTextures)(GLsizei n, GLuint* textures);
typedef void(GL_APIENTRY *PFN_glGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
typedef void(GL_APIENTRY *PFN_glGetActiveUniform)(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
typedef void(GL_APIENTRY *PFN_glGetAttachedShaders)(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
typedef GLint(GL_APIENTRY *PFN_glGetAttribLocation)(GLuint program, const GLchar* name);
typedef void(GL_APIENTRY *PFN_glGetBooleanv)(GLenum pname, GLboolean* params);
typedef void(GL_APIENTRY *PFN_glGetBufferParameteriv)(GLenum target, GLenum pname, GLint* params);
typedef GLenum(GL_APIENTRY *PFN_glGetError)(void);
typedef void(GL_APIENTRY *PFN_glGetFloatv)(GLenum pname, GLfloat* params);
typedef void(GL_APIENTRY *PFN_glGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint* params);
typedef void(GL_APIENTRY *PFN_glGetIntegerv)(GLenum pname, GLint* params);
typedef void(GL_APIENTRY *PFN_glGetProgramiv)(GLuint program, GLenum pname, GLint* params);
typedef void(GL_APIENTRY *PFN_glGetProgramInfoLog)(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
typedef void(GL_APIENTRY *PFN_glGetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint* params);
typedef void(GL_APIENTRY *PFN_glGetShaderiv)(GLuint shader, GLenum pname, GLint* params);
typedef void(GL_APIENTRY *PFN_glGetShaderInfoLog)(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
typedef void(GL_APIENTRY *PFN_glGetShaderPrecisionFormat)(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
typedef void(GL_APIENTRY *PFN_glGetShaderSource)(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);
typedef const GLubyte*(GL_APIENTRY *PFN_glGetString)(GLenum name);
typedef void(GL_APIENTRY *PFN_glGetTexParameterfv)(GLenum target, GLenum pname, GLfloat* params);
typedef void(GL_APIENTRY *PFN_glGetTexParameteriv)(GLenum target, GLenum pname, GLint* params);
typedef void(GL_APIENTRY *PFN_glGetUniformfv)(GLuint program, GLint location, GLfloat* params);
typedef void(GL_APIENTRY *PFN_glGetUniformiv)(GLuint program, GLint location, GLint* params);
typedef GLint(GL_APIENTRY *PFN_glGetUniformLocation)(GLuint program, const GLchar* name);
typedef void(GL_APIENTRY *PFN_glGetVertexAttribfv)(GLuint index, GLenum pname, GLfloat* params);
typedef void(GL_APIENTRY *PFN_glGetVertexAttribiv)(GLuint index, GLenum pname, GLint* params);
typedef void(GL_APIENTRY *PFN_glGetVertexAttribPointerv)(GLuint index, GLenum pname, GLvoid** pointer);
typedef void(GL_APIENTRY *PFN_glHint)(GLenum target, GLenum mode);
typedef GLboolean(GL_APIENTRY *PFN_glIsBuffer)(GLuint buffer);
typedef GLboolean(GL_APIENTRY *PFN_glIsEnabled)(GLenum cap);
typedef GLboolean(GL_APIENTRY *PFN_glIsFramebuffer)(GLuint framebuffer);
typedef GLboolean(GL_APIENTRY *PFN_glIsProgram)(GLuint program);
typedef GLboolean(GL_APIENTRY *PFN_glIsRenderbuffer)(GLuint renderbuffer);
typedef GLboolean(GL_APIENTRY *PFN_glIsShader)(GLuint shader);
typedef GLboolean(GL_APIENTRY *PFN_glIsTexture)(GLuint texture);
typedef void(GL_APIENTRY *PFN_glLineWidth)(GLfloat width);
typedef void(GL_APIENTRY *PFN_glLinkProgram)(GLuint program);
typedef void(GL_APIENTRY *PFN_glPixelStorei)(GLenum pname, GLint param);
typedef void(GL_APIENTRY *PFN_glPolygonOffset)(GLfloat factor, GLfloat units);
typedef void(GL_APIENTRY *PFN_glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
typedef void(GL_APIENTRY *PFN_glReleaseShaderCompiler)(void);
typedef void(GL_APIENTRY *PFN_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void(GL_APIENTRY *PFN_glSampleCoverage)(GLclampf value, GLboolean invert);
typedef void(GL_APIENTRY *PFN_glScissor)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void(GL_APIENTRY *PFN_glShaderBinary)(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length);
typedef void(GL_APIENTRY *PFN_glShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
typedef void(GL_APIENTRY *PFN_glStencilFunc)(GLenum func, GLint ref, GLuint mask);
typedef void(GL_APIENTRY *PFN_glStencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void(GL_APIENTRY *PFN_glStencilMask)(GLuint mask);
typedef void(GL_APIENTRY *PFN_glStencilMaskSeparate)(GLenum face, GLuint mask);
typedef void(GL_APIENTRY *PFN_glStencilOp)(GLenum fail, GLenum zfail, GLenum zpass);
typedef void(GL_APIENTRY *PFN_glStencilOpSeparate)(GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
typedef void(GL_APIENTRY *PFN_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
typedef void(GL_APIENTRY *PFN_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
typedef void(GL_APIENTRY *PFN_glTexParameterfv)(GLenum target, GLenum pname, const GLfloat* params);
typedef void(GL_APIENTRY *PFN_glTexParameteri)(GLenum target, GLenum pname, GLint param);
typedef void(GL_APIENTRY *PFN_glTexParameteriv)(GLenum target, GLenum pname, const GLint* params);
typedef void(GL_APIENTRY *PFN_glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
typedef void(GL_APIENTRY *PFN_glUniform1f)(GLint location, GLfloat x);
typedef void(GL_APIENTRY *PFN_glUniform1fv)(GLint location, GLsizei count, const GLfloat* v);
typedef void(GL_APIENTRY *PFN_glUniform1i)(GLint location, GLint x);
typedef void(GL_APIENTRY *PFN_glUniform1iv)(GLint location, GLsizei count, const GLint* v);
typedef void(GL_APIENTRY *PFN_glUniform2f)(GLint location, GLfloat x, GLfloat y);
typedef void(GL_APIENTRY *PFN_glUniform2fv)(GLint location, GLsizei count, const GLfloat* v);
typedef void(GL_APIENTRY *PFN_glUniform2i)(GLint location, GLint x, GLint y);
typedef void(GL_APIENTRY *PFN_glUniform2iv)(GLint location, GLsizei count, const GLint* v);
typedef void(GL_APIENTRY *PFN_glUniform3f)(GLint location, GLfloat x, GLfloat y, GLfloat z);
typedef void(GL_APIENTRY *PFN_glUniform3fv)(GLint location, GLsizei count, const GLfloat* v);
typedef void(GL_APIENTRY *PFN_glUniform3i)(GLint location, GLint x, GLint y, GLint z);
typedef void(GL_APIENTRY *PFN_glUniform3iv)(GLint location, GLsizei count, const GLint* v);
typedef void(GL_APIENTRY *PFN_glUniform4f)(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void(GL_APIENTRY *PFN_glUniform4fv)(GLint location, GLsizei count, const GLfloat* v);
typedef void(GL_APIENTRY *PFN_glUniform4i)(GLint location, GLint x, GLint y, GLint z, GLint w);
typedef void(GL_APIENTRY *PFN_glUniform4iv)(GLint location, GLsizei count, const GLint* v);
typedef void(GL_APIENTRY *PFN_glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void(GL_APIENTRY *PFN_glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void(GL_APIENTRY *PFN_glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void(GL_APIENTRY *PFN_glUseProgram)(GLuint program);
typedef void(GL_APIENTRY *PFN_glValidateProgram)(GLuint program);
typedef void(GL_APIENTRY *PFN_glVertexAttrib1f)(GLuint indx, GLfloat x);
typedef void(GL_APIENTRY *PFN_glVertexAttrib1fv)(GLuint indx, const GLfloat* values);
typedef void(GL_APIENTRY *PFN_glVertexAttrib2f)(GLuint indx, GLfloat x, GLfloat y);
typedef void(GL_APIENTRY *PFN_glVertexAttrib2fv)(GLuint indx, const GLfloat* values);
typedef void(GL_APIENTRY *PFN_glVertexAttrib3f)(GLuint indx, GLfloat x, GLfloat y, GLfloat z);
typedef void(GL_APIENTRY *PFN_glVertexAttrib3fv)(GLuint indx, const GLfloat* values);
typedef void(GL_APIENTRY *PFN_glVertexAttrib4f)(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void(GL_APIENTRY *PFN_glVertexAttrib4fv)(GLuint indx, const GLfloat* values);
typedef void(GL_APIENTRY *PFN_glVertexAttribPointer)(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
typedef void(GL_APIENTRY *PFN_glViewport)(GLint x, GLint y, GLsizei width, GLsizei height);
// Extensions
typedef void*(GL_APIENTRY *PFN_glMapBufferOES)(GLenum target, GLenum access);
typedef GLboolean(GL_APIENTRY *PFN_glUnmapBufferOES)(GLenum target);
// OpenGLES 3.0
typedef void(GL_APIENTRY *PFN_glTexStorage2D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);

#define DECL_PFN(func) PFN_##func func

struct GlPointers
{
	DECL_PFN(glActiveTexture);
	DECL_PFN(glAttachShader);
	DECL_PFN(glBindAttribLocation);
	DECL_PFN(glBindBuffer);
	DECL_PFN(glBindFramebuffer);
	DECL_PFN(glBindRenderbuffer);
	DECL_PFN(glBindTexture);
	DECL_PFN(glBlendColor);
	DECL_PFN(glBlendEquation);
	DECL_PFN(glBlendEquationSeparate);
	DECL_PFN(glBlendFunc);
	DECL_PFN(glBlendFuncSeparate);
	DECL_PFN(glBufferData);
	DECL_PFN(glBufferSubData);
	DECL_PFN(glCheckFramebufferStatus);
	DECL_PFN(glClear);
	DECL_PFN(glClearColor);
	DECL_PFN(glClearDepthf);
	DECL_PFN(glClearStencil);
	DECL_PFN(glColorMask);
	DECL_PFN(glCompileShader);
	DECL_PFN(glCompressedTexImage2D);
	DECL_PFN(glCompressedTexSubImage2D);
	DECL_PFN(glCopyTexImage2D);
	DECL_PFN(glCopyTexSubImage2D);
	DECL_PFN(glCreateProgram);
	DECL_PFN(glCreateShader);
	DECL_PFN(glCullFace);
	DECL_PFN(glDeleteBuffers);
	DECL_PFN(glDeleteFramebuffers);
	DECL_PFN(glDeleteProgram);
	DECL_PFN(glDeleteRenderbuffers);
	DECL_PFN(glDeleteShader);
	DECL_PFN(glDeleteTextures);
	DECL_PFN(glDepthFunc);
	DECL_PFN(glDepthMask);
	DECL_PFN(glDepthRangef);
	DECL_PFN(glDetachShader);
	DECL_PFN(glDisable);
	DECL_PFN(glDisableVertexAttribArray);
	DECL_PFN(glDrawArrays);
	DECL_PFN(glDrawElements);
	DECL_PFN(glEnable);
	DECL_PFN(glEnableVertexAttribArray);
	DECL_PFN(glFinish);
	DECL_PFN(glFlush);
	DECL_PFN(glFramebufferRenderbuffer);
	DECL_PFN(glFramebufferTexture2D);
	DECL_PFN(glFrontFace);
	DECL_PFN(glGenBuffers);
	DECL_PFN(glGenerateMipmap);
	DECL_PFN(glGenFramebuffers);
	DECL_PFN(glGenRenderbuffers);
	DECL_PFN(glGenTextures);
	DECL_PFN(glGetActiveAttrib);
	DECL_PFN(glGetActiveUniform);
	DECL_PFN(glGetAttachedShaders);
	DECL_PFN(glGetAttribLocation);
	DECL_PFN(glGetBooleanv);
	DECL_PFN(glGetBufferParameteriv);
	DECL_PFN(glGetError);
	DECL_PFN(glGetFloatv);
	DECL_PFN(glGetFramebufferAttachmentParameteriv);
	DECL_PFN(glGetIntegerv);
	DECL_PFN(glGetProgramiv);
	DECL_PFN(glGetProgramInfoLog);
	DECL_PFN(glGetRenderbufferParameteriv);
	DECL_PFN(glGetShaderiv);
	DECL_PFN(glGetShaderInfoLog);
	DECL_PFN(glGetShaderPrecisionFormat);
	DECL_PFN(glGetShaderSource);
	DECL_PFN(glGetString);
	DECL_PFN(glGetTexParameterfv);
	DECL_PFN(glGetTexParameteriv);
	DECL_PFN(glGetUniformfv);
	DECL_PFN(glGetUniformiv);
	DECL_PFN(glGetUniformLocation);
	DECL_PFN(glGetVertexAttribfv);
	DECL_PFN(glGetVertexAttribiv);
	DECL_PFN(glGetVertexAttribPointerv);
	DECL_PFN(glHint);
	DECL_PFN(glIsBuffer);
	DECL_PFN(glIsEnabled);
	DECL_PFN(glIsFramebuffer);
	DECL_PFN(glIsProgram);
	DECL_PFN(glIsRenderbuffer);
	DECL_PFN(glIsShader);
	DECL_PFN(glIsTexture);
	DECL_PFN(glLineWidth);
	DECL_PFN(glLinkProgram);
	DECL_PFN(glPixelStorei);
	DECL_PFN(glPolygonOffset);
	DECL_PFN(glReadPixels);
	DECL_PFN(glReleaseShaderCompiler);
	DECL_PFN(glRenderbufferStorage);
	DECL_PFN(glSampleCoverage);
	DECL_PFN(glScissor);
	DECL_PFN(glShaderBinary);
	DECL_PFN(glShaderSource);
	DECL_PFN(glStencilFunc);
	DECL_PFN(glStencilFuncSeparate);
	DECL_PFN(glStencilMask);
	DECL_PFN(glStencilMaskSeparate);
	DECL_PFN(glStencilOp);
	DECL_PFN(glStencilOpSeparate);
	DECL_PFN(glTexImage2D);
	DECL_PFN(glTexParameterf);
	DECL_PFN(glTexParameterfv);
	DECL_PFN(glTexParameteri);
	DECL_PFN(glTexParameteriv);
	DECL_PFN(glTexSubImage2D);
	DECL_PFN(glUniform1f);
	DECL_PFN(glUniform1fv);
	DECL_PFN(glUniform1i);
	DECL_PFN(glUniform1iv);
	DECL_PFN(glUniform2f);
	DECL_PFN(glUniform2fv);
	DECL_PFN(glUniform2i);
	DECL_PFN(glUniform2iv);
	DECL_PFN(glUniform3f);
	DECL_PFN(glUniform3fv);
	DECL_PFN(glUniform3i);
	DECL_PFN(glUniform3iv);
	DECL_PFN(glUniform4f);
	DECL_PFN(glUniform4fv);
	DECL_PFN(glUniform4i);
	DECL_PFN(glUniform4iv);
	DECL_PFN(glUniformMatrix2fv);
	DECL_PFN(glUniformMatrix3fv);
	DECL_PFN(glUniformMatrix4fv);
	DECL_PFN(glUseProgram);
	DECL_PFN(glValidateProgram);
	DECL_PFN(glVertexAttrib1f);
	DECL_PFN(glVertexAttrib1fv);
	DECL_PFN(glVertexAttrib2f);
	DECL_PFN(glVertexAttrib2fv);
	DECL_PFN(glVertexAttrib3f);
	DECL_PFN(glVertexAttrib3fv);
	DECL_PFN(glVertexAttrib4f);
	DECL_PFN(glVertexAttrib4fv);
	DECL_PFN(glVertexAttribPointer);
	DECL_PFN(glViewport);
	// Extensions
	DECL_PFN(glMapBufferOES);
	DECL_PFN(glUnmapBufferOES);
	// OpenGLES 3.0
	DECL_PFN(glTexStorage2D);
};
