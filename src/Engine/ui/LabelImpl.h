//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/3/3 15:15:46_
// ����:  
//

#ifndef _LABELIMPL_201433151546_
#define _LABELIMPL_201433151546_

#include "ControlImpl.h"

namespace panda
{
	class LabelImpl:public ControlImpl
	{
	public:
		LabelImpl(void);

		virtual void		SetText(const tstring& text);
		virtual void		OnRender(IGraph2D* graph);
	};
}

#endif // _LABELIMPL_201433151546_