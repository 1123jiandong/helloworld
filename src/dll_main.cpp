#if 0
#include <windows.h>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <string>

#include "amqp_client.h"
#include "split_utils.h"
#include "dll_main.h"
#include "EnnExchange.h"
#include "amqp_client_managed.h"


#pragma comment(lib, "ws2_32.lib")

namespace AMQP_CLIENT_MANAGED {
	const char* hostname = "127.0.0.1";
	const int   port = 5672;
	const char* user = "guest";
	const char* pwd = "guest";
	const char* vhost = "/";
	const char* exchangeFlag = "amq.direct";
	const char* queue_server = "queue_server";
	const char* queue_client = "queue_client";
	const char* queue_3d = "queue_3d";
	const char* queue_gis = "queue_gis";
	const char* consumer_queuename = nullptr;

	TarGets g_role_type = Targets_Unknow;


	//gcroot<AmqpClientManaged^>* amqp_Server = gcnew gcroot<AmqpClientManaged^>;
	gcroot<AmqpClientManaged^> amqp_Server = gcnew  AmqpClientManaged(hostname, port, user, pwd, vhost, exchangeFlag, queue_server);
	gcroot<AmqpClientManaged^> amqp_Client = gcnew  AmqpClientManaged(hostname, port, user, pwd, vhost, exchangeFlag, queue_client);
	gcroot<AmqpClientManaged^> amqp_3d = gcnew  AmqpClientManaged(hostname, port, user, pwd, vhost, exchangeFlag, queue_3d);
	gcroot<AmqpClientManaged^> amqp_Gis = gcnew  AmqpClientManaged(hostname, port, user, pwd, vhost, exchangeFlag, queue_gis);

	//*amqp_Server =  AmqpClientManaged(hostname, port, user, pwd, vhost, exchangeFlag, queue_server);

	//AmqpClientManaged amqp_Server(hostname, port, user, pwd, vhost, exchangeFlag, queue_server);
	//AmqpClientManaged amqp_Client(hostname, port, user, pwd, vhost, exchangeFlag, queue_client);
	//AmqpClientManaged amqp_3d(hostname, port, user, pwd, vhost, exchangeFlag, queue_3d);
	//AmqpClientManaged amqp_Gis(hostname, port, user, pwd, vhost, exchangeFlag, queue_gis);


	void SendMsgObjectManaged(CmdType type, TarGets taget, char *msg_buf)
	{
		const char* produce_queuename = nullptr;
		if (taget == TarGets_Servere) {
			if (amqp_Server->m_amqpclient->LsAlive() == false) {
				amqp_Server->m_amqpclient->ConnectRabbitmq();
			}
			amqp_Server->m_amqpclient->StartProducer_str(msg_buf);
		}
		else if (taget == TarGets_Client) {
			if (amqp_Server->m_amqpclient->LsAlive() == false) {
				amqp_Server->m_amqpclient->ConnectRabbitmq();
			}
			amqp_Server->m_amqpclient->StartProducer_str(msg_buf);
		}
		else if (taget == TarGets_3D) {
			if (amqp_Server->m_amqpclient->LsAlive() == false) {
				amqp_Server->m_amqpclient->ConnectRabbitmq();
			}
			amqp_Server->m_amqpclient->StartProducer_str(msg_buf);
		}
		else if (taget == TarGets_GIS) {
			if (amqp_Server->m_amqpclient->LsAlive() == false) {
				amqp_Server->m_amqpclient->ConnectRabbitmq();
			}
			amqp_Server->m_amqpclient->StartProducer_str(msg_buf);
		}
	}


	void MsgListenManaged(gcroot<EnnOnCmdMsgDelegate^>  func_ptr, TarGets role)
	{
		g_role_type = role;


		//IntPtr pvFun = Marshal::GetFunctionPointerForDelegate(func_ptr);//¿É
		//callback(10, (void(*)(int))pvFun.ToInt64());
		if (role == TarGets_Servere)
		{
			amqp_Server->m_amqpclient->ConnectRabbitmq();
			amqp_Server->m_amqpclient->RegisterRabbitmq();
			//amqp_Server->m_amqpclient->StartConsumer_str(func_ptr);
		}
		else if (role == TarGets_Client)
		{
			amqp_Client->m_amqpclient->ConnectRabbitmq();
			amqp_Client->m_amqpclient->RegisterRabbitmq();
			//amqp_Client->m_amqpclient->StartConsumer_str(func_ptr);
		}
		else if (role == TarGets_3D)
		{
			amqp_3d->m_amqpclient->ConnectRabbitmq();
			amqp_3d->m_amqpclient->RegisterRabbitmq();
			//amqp_3d->m_amqpclient->StartConsumer_str(func_ptr);
		}
		else  if (role == TarGets_GIS)
		{
			amqp_Gis->m_amqpclient->ConnectRabbitmq();
			amqp_Gis->m_amqpclient->RegisterRabbitmq();
			//amqp_Gis->m_amqpclient->StartConsumer_str(func_ptr);
		}
	}

	void MsgUnlistenManaged() {

		if (g_role_type == TarGets_Servere)
		{
			amqp_Server->m_amqpclient->UnRegisterRabbitmq();
		}
		else if (g_role_type == TarGets_Client)
		{
			amqp_Client->m_amqpclient->UnRegisterRabbitmq();

		}
		else if (g_role_type == TarGets_3D)
		{
			amqp_3d->m_amqpclient->UnRegisterRabbitmq();

		}
		else  if (g_role_type == TarGets_GIS)
		{
			amqp_Gis->m_amqpclient->UnRegisterRabbitmq();
		}
	}
}
/*
std::vector<std::string>  Restorehistorycmds() {

	std::fstream in("./config.dat", std::ios::binary | std::ios::in);
	std::string infilebuffer;
	while (getline(in, infilebuffer))
	{
		std::cout << infilebuffer << std::endl;
	}
	in.close();

	std::vector<std::string> v = split2(infilebuffer, msg_split);
	return v;
}*/

#endif
