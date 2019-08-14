#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdint.h>

#include "amqp.h"
#include "amqp_tcp_socket.h"
#include "amqp_framing.h"
#include "utils.h" 
#include "amqp_client.h"
#include "amqp_msg_object.h"

#pragma comment(lib, "ws2_32.lib")

/*
* hostname,port,user,pwd,vhost
*/
AmqpClient::AmqpClient(const char* hostname, const int port, const char* user,
	const char* pwd, const char* vhost,const char* exchange, const char* queuename)
{
	if ((hostname != NULL) || (port != 0) || (user != NULL)
		|| (pwd != NULL) || (vhost != NULL) || (queuename != NULL))
	{
		strcpy_s(this->m_hostname, hostname);
		this->m_port = port;
		strcpy_s(this->m_user, user);
		strcpy_s(this->m_pwd, pwd);
		strcpy_s(this->m_vhost, vhost);
		strcpy_s(this->m_exchange, exchange);
		strcpy_s(this->m_queuename, queuename);
	}
}

bool AmqpClient::ConnectRabbitmq()
{
	amqp_socket_t* socket;
	amqp_rpc_reply_t reply;
	int status;

	conn = amqp_new_connection();
	socket = amqp_tcp_socket_new(conn);
	if (!socket)
	{
		printf("amqp new socket error\n");
		return false;
	}


	status = amqp_socket_open(socket, m_hostname, m_port);
	if (status)
	{
		printf("amqp open socket error\n");
		return false;
	}

	reply = amqp_login(conn, m_vhost, 0, 4096,0,AMQP_SASL_METHOD_PLAIN, m_user, m_pwd);
	if (reply.reply_type == AMQP_RESPONSE_SERVER_EXCEPTION)
	{
		printf("amqp login error\n");
		return false;
	}
	
	amqp_channel_open(conn, 1);
	reply = amqp_get_rpc_reply(conn);
	if (reply.reply_type == AMQP_RESPONSE_SERVER_EXCEPTION)
	{
		printf("ConnectRabbitmq::amqp get rpc_reply error\n");
		return false;
	}

	m_alive = true;
	return true;
}

bool AmqpClient::RegisterRabbitmq() {

	{
		amqp_queue_delete(conn, 1, amqp_cstring_bytes(m_queuename), 0, 0);
		die_on_amqp_error(amqp_get_rpc_reply(conn), "deleting queue");

		amqp_queue_declare_ok_t* r = amqp_queue_declare(conn, 1, amqp_cstring_bytes(m_queuename), 0, 0, 0, 1, amqp_empty_table);
		die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");

		amqp_queue_bind(conn, 1, amqp_cstring_bytes(m_queuename), amqp_cstring_bytes(m_exchange),
			amqp_cstring_bytes(m_queuename), amqp_empty_table);
		die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue");
	}
	return false;
}

bool AmqpClient::UnRegisterRabbitmq() {

	{
		amqp_queue_delete(conn, 1, amqp_cstring_bytes(m_queuename), 0, 0);
		die_on_amqp_error(amqp_get_rpc_reply(conn), "deleting queue");
	}
	return false;
}

bool AmqpClient::StartProducer_str(char *msg_buf) {

	die_on_error(amqp_basic_publish(conn, 1, amqp_cstring_bytes(m_exchange),
		amqp_cstring_bytes(m_queuename), 0, 0, NULL,
		amqp_cstring_bytes(msg_buf)),
		"Publishing");

	//std::string cmd(msg_buf);
	//store_cmd(cmd);
	return false;
}


bool AmqpClient::RcvMsgObject(MESSAGE_OBJECT_STD::CallBackPtr func_ptr)
{
		amqp_basic_consume(conn, 1, amqp_cstring_bytes(m_queuename), amqp_empty_bytes, 0, 1, 0,
			amqp_empty_table);
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
				int msglength = envelope.message.body.len;
			
				char *temp = (char*)malloc(msglength + 1);
				memset(temp, 0x00, msglength + 1);
				char *temp1 = temp + msglength ;
				*temp1 = '\0';
				memcpy(temp, envelope.message.body.bytes,msglength);


				MESSAGE_OBJECT_STD::MsgObject *object = new MESSAGE_OBJECT_STD::MsgObject(temp, CmdType_Space, Targets_Unknow);
				func_ptr(object);
				amqp_destroy_envelope(&envelope);

				free(temp);

			}
		}
}

void AmqpClient::CloseConnect()
{
	amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
	amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
	amqp_destroy_connection(conn);
}

bool AmqpClient::LsAlive() {
	return m_alive;
}


