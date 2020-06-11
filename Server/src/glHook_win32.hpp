#include <Windows.h>
#include "win32/minhook/MinHook.h"
#include "log.h"

PROC (WINAPI *wglGetProcAddress_Original)(LPCSTR name);

BOOL (WINAPI *SwapBuffers_Original)(HDC hdc);

void* getProc(const char* name)
{
	void* p = (*wglGetProcAddress_Original)(name);
	if (	p == NULL ||
			p == (void*)0x1 || p == (void*)0x2 || p == (void*)0x3 ||
			p == (void*)-1	)
	{
		return NULL;
	}
	return p;
}

PROC WINAPI wglGetProcAddress_Hooked(LPCSTR name)
{
	#define CHECK_PROC(func) if (strcmp(name, STRINGIFY(func)) == 0) \
	{ \
		void* p = getProc(name); \
		if (p) \
		{ \
			LOGI("wglGetProcAddress_Hooked %s", name); \
			glPointers.func = (PFN_##func)p; \
			return (PROC)##func; \
		} \
		return NULL; \
	}
	
	CHECK_PROC(glActiveTexture); CHECK_PROC(glAttachShader); CHECK_PROC(glBindAttribLocation); CHECK_PROC(glBindBuffer); CHECK_PROC(glBindFramebuffer); CHECK_PROC(glBindRenderbuffer); CHECK_PROC(glBindTexture); CHECK_PROC(glBlendColor); CHECK_PROC(glBlendEquation); CHECK_PROC(glBlendEquationSeparate); CHECK_PROC(glBlendFunc); CHECK_PROC(glBlendFuncSeparate); CHECK_PROC(glBufferData); CHECK_PROC(glBufferSubData); CHECK_PROC(glCheckFramebufferStatus); CHECK_PROC(glClear); CHECK_PROC(glClearColor); CHECK_PROC(glClearDepthf); CHECK_PROC(glClearStencil); CHECK_PROC(glColorMask); CHECK_PROC(glCompileShader); CHECK_PROC(glCompressedTexImage2D); CHECK_PROC(glCompressedTexSubImage2D); CHECK_PROC(glCopyTexImage2D); CHECK_PROC(glCopyTexSubImage2D); CHECK_PROC(glCreateProgram); CHECK_PROC(glCreateShader); CHECK_PROC(glCullFace); CHECK_PROC(glDeleteBuffers); CHECK_PROC(glDeleteFramebuffers); CHECK_PROC(glDeleteProgram); CHECK_PROC(glDeleteRenderbuffers); CHECK_PROC(glDeleteShader); CHECK_PROC(glDeleteTextures); CHECK_PROC(glDepthFunc); CHECK_PROC(glDepthMask); CHECK_PROC(glDepthRangef); CHECK_PROC(glDetachShader); CHECK_PROC(glDisable); CHECK_PROC(glDisableVertexAttribArray); CHECK_PROC(glDrawArrays); CHECK_PROC(glDrawElements); CHECK_PROC(glEnable); CHECK_PROC(glEnableVertexAttribArray); CHECK_PROC(glFinish); CHECK_PROC(glFlush); CHECK_PROC(glFramebufferRenderbuffer); CHECK_PROC(glFramebufferTexture2D); CHECK_PROC(glFrontFace); CHECK_PROC(glGenBuffers); CHECK_PROC(glGenerateMipmap); CHECK_PROC(glGenFramebuffers); CHECK_PROC(glGenRenderbuffers); CHECK_PROC(glGenTextures); CHECK_PROC(glGetActiveAttrib); CHECK_PROC(glGetActiveUniform); CHECK_PROC(glGetAttachedShaders); CHECK_PROC(glGetAttribLocation); CHECK_PROC(glGetBooleanv); CHECK_PROC(glGetBufferParameteriv); CHECK_PROC(glGetError); CHECK_PROC(glGetFloatv); CHECK_PROC(glGetFramebufferAttachmentParameteriv); CHECK_PROC(glGetIntegerv); CHECK_PROC(glGetProgramiv); CHECK_PROC(glGetProgramInfoLog); CHECK_PROC(glGetRenderbufferParameteriv); CHECK_PROC(glGetShaderiv); CHECK_PROC(glGetShaderInfoLog); CHECK_PROC(glGetShaderPrecisionFormat); CHECK_PROC(glGetShaderSource); CHECK_PROC(glGetString); CHECK_PROC(glGetTexParameterfv); CHECK_PROC(glGetTexParameteriv); CHECK_PROC(glGetUniformfv); CHECK_PROC(glGetUniformiv); CHECK_PROC(glGetUniformLocation); CHECK_PROC(glGetVertexAttribfv); CHECK_PROC(glGetVertexAttribiv); CHECK_PROC(glGetVertexAttribPointerv); CHECK_PROC(glHint); CHECK_PROC(glIsBuffer); CHECK_PROC(glIsEnabled); CHECK_PROC(glIsFramebuffer); CHECK_PROC(glIsProgram); CHECK_PROC(glIsRenderbuffer); CHECK_PROC(glIsShader); CHECK_PROC(glIsTexture); CHECK_PROC(glLineWidth); CHECK_PROC(glLinkProgram); CHECK_PROC(glPixelStorei); CHECK_PROC(glPolygonOffset); CHECK_PROC(glReadPixels); CHECK_PROC(glReleaseShaderCompiler); CHECK_PROC(glRenderbufferStorage); CHECK_PROC(glSampleCoverage); CHECK_PROC(glScissor); CHECK_PROC(glShaderBinary); CHECK_PROC(glShaderSource); CHECK_PROC(glStencilFunc); CHECK_PROC(glStencilFuncSeparate); CHECK_PROC(glStencilMask); CHECK_PROC(glStencilMaskSeparate); CHECK_PROC(glStencilOp); CHECK_PROC(glStencilOpSeparate); CHECK_PROC(glTexImage2D); CHECK_PROC(glTexParameterf); CHECK_PROC(glTexParameterfv); CHECK_PROC(glTexParameteri); CHECK_PROC(glTexParameteriv); CHECK_PROC(glTexSubImage2D); CHECK_PROC(glUniform1f); CHECK_PROC(glUniform1fv); CHECK_PROC(glUniform1i); CHECK_PROC(glUniform1iv); CHECK_PROC(glUniform2f); CHECK_PROC(glUniform2fv); CHECK_PROC(glUniform2i); CHECK_PROC(glUniform2iv); CHECK_PROC(glUniform3f); CHECK_PROC(glUniform3fv); CHECK_PROC(glUniform3i); CHECK_PROC(glUniform3iv); CHECK_PROC(glUniform4f); CHECK_PROC(glUniform4fv); CHECK_PROC(glUniform4i); CHECK_PROC(glUniform4iv); CHECK_PROC(glUniformMatrix2fv); CHECK_PROC(glUniformMatrix3fv); CHECK_PROC(glUniformMatrix4fv); CHECK_PROC(glUseProgram); CHECK_PROC(glValidateProgram); CHECK_PROC(glVertexAttrib1f); CHECK_PROC(glVertexAttrib1fv); CHECK_PROC(glVertexAttrib2f); CHECK_PROC(glVertexAttrib2fv); CHECK_PROC(glVertexAttrib3f); CHECK_PROC(glVertexAttrib3fv); CHECK_PROC(glVertexAttrib4f); CHECK_PROC(glVertexAttrib4fv); CHECK_PROC(glVertexAttribPointer); CHECK_PROC(glViewport); CHECK_PROC(glMapBufferOES); CHECK_PROC(glUnmapBufferOES); CHECK_PROC(glTexStorage2D);

	LOGW("wglGetProcAddress_Hooked %s [NOT SUPPORTED]", name);
	return (*wglGetProcAddress_Original)(name);
}

BOOL WINAPI SwapBuffers_Hooked(HDC hdc)
{
	theServer->onSwapBuffers();
	return (*SwapBuffers_Original)(hdc);
}

void initHook(Server* server)
{
	theServer = server;

	MH_Initialize();

	#define HOOK_GL32(func) if (MH_CreateHookApi(L"opengl32.dll", STRINGIFY(func), ##func, (void**)&glPointers.func) == MH_OK) \
	{ \
		LOGI("opengl32.dll hooked: %s", STRINGIFY(func)); \
	}

	HOOK_GL32(glActiveTexture); HOOK_GL32(glAttachShader); HOOK_GL32(glBindAttribLocation); HOOK_GL32(glBindBuffer); HOOK_GL32(glBindFramebuffer); HOOK_GL32(glBindRenderbuffer); HOOK_GL32(glBindTexture); HOOK_GL32(glBlendColor); HOOK_GL32(glBlendEquation); HOOK_GL32(glBlendEquationSeparate); HOOK_GL32(glBlendFunc); HOOK_GL32(glBlendFuncSeparate); HOOK_GL32(glBufferData); HOOK_GL32(glBufferSubData); HOOK_GL32(glCheckFramebufferStatus); HOOK_GL32(glClear); HOOK_GL32(glClearColor); HOOK_GL32(glClearDepthf); HOOK_GL32(glClearStencil); HOOK_GL32(glColorMask); HOOK_GL32(glCompileShader); HOOK_GL32(glCompressedTexImage2D); HOOK_GL32(glCompressedTexSubImage2D); HOOK_GL32(glCopyTexImage2D); HOOK_GL32(glCopyTexSubImage2D); HOOK_GL32(glCreateProgram); HOOK_GL32(glCreateShader); HOOK_GL32(glCullFace); HOOK_GL32(glDeleteBuffers); HOOK_GL32(glDeleteFramebuffers); HOOK_GL32(glDeleteProgram); HOOK_GL32(glDeleteRenderbuffers); HOOK_GL32(glDeleteShader); HOOK_GL32(glDeleteTextures); HOOK_GL32(glDepthFunc); HOOK_GL32(glDepthMask); HOOK_GL32(glDepthRangef); HOOK_GL32(glDetachShader); HOOK_GL32(glDisable); HOOK_GL32(glDisableVertexAttribArray); HOOK_GL32(glDrawArrays); HOOK_GL32(glDrawElements); HOOK_GL32(glEnable); HOOK_GL32(glEnableVertexAttribArray); HOOK_GL32(glFinish); HOOK_GL32(glFlush); HOOK_GL32(glFramebufferRenderbuffer); HOOK_GL32(glFramebufferTexture2D); HOOK_GL32(glFrontFace); HOOK_GL32(glGenBuffers); HOOK_GL32(glGenerateMipmap); HOOK_GL32(glGenFramebuffers); HOOK_GL32(glGenRenderbuffers); HOOK_GL32(glGenTextures); HOOK_GL32(glGetActiveAttrib); HOOK_GL32(glGetActiveUniform); HOOK_GL32(glGetAttachedShaders); HOOK_GL32(glGetAttribLocation); HOOK_GL32(glGetBooleanv); HOOK_GL32(glGetBufferParameteriv); HOOK_GL32(glGetError); HOOK_GL32(glGetFloatv); HOOK_GL32(glGetFramebufferAttachmentParameteriv); HOOK_GL32(glGetIntegerv); HOOK_GL32(glGetProgramiv); HOOK_GL32(glGetProgramInfoLog); HOOK_GL32(glGetRenderbufferParameteriv); HOOK_GL32(glGetShaderiv); HOOK_GL32(glGetShaderInfoLog); HOOK_GL32(glGetShaderPrecisionFormat); HOOK_GL32(glGetShaderSource); HOOK_GL32(glGetString); HOOK_GL32(glGetTexParameterfv); HOOK_GL32(glGetTexParameteriv); HOOK_GL32(glGetUniformfv); HOOK_GL32(glGetUniformiv); HOOK_GL32(glGetUniformLocation); HOOK_GL32(glGetVertexAttribfv); HOOK_GL32(glGetVertexAttribiv); HOOK_GL32(glGetVertexAttribPointerv); HOOK_GL32(glHint); HOOK_GL32(glIsBuffer); HOOK_GL32(glIsEnabled); HOOK_GL32(glIsFramebuffer); HOOK_GL32(glIsProgram); HOOK_GL32(glIsRenderbuffer); HOOK_GL32(glIsShader); HOOK_GL32(glIsTexture); HOOK_GL32(glLineWidth); HOOK_GL32(glLinkProgram); HOOK_GL32(glPixelStorei); HOOK_GL32(glPolygonOffset); HOOK_GL32(glReadPixels); HOOK_GL32(glReleaseShaderCompiler); HOOK_GL32(glRenderbufferStorage); HOOK_GL32(glSampleCoverage); HOOK_GL32(glScissor); HOOK_GL32(glShaderBinary); HOOK_GL32(glShaderSource); HOOK_GL32(glStencilFunc); HOOK_GL32(glStencilFuncSeparate); HOOK_GL32(glStencilMask); HOOK_GL32(glStencilMaskSeparate); HOOK_GL32(glStencilOp); HOOK_GL32(glStencilOpSeparate); HOOK_GL32(glTexImage2D); HOOK_GL32(glTexParameterf); HOOK_GL32(glTexParameterfv); HOOK_GL32(glTexParameteri); HOOK_GL32(glTexParameteriv); HOOK_GL32(glTexSubImage2D); HOOK_GL32(glUniform1f); HOOK_GL32(glUniform1fv); HOOK_GL32(glUniform1i); HOOK_GL32(glUniform1iv); HOOK_GL32(glUniform2f); HOOK_GL32(glUniform2fv); HOOK_GL32(glUniform2i); HOOK_GL32(glUniform2iv); HOOK_GL32(glUniform3f); HOOK_GL32(glUniform3fv); HOOK_GL32(glUniform3i); HOOK_GL32(glUniform3iv); HOOK_GL32(glUniform4f); HOOK_GL32(glUniform4fv); HOOK_GL32(glUniform4i); HOOK_GL32(glUniform4iv); HOOK_GL32(glUniformMatrix2fv); HOOK_GL32(glUniformMatrix3fv); HOOK_GL32(glUniformMatrix4fv); HOOK_GL32(glUseProgram); HOOK_GL32(glValidateProgram); HOOK_GL32(glVertexAttrib1f); HOOK_GL32(glVertexAttrib1fv); HOOK_GL32(glVertexAttrib2f); HOOK_GL32(glVertexAttrib2fv); HOOK_GL32(glVertexAttrib3f); HOOK_GL32(glVertexAttrib3fv); HOOK_GL32(glVertexAttrib4f); HOOK_GL32(glVertexAttrib4fv); HOOK_GL32(glVertexAttribPointer); HOOK_GL32(glViewport); HOOK_GL32(glMapBufferOES); HOOK_GL32(glUnmapBufferOES); HOOK_GL32(glTexStorage2D);

	MH_CreateHookApi(L"opengl32.dll", "wglGetProcAddress", wglGetProcAddress_Hooked, (void**)&wglGetProcAddress_Original);

	MH_CreateHookApi(L"gdi32.dll", "SwapBuffers", SwapBuffers_Hooked, (void**)&SwapBuffers_Original);	

	MH_EnableHook(MH_ALL_HOOKS);
}
