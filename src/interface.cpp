
#include <windows.h>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "amqp_client.h"
#include "interface.h"
#include "types.h"
#include "amqp_msg_object.h"

#pragma comment(lib, "ws2_32.lib")

//using namespace MESSAGE_OBJECT_STD;
namespace CONFIG_ARGS {
	const char* hostname = "127.0.0.1";
	const int   port = 5672;
	const char* user = "guest";
	const char* pwd = "guest";
	const char* vhost = "/";
	const char* exchange = "amq.direct";
	const char* queue_server = "queue_server";
	const char* queue_client = "queue_client";
	const char* queue_3d = "queue_3d";
	const char* queue_gis = "queue_gis";
	const char* consumer_queuename = nullptr;
}

TarGets g_role_type = Targets_Unknow;
AmqpClient amqp_Server(CONFIG_ARGS::hostname, CONFIG_ARGS::port, CONFIG_ARGS::user, CONFIG_ARGS::pwd, CONFIG_ARGS::vhost, CONFIG_ARGS::exchange, CONFIG_ARGS::queue_server);
AmqpClient amqp_Client(CONFIG_ARGS::hostname, CONFIG_ARGS::port, CONFIG_ARGS::user, CONFIG_ARGS::pwd, CONFIG_ARGS::vhost, CONFIG_ARGS::exchange, CONFIG_ARGS::queue_client);
AmqpClient amqp_3d(CONFIG_ARGS::hostname, CONFIG_ARGS::port, CONFIG_ARGS::user, CONFIG_ARGS::pwd, CONFIG_ARGS::vhost, CONFIG_ARGS::exchange, CONFIG_ARGS::queue_3d);
AmqpClient amqp_Gis(CONFIG_ARGS::hostname, CONFIG_ARGS::port, CONFIG_ARGS::user, CONFIG_ARGS::pwd, CONFIG_ARGS::vhost, CONFIG_ARGS::exchange, CONFIG_ARGS::queue_gis);

void MsgListen(MESSAGE_OBJECT_STD::CallBackPtr func_ptr, TarGets role)
{
	g_role_type = role;
	if (role == TarGets_Servere)
	{
		amqp_Server.ConnectRabbitmq();
		amqp_Server.RegisterRabbitmq();
		std::thread thread1(AmqpClient::threadProc, (void*)&amqp_Server, func_ptr);
		thread1.detach();
	}
	else if (role == TarGets_Client)
	{
		amqp_Client.ConnectRabbitmq();
		amqp_Client.RegisterRabbitmq();
		std::thread thread1(AmqpClient::threadProc, (void*)&amqp_Client, func_ptr);
		thread1.detach();
	}
	else if (role == TarGets_3D)
	{
		amqp_3d.ConnectRabbitmq();
		amqp_3d.RegisterRabbitmq();
		std::thread thread1(AmqpClient::threadProc, (void*)&amqp_3d, func_ptr);
		thread1.detach();
	}
	else  if (role == TarGets_GIS)
	{
		amqp_Gis.ConnectRabbitmq();
		amqp_Gis.RegisterRabbitmq();
		std::thread thread1(AmqpClient::threadProc, (void*)&amqp_Gis, func_ptr);
		thread1.detach();
	}
}

void MsgUnlisten() {

	if (g_role_type == TarGets_Servere)
	{
		amqp_Server.UnRegisterRabbitmq();
	}
	else if (g_role_type == TarGets_Client)
	{
		amqp_Client.UnRegisterRabbitmq();

	}
	else if (g_role_type == TarGets_3D)
	{
		amqp_3d.UnRegisterRabbitmq();

	}
	else  if (g_role_type == TarGets_GIS)
	{
		amqp_Gis.UnRegisterRabbitmq();
	}
}
void SendMsgObject(MESSAGE_OBJECT_STD::MsgObject *msgobj)
{
	const char* produce_queuename = nullptr;
	if (msgobj->GetTarget() == TarGets_Servere) {
		if (amqp_Server.LsAlive() == false) {
			amqp_Server.ConnectRabbitmq();
		}
		amqp_Server.StartProducer_str(msgobj->GetBuf());
	}
	else if (msgobj->GetTarget() == TarGets_Client) {
		if (amqp_Client.LsAlive() == false) {
			amqp_Client.ConnectRabbitmq();
		}
		amqp_Client.StartProducer_str(msgobj->GetBuf());
	}
	else if (msgobj->GetTarget() == TarGets_3D) {
		if (amqp_3d.LsAlive() == false) {
			amqp_3d.ConnectRabbitmq();
		}
		amqp_Server.StartProducer_str(msgobj->GetBuf());
	}
	else if (msgobj->GetTarget() == TarGets_GIS) {
		if (amqp_Gis.LsAlive() == false) {
			amqp_Gis.ConnectRabbitmq();
		}
		amqp_Gis.StartProducer_str(msgobj->GetBuf());
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