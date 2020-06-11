#include "Messenger.h"
#include "log.h"

Messenger::Messenger()
{
}

Messenger::Messenger(Socket socket) : m_socket(socket)
{
}

int Messenger::send(Message& msg)
{
	int tmp = (int)msg.m_type;
	LOGD("[%s] type = %d, length = %d", __FUNCTION__, tmp, msg.m_length);

	int ret = SOCKET_SUCCESS;
	if (m_socket.send((const char*)&tmp, 4) == SOCKET_ERROR)
	{
		ret = SOCKET_ERROR;
		goto my_end;
	}
	if (m_socket.send((const char*)&msg.m_length, 4) == SOCKET_ERROR)
	{
		ret = SOCKET_ERROR;
		goto my_end;
	}
	if (msg.m_length > 0 && msg.m_pData)
	{
		if (m_socket.send(msg.m_pData, msg.m_length) == SOCKET_ERROR)
		{
			ret = SOCKET_ERROR;
			goto my_end;
		}
	}
	my_end:
	if (ret == SOCKET_ERROR)
	{
		LOGE("[%s] Sent failed, stop capturing", __FUNCTION__);
	}
	return ret;
}

int Messenger::send(GlObject& obj)
{
	Message* msg = obj.toMessage();
	int result = send(*msg);
	SAFE_DEL(msg);
	return result;
}

int Messenger::sendRequestFinish()
{
	Message msg;
	msg.m_type = KMT_REQUEST_FINISH;
	return send(msg);
}

int Messenger::sendRequestError(const char* error /* = NULL */)
{
	Message msg;
	msg.m_type = KMT_REQUEST_ERROR;

	if (error)
	{
		msg.m_length = STRLEN(error);
		if (msg.m_length > 0)
		{
			msg.m_pData = new char[msg.m_length];
			memcpy(msg.m_pData, error, msg.m_length);
		}
		else
		{
			msg.m_length = 0;
		}
	}
	return send(msg);
}

int Messenger::sendTexUnits(int num, u8 curActiveTexUnit, u32* texIds_2D, u32* texIds_CubeMap)
{
	Message msg;
	msg.m_type = KMT_STATE_CURRENT_TEXTURES_STATUS;
	msg.m_length = num * 4 * 2 + 1/*1 byte for current active tex unit (0-31)*/;
	msg.m_pData = new char[msg.m_length];
	char* buffer = msg.m_pData;
	
	for (int i = 0; i < num; ++i)
	{
		memcpy(buffer, &texIds_2D[i], 4);		buffer += 4;
		memcpy(buffer, &texIds_CubeMap[i], 4);	buffer += 4;
		LOGD("texUnit %d: texId_2D = %d, texId_CubeMap = %d", i, texIds_2D[i], texIds_CubeMap[i]);
	}
	memcpy(buffer, &curActiveTexUnit, 1);
	return send(msg);
}

int Messenger::sendCurrentUsingProgram(u32 progId)
{
	Message msg;
	msg.m_type = KMT_STATE_CURRENT_USING_PROGRAM;
	msg.m_length = 4;
	msg.m_pData = new char[msg.m_length];
	memcpy(msg.m_pData, &progId, 4);
	return send(msg);
}

int Messenger::sendCurrentBindingVbos(u32 vboArrayBuffer, u32 vboElementArrayBuffer)
{
	Message msg;
	msg.m_type = KMT_STATE_CURRENT_BINDING_VBOS;
	msg.m_length = 4 + 4;
	msg.m_pData = new char[msg.m_length];
	memcpy(msg.m_pData, &vboArrayBuffer, 4);
	memcpy(msg.m_pData + 4, &vboElementArrayBuffer, 4);
	return send(msg);
}

bool Messenger::receive(char* buffer, int len)
{
	return m_socket.receiveComplete(buffer, len);
}

bool Messenger::receiveUint(u32& output)
{
	return m_socket.receiveComplete((char*)&output, 4);
}

bool Messenger::receiveInt(int& output)
{
	return m_socket.receiveComplete((char*)&output, 4);
}

CaptureOption Messenger::receiveCaptureOption()
{
	u8 value;
	m_socket.receiveComplete((char*)&value, 1);
	CaptureOption co;
	co.scaleScreenshot = value == 1;
	return co;
}

void Messenger::close()
{
	m_socket.close();
}
