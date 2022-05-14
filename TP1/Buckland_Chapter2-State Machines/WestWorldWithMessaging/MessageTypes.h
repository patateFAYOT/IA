#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
	Msg_HiHoneyImHome,
	Msg_StewReady,
	Msg_WannaFight,
	Msg_Fighting
};


inline std::string MsgToStr(int msg)
{
	switch (msg)
	{
	case 0:

		return "HiHoneyImHome";

	case 1:

		return "StewReady";

	case 2:

		return "WannaFight";

	case 3:

		return "Fighting";

	default:

		return "Not recognized!";
	}
}

#endif