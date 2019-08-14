#include "EnnExchange.h"
#include "interface.h"

namespace EnnExchange {

	int  MethodConvert(MESSAGE_OBJECT_STD::MsgObject *obj) {
		CmdType type = obj->GetType();
		TarGets target = obj->GetTarget();
		char *msgbuf = obj->GetBuf();

		EnnExchange::MsgObject ^msgobj = gcnew EnnExchange::MsgObject();
		msgobj->m_type = type;
		msgobj->m_taget = target;
		ApiWrapper::callbackptr(msgobj);
		return 1;
	}

	void  ApiWrapper::SendMsgObjectManaged(MsgObject ^msgobj)
	{
		int target = msgobj->m_taget;
		int type = msgobj->m_type;
		char* msg = (char*)Marshal::StringToHGlobalAnsi(msgobj->msg_buf).ToPointer();

		MESSAGE_OBJECT_STD::MsgObject *obj = new MESSAGE_OBJECT_STD::MsgObject(msg, (CmdType)type, (TarGets)target);
		printf("sendbuf =%s \n", msg);
		SendMsgObject(obj);
		Marshal::FreeHGlobal(IntPtr(msg));
	}

	void  ApiWrapper::MsgListenManaged(EnnOnCmdMsgDelegate^ funptr , System::Int32 role) {
		callbackptr = funptr;
		MsgListen(MethodConvert, (TarGets)role);
	}

	void  ApiWrapper::MsgUnlistenManaged() {
		MsgUnlisten();
	}

}