Server* theServer = NULL;

#ifdef __cplusplus
extern "C" {
#endif

void GL_APIENTRY glActiveTexture(GLenum texture)
{
	glPointers.glActiveTexture(texture);
	theServer->on_glActiveTexture(texture);
}

void GL_APIENTRY glAttachShader(GLuint program, GLuint shader)
{
	glPointers.glAttachShader(program, shader);
	theServer->on_glAttachShader(program, shader);
}

void GL_APIENTRY glBindAttribLocation(GLuint program, GLuint index, const GLchar* name)
{
	glPointers.glBindAttribLocation(program, index, name);
	theServer->on_glBindAttribLocation(program, index, name);
}

void GL_APIENTRY glBindBuffer(GLenum target, GLuint buffer)
{
	glPointers.glBindBuffer(target, buffer);
	theServer->on_glBindBuffer(target, buffer);
}

void GL_APIENTRY glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	glPointers.glBindFramebuffer(target, framebuffer);
	theServer->on_glBindFramebuffer(target, framebuffer);
}

void GL_APIENTRY glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	glPointers.glBindRenderbuffer(target, renderbuffer);
	theServer->on_glBindRenderbuffer(target, renderbuffer);
}

void GL_APIENTRY glBindTexture(GLenum target, GLuint texture)
{
	glPointers.glBindTexture(target, texture);
	theServer->on_glBindTexture(target, texture);
}

void GL_APIENTRY glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	glPointers.glBlendColor(red, green, blue, alpha);
	theServer->on_glBlendColor(red, green, blue, alpha);
}

void GL_APIENTRY glBlendEquation(GLenum mode)
{
	glPointers.glBlendEquation(mode);
	theServer->on_glBlendEquation(mode);
}

void GL_APIENTRY glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	glPointers.glBlendEquationSeparate(modeRGB, modeAlpha);
	theServer->on_glBlendEquationSeparate(modeRGB, modeAlpha);
}

void GL_APIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	glPointers.glBlendFunc(sfactor, dfactor);
	theServer->on_glBlendFunc(sfactor, dfactor);
}

void GL_APIENTRY glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	glPointers.glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
	theServer->on_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void GL_APIENTRY glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	glPointers.glBufferData(target, size, data, usage);
	theServer->on_glBufferData(target, size, data, usage);
}

void GL_APIENTRY glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
	glPointers.glBufferSubData(target, offset, size, data);
	theServer->on_glBufferSubData(target, offset, size, data);
}

GLenum GL_APIENTRY glCheckFramebufferStatus(GLenum target)
{
	GLenum tmp = glPointers.glCheckFramebufferStatus(target);
	theServer->on_glCheckFramebufferStatus(target, tmp);
	return tmp;
}

void GL_APIENTRY glClear(GLbitfield mask)
{
	glPointers.glClear(mask);
	theServer->on_glClear(mask);
}

void GL_APIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	glPointers.glClearColor(red, green, blue, alpha);
	theServer->on_glClearColor(red, green, blue, alpha);
}

void GL_APIENTRY glClearDepthf(GLclampf depth)
{
	glPointers.glClearDepthf(depth);
	theServer->on_glClearDepthf(depth);
}

void GL_APIENTRY glClearStencil(GLint s)
{
	glPointers.glClearStencil(s);
	theServer->on_glClearStencil(s);
}

void GL_APIENTRY glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glPointers.glColorMask(red, green, blue, alpha);
	theServer->on_glColorMask(red, green, blue, alpha);
}

void GL_APIENTRY glCompileShader(GLuint shader)
{
	glPointers.glCompileShader(shader);
	theServer->on_glCompileShader(shader);
}

void GL_APIENTRY glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
{
	glPointers.glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	theServer->on_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

void GL_APIENTRY glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
{
	glPointers.glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	theServer->on_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void GL_APIENTRY glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	glPointers.glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	theServer->on_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void GL_APIENTRY glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	glPointers.glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	theServer->on_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

GLuint GL_APIENTRY glCreateProgram(void)
{
	GLuint tmp = glPointers.glCreateProgram();
	theServer->on_glCreateProgram(tmp);
	return tmp;
}

GLuint GL_APIENTRY glCreateShader(GLenum type)
{
	GLuint tmp = glPointers.glCreateShader(type);
	theServer->on_glCreateShader(type, tmp);
	return tmp;
}

void GL_APIENTRY glCullFace(GLenum mode)
{
	glPointers.glCullFace(mode);
	theServer->on_glCullFace(mode);
}

void GL_APIENTRY glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	glPointers.glDeleteBuffers(n, buffers);
	theServer->on_glDeleteBuffers(n, buffers);
}

void GL_APIENTRY glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	glPointers.glDeleteFramebuffers(n, framebuffers);
	theServer->on_glDeleteFramebuffers(n, framebuffers);
}

