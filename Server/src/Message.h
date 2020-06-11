#pragma once

#include "common.h"

enum KPMessageType
{
	KMT_REQUEST_ERROR = 0,
	KMT_REQUEST_FINISH,

	//=================================================
	KMT_OBJECT_TEXTURE,
	KMT_OBJECT_SHADER,
	KMT_OBJECT_PROGRAM,
	KMT_OBJECT_VBO,

	//=================================================
	KMT_STATE_CURRENT_TEXTURES_STATUS,
	KMT_STATE_CURRENT_USING_PROGRAM,
	KMT_STATE_CURRENT_BINDING_VBOS,

	//=================================================
	KMT_glActiveTexture,
	KMT_glAttachShader,
	KMT_glBindAttribLocation,
	KMT_glBindBuffer,
	KMT_glBindFramebuffer,
	KMT_glBindRenderbuffer,
	KMT_glBindTexture,
	KMT_glBlendColor,
	KMT_glBlendEquation,
	KMT_glBlendEquationSeparate,
	KMT_glBlendFunc,
	KMT_glBlendFuncSeparate,
	KMT_glBufferData,
	KMT_glBufferSubData,
	KMT_glCheckFramebufferStatus,
	KMT_glClear,
	KMT_glClearColor,
	KMT_glClearDepthf,
	KMT_glClearStencil,
	KMT_glColorMask,
	KMT_glCompileShader,
	KMT_glCompressedTexImage2D,
	KMT_glCompressedTexSubImage2D,
	KMT_glCopyTexImage2D,
	KMT_glCopyTexSubImage2D,
	KMT_glCreateProgram,
	KMT_glCreateShader,
	KMT_glCullFace,
	KMT_glDeleteBuffers,
	KMT_glDeleteFramebuffers,
	KMT_glDeleteProgram,
	KMT_glDeleteRenderbuffers,
	KMT_glDeleteShader,
	KMT_glDeleteTextures,
	KMT_glDepthFunc,
	KMT_glDepthMask,
	KMT_glDepthRangef,
	KMT_glDetachShader,
	KMT_glDisable,
	KMT_glDisableVertexAttribArray,
	KMT_glDrawArrays,
	KMT_glDrawElements,
	KMT_glEnable,
	KMT_glEnableVertexAttribArray,
	KMT_glFinish,
	KMT_glFlush,
	KMT_glFramebufferRenderbuffer,
	KMT_glFramebufferTexture2D,
	KMT_glFrontFace,
	KMT_glGenBuffers,
	KMT_glGenerateMipmap,
	KMT_glGenFramebuffers,
	KMT_glGenRenderbuffers,
	KMT_glGenTextures,
	KMT_glGetActiveAttrib,
	KMT_glGetActiveUniform,
	KMT_glGetAttachedShaders,
	KMT_glGetAttribLocation,
	KMT_glGetBooleanv,
	KMT_glGetBufferParameteriv,
	KMT_glGetError,
	KMT_glGetFloatv,
	KMT_glGetFramebufferAttachmentParameteriv,
	KMT_glGetIntegerv,
	KMT_glGetProgramiv,
	KMT_glGetProgramInfoLog,
	KMT_glGetRenderbufferParameteriv,
	KMT_glGetShaderiv,
	KMT_glGetShaderInfoLog,
	KMT_glGetShaderPrecisionFormat,
	KMT_glGetShaderSource,
	KMT_glGetString,
	KMT_glGetTexParameterfv,
	KMT_glGetTexParameteriv,
	KMT_glGetUniformfv,
	KMT_glGetUniformiv,
	KMT_glGetUniformLocation,
	KMT_glGetVertexAttribfv,
	KMT_glGetVertexAttribiv,
	KMT_glGetVertexAttribPointerv,
	KMT_glHint,
	KMT_glIsBuffer,
	KMT_glIsEnabled,
	KMT_glIsFramebuffer,
	KMT_glIsProgram,
	KMT_glIsRenderbuffer,
	KMT_glIsShader,
	KMT_glIsTexture,
	KMT_glLineWidth,
	KMT_glLinkProgram,
	KMT_glPixelStorei,
	KMT_glPolygonOffset,
	KMT_glReadPixels,
	KMT_glReleaseShaderCompiler,
	KMT_glRenderbufferStorage,
	KMT_glSampleCoverage,
	KMT_glScissor,
	KMT_glShaderBinary,
	KMT_glShaderSource,
	KMT_glStencilFunc,
	KMT_glStencilFuncSeparate,
	KMT_glStencilMask,
	KMT_glStencilMaskSeparate,
	KMT_glStencilOp,
	KMT_glStencilOpSeparate,
	KMT_glTexImage2D,
	KMT_glTexParameterf,
	KMT_glTexParameterfv,
	KMT_glTexParameteri,
	KMT_glTexParameteriv,
	KMT_glTexSubImage2D,
	KMT_glUniform1f,
	KMT_glUniform1fv,
	KMT_glUniform1i,
	KMT_glUniform1iv,
	KMT_glUniform2f,
	KMT_glUniform2fv,
	KMT_glUniform2i,
	KMT_glUniform2iv,
	KMT_glUniform3f,
	KMT_glUniform3fv,
	KMT_glUniform3i,
	KMT_glUniform3iv,
	KMT_glUniform4f,
	KMT_glUniform4fv,
	KMT_glUniform4i,
	KMT_glUniform4iv,
	KMT_glUniformMatrix2fv,
	KMT_glUniformMatrix3fv,
	KMT_glUniformMatrix4fv,
	KMT_glUseProgram,
	KMT_glValidateProgram,
	KMT_glVertexAttrib1f,
	KMT_glVertexAttrib1fv,
	KMT_glVertexAttrib2f,
	KMT_glVertexAttrib2fv,
	KMT_glVertexAttrib3f,
	KMT_glVertexAttrib3fv,
	KMT_glVertexAttrib4f,
	KMT_glVertexAttrib4fv,
	KMT_glVertexAttribPointer,
	KMT_glViewport,
	//
	KMT_glMapBufferOES,
	KMT_glUnmapBufferOES,
	KMT_glTexStorage2D,
	//=================================================

	KMT_NONE
};

struct Message
{
	KPMessageType	m_type;
	int				m_length;
	char*			m_pData;
	
	Message() : m_pData(NULL), m_type(KMT_NONE), m_length(0)
	{
	}
	
	~Message()
	{
		SAFE_DEL_ARRAY(m_pData);
	}
	
	void clearData()
	{
		m_type = KMT_NONE;
		m_length = 0;
		SAFE_DEL_ARRAY(m_pData);
	}
};
