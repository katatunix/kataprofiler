#include "Vbo.h"

Vbo::Vbo() : GlObject(), m_size(0), m_pData(NULL), m_usage(0)
{
}

Vbo::Vbo(u32 id) : GlObject(id), m_size(0), m_pData(NULL), m_usage(0)
{
}

Vbo::~Vbo()
{
	clearData();
}

void Vbo::clearData()
{
	m_size = 0;
	SAFE_DEL(m_pData);
	m_usage = 0;
}

void Vbo::on_glBufferData(int size,  const void * data,  u32 usage)
{
	clearData();
	m_size = size;
	// size can be zero
	if (size > 0)
	{
		m_pData = new char[size];
		if (data)
		{
			memcpy(m_pData, data, size);
		}
		else
		{
			memset(m_pData, 0, size);
		}
	}
	m_usage = usage;
}

void Vbo::on_glBufferSubData(int offset, int size, const void* data)
{
	// size can be zero
	if (size > 0)
	{
		memcpy(m_pData + offset, data, size);
	}
}

void Vbo::on_glMapBufferOES(GLenum access, void* ptr)
{
	SAFE_DEL(m_pData);
	m_pData = (char*)ptr;
}

void Vbo::on_glUnmapBufferOES()
{
	if (m_size > 0 && m_pData)
	{
		char* p = new char[m_size];
		memcpy(p, m_pData, m_size);
		m_pData = p;
	}
}

Message* Vbo::toMessage()
{
	Message* msg = new Message();
	msg->m_type = KMT_OBJECT_VBO;

	msg->m_length = 4 * 4;
	msg->m_pData = new char[msg->m_length];

	char* buffer = msg->m_pData;
	
	memcpy(buffer, &m_id, 4);		buffer += 4;
	memcpy(buffer, &m_size, 4);		buffer += 4;
	memcpy(buffer, &m_usage, 4);	buffer += 4;
	memcpy(buffer, &m_pData, 4);	buffer += 4;

	return msg;
}

int Vbo::getSize() { return m_size; }
char* Vbo::getData() { return m_pData; }
u32 Vbo::getUsage() { return m_usage; }
