#include "amqp_msg_object.h"
#include <string.h>
#include <stdlib.h>
namespace MESSAGE_OBJECT_STD {
	MsgObject::MsgObject(char* buf, CmdType type, TarGets target)
	{
		int bufLen = strlen(buf) + 1;
		m_buf = (char*)malloc(bufLen);
		memcpy(m_buf, buf, bufLen);

		m_type = type;
		m_taget = target;
	}

	MsgObject::~MsgObject()
	{
		if (m_buf != NULL)
			free(m_buf);
	}

	void MsgObject::SetBuf(char* buf,int msglen) {
		if (m_buf != NULL)
			free(m_buf);

		int bufLen = strlen(buf) + 1;
		m_buf = (char*)malloc(bufLen);
		memcpy(m_buf, buf, bufLen);
	}
	void  MsgObject::SetType(CmdType type) {
		m_type = type;
	}
	void  MsgObject::SetTarget(TarGets target) {
		m_taget = target;

	}
	char* MsgObject::GetBuf() {
		return m_buf;
	}

	CmdType  MsgObject::GetType() {
		return m_type;
	}

	TarGets  MsgObject::GetTarget() {
		return m_taget;
	}
}