void GL_APIENTRY glDeleteProgram(GLuint program)
{
	glPointers.glDeleteProgram(program);
	theServer->on_glDeleteProgram(program);
}

void GL_APIENTRY glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
	glPointers.glDeleteRenderbuffers(n, renderbuffers);
	theServer->on_glDeleteRenderbuffers(n, renderbuffers);
}

void GL_APIENTRY glDeleteShader(GLuint shader)
{
	glPointers.glDeleteShader(shader);
	theServer->on_glDeleteShader(shader);
}

void GL_APIENTRY glDeleteTextures(GLsizei n, const GLuint* textures)
{
	glPointers.glDeleteTextures(n, textures);
	theServer->on_glDeleteTextures(n, textures);
}

void GL_APIENTRY glDepthFunc(GLenum func)
{
	glPointers.glDepthFunc(func);
	theServer->on_glDepthFunc(func);
}

void GL_APIENTRY glDepthMask(GLboolean flag)
{
	glPointers.glDepthMask(flag);
	theServer->on_glDepthMask(flag);
}

void GL_APIENTRY glDepthRangef(GLclampf zNear, GLclampf zFar)
{
	glPointers.glDepthRangef(zNear, zFar);
	theServer->on_glDepthRangef(zNear, zFar);
}

void GL_APIENTRY glDetachShader(GLuint program, GLuint shader)
{
	glPointers.glDetachShader(program, shader);
	theServer->on_glDetachShader(program, shader);
}

void GL_APIENTRY glDisable(GLenum cap)
{
	glPointers.glDisable(cap);
	theServer->on_glDisable(cap);
}

void GL_APIENTRY glDisableVertexAttribArray(GLuint index)
{
	glPointers.glDisableVertexAttribArray(index);
	theServer->on_glDisableVertexAttribArray(index);
}

void GL_APIENTRY glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	glPointers.glDrawArrays(mode, first, count);
	theServer->on_glDrawArrays(mode, first, count);
}

void GL_APIENTRY glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
	glPointers.glDrawElements(mode, count, type, indices);
	theServer->on_glDrawElements(mode, count, type, indices);
}

void GL_APIENTRY glEnable(GLenum cap)
{
	glPointers.glEnable(cap);
	theServer->on_glEnable(cap);
}

void GL_APIENTRY glEnableVertexAttribArray(GLuint index)
{
	glPointers.glEnableVertexAttribArray(index);
	theServer->on_glEnableVertexAttribArray(index);
}

void GL_APIENTRY glFinish(void)
{
	glPointers.glFinish();
	theServer->on_glFinish();
}

void GL_APIENTRY glFlush(void)
{
	glPointers.glFlush();
	theServer->on_glFlush();
}

void GL_APIENTRY glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	glPointers.glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	theServer->on_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void GL_APIENTRY glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	glPointers.glFramebufferTexture2D(target, attachment, textarget, texture, level);
	theServer->on_glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void GL_APIENTRY glFrontFace(GLenum mode)
{
	glPointers.glFrontFace(mode);
	theServer->on_glFrontFace(mode);
}

void GL_APIENTRY glGenBuffers(GLsizei n, GLuint* buffers)
{
	glPointers.glGenBuffers(n, buffers);
	theServer->on_glGenBuffers(n, buffers);
}

void GL_APIENTRY glGenerateMipmap(GLenum target)
{
	glPointers.glGenerateMipmap(target);
	theServer->on_glGenerateMipmap(target);
}

void GL_APIENTRY glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	glPointers.glGenFramebuffers(n, framebuffers);
	theServer->on_glGenFramebuffers(n, framebuffers);
}

void GL_APIENTRY glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
	glPointers.glGenRenderbuffers(n, renderbuffers);
	theServer->on_glGenRenderbuffers(n, renderbuffers);
}

