//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/21 10:45:38_
// 描述:  
//

#ifndef _IDESERIALIZE_2014521104538_
#define _IDESERIALIZE_2014521104538_

#include "FileStream.h"

namespace panda
{
	class IDeserialize
	{
	public:
		virtual s32			GetChunk(void) const = 0;
		virtual void		Load(FileStream& file, ILevel* level) = 0;
	};
}

#endif // _IDESERIALIZE_2014521104538_