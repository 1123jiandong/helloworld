#ifndef _AMQPCLIENT_H
#define _AMQPCLIENT_H

#pragma once

#include "amqp.h"
#include "amqp_msg_object.h"



class AmqpClient {
public:
	AmqpClient(const char* hostname, const int port, const char* user,
		const char* pwd, const char* vhost, const char* exchage, const char* queuename);
	bool ConnectRabbitmq();
	bool RegisterRabbitmq();
	bool UnRegisterRabbitmq();

	bool RcvMsgObject(MESSAGE_OBJECT_STD::CallBackPtr func_ptr);
	bool StartProducer_str(char *msg_buf);
	bool LsAlive();
	void CloseConnect();

	static unsigned int __stdcall threadProc(void* pV, MESSAGE_OBJECT_STD::CallBackPtr func_ptr) {
		AmqpClient* p = (AmqpClient*)pV;
		p->RcvMsgObject(func_ptr);
		return 0;
	}

private:
	amqp_connection_state_t conn = NULL;
	char m_hostname[128];
	int m_port;
	char m_user[128];
	char m_pwd[128];
	char m_vhost[128];
	char m_exchange[128];
	char m_queuename[128];
	bool m_alive = false;
};
#endif
