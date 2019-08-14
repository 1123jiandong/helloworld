
#include "amqp_msg_object.h"
#include <vector>
#include <string>


#ifdef _EXPORTING
#define API_DECLSPEC __declspec(dllexport)
#else
#define API_DECLSPEC __declspec(dllimport)
#endif

void API_DECLSPEC SendMsgObject(MESSAGE_OBJECT_STD::MsgObject *msgobj);
void API_DECLSPEC MsgListen(MESSAGE_OBJECT_STD::CallBackPtr func_ptr, TarGets role);
void API_DECLSPEC MsgUnlisten();

//std::vector<std::string>  Restorehistorycmds();