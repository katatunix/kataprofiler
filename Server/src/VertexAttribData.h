#pragma once

#include "common.h"
#include "glDefine.h"

class VertexAttribData
{
public:
	VertexAttribData();
	virtual ~VertexAttribData();

	void on_glVertexAttribPointer(GLint size, GLenum type, GLboolean normalized,
			GLsizei stride, const GLvoid * pointer, u32 vboId);

	void on_glVertexAttrib(int components, const float* v);

	void			setEnableVertexAttribArray(bool b);
	
	bool			getEnableVertexAttribArray() const;
	int				getDataComponentsNumber() const;
	u32				getDataType() const;
	bool			getDataNormalized() const;
	int				getDataStride() const;
	const void*		getDataPointer() const;
	u32				getVboId() const;

	int				getDataNonArray_Components() const;
	const float*	getDataNonArray_Values() const;

private:
	bool			m_enableVertexAttribArray;

	int				m_dataComponentsNumber;
	u32				m_dataType;
	bool			m_dataNormalized;
	int				m_dataStride;
	const void*		m_dataPointer;
	u32				m_vboId;

	int				m_dataNonArray_Components;
	float			m_dataNonArray_Values[4];
};
