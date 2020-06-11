#include "Server.h"
#include "GlHelper.h"
#include "ImageHelper.h"
#include "net/Socket.h"
#include "ServerOption.h"
#include "log.h"

Server::Server(GlHelper glHelper) : m_state(IDLE), m_glHelper(glHelper)
{
}

Server::~Server()
{
	for (int i = 0; i < MAX_PROGRAMS_NUMBER; i++)
	{
		m_pProgramsList[i].clearData();
	}
	for (int i = 0; i < MAX_SHADERS_NUMBER; i++)
	{
		m_pShadersList[i].clearData();
	}

	for (int i = 0; i < MAX_VBOS_NUMBER; i++)
	{
		m_pVbosList[i].clearData();
	}
}

void Server::makeGLCommandMsg(KPMessageType type)
{
	m_msg.clearData();
	m_msg.m_type = type;
}

bool Server::isBusy()
{
	LockScope ls(m_mutex);
	return m_state != IDLE;
}

void Server::enterPreCapture()
{
	LockScope ls(m_mutex);
	m_state = PRE_CAPTURE;
}

void Server::enterModifyingProgram()
{
	LockScope ls(m_mutex);
	m_state = MODIFYING_PROGRAM;
}

void Server::onRequestCapture(Messenger m, CaptureOption co)
{
	m_messenger = m;
	m_captureOption = co;
}

void Server::onRequestModifyProgram(Messenger m)
{
	m_messenger = m;
}

Program* Server::getProgram(u32 id)
{
	if (id == 0) return NULL;
	for (int i = 0; i < MAX_PROGRAMS_NUMBER; i++)
	{
		if (m_pProgramsList[i].getId() == id) return &m_pProgramsList[i];
	}
	return NULL;
}

Program* Server::getFreeProgram()
{
	for (int i = 0; i < MAX_PROGRAMS_NUMBER; i++)
	{
		if (m_pProgramsList[i].getId() == 0) return &m_pProgramsList[i];
	}
	return NULL;
}

Shader* Server::getShader(u32 id)
{
	if (id == 0) return NULL;
	for (int i = 0; i < MAX_SHADERS_NUMBER; i++)
	{
		if (m_pShadersList[i].getId() == id) return &m_pShadersList[i];
	}
	return NULL;
}

Shader* Server::getFreeShader()
{
	for (int i = 0; i < MAX_SHADERS_NUMBER; i++)
	{
		if (m_pShadersList[i].getId() == 0) return &m_pShadersList[i];
	}
	return NULL;
}

Texture* Server::getTexture(u32 id)
{
	if (id == 0) return NULL;
	for (int i = 0; i < MAX_TEXTURES_NUMBER; i++)
	{
		if (m_pTexturesList[i].getId() == id) return &m_pTexturesList[i];
	}
	return NULL;
}

Texture* Server::getFreeTexture()
{
	for (int i = 0; i < MAX_TEXTURES_NUMBER; i++)
	{
		if (m_pTexturesList[i].getId() == 0) return &m_pTexturesList[i];
	}
	return NULL;
}

Vbo* Server::getVbo(u32 id)
{
	if (id == 0) return NULL;
	for (int i = 0; i < MAX_VBOS_NUMBER; i++)
	{
		if (m_pVbosList[i].getId() == id) return &m_pVbosList[i];
	}
	return NULL;
}

Vbo* Server::getFreeVbo()
{
	for (int i = 0; i < MAX_VBOS_NUMBER; i++)
	{
		if (m_pVbosList[i].getId() == 0) return &m_pVbosList[i];
	}
	return NULL;
}

//========================================================================================

void Server::onSwapBuffers()
{
	LockScope ls(m_mutex);
	switch (m_state)
	{
	case PRE_CAPTURE:
	{
		if (sendObjects())
			m_state = CAPTURING;
		else
		{
			m_messenger.close();
			m_state = IDLE;
		}
		break;
	}
	case CAPTURING:
	{
		m_messenger.sendRequestFinish();
		m_messenger.close();
		m_state = IDLE;
		LOGD("Capturing finished");
		break;
	}
	case MODIFYING_PROGRAM:
	{
		modifyProgram();
		m_messenger.close();
		m_state = IDLE;
		LOGD("Shader modifying finished");
		break;
	}
	}
}

bool Server::sendObjects()
{
	for (int i = 0; i < MAX_PROGRAMS_NUMBER; i++) if (m_pProgramsList[i].getId())
		if (m_messenger.send(m_pProgramsList[i]) == SOCKET_ERROR)
			return false;

	for (int i = 0; i < MAX_SHADERS_NUMBER; i++) if (m_pShadersList[i].getId())
		if (m_messenger.send(m_pShadersList[i]) == SOCKET_ERROR)
			return false;

	for (int i = 0; i < MAX_TEXTURES_NUMBER; i++) if (m_pTexturesList[i].getId())
		if (m_messenger.send(m_pTexturesList[i]) == SOCKET_ERROR)
			return false;

	for (int i = 0; i < MAX_VBOS_NUMBER; i++) if (m_pVbosList[i].getId())
		if (m_messenger.send(m_pVbosList[i]) == SOCKET_ERROR)
			return false;

	if (sendTexUnits() == SOCKET_ERROR)
		return false;
	
	u32 progId = m_glHelper.get_CURRENT_PROGRAM();
	if (m_messenger.sendCurrentUsingProgram(progId) == SOCKET_ERROR)
		return false;
	
	u32 vboArrayBuffer = m_glHelper.get_ARRAY_BUFFER_BINDING();
	u32 vboElementArrayBuffer = m_glHelper.get_ELEMENT_ARRAY_BUFFER_BINDING();
	if (m_messenger.sendCurrentBindingVbos(vboArrayBuffer, vboElementArrayBuffer) == SOCKET_ERROR)
		return false;

	return true;
}

int Server::sendTexUnits()
{
	const int NUM_TEX_UNITS = 32;
	int actual = m_glHelper.get_MAX_COMBINED_TEXTURE_IMAGE_UNITS();
	if (actual > NUM_TEX_UNITS)
		actual = NUM_TEX_UNITS;

	u8 curActiveTexUnit = m_glHelper.get_ACTIVE_TEXTURE();
	u32 texIds_2D[NUM_TEX_UNITS];
	u32 texIds_CubeMap[NUM_TEX_UNITS];
	for (int i = 0; i < actual; ++i)
	{
		m_glHelper.activeTexture(i);
		texIds_2D[i] = m_glHelper.get_TEXTURE_BINDING_2D();
		texIds_CubeMap[i] = m_glHelper.get_TEXTURE_BINDING_CUBE_MAP();
	}
	for (int i = actual; i < NUM_TEX_UNITS; ++i)
	{
		texIds_2D[i] = 0;
		texIds_CubeMap[i] = 0;
	}
	m_glHelper.activeTexture(curActiveTexUnit);
	return m_messenger.sendTexUnits(NUM_TEX_UNITS, curActiveTexUnit, texIds_2D, texIds_CubeMap);
}

void Server::modifyProgram()
{
	//---------------------------------------------------------------------------------------------
	// Receive data from client
	u32 progId, vsId, fsId;
	s32 vsSourceLen, fsSourceLen;
	char* vsSourceString = NULL;
	char* fsSourceString = NULL;
	int len = 0;
	Program* pOldProg = NULL;
	Program newProg;
	char* error = NULL;

	//---------------------------------------------------------------------------------------------
	// Read id(s)
	if (!m_messenger.receiveUint(progId)) goto my_end_modifying_program;
	if (!m_messenger.receiveUint(vsId)) goto my_end_modifying_program;
	if (!m_messenger.receiveUint(fsId)) goto my_end_modifying_program;

	//---------------------------------------------------------------------------------------------
	// Read vsSourceString
	if (!m_messenger.receiveInt(len)) goto my_end_modifying_program;
	if (len < 0) len = 0;
	vsSourceString = new char[len + 1];
	if (len > 0)
	{
		if (!m_messenger.receive(vsSourceString, len)) goto my_end_modifying_program;
	}
	vsSourceString[len] = 0;
	vsSourceLen = len;

	//---------------------------------------------------------------------------------------------
	// Read fsSourceString
	if (!m_messenger.receiveInt(len)) goto my_end_modifying_program;
	if (len < 0) len = 0;
	fsSourceString = new char[len + 1];
	if (len > 0)
	{
		if (!m_messenger.receive(fsSourceString, len)) goto my_end_modifying_program;
	}
	fsSourceString[len] = 0;
	fsSourceLen = len;

	//--------------------------------------------------------------------------------------------
	// Process the data received

	pOldProg = getProgram(progId);

	error = m_glHelper.checkValidModifiedProgram(progId, vsId, fsId, vsSourceString, fsSourceString, pOldProg, newProg);

	if (error)
	{
		m_messenger.sendRequestError(error);
	}
	else
	{
		//--------------------------------------------------------------------------------------------
		// Compile the new shader sources

		m_glHelper.shaderSource(vsId, 1, (const char**)&vsSourceString, NULL);
		m_glHelper.compileShader(vsId);
		m_glHelper.shaderSource(fsId, 1, (const char**)&fsSourceString, NULL);
		m_glHelper.compileShader(fsId);

		//--------------------------------------------------------------------------------------------
		// Copy/bind location of attributes
		int count = pOldProg->getAttributesCount();
		for (int i = 0; i < count; i++)
		{
			const KPAttribute& att = pOldProg->getAttribute(i);
			m_glHelper.bindAttribLocation(progId, att.m_location, att.m_szName);
		}
		
		m_glHelper.linkProgram(progId);

		//--------------------------------------------------------------------------------------------
		u32 oldUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		m_glHelper.useProgram(progId);
		// Copy/upload/restore value of uniforms
		m_glHelper.copyProgramUniformsStateToGpu(newProg, *pOldProg);

		m_glHelper.useProgram(oldUsingProgram);

		// NOTE this
		//pOldProg->link();
		//

		getShader(vsId)->setSource(vsSourceString);
		getShader(fsId)->setSource(fsSourceString);

		m_messenger.sendRequestFinish();
	}

	my_end_modifying_program:
	SAFE_DEL_ARRAY(vsSourceString);
	SAFE_DEL_ARRAY(fsSourceString);
	SAFE_DEL_ARRAY(error);
}

//========================================================================================
//========================================================================================
//========================================================================================
//========================================================================================

void Server::on_glActiveTexture(GLenum texture)
{
	LockScope ls(m_mutex);

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glActiveTexture);

		m_msg.m_length = 4 + 1;
		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &texture, 4); buffer += 4;

		u8 actual = m_glHelper.get_ACTIVE_TEXTURE();
		memcpy(buffer, &actual, 1); buffer += 1;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}

}

