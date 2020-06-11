#include "VertexAttribData.h"

VertexAttribData::VertexAttribData():
		m_enableVertexAttribArray	(true),

		m_dataComponentsNumber		(0),
		m_dataType					(0),
		m_dataStride				(0),
		m_dataPointer				(NULL),
		m_vboId						(0),

		m_dataNonArray_Components	(0)
{
}

VertexAttribData::~VertexAttribData()
{
}

void VertexAttribData::on_glVertexAttribPointer(GLint size, GLenum type, GLboolean normalized,
			GLsizei stride, const GLvoid * pointer, u32 vboId)
{
	m_dataComponentsNumber		= size;
	m_dataType					= type;
	m_dataNormalized			= normalized;
	m_dataStride				= stride;
	m_dataPointer				= pointer;
	m_vboId						= vboId;
}

void VertexAttribData::on_glVertexAttrib(int components, const float* v)
{
	m_dataNonArray_Components = components;
	for (int i = 0; i < components; i++)
	{
		m_dataNonArray_Values[i] = v[i];
	}
}

void VertexAttribData::setEnableVertexAttribArray(bool b)
{
	m_enableVertexAttribArray = b;
}

bool VertexAttribData::getEnableVertexAttribArray() const
{
	return m_enableVertexAttribArray;
}

int VertexAttribData::getDataComponentsNumber() const
{
	return m_dataComponentsNumber;
}

u32 VertexAttribData::getDataType() const
{
	return m_dataType;
}

bool VertexAttribData::getDataNormalized() const
{
	return m_dataNormalized;
}

int VertexAttribData::getDataStride() const
{
	return m_dataStride;
}
const void* VertexAttribData::getDataPointer() const
{
	return m_dataPointer;
}

u32 VertexAttribData::getVboId() const
{
	return m_vboId;
}

int VertexAttribData::getDataNonArray_Components() const
{
	return m_dataNonArray_Components;
}

const float* VertexAttribData::getDataNonArray_Values() const
{
	return (const float*)m_dataNonArray_Values;
}
