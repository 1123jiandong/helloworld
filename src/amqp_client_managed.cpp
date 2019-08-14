#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdint.h>
#if 0
#include "amqp.h"
#include "amqp_tcp_socket.h"
//#include "amqp_framing.h"
//#include "platform_utils.h"
#include "utils.h" 
#include "amqp_client.h"
#include "split_utils.h"
//#include "consumer_work.h"
#include "amqp_client_managed.h"

#pragma comment(lib, "ws2_32.lib")

using System::Threading::Thread;
using System::Threading::ThreadStart;
using System::Threading::Tasks::Task;

/*
* hostname,port,user,pwd,vhost
*/

bool AmqpClientManaged::ConnectRabbitmq()
{
	return m_amqpclient->ConnectRabbitmq();
}

bool AmqpClientManaged::RegisterRabbitmq() {
	return m_amqpclient->RegisterRabbitmq();
}

bool AmqpClientManaged::UnRegisterRabbitmq() {
	return m_amqpclient->UnRegisterRabbitmq();
}

bool AmqpClientManaged::StartProducer_str(char *msg_buf) {
	return m_amqpclient->StartProducer_str(msg_buf);
}


bool AmqpClientManaged::StartConsumer_str(gcroot<EnnOnCmdMsgDelegate^> funptr)
{
	printf("starting consumer thread!\n");
/*	WorkConsumer ^object = gcnew WorkConsumer();
	String^ temp=System::Runtime::InteropServices::Marshal::PtrToStringAnsi((IntPtr)m_queuename);
	object->m_queuename = temp;
	object->conn = conn;
	object->func_ptr = funptr;

	//ThreadStart ^threadstart = gcnew ThreadStart(object, &WorkConsumer::DoWork);

	Thread^ consumerThread = gcnew Thread(gcnew ThreadStart(object, &WorkConsumer::DoWork));
	consumerThread->Start();*/
	
	return false;
}


void AmqpClientManaged::CloseConnect(){
	m_amqpclient->CloseConnect();
}

bool AmqpClientManaged::LsAlive() {
	return m_amqpclient->LsAlive();
}

#endif