void Server::on_glAttachShader(GLuint program, GLuint shader)
{
	LockScope ls(m_mutex);
	u8 error = 0;

	Program* prog = getProgram(program);
	if (prog)
	{
		Shader* pshader = getShader(shader);
		if (pshader)
		{
			if (pshader->getType() == GL_VERTEX_SHADER)
			{
				if (!prog->attachVs(shader))
				{
					error = 1;
					LOGE("error [%s] can not attach vs=%d, program=%d", __FUNCTION__, shader, program);
				}
			}
			else
			{
				if (!prog->attachFs(shader))
				{
					error = 1;
					LOGE("error [%s] can not attach fs=%d, program=%d", __FUNCTION__, shader, program);
				}
			}
		}
		else
		{
			error = 1;
			LOGE("error [%s] not found the shader id = %d", __FUNCTION__, shader);
		}
	}
	else
	{
		error = 1;
		LOGE("error [%s] not found the program id = %d", __FUNCTION__, program);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glAttachShader);

		m_msg.m_length = 1 + 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);					buffer += 1;
		memcpy(buffer, &program, 4);				buffer += 4;
		memcpy(buffer, &shader, 4);					buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBindAttribLocation(GLuint program, GLuint index, const GLchar* name)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBindAttribLocation);

		int strLen = name ? STRLEN(name) : 0;

		m_msg.m_length = 4 + 4 + strLen;
		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &program, 4);			buffer += 4;
		memcpy(buffer, &index, 4);				buffer += 4;
		if (strLen > 0)
		{
			memcpy(buffer, name, strLen);
			buffer += strLen;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBindBuffer(GLenum target, GLuint buffer)
{
	LockScope ls(m_mutex);

	u8 error = 0;
	if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER)
	{
		LOGE("[%s] invalid target = 0x%x", __FUNCTION__, target);
		error = 1;
		goto my_end;
	}

	if (buffer > 0 && !getVbo(buffer))
	{
		LOGE("[%s] not found the buffer id = %d", __FUNCTION__, buffer);
		error = 1;
		goto my_end;
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBindBuffer);

		m_msg.m_length = 1 + 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		char* _buffer = m_msg.m_pData;

		memcpy(_buffer, &error, 1);					_buffer += 1;
		memcpy(_buffer, &target, 4);				_buffer += 4;
		memcpy(_buffer, &buffer, 4);				_buffer += 4;
		u32 actualBoundBuffer = m_glHelper.get_BUFFER_BINDING(target);
		memcpy(_buffer, &actualBoundBuffer, 4);		_buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBindFramebuffer);

		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &framebuffer, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBindRenderbuffer);

		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &renderbuffer, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBindTexture(GLenum target, GLuint texture)
{
	LockScope ls(m_mutex);

	u8 error = 0;
	Texture* tex;

	if (target != GL_TEXTURE_2D && target != GL_TEXTURE_CUBE_MAP)
	{
		LOGE("error [%s] invalid target = 0x%x", __FUNCTION__, target);
		error = 1;
		goto my_end;
	}

	if (texture > 0)
	{
		tex = getTexture(texture);
		if (!tex)
		{
			LOGE("error [%s] not found the texture id = %d", __FUNCTION__, texture);
			error = 1;
			goto my_end;
		}
		TextureType texType = tex->getTexType();
		if (texType != TEX_NONE)
		{
			if (target == GL_TEXTURE_2D && texType != TEX_2D)
			{
				LOGE("error [%s] can not bind a non-2D texture to target GL_TEXTURE_2D", __FUNCTION__);
				error = 1;
				goto my_end;
			}
			if (target == GL_TEXTURE_CUBE_MAP && texType != TEX_CUBE_MAP)
			{
				LOGE("error [%s] can not bind a non-CubeMap texture to target GL_TEXTURE_CUBE_MAP", __FUNCTION__);
				error = 1;
				goto my_end;
			}
		}
		else
		{
			tex->setTexType(target == GL_TEXTURE_2D ? TEX_2D : TEX_CUBE_MAP);
		}
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBindTexture);

		m_msg.m_length = 1 + 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);					buffer += 1;
		memcpy(buffer, &target, 4);					buffer += 4;
		memcpy(buffer, &texture, 4);				buffer += 4;

		u32 actual = 0;
		if (target == GL_TEXTURE_2D)			actual = m_glHelper.get_TEXTURE_BINDING_2D();
		else if (target == GL_TEXTURE_CUBE_MAP)	actual = m_glHelper.get_TEXTURE_BINDING_CUBE_MAP();
		memcpy(buffer, &actual, 4);					buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBlendColor);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &red, 4);
		memcpy(m_msg.m_pData + 4, &green, 4);
		memcpy(m_msg.m_pData + 8, &blue, 4);
		memcpy(m_msg.m_pData + 12, &alpha, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBlendEquation(GLenum mode)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBlendEquation);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &mode, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBlendEquationSeparate);

		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &modeRGB, 4);
		memcpy(m_msg.m_pData + 4, &modeAlpha, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBlendFunc);

		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &sfactor, 4);
		memcpy(m_msg.m_pData + 4, &dfactor, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBlendFuncSeparate);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &srcRGB, 4);
		memcpy(m_msg.m_pData + 4, &dstRGB, 4);
		memcpy(m_msg.m_pData + 8, &srcAlpha, 4);
		memcpy(m_msg.m_pData + 12, &dstAlpha, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	LockScope ls(m_mutex);

	u32 currentBindingVbo;
	Vbo* vbo;
	u8 error = 0;

	if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER)
	{
		LOGE("error [%s] Unknown target = 0x%x", __FUNCTION__, target);
		error = 1;
		goto my_end;
	}

	if (size < 0)
	{
		LOGE("error [%s] size is negative, size = %d", __FUNCTION__, size);
		error = 1;
		goto my_end;
	}

	if (usage != GL_STREAM_DRAW && usage != GL_STATIC_DRAW && usage != GL_DYNAMIC_DRAW)
	{
		LOGE("error [%s] Unknown usage = 0x%x", __FUNCTION__, usage);
		error = 1;
		goto my_end;
	}

	currentBindingVbo = m_glHelper.get_BUFFER_BINDING(target);

	vbo = getVbo(currentBindingVbo);
	if (vbo)
	{
		vbo->on_glBufferData(size, data, usage);
	}
	else
	{
		LOGE("error [%s] Not found the vbo id: %d", __FUNCTION__, currentBindingVbo);
		error = 1;
		goto my_end;
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBufferData);

		m_msg.m_length = 1/*error*/ + 4/*currentBindingVbo*/ + 4 + 4 + 4 + 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);					buffer += 1;
		memcpy(buffer, &currentBindingVbo, 4);		buffer += 4;
		memcpy(buffer, &target, 4);					buffer += 4;
		memcpy(buffer, &size, 4);					buffer += 4;
		memcpy(buffer, &data, 4);					buffer += 4;
		memcpy(buffer, &usage, 4);					buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
	LockScope ls(m_mutex);

	u32 currentBindingVbo;
	Vbo* vbo;
	u8 error = 0;

	if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER)
	{
		LOGE("error [%s] Unknown target = 0x%x", __FUNCTION__, target);
		error = 1;
		goto my_end;
	}

	if (size < 0 || offset < 0)
	{
		LOGE("error [%s] size or offset is negative, size = %d, offset = %d", __FUNCTION__, size, offset);
		error = 1;
		goto my_end;
	}

	if (!data)
	{
		LOGE("error [%s] data is NULL", __FUNCTION__);
		error = 1;
		goto my_end;
	}

	currentBindingVbo = m_glHelper.get_BUFFER_BINDING(target);

	vbo = getVbo(currentBindingVbo);
	if (vbo)
	{
		int prevSize = vbo->getSize();
		if (offset + size <= prevSize)
		{
			vbo->on_glBufferSubData(offset, size, data);
		}
		else
		{
			LOGE("error [%s] extends beyond the buffer object's allocated data store: offset=%d, size=%d, prevSize=%d",
				__FUNCTION__, offset, size, prevSize);
			error = 1;
			goto my_end;
		}
	}
	else
	{
		LOGE("error [%s] Not found the vbo id: %d", __FUNCTION__, currentBindingVbo);
		error = 1;
		goto my_end;
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glBufferSubData);

		m_msg.m_length = 1/*error*/ + 4/*currentBindingVbo*/ + 4 + 4 + 4 + 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);					buffer += 1;
		memcpy(buffer, &currentBindingVbo, 4);		buffer += 4;
		memcpy(buffer, &target, 4);					buffer += 4;
		memcpy(buffer, &offset, 4);					buffer += 4;
		memcpy(buffer, &size, 4);					buffer += 4;
		memcpy(buffer, &data, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glCheckFramebufferStatus(GLenum target, GLenum result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glCheckFramebufferStatus);

		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &result, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glClear(GLbitfield mask)
{
	LockScope ls(m_mutex);
	char* rgbaScreenshot = NULL;
	int width, height;
	if (m_state == CAPTURING)
	{
		int widthScaled, heightScaled, imageLen;
		rgbaScreenshot = takeRgbaScreenshot(width, height);
		char* bgrScreenshot = makeBgrScreenshot(rgbaScreenshot, width, height, widthScaled, heightScaled, imageLen);

		makeGLCommandMsg(KMT_glClear);

		m_msg.m_length = 4/*fbo*/ + 4 + 4 * 2 + 4 * 2 + 4 + imageLen;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		u32 fbo = m_glHelper.get_FRAMEBUFFER_BINDING();
		memcpy(buffer, &fbo, 4);				buffer += 4;

		memcpy(buffer, &mask, 4);				buffer += 4;

		memcpy(buffer, &width, 4);				buffer += 4;
		memcpy(buffer, &height, 4);				buffer += 4;

		memcpy(buffer, &widthScaled, 4);		buffer += 4;
		memcpy(buffer, &heightScaled, 4);		buffer += 4;

		memcpy(buffer, &imageLen, 4);			buffer += 4;

		if (bgrScreenshot && imageLen > 0)
		{
			memcpy(buffer, bgrScreenshot, imageLen);
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();

		SAFE_DEL(bgrScreenshot);
	}
#if CAPTURE_RENDER_TO_TEXTURE
	copyCurrentFboToTexture(&rgbaScreenshot, width, height);
#endif
	SAFE_DEL(rgbaScreenshot);
}

char* Server::takeRgbaScreenshot(int& width, int& height)
{
	int x, y;
	m_glHelper.getViewport(x, y, width, height);
	char* pixels = new char[width * height * 4];
	m_glHelper.readPixels(x, y, width, height, pixels);
	return pixels;
}

char* Server::makeBgrScreenshot(char* rgba, int width, int height, int& widthScaled, int& heightScaled, int& imageLen)
{
	const bool swapRb = true;
	return ImageHelper::polishScreenshot(rgba, width, height,
		m_captureOption.scaleScreenshot, swapRb, widthScaled, heightScaled, imageLen);
}

void Server::copyCurrentFboToTexture(char** pixels, int width, int height)
{
	u32 texId;
	int mipLevel;
	if (m_glHelper.isRenderingToTexture(texId, mipLevel))
	{
		Texture* tex = getTexture(texId);
		if (tex)
		{
			if (!*pixels) *pixels = takeRgbaScreenshot(width, height);
			tex->copyRenderingRgba(mipLevel, width, height, *pixels);
		}
	}
}

void Server::on_glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glClearColor);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &red, 4);
		memcpy(m_msg.m_pData + 4, &green, 4);
		memcpy(m_msg.m_pData + 8, &blue, 4);
		memcpy(m_msg.m_pData + 12, &alpha, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glClearDepthf(GLclampf depth)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glClearDepthf);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &depth, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glClearStencil(GLint s)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glClearStencil);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &s, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glColorMask);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &red, 1);
		memcpy(m_msg.m_pData + 1, &green, 1);
		memcpy(m_msg.m_pData + 2, &blue, 1);
		memcpy(m_msg.m_pData + 3, &alpha, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glCompileShader(GLuint shader)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glCompileShader);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];
		memcpy(m_msg.m_pData, &shader, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat,
	GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
{
	LockScope ls(m_mutex);

	u32 id = m_glHelper.get_TEXTURE_BINDING(target);

	LOGD("[%s] id=%d, target=0x%x, level=%d, internalformat=0x%x, width=%d, height=%d, border=%d, imageSize=%d, data=%p",
		__FUNCTION__, id, target, level, internalformat, width, height, border, imageSize, data);

	Texture* tex = getTexture(id);
	Mipmap* mip = NULL;
	if (!tex)
	{
		LOGE("[%s] Not found the texture id %d", __FUNCTION__, id);
	}
	else
	{
		mip = tex->on_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glCompressedTexImage2D);
		m_msg.m_length = 1/*error*/ + 4/*id*/ + 4/*target*/ + 4/*level*/ + 4/*internalformat*/ + 4/*width*/ + 4/*height*/ +
			4/*border*/ + 4/*imageSize*/ + 4 /*data pointer address*/;
		if (mip)
		{
			m_msg.m_length += imageSize;
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;
		u8 error = mip ? 0 : 1;
		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &id, 4);					buffer += 4;
		memcpy(buffer, &target, 4);				buffer += 4;
		memcpy(buffer, &level, 4);				buffer += 4;
		memcpy(buffer, &internalformat, 4);		buffer += 4;
		memcpy(buffer, &width, 4);				buffer += 4;
		memcpy(buffer, &height, 4);				buffer += 4;
		memcpy(buffer, &border, 4);				buffer += 4;
		memcpy(buffer, &imageSize, 4);			buffer += 4;
		memcpy(buffer, &data, 4);				buffer += 4;

		if (mip)
		{
			memcpy(buffer, data, imageSize);
			buffer += imageSize;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}

}

void Server::on_glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
	GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
{
	LockScope ls(m_mutex);

	u32 id = m_glHelper.get_TEXTURE_BINDING(target);

	LOGD("[%s] id=%d, target=0x%x, level=%d, xoffset=%d, yoffset=%d, width=%d, height=%d, format=0x%x, imageSize=0x%x, data=%p",
		__FUNCTION__, id, target, level, xoffset, yoffset, width, height, format, imageSize, data);

	Texture* tex = getTexture(id);
	Mipmap* subMip = NULL;
	if (!tex)
	{
		LOGE("error [%s] Not found the texture id = %d", __FUNCTION__, id);
	}
	else
	{
		subMip = tex->on_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glCompressedTexSubImage2D);
		m_msg.m_length = 1/*error*/ + 4/*id*/ + +4/*target*/ + 4/*level*/ + 4/*xoffset*/ + 4/*yoffset*/ +
			4/*width*/ + 4/*height*/ + 4/*format*/ + 4/*imageSize*/ + 4/*data pointer address*/;
		if (subMip)
		{
			m_msg.m_length += imageSize;
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;
		u8 error = subMip ? 0 : 1;
		memcpy(buffer, &error, 1);		buffer += 1;
		memcpy(buffer, &id, 4);			buffer += 4;
		memcpy(buffer, &target, 4);		buffer += 4;
		memcpy(buffer, &level, 4);		buffer += 4;
		memcpy(buffer, &xoffset, 4);	buffer += 4;
		memcpy(buffer, &yoffset, 4);	buffer += 4;
		memcpy(buffer, &width, 4);		buffer += 4;
		memcpy(buffer, &height, 4);		buffer += 4;
		memcpy(buffer, &format, 4);		buffer += 4;
		memcpy(buffer, &imageSize, 4);	buffer += 4;
		memcpy(buffer, &data, 4);		buffer += 4;
		if (subMip)
		{
			memcpy(buffer, data, imageSize);
			buffer += imageSize;
		}
		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
	//SAFE_DEL(subMip); //TODO
}

void Server::on_glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat,
	GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	LockScope ls(m_mutex);

	Mipmap* mip = NULL;
	Texture* tex = NULL;
	u32 id = m_glHelper.get_TEXTURE_BINDING(target);

	if (!m_glHelper.isCurrentFramebufferComplete())
	{
		LOGE("[%s] currently bound framebuffer is not framebuffer complete", __FUNCTION__);
		goto my_end;
	}

	LOGD("[%s] id=%d, target=0x%x, level=%d, internalformat=0x%x, x=%d, y=%d, width=%d, height=%d, border=%d",
			__FUNCTION__, id, target, level, internalformat, x, y, width, height, border);
	
	tex = getTexture(id);
	if (!tex)
	{
		LOGE("[%s] Not found the texture id %d", __FUNCTION__, id);
	}
	else
	{
		char* screenshot = new char[width * height * 4];
		m_glHelper.readPixels(x, y, width, height, screenshot);
		mip = tex->on_glCopyTexImage2D(target, level, internalformat, width, height, border, screenshot);
		SAFE_DEL(screenshot);
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glCopyTexImage2D);
		m_msg.m_length = 1/*error*/ + 4/*id*/ + 4/*target*/ + 4/*level*/ + 4/*internalformat*/ +
						4/*x*/ + 4/*y*/ + 4/*width*/ + 4/*height*/ + 4/*border*/;
		int size;
		if (mip)
		{
			size = mip->getImageSize();
			m_msg.m_length += 4/*actualformat*/ + size;
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;
		u8 error = mip ? 0 : 1;
		memcpy(buffer, &error, 1);						buffer += 1;
		memcpy(buffer, &id, 4);							buffer += 4;
		memcpy(buffer, &target, 4);						buffer += 4;
		memcpy(buffer, &level, 4);						buffer += 4;
		memcpy(buffer, &internalformat, 4);				buffer += 4;
		memcpy(buffer, &x, 4);							buffer += 4;
		memcpy(buffer, &y, 4);							buffer += 4;
		memcpy(buffer, &width, 4);						buffer += 4;
		memcpy(buffer, &height, 4);						buffer += 4;
		memcpy(buffer, &border, 4);						buffer += 4;

		if (mip)
		{
			GLenum actualformat = mip->getFormat();
			memcpy(buffer, &actualformat, 4);			buffer += 4;
			memcpy(buffer, mip->getPixels(), size);
			if (mip->isRawRgba() || mip->isRawRgb())
				ImageHelper::swapRB(buffer, width * height, mip->isRawRgba());
			buffer += size;
		}
	
		if ( m_messenger.send(m_msg) == SOCKET_ERROR ) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
	GLint x, GLint y, GLsizei width, GLsizei height)
{
	LockScope ls(m_mutex);

	Mipmap* subMip = NULL;
	Texture* tex = NULL;
	u32 id = m_glHelper.get_TEXTURE_BINDING(target);

	LOGD("[%s] id=%d, target=0x%x, level=%d, xoffset=%d, yoffset=%d, x=%d, y=%d, width=%d, height=%d",
		__FUNCTION__, id, target, level, xoffset, yoffset, x, y, width, height);

	if (!m_glHelper.isCurrentFramebufferComplete())
	{
		LOGE("[%s] currently bound framebuffer is not framebuffer complete", __FUNCTION__);
		goto my_end;
	}

	tex = getTexture(id);
	if (!tex)
	{
		LOGE("[%s] Not found the texture id %d", __FUNCTION__, id);
	}
	else
	{
		char* screenshot = new char[width * height * 4];
		m_glHelper.readPixels(x, y, width, height, screenshot);
		subMip = tex->on_glCopyTexSubImage2D(target, level, xoffset, yoffset, width, height, screenshot);
		SAFE_DEL(screenshot);
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glCopyTexSubImage2D);
		m_msg.m_length = 1/*error*/ + 4/*id*/ + 4/*target*/ + 4/*level*/ + 4/*xoffset*/ + 4/*yoffset*/ +
						4/*x*/ + 4/*y*/ + 4/*width*/ + 4/*height*/;
		int size;
		if (subMip)
		{
			size = subMip->getImageSize();
			m_msg.m_length += size;
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;
		u8 error = subMip ? 0 : 1;
		memcpy(buffer, &error, 1);						buffer += 1;
		memcpy(buffer, &id, 4);							buffer += 4;
		memcpy(buffer, &target, 4);						buffer += 4;
		memcpy(buffer, &level, 4);						buffer += 4;
		memcpy(buffer, &xoffset, 4);					buffer += 4;
		memcpy(buffer, &yoffset, 4);					buffer += 4;
		memcpy(buffer, &x, 4);							buffer += 4;
		memcpy(buffer, &y, 4);							buffer += 4;
		memcpy(buffer, &width, 4);						buffer += 4;
		memcpy(buffer, &height, 4);						buffer += 4;

		if (subMip)
		{
			memcpy(buffer, subMip->getPixels(), size);
			if (subMip->isRawRgba() || subMip->isRawRgb())
				ImageHelper::swapRB(buffer, width * height, subMip->isRawRgba());
			buffer += size;
		}
	
		if ( m_messenger.send(m_msg) == SOCKET_ERROR ) m_state = IDLE;
		m_msg.clearData();
	}
	SAFE_DEL(subMip);
}

void Server::on_glCreateProgram(GLuint result)
{
	LockScope ls(m_mutex);

	LOGD("[%s] program id = %d", __FUNCTION__, result);

	u8 error = 0;

	if (result > 0)
	{
		Program* prog = getProgram(result);
		if (prog)
		{
			LOGW("Warning: [%s] id=%d has aleady exsited, now overwrite it", __FUNCTION__, result);
		}
		else
		{
			prog = getFreeProgram();
		}
		if (prog)
		{
			prog->clearData();
			prog->setId(result);
		}
		else
		{
			error = 1;
			LOGE("error [%s] Not found a free program", __FUNCTION__);
		}
	}
	else
	{
		LOGE("error [%s] result = %d", __FUNCTION__, result);
		error = 1;
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glCreateProgram);

		m_msg.m_length = 1 + 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);	buffer += 1;
		memcpy(buffer, &result, 4);	buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glCreateShader(GLenum type, GLuint result)
{
	LockScope ls(m_mutex);

	u8 error = 0;
	if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER)
	{
		LOGE("error [%s] type = 0x%x", __FUNCTION__, type);
		error = 1;
		goto my_end;
	}

	if (result > 0)
	{
		Shader* shader = getShader(result);
		if (shader)
		{
			LOGW("Warning: [%s] id=%d has already existed, now overwrite it", __FUNCTION__, result);
		}
		else
		{
			shader = getFreeShader();
		}

		if (shader)
		{
			shader->clearData();
			shader->setId(result);
			shader->setType(type);
		}
		else
		{
			error = 1;
			LOGE("error [%s] Not found a free shader", __FUNCTION__);
		}
	}
	else
	{
		error = 1;
		LOGE("error [%s] result = %d", __FUNCTION__, result);
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glCreateShader);

		m_msg.m_length = 1 + 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);					buffer += 1;
		memcpy(buffer, &type, 4);					buffer += 4;
		memcpy(buffer, &result, 4);					buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glCullFace(GLenum mode)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glCullFace);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &mode, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	LockScope ls(m_mutex);
	for (int i = 0; i < n; i++)
	{
		Vbo* vbo = getVbo(buffers[i]);
		if (vbo)
		{
			vbo->clearData();
			vbo->setId(0);
		}
		else
		{
			LOGE("error [%s] Not found the vbo id: %d", __FUNCTION__, buffers[i]);
		}
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDeleteBuffers);

		m_msg.m_length = 4; // n

		if (n > 0)
		{
			m_msg.m_length += n * 4; // buffers
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &n, 4); buffer += 4;

		if (n > 0)
		{
			memcpy(buffer, buffers, n * 4);
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDeleteFramebuffers);

		m_msg.m_length = 4; // n
		const int len = n * 4;
		if (n > 0)
		{
			m_msg.m_length += len;
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &n, 4); buffer += 4;
		if (n > 0)
		{
			memcpy(buffer, framebuffers, len); buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDeleteProgram(GLuint program)
{
	LockScope ls(m_mutex);

	LOGD("[%s] program id = %d", __FUNCTION__, program);

	u8 error = 0;
	Program* prog = getProgram(program);

	if (prog)
	{
		prog->clearData();
		prog->setId(0);
	}
	else
	{
		error = 1;
		LOGE("error [%s] Not found the program id: %d", __FUNCTION__, program);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDeleteProgram);

		m_msg.m_length = 1 + 4;
		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &program, 4);			buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDeleteRenderbuffers);

		m_msg.m_length = 4; // n
		const int len = n * 4;
		if (n > 0)
		{
			m_msg.m_length += len;
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &n, 4); buffer += 4;
		if (n > 0)
		{
			memcpy(buffer, renderbuffers, len); buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDeleteShader(GLuint shader)
{
	LockScope ls(m_mutex);

	u8 error = 0;

	Shader* pshader = getShader(shader);

	if (pshader)
	{
		pshader->clearData();
		pshader->setId(0);
	}
	else
	{
		error = 1;
		LOGE("error [%s] Not found the shader id: %d", __FUNCTION__, shader);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDeleteShader);

		m_msg.m_length = 1 + 4;
		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &shader, 4);				buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDeleteTextures(GLsizei n, const GLuint* textures)
{
	LockScope ls(m_mutex);

	for (int i = 0; i < n; i++)
	{
		Texture* tex = getTexture(textures[i]);
		if (tex)
		{
			tex->clearData();
			tex->setId(0);
		}
		else
		{
			LOGE("error [%s] Not found the texture id: %d", __FUNCTION__, textures[i]);
		}
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDeleteTextures);

		m_msg.m_length = 4; // n

		if (n > 0)
		{
			m_msg.m_length += 4 * n; // textures
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &n, 4); buffer += 4;

		if (n > 0)
		{
			memcpy(buffer, textures, n * 4);
			buffer += n * 4;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDepthFunc(GLenum func)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDepthFunc);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &func, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDepthMask(GLboolean flag)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDepthMask);

		m_msg.m_length = 1;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &flag, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDepthRangef(GLclampf zNear, GLclampf zFar)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDepthRangef);

		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &zNear, 4);
		memcpy(m_msg.m_pData + 4, &zFar, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDetachShader(GLuint program, GLuint shader)
{
	LockScope ls(m_mutex);
	LOGD("[%s] program = %d, shader = %d", __FUNCTION__, program, shader);

	u8 error = 0;

	Program* prog = getProgram(program);
	if (prog)
	{
		Shader* pshader = getShader(shader);
		if (pshader)
		{
			if (!prog->detach(shader))
			{
				error = 1;
				LOGE("error [%s] can not detach shader=%d, program=%d", __FUNCTION__, shader, program);
			}
		}
		else
		{
			error = 1;
			LOGE("error [%s] not found the shader id = %d", __FUNCTION__, shader);
		}
	}
	else
	{
		error = 1;
		LOGE("error [%s] not found the program id = %d", __FUNCTION__, program);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDetachShader);

		m_msg.m_length = 1 + 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);			buffer += 1;

		memcpy(buffer, &program, 4);		buffer += 4;
		memcpy(buffer, &shader, 4);			buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDisable(GLenum cap)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDisable);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &cap, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDisableVertexAttribArray(GLuint index)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (index >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] index = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, index, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	m_vertexAttributes[index].setEnableVertexAttribArray(false);

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glDisableVertexAttribArray);

		m_msg.m_length = 1 + 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &error, 1);
		memcpy(m_msg.m_pData + 1, &index, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	LockScope ls(m_mutex);
	char* rgbaScreenshot = NULL;
	int width, height;
	if (m_state == CAPTURING)
	{	
		int widthScaled, heightScaled, imageLen;
		rgbaScreenshot = takeRgbaScreenshot(width, height);
		char* bgrScreenshot = makeBgrScreenshot(rgbaScreenshot, width, height, widthScaled, heightScaled, imageLen);

		makeGLCommandMsg(KMT_glDrawArrays);

		Program* prog = getProgram(m_glHelper.get_CURRENT_PROGRAM());

		m_msg.m_length = 4 + // fbo
			4 * 3 + // mod, first, count
			4 * 2 + // zNear and zFar
			4 * 2 + 4 * 2 + // width, height, widthScaled, heightScaled
			4 + imageLen +
			calculateVertexAttribDataLength(prog, count);
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		u32 fbo = m_glHelper.get_FRAMEBUFFER_BINDING();
		memcpy(buffer, &fbo, 4);			buffer += 4;

		memcpy(buffer, &mode, 4);			buffer += 4;
		memcpy(buffer, &first, 4);			buffer += 4;
		memcpy(buffer, &count, 4);			buffer += 4;

		float n, f;
		m_glHelper.get_DEPTH_RANGE(n, f);
		memcpy(buffer, &n, 4); buffer += 4;
		memcpy(buffer, &f, 4); buffer += 4;

		memcpy(buffer, &width, 4);		buffer += 4;
		memcpy(buffer, &height, 4);		buffer += 4;

		memcpy(buffer, &widthScaled, 4);		buffer += 4;
		memcpy(buffer, &heightScaled, 4);		buffer += 4;

		memcpy(buffer, &imageLen, 4);			buffer += 4;
		if (bgrScreenshot && imageLen > 0)
		{
			memcpy(buffer, bgrScreenshot, imageLen);	buffer += imageLen;
		}
		
		makeVertexAttribData(buffer, prog, false, 0, 0, NULL, first, count);
		
		if (m_messenger.send(m_msg) == SOCKET_ERROR)
		{
			m_state = IDLE;
		}
		m_msg.clearData();

		SAFE_DEL(bgrScreenshot);
	}
#if CAPTURE_RENDER_TO_TEXTURE
	copyCurrentFboToTexture(&rgbaScreenshot, width, height);
#endif
	SAFE_DEL(rgbaScreenshot);
}

