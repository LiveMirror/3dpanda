//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/8 17:10:05_
// 描述:  
//

#ifndef _IBONE_201458171005_
#define _IBONE_201458171005_

#include "INode.h"

namespace panda
{
	class BoneImpl;
	class IBone:public INode
	{
	public:
		IBone(BoneImpl* pImpl);

		virtual void			AddChild(IBone* pBone);
		virtual u16				GetHandle(void)const;
		virtual const tstring&	GetName(void)const;
	};
}

#endif // _IBONE_201458171005_