////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-25 21:07:09
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014225210709_H_
#define	_Tian_2014225210709_H_

#include "IControl.h"

namespace panda
{
	class PanelImpl;
	/*
	* Provides focus-management functionality for controls that can function as
	* a container for other controls. A base class for controls that support auto-scrolling behavior.
	*/
	class ENGINE_API IPanel:public IControl
	{
	public:
		IPanel(void);
		IPanel(PanelImpl* impl);

		virtual void		AddChild(IControl* ctrl);
		virtual bool		HasChild(IControl* ctrl);

		virtual void		RemoveChild(IControl* ctrl);
	};
}

#endif _Tian_2014225210709_H_