void Server::on_glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
	LockScope ls(m_mutex);
	char* rgbaScreenshot = NULL;
	int width, height;
	if (m_state == CAPTURING)
	{
		const GLvoid* backup_indices = indices;

		u32 vboId = m_glHelper.get_ELEMENT_ARRAY_BUFFER_BINDING();
		if (vboId > 0)
		{
			int offset = castPtr(indices);
			Vbo* vbo = getVbo(vboId);
			indices = (const GLvoid*)(vbo->getData() + offset);
		}

		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		Program* prog = getProgram(currentUsingProgram);
		
		int widthScaled, heightScaled, imageLen;
		rgbaScreenshot = takeRgbaScreenshot(width, height);
		char* bgrScreenshot = makeBgrScreenshot(rgbaScreenshot, width, height, widthScaled, heightScaled, imageLen);
		
		makeGLCommandMsg(KMT_glDrawElements);

		m_msg.m_length = 4 + // fbo
			4 * 4 + // mode, count, type, indices pointer address
			4 * 2 + // zNear and zFar
			4 * 2 + 4 * 2 + // width, height, widthScaled, heightScaled
			4 + imageLen +
			calculateVertexAttribDataLength(prog, count);

		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		u32 fbo = m_glHelper.get_FRAMEBUFFER_BINDING();
		memcpy(buffer, &fbo, 4);		buffer += 4;

		memcpy(buffer, &mode, 4);		buffer += 4;
		memcpy(buffer, &count, 4);		buffer += 4;
		memcpy(buffer, &type, 4);		buffer += 4;
		memcpy(buffer, &backup_indices, 4);	buffer += 4;

		float n, f;
		m_glHelper.get_DEPTH_RANGE(n, f);
		memcpy(buffer, &n, 4); buffer += 4;
		memcpy(buffer, &f, 4); buffer += 4;

		memcpy(buffer, &width, 4);		buffer += 4;
		memcpy(buffer, &height, 4);		buffer += 4;

		memcpy(buffer, &widthScaled, 4);		buffer += 4;
		memcpy(buffer, &heightScaled, 4);		buffer += 4;

		memcpy(buffer, &imageLen, 4);			buffer += 4;
		if (bgrScreenshot && imageLen > 0)
		{
			memcpy(buffer, bgrScreenshot, imageLen);	buffer += imageLen;
		}

		makeVertexAttribData(buffer, prog, true, count, type, indices, 0, 0);

		if (m_messenger.send(m_msg) == SOCKET_ERROR)
		{
			m_state = IDLE;
		}
		m_msg.clearData();

		SAFE_DEL(bgrScreenshot);
	}