void GL_APIENTRY glGenTextures(GLsizei n, GLuint* textures)
{
	glPointers.glGenTextures(n, textures);
	theServer->on_glGenTextures(n, textures);
}

void GL_APIENTRY glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	glPointers.glGetActiveAttrib(program, index, bufsize, length, size, type, name);
	theServer->on_glGetActiveAttrib(program, index, bufsize, length, size, type, name);
}

void GL_APIENTRY glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	glPointers.glGetActiveUniform(program, index, bufsize, length, size, type, name);
	theServer->on_glGetActiveUniform(program, index, bufsize, length, size, type, name);
}

void GL_APIENTRY glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
	glPointers.glGetAttachedShaders(program, maxcount, count, shaders);
	theServer->on_glGetAttachedShaders(program, maxcount, count, shaders);
}

int GL_APIENTRY glGetAttribLocation(GLuint program, const GLchar* name)
{
	int tmp = glPointers.glGetAttribLocation(program, name);
	theServer->on_glGetAttribLocation(program, name, tmp);
	return tmp;
}

void GL_APIENTRY glGetBooleanv(GLenum pname, GLboolean* params)
{
	glPointers.glGetBooleanv(pname, params);
	theServer->on_glGetBooleanv(pname, params);
}

void GL_APIENTRY glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	glPointers.glGetBufferParameteriv(target, pname, params);
	theServer->on_glGetBufferParameteriv(target, pname, params);
}

GLenum GL_APIENTRY glGetError(void)
{
	GLenum tmp = glPointers.glGetError();
	theServer->on_glGetError(tmp);
	return tmp;
}

void GL_APIENTRY glGetFloatv(GLenum pname, GLfloat* params)
{
	glPointers.glGetFloatv(pname, params);
	theServer->on_glGetFloatv(pname, params);
}

void GL_APIENTRY glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
	glPointers.glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	theServer->on_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

void GL_APIENTRY glGetIntegerv(GLenum pname, GLint* params)
{
	glPointers.glGetIntegerv(pname, params);
	theServer->on_glGetIntegerv(pname, params);
}

void GL_APIENTRY glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	glPointers.glGetProgramiv(program, pname, params);
	theServer->on_glGetProgramiv(program, pname, params);
}

void GL_APIENTRY glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
	glPointers.glGetProgramInfoLog(program, bufsize, length, infolog);
	theServer->on_glGetProgramInfoLog(program, bufsize, length, infolog);
}

void GL_APIENTRY glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	glPointers.glGetRenderbufferParameteriv(target, pname, params);
	theServer->on_glGetRenderbufferParameteriv(target, pname, params);
}

void GL_APIENTRY glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	glPointers.glGetShaderiv(shader, pname, params);
	theServer->on_glGetShaderiv(shader, pname, params);
}

void GL_APIENTRY glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
	glPointers.glGetShaderInfoLog(shader, bufsize, length, infolog);
	theServer->on_glGetShaderInfoLog(shader, bufsize, length, infolog);
}

void GL_APIENTRY glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
	glPointers.glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	theServer->on_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

void GL_APIENTRY glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)
{
	glPointers.glGetShaderSource(shader, bufsize, length, source);
	theServer->on_glGetShaderSource(shader, bufsize, length, source);
}

const GLubyte* GL_APIENTRY glGetString(GLenum name)
{
	const GLubyte* tmp = glPointers.glGetString(name);
	theServer->on_glGetString(name, tmp);
	return tmp;
}

void GL_APIENTRY glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
{
	glPointers.glGetTexParameterfv(target, pname, params);
	theServer->on_glGetTexParameterfv(target, pname, params);
}

void GL_APIENTRY glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{
	glPointers.glGetTexParameteriv(target, pname, params);
	theServer->on_glGetTexParameteriv(target, pname, params);
}

void GL_APIENTRY glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
	glPointers.glGetUniformfv(program, location, params);
	theServer->on_glGetUniformfv(program, location, params);
}

void GL_APIENTRY glGetUniformiv(GLuint program, GLint location, GLint* params)
{
	glPointers.glGetUniformiv(program, location, params);
	theServer->on_glGetUniformiv(program, location, params);
}

int GL_APIENTRY glGetUniformLocation(GLuint program, const GLchar* name)
{
	int tmp = glPointers.glGetUniformLocation(program, name);
	theServer->on_glGetUniformLocation(program, name, tmp);
	return tmp;
}

