#pragma once
#if 0
#include <vcclr.h>
#include "amqp.h"
#include "EnnExchange.h"

namespace EnnExchange {
	ref class WorkConsumer
	{
	public:
		amqp_connection_state_t conn = NULL;
		System::String^ m_queuename;
		EnnOnCmdMsgDelegate^ func_ptr;
	public:
		void DoWork();
	};
}
#endif