#if CAPTURE_RENDER_TO_TEXTURE
	copyCurrentFboToTexture(&rgbaScreenshot, width, height);
#endif
	SAFE_DEL(rgbaScreenshot);
}

void Server::on_glEnable(GLenum cap)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glEnable);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &cap, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glEnableVertexAttribArray(GLuint index)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (index >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] index = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, index, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	m_vertexAttributes[index].setEnableVertexAttribArray(true);

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glEnableVertexAttribArray);

		m_msg.m_length = 1 + 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &error, 1);
		memcpy(m_msg.m_pData + 1, &index, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glFinish(void)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glFinish);
		m_msg.m_length = 0;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glFlush(void)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glFlush);
		m_msg.m_length = 0;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glFramebufferRenderbuffer);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &attachment, 4);
		memcpy(m_msg.m_pData + 8, &renderbuffertarget, 4);
		memcpy(m_msg.m_pData + 12, &renderbuffer, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glFramebufferTexture2D);

		m_msg.m_length = 4 * 5;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &attachment, 4);
		memcpy(m_msg.m_pData + 8, &textarget, 4);
		memcpy(m_msg.m_pData + 12, &texture, 4);
		memcpy(m_msg.m_pData + 16, &level, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glFrontFace(GLenum mode)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glFrontFace);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &mode, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGenBuffers(GLsizei n, GLuint* buffers)
{
	LockScope ls(m_mutex);

	for (int k = 0; k < n; k++)
	{
		u32 newId = buffers[k];
		Vbo* vbo = getVbo(newId);
		if (vbo)
		{
			LOGW("Warning: [%s] id=%d has already existed, now overwrite it", __FUNCTION__, newId);
			vbo->clearData();
		}
		else
		{
			vbo = getFreeVbo();
			if (vbo)
			{
				vbo->setId(newId);
			}
			else
			{
				LOGE("error [%s] Not found a free vbo", __FUNCTION__);
			}
		}
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGenBuffers);

		m_msg.m_length = 4; // n
		if (n > 0)
		{
			m_msg.m_length += n * 4; // buffers
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &n, 4);			buffer += 4;
		if (n > 0)
		{
			memcpy(buffer, buffers, n * 4);
			buffer += n * 4;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGenerateMipmap(GLenum target)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGenerateMipmap);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGenFramebuffers);

		m_msg.m_length = 4; // n
		const int len = n * 4;
		if (n > 0)
		{
			m_msg.m_length += len;
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &n, 4); buffer += 4;

		if (n > 0)
		{
			memcpy(buffer, framebuffers, len); buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGenRenderbuffers);

		m_msg.m_length = 4; // n
		const int len = n * 4;
		if (n > 0)
		{
			m_msg.m_length += len;
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &n, 4); buffer += 4;

		if (n > 0)
		{
			memcpy(buffer, renderbuffers, len); buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGenTextures(GLsizei n, GLuint* textures)
{
	LockScope ls(m_mutex);

	for (int k = 0; k < n; k++)
	{
		u32 newId = textures[k];
		Texture* tex = getTexture(newId);
		if (tex)
		{
			LOGW("Warning: [%s] id=%d has already existed, now overwrite it", __FUNCTION__, newId);
			tex->clearData();
		}
		else
		{
			tex = getFreeTexture();
			if (!tex)
			{
				LOGE("error [%s] Not found a free texture", __FUNCTION__);
			}
			else
				tex->setId(newId);
		}
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGenTextures);

		m_msg.m_length = 4; // n
		if (n > 0)
		{
			m_msg.m_length += n * 4; // textures
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &n, 4); buffer += 4;

		if (n > 0)
		{
			memcpy(buffer, textures, 4 * n);
			buffer += 4 * n;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize,
	GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetActiveAttrib);

		m_msg.m_length = 4/*program*/ + 4/*index*/ + 4/*bufsize*/ + 4/*length*/ +
			4/*size*/ + 4/*type*/ + 4/*name*/;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &program, 4);		buffer += 4;
		memcpy(buffer, &index, 4);			buffer += 4;
		memcpy(buffer, &bufsize, 4);		buffer += 4;
		memcpy(buffer, &length, 4);			buffer += 4;
		memcpy(buffer, &size, 4);			buffer += 4;
		memcpy(buffer, &type, 4);			buffer += 4;
		memcpy(buffer, &name, 4);			buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size,
	GLenum* type, GLchar* name)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetActiveUniform);

		m_msg.m_length = 4/*program*/ + 4/*index*/ + 4/*bufsize*/ + 4/*length*/ +
			4/*size*/ + 4/*type*/ + 4/*name*/;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &program, 4);		buffer += 4;
		memcpy(buffer, &index, 4);			buffer += 4;
		memcpy(buffer, &bufsize, 4);		buffer += 4;
		memcpy(buffer, &length, 4);			buffer += 4;
		memcpy(buffer, &size, 4);			buffer += 4;
		memcpy(buffer, &type, 4);			buffer += 4;
		memcpy(buffer, &name, 4);			buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetAttachedShaders);
		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &program, 4);
		memcpy(m_msg.m_pData + 4, &maxcount, 4);
		memcpy(m_msg.m_pData + 8, &count, 4);
		memcpy(m_msg.m_pData + 12, &shaders, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetAttribLocation(GLuint program, const GLchar* name, GLint result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetAttribLocation);
		const int strLen = name ? STRLEN(name) : 0;
		m_msg.m_length = 4 + strLen + 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &program, 4);			buffer += 4;
		if (strLen > 0)
		{
			memcpy(buffer, name, strLen);		buffer += strLen;
		}
		memcpy(buffer, &result, 4);				buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetBooleanv(GLenum pname, GLboolean* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetBooleanv);
		m_msg.m_length = 4 + 1;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &pname, 4);
		memcpy(m_msg.m_pData + 4, params, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetBufferParameteriv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetError(GLenum result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetError);
		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &result, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetFloatv(GLenum pname, GLfloat* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetFloatv);
		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &pname, 4);
		memcpy(m_msg.m_pData + 4, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetFramebufferAttachmentParameteriv);
		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &attachment, 4);
		memcpy(m_msg.m_pData + 8, &pname, 4);
		memcpy(m_msg.m_pData + 12, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetIntegerv(GLenum pname, GLint* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetIntegerv);
		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &pname, 4);
		memcpy(m_msg.m_pData + 4, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetProgramiv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &program, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetProgramInfoLog);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &program, 4);	buffer += 4;
		memcpy(buffer, &bufsize, 4);	buffer += 4;
		memcpy(buffer, &length, 4);		buffer += 4;
		memcpy(buffer, &infolog, 4);	buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetRenderbufferParameteriv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetShaderiv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &shader, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetShaderInfoLog);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &shader, 4);		buffer += 4;
		memcpy(buffer, &bufsize, 4);	buffer += 4;
		memcpy(buffer, &length, 4);		buffer += 4;
		memcpy(buffer, &infolog, 4);	buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetShaderPrecisionFormat);
		m_msg.m_length = 4 + 4 + 4 * 2 + 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &shadertype, 4);
		memcpy(m_msg.m_pData + 4, &precisiontype, 4);
		memcpy(m_msg.m_pData + 8, range, 4 * 2);
		memcpy(m_msg.m_pData + 16, precision, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetShaderSource);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &shader, 4);		buffer += 4;
		memcpy(buffer, &bufsize, 4);	buffer += 4;
		memcpy(buffer, &length, 4);		buffer += 4;
		memcpy(buffer, &source, 4);		buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetString(GLenum name, const GLubyte* result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetString);
		const char* sz = (const char*)result;
		const int strLen = sz ? STRLEN(sz) : 0;
		m_msg.m_length = 4 + strLen;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &name, 4);
		if (strLen > 0)
		{
			memcpy(m_msg.m_pData + 4, sz, strLen);
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetTexParameterfv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetTexParameteriv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetUniformfv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &program, 4);
		memcpy(m_msg.m_pData + 4, &location, 4);
		memcpy(m_msg.m_pData + 8, &params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetUniformiv(GLuint program, GLint location, GLint* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetUniformiv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &program, 4);
		memcpy(m_msg.m_pData + 4, &location, 4);
		memcpy(m_msg.m_pData + 8, &params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetUniformLocation(GLuint program, const GLchar* name, GLint result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetUniformLocation);
		const int strLen = name ? STRLEN(name) : 0;
		m_msg.m_length = 4 + 4 + strLen;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &program, 4);			buffer += 4;
		memcpy(buffer, &result, 4);				buffer += 4;
		if (strLen > 0)
		{
			memcpy(buffer, name, strLen);		buffer += strLen;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetVertexAttribfv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &index, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, &params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetVertexAttribiv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &index, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, &params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glGetVertexAttribPointerv);
		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &index, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, *pointer, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glHint(GLenum target, GLenum mode)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glHint);
		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &mode, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glIsBuffer(GLuint buffer, GLboolean result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glIsBuffer);
		m_msg.m_length = 4 + 1;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &buffer, 4);
		memcpy(m_msg.m_pData + 4, &result, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glIsEnabled(GLenum cap, GLboolean result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glIsEnabled);
		m_msg.m_length = 4 + 1;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &cap, 4);
		memcpy(m_msg.m_pData + 4, &result, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glIsFramebuffer(GLuint framebuffer, GLboolean result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glIsFramebuffer);
		m_msg.m_length = 4 + 1;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &framebuffer, 4);
		memcpy(m_msg.m_pData + 4, &result, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glIsProgram(GLuint program, GLboolean result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glIsProgram);
		m_msg.m_length = 4 + 1;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &program, 4);
		memcpy(m_msg.m_pData + 4, &result, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glIsRenderbuffer(GLuint renderbuffer, GLboolean result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glIsRenderbuffer);
		m_msg.m_length = 4 + 1;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &renderbuffer, 4);
		memcpy(m_msg.m_pData + 4, &result, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glIsShader(GLuint shader, GLboolean result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glIsShader);
		m_msg.m_length = 4 + 1;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &shader, 4);
		memcpy(m_msg.m_pData + 4, &result, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glIsTexture(GLuint texture, GLboolean result)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glIsTexture);
		m_msg.m_length = 4 + 1;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &texture, 4);
		memcpy(m_msg.m_pData + 4, &result, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glLineWidth(GLfloat width)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glLineWidth);
		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &width, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glLinkProgram(GLuint program)
{
	LockScope ls(m_mutex);

	u8 error = 0;

	Program* prog = getProgram(program);
	if (prog)
	{
		prog->link(m_glHelper);
	}
	else
	{
		error = 1;
		LOGE("error [%s] Not found the program id = %d", __FUNCTION__, program);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glLinkProgram);

		m_msg.m_length = 1 + 4;

		if (error)
		{
			m_msg.m_pData = new char[m_msg.m_length];
			char* buffer = m_msg.m_pData;

			memcpy(buffer, &error, 1);		buffer += 1;
			memcpy(buffer, &program, 4);	buffer += 4;
		}
		else
		{
			Message* msgProg = prog->toMessage();
			const int len = msgProg->m_length;

			m_msg.m_length += len;
			m_msg.m_pData = new char[m_msg.m_length];

			char* buffer = m_msg.m_pData;

			memcpy(buffer, &error, 1);		buffer += 1;
			memcpy(buffer, &program, 4);	buffer += 4;

			if (len > 0)
			{
				memcpy(buffer, msgProg->m_pData, len);
				buffer += len;
			}

			delete msgProg;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}

}

