#if 0

#ifndef _MANAGED_AMQPCLIENT_H
#define _MANAGED_AMQPCLIENT_H

#pragma once

#include <vcclr.h>
#include "amqp.h"
#include "EnnExchange.h"

using namespace EnnExchange;
using namespace System;
using namespace System::Threading;
using System::Threading::Thread;
using System::Threading::ThreadStart;
using System::Threading::Tasks::Task;

ref class AmqpClientManaged {
public:

	AmqpClientManaged(const char* hostname, const int port, const char* user,
		const char* pwd, const char* vhost, const char* exchage, const char* queuename)
		:m_amqpclient(new AmqpClient( hostname, port,  user,pwd, vhost, exchage, queuename)) {}

	~AmqpClientManaged()
	{
		delete m_amqpclient;
	}

	bool ConnectRabbitmq();
	bool RegisterRabbitmq();
	bool UnRegisterRabbitmq();

	bool StartConsumer_str(gcroot<EnnExchange::EnnOnCmdMsgDelegate^> func_ptr);
	bool StartProducer_str(char *msg_buf);
	bool LsAlive();
	void CloseConnect();

	AmqpClient* m_amqpclient;
};
#endif
#endif
