//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2013/3/8 17:30:17_
// 描述:
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
		static s32		AdapterNum(void);				// 网络适配器数量
		static tstring	AdapterAddr(s32 index);			// 网络适配器地址	即MAC地址
		static IPv4		LocalHost(s32 index = 0);		// 本地IP地址

		static IPv4		HostToIp(const tchar* host);	// 域名解析
		static IPv4		StrToIp(const tchar* ip);
		static tstring	IpToStr(IPv4 ip);
	};
}

#endif // _NETUTILS_201338173017_