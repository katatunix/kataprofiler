#pragma once

#include "GlObject.h"

class Shader : public GlObject
{
public:
	Shader() : GlObject(), m_szSource(NULL), m_type(0) {}

	Shader(u32 id) : GlObject(id), m_szSource(NULL), m_type(0) {}

	Shader(u32 id, const char* kszSource);

	~Shader();

	//

	void setSource(const char* kszSource);
	void setType(u32 type);
	u32 getType();
	
	void clearData();
	Message* toMessage();

protected:
	char* m_szSource;
	u32 m_type;
};