void Server::on_glPixelStorei(GLenum pname, GLint param)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glPixelStorei);
		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &pname, 4);
		memcpy(m_msg.m_pData + 4, &param, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glPolygonOffset(GLfloat factor, GLfloat units)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glPolygonOffset);
		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &factor, 4);
		memcpy(m_msg.m_pData + 4, &units, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glReadPixels);
		m_msg.m_length = 4 * 7;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &x, 4);
		buffer += 4;

		memcpy(buffer, &y, 4);
		buffer += 4;

		memcpy(buffer, &width, 4);
		buffer += 4;

		memcpy(buffer, &height, 4);
		buffer += 4;

		memcpy(buffer, &format, 4);
		buffer += 4;

		memcpy(buffer, &type, 4);
		buffer += 4;

		memcpy(buffer, &pixels, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glReleaseShaderCompiler(void)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glReleaseShaderCompiler);
		m_msg.m_length = 0;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glRenderbufferStorage);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &internalformat, 4);
		memcpy(m_msg.m_pData + 8, &width, 4);
		memcpy(m_msg.m_pData + 12, &height, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glSampleCoverage(GLclampf value, GLboolean invert)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glSampleCoverage);

		m_msg.m_length = 4 + 1;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &value, 4);
		memcpy(m_msg.m_pData + 4, &invert, 1);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glScissor);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &x, 4);
		memcpy(m_msg.m_pData + 4, &y, 4);
		memcpy(m_msg.m_pData + 8, &width, 4);
		memcpy(m_msg.m_pData + 12, &height, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glShaderBinary);

		m_msg.m_length = 4 * 5;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &n, 4);				buffer += 4;
		memcpy(buffer, &shaders, 4);		buffer += 4;
		memcpy(buffer, &binaryformat, 4);	buffer += 4;
		memcpy(buffer, &binary, 4);			buffer += 4;
		memcpy(buffer, &length, 4);			buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length)
{
	LockScope ls(m_mutex);
	
	u8 error = 0;
	Shader* pshader = NULL;

	if (count < 0)
	{
		LOGE("error [%s] count = %d", __FUNCTION__, count);
		error = 1;
		goto my_end;
	}
	
	pshader = getShader(shader);
	if (pshader)
	{
		int sourceLen = m_glHelper.calculateShaderSourceSize(count, string, length);	
		char* buffer = new char[sourceLen + 1];
		m_glHelper.copyShaderSource(buffer, count, string, length);
		buffer[sourceLen] = 0;
		pshader->setSource(buffer);
		delete[] buffer;
	}
	else
	{
		LOGE("error [%s] not found the shader id = %d", __FUNCTION__, shader);
		error = 1;
		goto my_end;
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glShaderSource);

		const int sourceLen = m_glHelper.calculateShaderSourceSize(count, string, length);

		m_msg.m_length = 1 + 4 + sourceLen;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;
		memcpy(buffer, &error, 1);			buffer += 1;
		memcpy(buffer, &shader, 4);			buffer += 4;

		if (sourceLen > 0)
		{
			m_glHelper.copyShaderSource(buffer, count, string, length);
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glStencilFunc);

		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &func, 4);
		memcpy(m_msg.m_pData + 4, &ref, 4);
		memcpy(m_msg.m_pData + 8, &mask, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glStencilFuncSeparate);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &face, 4);
		memcpy(m_msg.m_pData + 4, &func, 4);
		memcpy(m_msg.m_pData + 8, &ref, 4);
		memcpy(m_msg.m_pData + 12, &mask, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glStencilMask(GLuint mask)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glStencilMask);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &mask, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glStencilMaskSeparate(GLenum face, GLuint mask)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glStencilMaskSeparate);

		m_msg.m_length = 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &face, 4);
		memcpy(m_msg.m_pData + 4, &mask, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glStencilOp);

		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &fail, 4);
		memcpy(m_msg.m_pData + 4, &zfail, 4);
		memcpy(m_msg.m_pData + 8, &zpass, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glStencilOpSeparate);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &face, 4);
		memcpy(m_msg.m_pData + 4, &fail, 4);
		memcpy(m_msg.m_pData + 8, &zfail, 4);
		memcpy(m_msg.m_pData + 12, &zpass, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
	GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
	LockScope ls(m_mutex);

	u32 id = m_glHelper.get_TEXTURE_BINDING(target);

	LOGD("[%s] id=%d, target=0x%x, level=%d, internalformat=0x%x, width=%d, height=%d, border=%d, type=0x%x, pixels=0x%p",
		__FUNCTION__, id, target, level, internalformat, width, height, border, type, pixels);

	Texture* tex = getTexture(id);
	Mipmap* mip = NULL;
	if (!tex)
	{
		LOGE("[%s] Not found the texture id %d", __FUNCTION__, id);
	}
	else
	{
		mip = tex->on_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels, m_glHelper.get_UNPACK_ALIGNMENT());
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glTexImage2D);
		m_msg.m_length = 1/*error*/ + 4/*id*/ + 4/*target*/ + 4/*level*/ + 4/*internalformat*/ + 4/*width*/ + 4/*height*/ +
			4/*border*/ + 4/*format*/ + 4/*type*/ + 4/*pointer address*/;
		int size;
		if (mip)
		{
			size = mip->getImageSize();
			m_msg.m_length += size;
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;
		u8 error = mip ? 0 : 1;
		memcpy(buffer, &error, 1);						buffer += 1;
		memcpy(buffer, &id, 4);							buffer += 4;
		memcpy(buffer, &target, 4);						buffer += 4;
		memcpy(buffer, &level, 4);						buffer += 4;
		memcpy(buffer, &internalformat, 4);				buffer += 4;
		memcpy(buffer, &width, 4);						buffer += 4;
		memcpy(buffer, &height, 4);						buffer += 4;
		memcpy(buffer, &border, 4);						buffer += 4;
		memcpy(buffer, &format, 4);						buffer += 4;
		memcpy(buffer, &type, 4);						buffer += 4;
		memcpy(buffer, &pixels, 4);						buffer += 4;
		if (mip)
		{
			memcpy(buffer, mip->getPixels(), size);
			if (mip->isRawRgba() || mip->isRawRgb())
				ImageHelper::swapRB(buffer, width * height, mip->isRawRgba());
			buffer += size;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glTexParameterf);

		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, &param, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glTexParameterfv);

		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glTexParameteri);

		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, &param, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glTexParameteriv);

		m_msg.m_length = 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &target, 4);
		memcpy(m_msg.m_pData + 4, &pname, 4);
		memcpy(m_msg.m_pData + 8, params, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
	GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
{
	LockScope ls(m_mutex);

	u32 id = m_glHelper.get_TEXTURE_BINDING(target);

	LOGD("[%s] id=%d, target=0x%x, level=%d, xoffset=%d, yoffset=%d, width=%d, height=%d, format=0x%x, type=0x%x, pixels=%p",
		__FUNCTION__, id, target, level, xoffset, yoffset, width, height, format, type, pixels);

	Texture* tex = getTexture(id);
	Mipmap* subMip = NULL;
	if (!tex)
	{
		LOGE("error [%s] Not found the texture id = %d", __FUNCTION__, id);
	}
	else
	{
		subMip = tex->on_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type,
			pixels, m_glHelper.get_UNPACK_ALIGNMENT());
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glTexSubImage2D);
		m_msg.m_length = 1/*error*/ + 4/*id*/ + 4/*target*/ + 4/*level*/ + 4/*xoffset*/ + 4/*yoffset*/ +
			4/*width*/ + 4/*height*/ + 4/*format*/ + 4/*type*/ + 4/*address*/;
		int size;
		if (subMip)
		{
			size = subMip->getImageSize();
			m_msg.m_length += size;
		}

		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;
		u8 error = subMip ? 0 : 1;
		memcpy(buffer, &error, 1);					buffer += 1;
		memcpy(buffer, &id, 4);						buffer += 4;
		memcpy(buffer, &target, 4);					buffer += 4;
		memcpy(buffer, &level, 4);					buffer += 4;
		memcpy(buffer, &xoffset, 4);				buffer += 4;
		memcpy(buffer, &yoffset, 4);				buffer += 4;
		memcpy(buffer, &width, 4);					buffer += 4;
		memcpy(buffer, &height, 4);					buffer += 4;
		memcpy(buffer, &format, 4);					buffer += 4;
		memcpy(buffer, &type, 4);					buffer += 4;
		memcpy(buffer, &pixels, 4);					buffer += 4;

		if (subMip)
		{
			memcpy(buffer, subMip->getPixels(), size);
			if (subMip->isRawRgba() || subMip->isRawRgb())
				ImageHelper::swapRB(buffer, width * height, subMip->isRawRgba());
			buffer += size;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
	SAFE_DEL(subMip);
}

//==============================================================================
// glUniform***

Program* Server::validate_glUniform1234fiv(const char* funcName, int comps, bool isFloat, bool isVector,
	GLint location, GLsizei count/* = 0*/)
{
	if (isVector && count < 0)
	{
		return NULL;
	}

	u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
	Program* prog = getProgram(currentUsingProgram);
	if (!prog)
	{
		LOGE("error [%s] not found current using program id = %d", funcName, currentUsingProgram);
		return NULL;
	}

	if (location == -1) return prog;

	const KPUniform* pUniform = prog->getUniformByLocation(location);
	if (!pUniform)
	{
		LOGE("error [%s] invalid uniform location = %d", funcName, location);
		return NULL;
	}

	if (pUniform->isTypeMatrix())
	{
		LOGE("error [%s] the uniform is a matrix", funcName);
		return NULL;
	}

	if (comps != pUniform->getTypeComponents())
	{
		LOGE("error [%s] wrong components", funcName);
		return NULL;
	}

	if (isFloat != pUniform->isTypeFloat())
	{
		LOGE("error [%s] wrong type (float - int)", funcName);
		return NULL;
	}

	if (isVector && count > 1 && !pUniform->isArray())
	{
		LOGE("error [%s] count = %d but the uniform is not an array variable", funcName, count);
		return NULL;
	}

	return prog;
}

Program* Server::validate_glUniformMatrix(const char* funcName, int size, GLint location, GLsizei count, GLboolean transpose)
{
	if (count < 0) return NULL;
	if (transpose != GL_FALSE) return NULL;

	u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
	Program* prog = getProgram(currentUsingProgram);
	if (!prog)
	{
		LOGE("error [%s] not found current using program id = %d", funcName, currentUsingProgram);
		return NULL;
	}

	if (location == -1) return prog;

	const KPUniform* pUniform = prog->getUniformByLocation(location);
	if (!pUniform)
	{
		LOGE("error [%s] invalid uniform location = %d", funcName, location);
		return NULL;
	}

	if (!pUniform->isTypeMatrix())
	{
		LOGE("error [%s] the uniform is not a matrix", funcName);
		return NULL;
	}

	if (size != pUniform->getTypeComponents())
	{
		LOGE("error [%s] the size of matrix is not matched", funcName);
		return NULL;
	}

	return prog;
}

void Server::on_glUniform1f(GLint location, GLfloat x)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform1f", 1, true/*isFloat*/, false/*isVector*/, location);
	u8 error = prog ? 0 : 1;
	if (!error)
	{
		prog->on_glUniform1f(location, x);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform1f);
		m_msg.m_length = 1 + 4 * 2 + 4 * 1;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &x, 4);								buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform1fv(GLint location, GLsizei count, const GLfloat* v)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform1fv", 1, true/*isFloat*/, true/*isVector*/, location, count);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniform1fv(location, count, v);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform1fv);
		m_msg.m_length = 1 + 4 + 4 + 4;
		if (count > 0)
		{
			m_msg.m_length += count * 4;
		}
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &count, 4);							buffer += 4;
		if (count > 0)
		{
			memcpy(buffer, v, count * 4);					buffer += count * 4;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform1i(GLint location, GLint x)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform1i", 1, false/*isFloat*/, false/*isVector*/, location);
	u8 error = prog ? 0 : 1;
	if (!error)
	{
		prog->on_glUniform1i(location, x);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform1i);
		m_msg.m_length = 1 + 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);						buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);		buffer += 4;
		memcpy(buffer, &location, 4);					buffer += 4;
		memcpy(buffer, &x, 4);							buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform1iv(GLint location, GLsizei count, const GLint* v)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform1iv", 1, false/*isFloat*/, true/*isVector*/, location, count);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniform1iv(location, count, v);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform1iv);
		m_msg.m_length = 1 + 4 + 4 + 4;
		if (count > 0)
		{
			m_msg.m_length += count * 4;
		}
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &count, 4);							buffer += 4;
		if (count > 0)
		{
			memcpy(buffer, v, count * 4);					buffer += count * 4;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform2f(GLint location, GLfloat x, GLfloat y)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform2f", 2, true/*isFloat*/, false/*isVector*/, location);
	u8 error = prog ? 0 : 1;
	if (!error)
	{
		prog->on_glUniform2f(location, x, y);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform2f);
		m_msg.m_length = 1 + 4 * 2 + 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &x, 4);								buffer += 4;
		memcpy(buffer, &y, 4);								buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform2fv(GLint location, GLsizei count, const GLfloat* v)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform2fv", 2, true/*isFloat*/, true/*isVector*/, location, count);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniform2fv(location, count, v);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform2fv);
		m_msg.m_length = 1 + 4 + 4 + 4;
		const int len = count * 4 * 2;
		if (count > 0)
		{
			m_msg.m_length += len;
		}
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &count, 4);							buffer += 4;
		if (count > 0)
		{
			memcpy(buffer, v, len);							buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform2i(GLint location, GLint x, GLint y)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform2i", 2, false/*isFloat*/, false/*isVector*/, location);
	u8 error = prog ? 0 : 1;
	if (!error)
	{
		prog->on_glUniform2i(location, x, y);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform2i);
		m_msg.m_length = 1 + 4 * 2 + 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);						buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);		buffer += 4;
		memcpy(buffer, &location, 4);					buffer += 4;
		memcpy(buffer, &x, 4);							buffer += 4;
		memcpy(buffer, &y, 4);							buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform2iv(GLint location, GLsizei count, const GLint* v)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform2iv", 2, false/*isFloat*/, true/*isVector*/, location, count);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniform2iv(location, count, v);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform2iv);
		m_msg.m_length = 1 + 4 + 4 + 4;
		const int len = count * 4 * 2;
		if (count > 0)
		{
			m_msg.m_length += len;
		}
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &count, 4);							buffer += 4;
		if (count > 0)
		{
			memcpy(buffer, v, len);							buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform3f", 3, true/*isFloat*/, false/*isVector*/, location);
	u8 error = prog ? 0 : 1;
	if (!error)
	{
		prog->on_glUniform3f(location, x, y, z);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform3f);
		m_msg.m_length = 1 + 4 * 2 + 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &x, 4);								buffer += 4;
		memcpy(buffer, &y, 4);								buffer += 4;
		memcpy(buffer, &z, 4);								buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform3fv(GLint location, GLsizei count, const GLfloat* v)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform3fv", 3, true/*isFloat*/, true/*isVector*/, location, count);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniform3fv(location, count, v);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform3fv);
		m_msg.m_length = 1 + 4 + 4 + 4;
		const int len = count * 4 * 3;
		if (count > 0)
		{
			m_msg.m_length += len;
		}
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &count, 4);							buffer += 4;
		if (count > 0)
		{
			memcpy(buffer, v, len);							buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform3i(GLint location, GLint x, GLint y, GLint z)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform3i", 3, false/*isFloat*/, false/*isVector*/, location);
	u8 error = prog ? 0 : 1;
	if (!error)
	{
		prog->on_glUniform3i(location, x, y, z);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform3i);
		m_msg.m_length = 1 + 4 * 2 + 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);						buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);		buffer += 4;
		memcpy(buffer, &location, 4);					buffer += 4;
		memcpy(buffer, &x, 4);							buffer += 4;
		memcpy(buffer, &y, 4);							buffer += 4;
		memcpy(buffer, &z, 4);							buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform3iv(GLint location, GLsizei count, const GLint* v)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform3iv", 3, false/*isFloat*/, true/*isVector*/, location, count);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniform3iv(location, count, v);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform3iv);
		m_msg.m_length = 1 + 4 + 4 + 4;
		const int len = count * 4 * 3;
		if (count > 0)
		{
			m_msg.m_length += len;
		}
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &count, 4);							buffer += 4;
		if (count > 0)
		{
			memcpy(buffer, v, len);							buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform4f", 4, true/*isFloat*/, false/*isVector*/, location);
	u8 error = prog ? 0 : 1;
	if (!error)
	{
		prog->on_glUniform4f(location, x, y, z, w);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform4f);
		m_msg.m_length = 1 + 4 * 2 + 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &x, 4);								buffer += 4;
		memcpy(buffer, &y, 4);								buffer += 4;
		memcpy(buffer, &z, 4);								buffer += 4;
		memcpy(buffer, &w, 4);								buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform4fv(GLint location, GLsizei count, const GLfloat* v)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform4fv", 4, true/*isFloat*/, true/*isVector*/, location, count);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniform4fv(location, count, v);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform4fv);
		m_msg.m_length = 1 + 4 + 4 + 4;
		const int len = count * 4 * 4;
		if (count > 0)
		{
			m_msg.m_length += len;
		}
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &count, 4);							buffer += 4;
		if (count > 0)
		{
			memcpy(buffer, v, len);							buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform4i", 4, false/*isFloat*/, false/*isVector*/, location);
	u8 error = prog ? 0 : 1;
	if (!error)
	{
		prog->on_glUniform4i(location, x, y, z, w);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform4i);
		m_msg.m_length = 1 + 4 * 2 + 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);						buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);		buffer += 4;
		memcpy(buffer, &location, 4);					buffer += 4;
		memcpy(buffer, &x, 4);							buffer += 4;
		memcpy(buffer, &y, 4);							buffer += 4;
		memcpy(buffer, &z, 4);							buffer += 4;
		memcpy(buffer, &w, 4);							buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniform4iv(GLint location, GLsizei count, const GLint* v)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniform1234fiv("on_glUniform4iv", 4, false/*isFloat*/, true/*isVector*/, location, count);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniform4iv(location, count, v);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniform4iv);
		m_msg.m_length = 1 + 4 + 4 + 4;
		const int len = count * 4 * 4;
		if (count > 0)
		{
			m_msg.m_length += len;
		}
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);							buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);			buffer += 4;
		memcpy(buffer, &location, 4);						buffer += 4;
		memcpy(buffer, &count, 4);							buffer += 4;
		if (count > 0)
		{
			memcpy(buffer, v, len);							buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniformMatrix("on_glUniformMatrix2fv", 2, location, count, transpose);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniformMatrix2fv(location, count, transpose, value);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniformMatrix2fv);

		m_msg.m_length = 1 + 4 + 4 + 4 + 1;
		int len = 0;
		if (count > 0)
		{
			len = count * 2 * 2 * 4;
			m_msg.m_length += len;
		}
		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);						buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);		buffer += 4;
		memcpy(buffer, &location, 4);					buffer += 4;
		memcpy(buffer, &count, 4);						buffer += 4;
		memcpy(buffer, &transpose, 1);					buffer += 1;
		if (count > 0)
		{
			memcpy(buffer, value, len);					buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniformMatrix("on_glUniformMatrix3fv", 3, location, count, transpose);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniformMatrix3fv(location, count, transpose, value);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniformMatrix3fv);

		m_msg.m_length = 1 + 4 + 4 + 4 + 1;
		int len = 0;
		if (count > 0)
		{
			len = count * 3 * 3 * 4;
			m_msg.m_length += len;
		}
		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);						buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);		buffer += 4;
		memcpy(buffer, &location, 4);					buffer += 4;
		memcpy(buffer, &count, 4);						buffer += 4;
		memcpy(buffer, &transpose, 1);					buffer += 1;
		if (count > 0)
		{
			memcpy(buffer, value, len);					buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	LockScope ls(m_mutex);

	Program* prog = validate_glUniformMatrix("on_glUniformMatrix4fv", 4, location, count, transpose);
	u8 error = prog ? 0 : 1;
	if (!error && location != -1 && count > 0)
	{
		prog->on_glUniformMatrix4fv(location, count, transpose, value);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUniformMatrix4fv);

		m_msg.m_length = 1 + 4 + 4 + 4 + 1;
		int len = 0;
		if (count > 0)
		{
			len = count * 4 * 4 * 4;
			m_msg.m_length += len;
		}
		m_msg.m_pData = new char[m_msg.m_length];
		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);						buffer += 1;
		u32 currentUsingProgram = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(buffer, &currentUsingProgram, 4);		buffer += 4;
		memcpy(buffer, &location, 4);					buffer += 4;
		memcpy(buffer, &count, 4);						buffer += 4;
		memcpy(buffer, &transpose, 1);					buffer += 1;
		if (count > 0)
		{
			memcpy(buffer, value, len);					buffer += len;
		}

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

