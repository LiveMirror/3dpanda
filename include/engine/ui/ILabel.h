//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/3/3 15:14:01_
// ����:  
//

#ifndef _ILABEL_201433151401_
#define _ILABEL_201433151401_

#include "IControl.h"

namespace panda
{
	class LabelImpl;
	class ENGINE_API ILabel:public IControl
	{
	public:
		ILabel(void);
		ILabel(LabelImpl* impl);
	};
}

#endif // _ILABEL_201433151401_
