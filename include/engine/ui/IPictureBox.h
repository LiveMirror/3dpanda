//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/28 15:26:48_
// 描述:  
//

#ifndef _IPICTUREBOX_2014228152648_
#define _IPICTUREBOX_2014228152648_

#include "IControl.h"

namespace panda
{
	class PictureBoxImpl;
	class ENGINE_API IPictureBox:public IControl
	{
	public:
		IPictureBox(void);
		IPictureBox(PictureBoxImpl* impl);
	};
}

#endif // _IPICTUREBOX_2014228152648_