// end of glUniform***
//===============================================================================

void Server::on_glUseProgram(GLuint program)
{
	LockScope ls(m_mutex);

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUseProgram);

		m_msg.m_length = 4 + 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &program, 4);
		u32 actual = m_glHelper.get_CURRENT_PROGRAM();
		memcpy(m_msg.m_pData + 4, &actual, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glValidateProgram(GLuint program)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glValidateProgram);

		m_msg.m_length = 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &program, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}
//===========================================================================================
void Server::on_glVertexAttrib1f(GLuint indx, GLfloat x)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (indx >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] indx = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, indx, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	m_vertexAttributes[indx].on_glVertexAttrib(1, &x);

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glVertexAttrib1f);

		m_msg.m_length = 1 + 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &indx, 4);				buffer += 4;
		memcpy(buffer, &x, 4);					buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glVertexAttrib1fv(GLuint indx, const GLfloat* values)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (indx >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] indx = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, indx, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	m_vertexAttributes[indx].on_glVertexAttrib(1, values);

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glVertexAttrib1fv);

		m_msg.m_length = 1 + 4 * 2;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &indx, 4);				buffer += 4;
		memcpy(buffer, values, 4);				buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (indx >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] indx = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, indx, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	{
		GLfloat tmp[] = { x, y };
		m_vertexAttributes[indx].on_glVertexAttrib(2, tmp);
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glVertexAttrib2f);

		m_msg.m_length = 1 + 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &indx, 4);				buffer += 4;
		memcpy(buffer, &x, 4);					buffer += 4;
		memcpy(buffer, &y, 4);					buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glVertexAttrib2fv(GLuint indx, const GLfloat* values)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (indx >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] indx = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, indx, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	m_vertexAttributes[indx].on_glVertexAttrib(2, values);

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glVertexAttrib2fv);

		m_msg.m_length = 1 + 4 * 3;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &indx, 4);				buffer += 4;
		memcpy(buffer, values, 4);				buffer += 4; values += 4;
		memcpy(buffer, values, 4);				buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (indx >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] indx = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, indx, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	{
		GLfloat tmp[] = { x, y, z };
		m_vertexAttributes[indx].on_glVertexAttrib(3, tmp);
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glVertexAttrib3f);

		m_msg.m_length = 1 + 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &indx, 4);				buffer += 4;
		memcpy(buffer, &x, 4);					buffer += 4;
		memcpy(buffer, &y, 4);					buffer += 4;
		memcpy(buffer, &z, 4);					buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glVertexAttrib3fv(GLuint indx, const GLfloat* values)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (indx >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] indx = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, indx, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	m_vertexAttributes[indx].on_glVertexAttrib(3, values);

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glVertexAttrib3fv);

		m_msg.m_length = 1 + 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &indx, 4);				buffer += 4;
		memcpy(buffer, values, 4);				buffer += 4; values += 4;
		memcpy(buffer, values, 4);				buffer += 4; values += 4;
		memcpy(buffer, values, 4);				buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (indx >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] indx = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, indx, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	{
		GLfloat tmp[] = { x, y, z, w };
		m_vertexAttributes[indx].on_glVertexAttrib(4, tmp);
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glVertexAttrib4f);

		m_msg.m_length = 1 + 4 * 5;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &indx, 4);				buffer += 4;
		memcpy(buffer, &x, 4);					buffer += 4;
		memcpy(buffer, &y, 4);					buffer += 4;
		memcpy(buffer, &z, 4);					buffer += 4;
		memcpy(buffer, &w, 4);					buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glVertexAttrib4fv(GLuint indx, const GLfloat* values)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (indx >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] indx = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, indx, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	m_vertexAttributes[indx].on_glVertexAttrib(4, values);

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glVertexAttrib4fv);

		m_msg.m_length = 1 + 4 * 5;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);				buffer += 1;
		memcpy(buffer, &indx, 4);				buffer += 4;
		memcpy(buffer, values, 4);				buffer += 4; values += 4;
		memcpy(buffer, values, 4);				buffer += 4; values += 4;
		memcpy(buffer, values, 4);				buffer += 4; values += 4;
		memcpy(buffer, values, 4);				buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glVertexAttribPointer(GLuint indx, GLint size, GLenum type,
	GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
	LockScope ls(m_mutex);

	const unsigned int MAX_VERTEX_ATTRIBS = (const unsigned int)m_glHelper.get_MAX_VERTEX_ATTRIBS();
	u8 error = 0;

	if (type != GL_BYTE &&
		type != GL_UNSIGNED_BYTE &&
		type != GL_SHORT &&
		type != GL_UNSIGNED_SHORT &&
		type != GL_FIXED &&
		type != GL_FLOAT)
	{
		LOGE("error [%s] type = 0x%x", __FUNCTION__, type);
		error = 1;
		goto my_end;
	}

	if (indx >= MAX_VERTEX_ATTRIBS)
	{
		LOGE("error [%s] indx = %d, MAX_VERTEX_ATTRIBS = %d", __FUNCTION__, indx, MAX_VERTEX_ATTRIBS);
		error = 1;
		goto my_end;
	}

	if (size < 1 || size > 4)
	{
		LOGE("error [%s] size = %d", __FUNCTION__, size);
		error = 1;
		goto my_end;
	}

	if (stride < 0)
	{
		LOGE("error [%s] stride = %d", __FUNCTION__, stride);
		error = 1;
		goto my_end;
	}

	m_vertexAttributes[indx].on_glVertexAttribPointer(size, type, normalized,
		stride, ptr, m_glHelper.get_ARRAY_BUFFER_BINDING());

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glVertexAttribPointer);

		m_msg.m_length = 1/*error*/ + 4/*indx*/ + 4/*size*/ + 4/*type*/ + 1/*normalized*/ + 4/*stride*/ + 4/*ptr*/;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);		buffer += 1;
		memcpy(buffer, &indx, 4);		buffer += 4;
		memcpy(buffer, &size, 4);		buffer += 4;
		memcpy(buffer, &type, 4);		buffer += 4;
		memcpy(buffer, &normalized, 1);	buffer += 1;
		memcpy(buffer, &stride, 4);		buffer += 4;
		memcpy(buffer, &ptr, 4);		buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	LockScope ls(m_mutex);
	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glViewport);

		m_msg.m_length = 4 * 4;
		m_msg.m_pData = new char[m_msg.m_length];

		memcpy(m_msg.m_pData, &x, 4);
		memcpy(m_msg.m_pData + 4, &y, 4);
		memcpy(m_msg.m_pData + 8, &width, 4);
		memcpy(m_msg.m_pData + 12, &height, 4);

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

