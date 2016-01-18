//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/22 11:45:50_
// ����:  ���۵������ؼ�
//

#ifndef _IFOLDPANEL_2014522114550_
#define _IFOLDPANEL_2014522114550_

#include "IPanel.h"

namespace panda
{
	class FoldPageImpl;
	class IFoldPage:public IPanel
	{
	public:
		IFoldPage(void);
		IFoldPage(FoldPageImpl* impl);
	};

	class FoldPanelImpl;
	class IFoldPanel:public IPanel
	{
	public:
		IFoldPanel(void);
		IFoldPanel(FoldPanelImpl* impl);

		virtual IFoldPage*	AddPage(const tstring& name);

		virtual u32			GetPageNum(void)const;
		virtual IFoldPage*	GetPage(u32 index)const;

		virtual void		SetSelPage(u32 index);
		virtual s32			GetSelIndex(void)const;
		virtual IFoldPage*	GetSelPage(void)const;

		virtual EventCtrl&	OnSelPageChanged(void);
	};
}

#endif // _IFOLDPANEL_2014522114550_