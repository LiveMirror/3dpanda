//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/21 10:41:35_
// ����:  ���л�
//

#ifndef _ISERIALIZE_2014521104135_
#define _ISERIALIZE_2014521104135_

#include "FileStream.h"

namespace panda
{
	class ILevel;
	class ISerialize
	{
	public:
		virtual s32			GetChunk(void) const = 0;
		virtual void		Save(FileStream& file, ILevel* level) = 0;
	};
}

#endif // _ISERIALIZE_2014521104135_