// Extensions
void Server::on_glMapBufferOES(GLenum target, GLenum access, void* ptr)
{
	LockScope ls(m_mutex);

	u32 currentBindingVbo;
	Vbo* vbo;
	u8 error = 0;

	if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER)
	{
		LOGE("error [%s] Unknown target = 0x%x", __FUNCTION__, target);
		error = 1;
		goto my_end;
	}

	currentBindingVbo = m_glHelper.get_BUFFER_BINDING(target);

	vbo = getVbo(currentBindingVbo);
	if (vbo)
	{
		vbo->on_glMapBufferOES(access, ptr);
	}
	else
	{
		LOGE("error [%s] Not found the vbo id: %d", __FUNCTION__, currentBindingVbo);
		error = 1;
		goto my_end;
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glMapBufferOES);

		m_msg.m_length = 1/*error*/ + 4/*currentBindingVbo*/ + 4/*target*/ + 4/*access*/ + 4/*ptr*/;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);					buffer += 1;
		memcpy(buffer, &currentBindingVbo, 4);		buffer += 4;
		memcpy(buffer, &target, 4);					buffer += 4;
		memcpy(buffer, &access, 4);					buffer += 4;
		memcpy(buffer, &ptr, 4);					buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glUnmapBufferOES(GLenum target)
{
	LockScope ls(m_mutex);

	u32 currentBindingVbo;
	Vbo* vbo;
	u8 error = 0;

	if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER)
	{
		LOGE("error [%s] Unknown target = 0x%x", __FUNCTION__, target);
		error = 1;
		goto my_end;
	}

	currentBindingVbo = m_glHelper.get_BUFFER_BINDING(target);

	vbo = getVbo(currentBindingVbo);
	if (vbo)
	{
		vbo->on_glUnmapBufferOES();
	}
	else
	{
		LOGE("error [%s] Not found the vbo id: %d", __FUNCTION__, currentBindingVbo);
		error = 1;
		goto my_end;
	}

	my_end:

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glUnmapBufferOES);

		m_msg.m_length = 1/*error*/ + 4/*currentBindingVbo*/ + 4/*target*/;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;

		memcpy(buffer, &error, 1);					buffer += 1;
		memcpy(buffer, &currentBindingVbo, 4);		buffer += 4;
		memcpy(buffer, &target, 4);					buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

