#pragma once

#include "glDefine.h"
#include "GlObject.h"

class Vbo : public GlObject
{
public:
	Vbo();
	Vbo(u32 id);

	virtual ~Vbo();

	//
	void clearData();
	Message* toMessage();

	//
	void on_glBufferData(int size,  const void * data,  u32 usage);
	void on_glBufferSubData(int offset, int size, const void* data);

	void on_glMapBufferOES (GLenum access, void* ptr);
	void on_glUnmapBufferOES();

	//
	int getSize();
	char* getData();
	u32 getUsage();

private:
	int		m_size;
	char*	m_pData;
	u32		m_usage;
};
