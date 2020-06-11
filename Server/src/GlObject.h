#pragma once

#include "common.h"
#include "Message.h"

class GlObject
{
public:
	GlObject() : m_id(0) {}
	GlObject(u32 id) : m_id(id) {}

	virtual ~GlObject() {}

	u32 getId() { return m_id; }
	void setId(u32 id) { m_id = id; }

	virtual void clearData() = 0;
	virtual Message* toMessage() = 0;

protected:
	u32 m_id;
};
