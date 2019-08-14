#if 0

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdint.h>
#include "amqp.h"
#include "amqp_tcp_socket.h"
//#include "amqp_framing.h"
#include "platform_utils.h"
#include "utils.h" 
#include "consumer_work.h"
#include "split_utils.h"

#pragma comment(lib, "ws2_32.lib")

using System::Threading::Thread;
using System::Threading::ThreadStart;
using System::Threading::Tasks::Task;

namespace EnnExchange {

	void WorkConsumer::DoWork() {
		char* temp = (char*)(void*)Marshal::StringToHGlobalAnsi(m_queuename);
		amqp_basic_consume(conn, 1, amqp_cstring_bytes(temp), amqp_empty_bytes, 0, 1, 0,amqp_empty_table);
		while (1)
		{
			amqp_rpc_reply_t ret;
			amqp_envelope_t envelope;
			memset(&envelope, 0x00, sizeof(envelope));


			timeval temp{ 0,1 };
			ret = amqp_consume_message(conn, &envelope, &temp, 0);
			if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
			}
			else {
				size_t msglength = envelope.message.body.len;

				void* msg = (void*)malloc(msglength);
				memset(msg, 0x00, msglength);

				memcpy(msg, envelope.message.body.bytes, msglength);
				//printf("in the app str =%s    msglen = %d \n", (char*)msg, msglength);

				MsgObject^ msg_obj = gcnew MsgObject();
				msg_obj->msg_buf = gcnew System::String((char*)(envelope.message.body.bytes));
				func_ptr(msg_obj);
				free(msg);
				amqp_destroy_envelope(&envelope);
			}
		}
	}
}
#endif