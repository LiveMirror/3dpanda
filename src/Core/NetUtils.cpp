#include "core.h"
#include "NetUtils.h"
#include "StringUtils.h"

#pragma comment(lib,"Iphlpapi.lib") //需要添加Iphlpapi.lib库
#pragma comment(lib, "ws2_32.lib")

namespace panda
{
	s32 NetUtils::AdapterNum( void )
	{
		unsigned long int               ulSize = 0;
		PIP_ADAPTER_INFO    pInfo = NULL, pSrc = NULL;

		DWORD temp = 0;
		temp = ::GetAdaptersInfo( pInfo, &ulSize ); // 第一次调用，获取缓冲区大小

		// 分配空间
		pInfo = (PIP_ADAPTER_INFO)malloc( ulSize );
		pSrc = pInfo;
		temp = ::GetAdaptersInfo( pInfo, &ulSize );

		if ( ERROR_SUCCESS != temp )
		{
			free( pSrc );
			return -1;
		}

		// 遍历每一张网卡
		s32 iCount = 0;
		while ( pInfo ) {
			pInfo = pInfo->Next;
			++iCount;
		} // while

		free( pSrc );
		return iCount;
	}

	tstring NetUtils::AdapterAddr( s32 index )
	{
		tstring mac = _T("");
		ULONG               ulSize = 0;
		PIP_ADAPTER_INFO    pInfo = NULL, pSrc = NULL;
		//memset( addr.addr, 0, sizeof(addr.addr)/sizeof(addr.addr[0]) );

		DWORD temp = 0;
		temp = GetAdaptersInfo( pInfo, &ulSize ); // 第一次调用，获取缓冲区大小

		// 分配空间
		pInfo = (PIP_ADAPTER_INFO)malloc( ulSize );
		pSrc = pInfo;
		temp = GetAdaptersInfo( pInfo, &ulSize );

		if ( ERROR_SUCCESS != temp )
		{
			free( pSrc );
			return mac;
		}

		// 遍历每一张网卡
		s32 iCount = 0;
		while ( pInfo ) {

			if ( index == iCount )
			{
				for ( s32 i = 0; i < 4; ++i )
				{
					mac += pInfo->Address[i];
				}
				break;
			}

			pInfo = pInfo->Next;
			++iCount;
		} // while

		free( pSrc );
		return mac;
	}

	IPv4 NetUtils::LocalHost( s32 index /*= 0*/ )
	{
		// 本机名.
		char szName[255] = {0};

		// 获得本机名.
		if ( !gethostname(szName, sizeof(szName)) )
		{
			hostent* host = ::gethostbyname(szName);
			if (host) {
				return (*(in_addr*)*host->h_addr_list).s_addr;
			}
		}

		return 0;
	}

	IPv4 NetUtils::HostToIp( const tchar* host )
	{
		if ( NULL == host )
		{
			return 0;
		}

		struct hostent* pHostent = NULL;

#ifdef _UNICODE
		std::string str;
		StringUtils::Wide2narrow( host, StringUtils::GetLength(host), str );
		pHostent = gethostbyname( str.c_str() );
#else
		pHostent = gethostbyname( host );
#endif
		if ( NULL == pHostent || NULL == pHostent->h_addr_list )
		{
			return 0;
		}

		char* pAddr = pHostent->h_addr_list[0];
		return (*(IPv4*)pAddr);
	}

	IPv4 NetUtils::StrToIp( const tchar* ip )
	{
#ifdef _UNICODE
		std::string str;
		StringUtils::Wide2narrow( ip, StringUtils::GetLength(ip), str );
		return inet_addr( str.c_str() );
#else
		return inet_addr( ip );
#endif
	}

	tstring NetUtils::IpToStr( IPv4 ip )
	{
		IN_ADDR ia;
		ia.s_addr = ip;
		tstring ipStr;
#ifdef _UNICODE
		std::string temp;
		temp = inet_ntoa( ia );
		StringUtils::Narrow2wide(temp.c_str(), temp.length(), ipStr);
#else
		ipStr = inet_ntoa( ia );
#endif
		return ipStr;
	}
}