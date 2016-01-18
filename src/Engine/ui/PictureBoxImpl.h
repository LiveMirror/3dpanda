//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/28 15:30:57_
// 描述:  
//

#ifndef _PICTUREBOXIMPL_2014228153057_
#define _PICTUREBOXIMPL_2014228153057_

#include "ControlImpl.h"

namespace panda
{
	class PictureBoxImpl:public ControlImpl
	{
	public:
		PictureBoxImpl(void);
		virtual void		OnRender(IGraph2D* graph);
	};
}

#endif // _PICTUREBOXIMPL_2014228153057_