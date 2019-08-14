#pragma once

#include <string>
#include <windows.h>
#include <vcclr.h>
//#include "types.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace std;

namespace EnnExchange {
	public ref class MsgObject {
	public:
		System::String ^msg_buf;
		System::Int32 m_type;
		System::Int32 m_taget;
	};

	public delegate int EnnOnCmdMsgDelegate(MsgObject ^msgobj);

	public ref class ApiWrapper {
	public:
		void static SendMsgObjectManaged(MsgObject ^ msgobj);
		void static MsgListenManaged(EnnOnCmdMsgDelegate^ funcptr, System::Int32 role);
		void static MsgUnlistenManaged();
		//int MethodConvert(MESSAGE_OBJECT_STD::MsgObject *obj);
		static EnnOnCmdMsgDelegate ^callbackptr;
	};
}


