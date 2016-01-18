//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2013/3/8 17:30:17_
// ����:
//

#ifndef _NETUTILS_201338173017_
#define _NETUTILS_201338173017_

#include "Config.h"

namespace panda
{
	struct NetAddr
	{
		NetAddr()
		{
			ip = 0;
			port = 0;
		}
		IPv4	ip;
		s32		port;

		bool IsNull()
		{
			if(0 == ip && 0 == port)
			{
				return true;
			}
			return false;
		}
	};

	class NetUtils
	{
	public:
		static s32		AdapterNum(void);				// ��������������
		static tstring	AdapterAddr(s32 index);			// ������������ַ	��MAC��ַ
		static IPv4		LocalHost(s32 index = 0);		// ����IP��ַ

		static IPv4		HostToIp(const tchar* host);	// ��������
		static IPv4		StrToIp(const tchar* ip);
		static tstring	IpToStr(IPv4 ip);
	};
}

#endif // _NETUTILS_201338173017_