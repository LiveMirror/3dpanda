//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/26 9:51:03_
// 描述:  
//

#ifndef _CTRLDEF_201422695103_
#define _CTRLDEF_201422695103_

#include "Event.h"

namespace panda
{
	struct MouseButtons
	{
		enum eValue
		{
			LButton = 0x0001,
			RButton = 0x0002,
			Shift	= 0x0004,
			Contorl = 0x0008,
			MButton = 0x0010,
			xButton1 = 0x0020,
			xButton2 = 0x0040,
		};
	};

	struct	PropertyGridType
	{
		enum eValue
		{
			Type_S32,
			Type_F32,
			Type_Vector3Df,
			Type_4F32,
			Type_String,
			Type_Bool
		};
	};

	struct MouseEventArgs
	{
		s32				x;
		s32				y;
		s32				delta;
		MouseButtons::eValue	button;
	};

	struct KeyEventArgs
	{
		bool			contrl;
		bool			shift;
		s32				keyCode;
	};

	class IControl;
	typedef Event<void(s32)>						EventCommon;    // 通用事件
	typedef Event<bool(IControl*)>					EventCtrl;		// 控件事件
	typedef Event<bool(IControl*, MouseEventArgs&)>	EventMouse;		// 鼠标事件
	typedef Event<bool(IControl*, KeyEventArgs&)>	EventKey;		// 键盘事件
	typedef Event<bool(IControl*, s32, s32)>		EventHandle;    // 控件事件

}

#endif // _CTRLDEF_201422695103_