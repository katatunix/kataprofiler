#pragma once

#include "glDefine.h"
#include "GlObject.h"
#include "GlHelper.h"

//=======================================================================================================
//=======================================================================================================
struct KPVar
{
public:
	enum { MAX_VAR_NAME_LENGTH = 128 };
	char m_szName[MAX_VAR_NAME_LENGTH];
	
	int m_location;
	int m_size;
	u32 m_type;

	KPVar() : m_location(-1), m_size(-1), m_type(0)
	{
		m_szName[0] = 0;
	}

	virtual ~KPVar()
	{
	}

	bool isTheSamePrototype(const KPVar& other) const
	{
		return m_location == other.m_location && m_size == other.m_size && m_type == other.m_type &&
			strcmp(m_szName, other.m_szName) == 0;
	}

	bool isArray() const
	{
		return strstr(m_szName, "[") && strstr(m_szName, "]");
	}

	int getTypeComponents() const // if this is a matrix, size of matrix is returned
	{
		switch (m_type)
		{
			case GL_FLOAT: case GL_INT: case GL_BOOL: case GL_SAMPLER_2D: case GL_SAMPLER_3D: case GL_SAMPLER_CUBE: return 1;
			case GL_FLOAT_VEC2: case GL_INT_VEC2: case GL_BOOL_VEC2: case GL_FLOAT_MAT2: return 2;
			case GL_FLOAT_VEC3: case GL_INT_VEC3: case GL_BOOL_VEC3: case GL_FLOAT_MAT3: return 3;
			case GL_FLOAT_VEC4: case GL_INT_VEC4: case GL_BOOL_VEC4: case GL_FLOAT_MAT4: return 4;
		}
		return 0;
	}

	bool isTypeFloat() const
	{
		return m_type == GL_FLOAT || m_type == GL_FLOAT_VEC2 || m_type == GL_FLOAT_VEC3 || m_type == GL_FLOAT_VEC4 ||
			m_type == GL_FLOAT_MAT2 || m_type == GL_FLOAT_MAT3 || m_type == GL_FLOAT_MAT4;
	}

	bool isTypeMatrix() const
	{
		return m_type == GL_FLOAT_MAT2 || m_type == GL_FLOAT_MAT3 || m_type == GL_FLOAT_MAT4;
	}
};

//=======================================================================================================
//=======================================================================================================
struct KPAttribute : public KPVar
{
public:
};

//=======================================================================================================
//=======================================================================================================
struct KPUniform : public KPVar
{
public:
	KPUniform() : KPVar(), m_pValuePointer(NULL), m_valueBytesNumber(0)
	{
		
	}

	virtual ~KPUniform()
	{
		freeValue();
	}

	void freeValue()
	{
		SAFE_DEL_ARRAY(m_pValuePointer);
		m_valueBytesNumber = 0;
	}

	char*	m_pValuePointer;
	int		m_valueBytesNumber;
};

//=======================================================================================================
//=======================================================================================================
class Program : public GlObject
{
public:
	Program() : GlObject(), m_vsId(0), m_fsId(0), m_attributesCount(0), m_uniformsCount(0) {}

	Program(u32 id) : GlObject(id), m_vsId(0), m_fsId(0), m_attributesCount(0), m_uniformsCount(0) {}

	virtual ~Program() {}

	void clearData();
	Message* toMessage();

	bool attachVs(u32 vs);
	bool attachFs(u32 fs);
	bool detach(u32 shader);

	void link(GlHelper& glHelper);

	int getUniformsCount() const;
	const KPUniform& getUniform(int index) const;
	const KPUniform* getUniformByLocation(int location) const;

	int getAttributesCount() const;
	const KPAttribute& getAttribute(int index) const;

	//
	void on_glUniform1f(GLint location, GLfloat x);
	void on_glUniform1fv(GLint location, GLsizei count, const GLfloat* v);
	void on_glUniform1i(GLint location, GLint x);
	void on_glUniform1iv(GLint location, GLsizei count, const GLint* v);
	void on_glUniform2f(GLint location, GLfloat x, GLfloat y);
	void on_glUniform2fv(GLint location, GLsizei count, const GLfloat* v);
	void on_glUniform2i(GLint location, GLint x, GLint y);
	void on_glUniform2iv(GLint location, GLsizei count, const GLint* v);
	void on_glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z);
	void on_glUniform3fv(GLint location, GLsizei count, const GLfloat* v);
	void on_glUniform3i(GLint location, GLint x, GLint y, GLint z);
	void on_glUniform3iv(GLint location, GLsizei count, const GLint* v);
	void on_glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void on_glUniform4fv(GLint location, GLsizei count, const GLfloat* v);
	void on_glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w);
	void on_glUniform4iv(GLint location, GLsizei count, const GLint* v);
	void on_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	void on_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	void on_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

	void on_glUniformMatrix(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value, int size);

protected:
	enum
	{
		MAX_ATTRIBUTES_NUMBER = 128,
		MAX_UNIFORMS_NUMBER = 128
	};

	u32 m_vsId;
	u32 m_fsId;

	int m_attributesCount;
	KPAttribute m_attributes[MAX_ATTRIBUTES_NUMBER];

	int m_uniformsCount;
	KPUniform m_uniforms[MAX_UNIFORMS_NUMBER];
};