void GL_APIENTRY glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
	glPointers.glGetVertexAttribfv(index, pname, params);
	theServer->on_glGetVertexAttribfv(index, pname, params);
}

void GL_APIENTRY glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
	glPointers.glGetVertexAttribiv(index, pname, params);
	theServer->on_glGetVertexAttribiv(index, pname, params);
}

void GL_APIENTRY glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer)
{
	glPointers.glGetVertexAttribPointerv(index, pname, pointer);
	theServer->on_glGetVertexAttribPointerv(index, pname, pointer);
}

void GL_APIENTRY glHint(GLenum target, GLenum mode)
{
	glPointers.glHint(target, mode);
	theServer->on_glHint(target, mode);
}

GLboolean GL_APIENTRY glIsBuffer(GLuint buffer)
{
	GLboolean tmp = glPointers.glIsBuffer(buffer);
	theServer->on_glIsBuffer(buffer, tmp);
	return tmp;
}

GLboolean GL_APIENTRY glIsEnabled(GLenum cap)
{
	GLboolean tmp = glPointers.glIsEnabled(cap);
	theServer->on_glIsEnabled(cap, tmp);
	return tmp;
}

GLboolean GL_APIENTRY glIsFramebuffer(GLuint framebuffer)
{
	GLboolean tmp = glPointers.glIsFramebuffer(framebuffer);
	theServer->on_glIsFramebuffer(framebuffer, tmp);
	return tmp;
}

GLboolean GL_APIENTRY glIsProgram(GLuint program)
{
	GLboolean tmp = glPointers.glIsProgram(program);
	theServer->on_glIsProgram(program, tmp);
	return tmp;
}

GLboolean GL_APIENTRY glIsRenderbuffer(GLuint renderbuffer)
{
	GLboolean tmp = glPointers.glIsRenderbuffer(renderbuffer);
	theServer->on_glIsRenderbuffer(renderbuffer, tmp);
	return tmp;
}

GLboolean GL_APIENTRY glIsShader(GLuint shader)
{
	GLboolean tmp = glPointers.glIsShader(shader);
	theServer->on_glIsShader(shader, tmp);
	return tmp;
}

GLboolean GL_APIENTRY glIsTexture(GLuint texture)
{
	GLboolean tmp = glPointers.glIsTexture(texture);
	theServer->on_glIsTexture(texture, tmp);
	return tmp;
}

void GL_APIENTRY glLineWidth(GLfloat width)
{
	glPointers.glLineWidth(width);
	theServer->on_glLineWidth(width);
}

void GL_APIENTRY glLinkProgram(GLuint program)
{
	glPointers.glLinkProgram(program);
	theServer->on_glLinkProgram(program);
}

void GL_APIENTRY glPixelStorei(GLenum pname, GLint param)
{
	glPointers.glPixelStorei(pname, param);
	theServer->on_glPixelStorei(pname, param);
}

void GL_APIENTRY glPolygonOffset(GLfloat factor, GLfloat units)
{
	glPointers.glPolygonOffset(factor, units);
	theServer->on_glPolygonOffset(factor, units);
}

void GL_APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
{
	glPointers.glReadPixels(x, y, width, height, format, type, pixels);
	theServer->on_glReadPixels(x, y, width, height, format, type, pixels);
}

void GL_APIENTRY glReleaseShaderCompiler(void)
{
	glPointers.glReleaseShaderCompiler();
	theServer->on_glReleaseShaderCompiler();
}

void GL_APIENTRY glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	glPointers.glRenderbufferStorage(target, internalformat, width, height);
	theServer->on_glRenderbufferStorage(target, internalformat, width, height);
}

void GL_APIENTRY glSampleCoverage(GLclampf value, GLboolean invert)
{
	glPointers.glSampleCoverage(value, invert);
	theServer->on_glSampleCoverage(value, invert);
}

void GL_APIENTRY glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glPointers.glScissor(x, y, width, height);
	theServer->on_glScissor(x, y, width, height);
}

void GL_APIENTRY glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)
{
	glPointers.glShaderBinary(n, shaders, binaryformat, binary, length);
	theServer->on_glShaderBinary(n, shaders, binaryformat, binary, length);
}

void GL_APIENTRY glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length)
{
	glPointers.glShaderSource(shader, count, string, length);
	theServer->on_glShaderSource(shader, count, string, length);
}