void Server::on_glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	LockScope ls(m_mutex);

	u32 id = m_glHelper.get_TEXTURE_BINDING_2D();

	LOGD("[%s] id=%d, target=0x%x, levels=%d, internalformat=0x%x, width=%d, height=%d",
		__FUNCTION__, id, target, levels, internalformat, width, height);

	Texture* tex = getTexture(id);
	u8 error = true;
	if (!tex)
	{
		LOGE("[%s] Not found the texture id = %d", __FUNCTION__, id);
	}
	else
	{
		error = tex->on_glTexStorage2D(target, levels, internalformat, width, height);
	}

	if (m_state == CAPTURING)
	{
		makeGLCommandMsg(KMT_glTexStorage2D);
		m_msg.m_length = 1/*error*/ + 4/*id*/ + 4/*target*/ + 4/*levels*/ + 4/*internalformat*/ + 4/*width*/ + 4/*height*/;
		m_msg.m_pData = new char[m_msg.m_length];

		char* buffer = m_msg.m_pData;
		memcpy(buffer, &error, 1);						buffer += 1;
		memcpy(buffer, &id, 4);							buffer += 4;
		memcpy(buffer, &target, 4);						buffer += 4;
		memcpy(buffer, &levels, 4);						buffer += 4;
		memcpy(buffer, &internalformat, 4);				buffer += 4;
		memcpy(buffer, &width, 4);						buffer += 4;
		memcpy(buffer, &height, 4);						buffer += 4;

		if (m_messenger.send(m_msg) == SOCKET_ERROR) m_state = IDLE;
		m_msg.clearData();
	}
}

//==================================================================================================
//==================================================================================================
//==================================================================================================

int Server::calculateVertexAttribDataLength(Program* prog, int vertexCount)
{
	if (!prog) return 4;

	int attCount = prog->getAttributesCount();
	int dataLength = 4/*attCount*/;

	for (int i = 0; i < attCount; i++)
	{
		const KPAttribute& att = prog->getAttribute(i);

		VertexAttribData& vad = m_vertexAttributes[att.m_location];

		u8 enableVertexAttribArray = vad.getEnableVertexAttribArray() ? 1 : 0;

		dataLength += 1/*enableVertexAttribArray*/;
		if (enableVertexAttribArray)
		{
			dataLength +=
				4/*location*/ +
				4/*dataComponentsNumber*/ +
				1/*normalized*/ +
				4/*vboId*/ +
				4/*dataType*/ +
				m_glHelper.getSize(vad.getDataType()) * vad.getDataComponentsNumber() * vertexCount;
		}
		else
		{
			dataLength +=
				4/*location*/ +
				4/*m_dataNonArray_Components*/ +
				vad.getDataNonArray_Components() * 4;

		}
	}

	return dataLength;
}

void Server::makeVertexAttribData(char* buffer, Program* prog,
	bool isDrawElements,
	GLsizei countElements, GLenum type, const GLvoid* indices,
	GLint first, GLsizei countArrays)
{
	if (!prog)
	{
		int attCount = 0;
		memcpy(buffer, &attCount, 4);
		return;
	}

	int attCount = prog->getAttributesCount();
	memcpy(buffer, &attCount, 4); buffer += 4;

	for (int i = 0; i < attCount; i++)
	{
		const KPAttribute& att = prog->getAttribute(i);
		int location = att.m_location;
		VertexAttribData& vad = m_vertexAttributes[location];

		u8 enableVertexAttribArray = vad.getEnableVertexAttribArray() ? 1 : 0;
		memcpy(buffer, &enableVertexAttribArray, 1);
		buffer += 1;

		if (enableVertexAttribArray)
		{
			int components = vad.getDataComponentsNumber();
			u32 dataType = vad.getDataType();
			int dataStride = vad.getDataStride();
			u8 normalized = vad.getDataNormalized() ? 1 : 0;

			u32 vboId = vad.getVboId();

			memcpy(buffer, &location, 4);		buffer += 4;
			memcpy(buffer, &components, 4);		buffer += 4;
			memcpy(buffer, &normalized, 1);		buffer += 1;

			memcpy(buffer, &vboId, 4);			buffer += 4;
			memcpy(buffer, &dataType, 4);		buffer += 4;

			const int smallStride = m_glHelper.getSize(dataType) * components;
			const int bigStride = dataStride > 0 ? dataStride : smallStride;

			const char* data = NULL;
			if (vboId > 0)
			{
				int offset = castPtr(vad.getDataPointer());
				Vbo* vbo = getVbo(vboId);
				LOGD("offset = 0x%x, vbo = 0x%p, vbo->getData() = 0x%p, vbo->getSize() = %d", offset, vbo, vbo->getData(), vbo->getSize());
				if (vbo && vbo->getData() && offset >= 0 && offset < vbo->getSize())
				{
					data = (const char*)(vbo->getData() + offset);
				}
				else
				{
					LOGW("[%s] The VBO %d has no data", __FUNCTION__, vboId);
				}
			}
			else
			{
				data = (const char*)(vad.getDataPointer());
			}

			if (isDrawElements && data)
			{
				const u8*	pIndices8 = (const u8*)indices;
				const u16*	pIndices16 = (const u16*)indices;
				for (int j = 0; j < countElements; j++)
				{
					int vertexIndex = (int)(type == GL_UNSIGNED_BYTE ? pIndices8[j] : pIndices16[j]);
					memcpy(buffer, data + bigStride * vertexIndex, smallStride);
					buffer += smallStride;
				}
			}
			else if (isDrawElements && !data)
			{
				const int len = countElements * smallStride;
				memset(buffer, 0, len);
				buffer += len;
			}
			else
			{
				for (int j = 0; j < countArrays; j++)
				{
					int vertexIndex = first + j;
					if (data)
						memcpy(buffer, data + bigStride * vertexIndex, smallStride);
					else
						memset(buffer, 0, smallStride);
					buffer += smallStride;
				}
			}
		}
		else // enableVertexAttribArray == false
		{
			int components = vad.getDataNonArray_Components();
			const float* values = vad.getDataNonArray_Values();

			memcpy(buffer, &location, 4);				buffer += 4;
			memcpy(buffer, &components, 4);				buffer += 4;
			memcpy(buffer, values, components * 4);		buffer += components * 4;
		}
	}
}
