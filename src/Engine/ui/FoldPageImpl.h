//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/22 15:17:40_
// ����:  
//

#ifndef _FOLDPAGEIMPL_2014522151740_
#define _FOLDPAGEIMPL_2014522151740_

#include "PanelImpl.h"

namespace panda
{
	class FoldPageImpl:public PanelImpl
	{
	public:
		FoldPageImpl(void);

		virtual void		OnRender(IGraph2D* graph);
	};
}

#endif // _FOLDPAGEIMPL_2014522151740_