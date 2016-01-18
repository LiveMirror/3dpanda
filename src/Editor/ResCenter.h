//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/16 11:28:38_
// 描述:  资源中心
//

#ifndef _RESCENTER_2014416112838_
#define _RESCENTER_2014416112838_

#include "IPanda.h"
#include "EditorDef.h"
using namespace panda;

namespace editor
{
	class DlgChooseRes;
	class ResCenter
	{
	public:
		ResCenter(void);
		void			InitUI(IUiManager* uiMgr);

		EventRes&		OnResChoosed();
		void			ChooseRes(s32 filter = -1);
	protected:
		DlgChooseRes*	mDlgChoose;
	};
}

#endif // _RESCENTER_2014416112838_