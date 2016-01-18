//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/26 11:39:03_
// 描述:  
//

#ifndef _EFFECT2D_2014226113903_
#define _EFFECT2D_2014226113903_

#include "base/Config.h"
#include <d3dx9.h>

namespace panda
{
	class Effect2D
	{
	public:
		Effect2D(void);

		virtual bool	InitEffect(void);
		virtual void	BeginEffect(D3DXHANDLE tech);
		void			Set2DSize(s32 width, s32 height);
		void			EndEffect(void);

		void			DeviceLost(void);
		void			ResetDevice(void);
	public:
		ID3DXEffect*	mEffect;
		D3DXHANDLE		mUiSizeHandle;
	};
}

#endif // _EFFECT2D_2014226113903_