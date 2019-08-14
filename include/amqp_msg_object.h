#pragma once

#include "types.h"

#ifndef _MSGOBJECT_H_
#define _MSGOBJECT_H_
namespace MESSAGE_OBJECT_STD {

#ifdef _EXPORTING
#define API_DECLSPEC __declspec(dllexport)
#else
#define API_DECLSPEC __declspec(dllimport)
#endif

	class API_DECLSPEC MsgObject
	{
	public:
		MsgObject(char* buf, CmdType type, TarGets target);
		~MsgObject();
		void SetBuf(char* buf,int msglen);
		void SetType(CmdType type);
		void SetTarget(TarGets TarGets);
		char* GetBuf();
		CmdType GetType();
		TarGets GetTarget();

	private:
		char *m_buf;
		CmdType m_type;
		TarGets m_taget;
	};

	typedef  int(*CallBackPtr)(MsgObject *msg);

}
#endif