void GL_APIENTRY glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	glPointers.glStencilFunc(func, ref, mask);
	theServer->on_glStencilFunc(func, ref, mask);
}

void GL_APIENTRY glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	glPointers.glStencilFuncSeparate(face, func, ref, mask);
	theServer->on_glStencilFuncSeparate(face, func, ref, mask);
}

void GL_APIENTRY glStencilMask(GLuint mask)
{
	glPointers.glStencilMask(mask);
	theServer->on_glStencilMask(mask);
}

void GL_APIENTRY glStencilMaskSeparate(GLenum face, GLuint mask)
{
	glPointers.glStencilMaskSeparate(face, mask);
	theServer->on_glStencilMaskSeparate(face, mask);
}

void GL_APIENTRY glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	glPointers.glStencilOp(fail, zfail, zpass);
	theServer->on_glStencilOp(fail, zfail, zpass);
}

void GL_APIENTRY glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
	glPointers.glStencilOpSeparate(face, fail, zfail, zpass);
	theServer->on_glStencilOpSeparate(face, fail, zfail, zpass);
}

#if defined OS_TIZEN
void GL_APIENTRY glTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
	glPointers.glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	theServer->on_glTexImage2D(target, level, (GLint)internalformat, width, height, border, format, type, pixels);
}
#else
void GL_APIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
	glPointers.glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	theServer->on_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}
#endif

void GL_APIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	glPointers.glTexParameterf(target, pname, param);
	theServer->on_glTexParameterf(target, pname, param);
}

void GL_APIENTRY glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{
	glPointers.glTexParameterfv(target, pname, params);
	theServer->on_glTexParameterfv(target, pname, params);
}

void GL_APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	glPointers.glTexParameteri(target, pname, param);
	theServer->on_glTexParameteri(target, pname, param);
}

void GL_APIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{
	glPointers.glTexParameteriv(target, pname, params);
	theServer->on_glTexParameteriv(target, pname, params);
}

void GL_APIENTRY glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
{
	glPointers.glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	theServer->on_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void GL_APIENTRY glUniform1f(GLint location, GLfloat x)
{
	glPointers.glUniform1f(location, x);
	theServer->on_glUniform1f(location, x);
}

void GL_APIENTRY glUniform1fv(GLint location, GLsizei count, const GLfloat* v)
{
	glPointers.glUniform1fv(location, count, v);
	theServer->on_glUniform1fv(location, count, v);
}

void GL_APIENTRY glUniform1i(GLint location, GLint x)
{
	glPointers.glUniform1i(location, x);
	theServer->on_glUniform1i(location, x);
}

void GL_APIENTRY glUniform1iv(GLint location, GLsizei count, const GLint* v)
{
	glPointers.glUniform1iv(location, count, v);
	theServer->on_glUniform1iv(location, count, v);
}

void GL_APIENTRY glUniform2f(GLint location, GLfloat x, GLfloat y)
{
	glPointers.glUniform2f(location, x, y);
	theServer->on_glUniform2f(location, x, y);
}

void GL_APIENTRY glUniform2fv(GLint location, GLsizei count, const GLfloat* v)
{
	glPointers.glUniform2fv(location, count, v);
	theServer->on_glUniform2fv(location, count, v);
}

void GL_APIENTRY glUniform2i(GLint location, GLint x, GLint y)
{
	glPointers.glUniform2i(location, x, y);
	theServer->on_glUniform2i(location, x, y);
}

void GL_APIENTRY glUniform2iv(GLint location, GLsizei count, const GLint* v)
{
	glPointers.glUniform2iv(location, count, v);
	theServer->on_glUniform2iv(location, count, v);
}

void GL_APIENTRY glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	glPointers.glUniform3f(location, x, y, z);
	theServer->on_glUniform3f(location, x, y, z);
}

void GL_APIENTRY glUniform3fv(GLint location, GLsizei count, const GLfloat* v)
{
	glPointers.glUniform3fv(location, count, v);
	theServer->on_glUniform3fv(location, count, v);
}

void GL_APIENTRY glUniform3i(GLint location, GLint x, GLint y, GLint z)
{
	glPointers.glUniform3i(location, x, y, z);
	theServer->on_glUniform3i(location, x, y, z);
}

