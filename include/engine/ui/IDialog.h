////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-4 23:45:42
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201434234542_H_
#define	_Tian_201434234542_H_

#include "IPanel.h"

namespace panda
{
	class DialogImpl;
	/*
	*
	*/
	class IDialog:public IPanel
	{
	public:
		IDialog(void);
		IDialog(DialogImpl* impl);

		virtual void	SetEnableMove(bool enable);
		virtual bool	GetEnableMove(void)const;

		virtual void	DoMode(void);
		virtual void	CloseDlg(void);
	};
}

#endif _Tian_201434234542_H_