//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 15:10:27_
// 描述:  
//

#ifndef _IPASS_201443151027_
#define _IPASS_201443151027_

namespace panda
{
	class IPass
	{
	public:
		virtual ~IPass(void) {}
		virtual bool		LoadVertexShader(const tstring& file) = 0;
		virtual bool		LoadPixelShader(const tstring& file) = 0;
	};
}

#endif // _IPASS_201443151027_