void GL_APIENTRY glUniform3iv(GLint location, GLsizei count, const GLint* v)
{
	glPointers.glUniform3iv(location, count, v);
	theServer->on_glUniform3iv(location, count, v);
}

void GL_APIENTRY glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glPointers.glUniform4f(location, x, y, z, w);
	theServer->on_glUniform4f(location, x, y, z, w);
}

void GL_APIENTRY glUniform4fv(GLint location, GLsizei count, const GLfloat* v)
{
	glPointers.glUniform4fv(location, count, v);
	theServer->on_glUniform4fv(location, count, v);
}

void GL_APIENTRY glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
	glPointers.glUniform4i(location, x, y, z, w);
	theServer->on_glUniform4i(location, x, y, z, w);
}

void GL_APIENTRY glUniform4iv(GLint location, GLsizei count, const GLint* v)
{
	glPointers.glUniform4iv(location, count, v);
	theServer->on_glUniform4iv(location, count, v);
}

void GL_APIENTRY glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	glPointers.glUniformMatrix2fv(location, count, transpose, value);
	theServer->on_glUniformMatrix2fv(location, count, transpose, value);
}

void GL_APIENTRY glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	glPointers.glUniformMatrix3fv(location, count, transpose, value);
	theServer->on_glUniformMatrix3fv(location, count, transpose, value);
}

void GL_APIENTRY glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	glPointers.glUniformMatrix4fv(location, count, transpose, value);
	theServer->on_glUniformMatrix4fv(location, count, transpose, value);
}

void GL_APIENTRY glUseProgram(GLuint program)
{
	glPointers.glUseProgram(program);
	theServer->on_glUseProgram(program);
}

void GL_APIENTRY glValidateProgram(GLuint program)
{
	glPointers.glValidateProgram(program);
	theServer->on_glValidateProgram(program);
}

void GL_APIENTRY glVertexAttrib1f(GLuint indx, GLfloat x)
{
	glPointers.glVertexAttrib1f(indx, x);
	theServer->on_glVertexAttrib1f(indx, x);
}

void GL_APIENTRY glVertexAttrib1fv(GLuint indx, const GLfloat* values)
{
	glPointers.glVertexAttrib1fv(indx, values);
	theServer->on_glVertexAttrib1fv(indx, values);
}

void GL_APIENTRY glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
{
	glPointers.glVertexAttrib2f(indx, x, y);
	theServer->on_glVertexAttrib2f(indx, x, y);
}

void GL_APIENTRY glVertexAttrib2fv(GLuint indx, const GLfloat* values)
{
	glPointers.glVertexAttrib2fv(indx, values);
	theServer->on_glVertexAttrib2fv(indx, values);
}

void GL_APIENTRY glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
	glPointers.glVertexAttrib3f(indx, x, y, z);
	theServer->on_glVertexAttrib3f(indx, x, y, z);
}

void GL_APIENTRY glVertexAttrib3fv(GLuint indx, const GLfloat* values)
{
	glPointers.glVertexAttrib3fv(indx, values);
	theServer->on_glVertexAttrib3fv(indx, values);
}

void GL_APIENTRY glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glPointers.glVertexAttrib4f(indx, x, y, z, w);
	theServer->on_glVertexAttrib4f(indx, x, y, z, w);
}

void GL_APIENTRY glVertexAttrib4fv(GLuint indx, const GLfloat* values)
{
	glPointers.glVertexAttrib4fv(indx, values);
	theServer->on_glVertexAttrib4fv(indx, values);
}

void GL_APIENTRY glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
	glPointers.glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
	theServer->on_glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
}

void GL_APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glPointers.glViewport(x, y, width, height);
	theServer->on_glViewport(x, y, width, height);
}

// Extensions

void* GL_APIENTRY glMapBufferOES(GLenum target, GLenum access)
{
	void* tmp = glPointers.glMapBufferOES(target, access);
	theServer->on_glMapBufferOES(target, access, tmp);
	return tmp;
}

GLboolean GL_APIENTRY glUnmapBufferOES(GLenum target)
{
	theServer->on_glUnmapBufferOES(target);
	return glPointers.glUnmapBufferOES(target);
}

// OpenGLES 3.0

void GL_APIENTRY glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	glPointers.glTexStorage2D(target, levels, internalformat, width, height);
	theServer->on_glTexStorage2D(target, levels, internalformat, width, height);
}

#ifdef __cplusplus
}
#endif
