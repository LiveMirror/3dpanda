////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-3 22:13:29
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201443221329_H_
#define	_Tian_201443221329_H_

#include "ControlImpl.h"

namespace panda
{
	/*
	* 默认为label
	*/
	class ToolBarItemImpl:public ControlImpl
	{
	public:
		ToolBarItemImpl(void);
		virtual void		OnRender(IGraph2D* graph);
		virtual void		CalculateSize(s32 parentHeight);


	};

	
	class ToolBarButtonItemImpl:public ToolBarItemImpl
	{
	public:
		ToolBarButtonItemImpl(void);
		virtual void		OnRender(IGraph2D* graph);
		virtual void		CalculateSize(s32 parentHeight);

		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseUp(MouseEventArgs& e);
		virtual void		OnMouseEnter(void);
		virtual void		OnMouseLevae(void);
		virtual void		Update(s32 tick);
	public:
		bool		mMouseDown;
		f32			mAniAlpha;
	};

	class ToolBarToggleButton:public ToolBarButtonItemImpl
	{
	public:
		ToolBarToggleButton(void);
		virtual void		OnRender(IGraph2D* graph);
		virtual void		OnMouseClick(MouseEventArgs& e);
	public:
		bool			mSelected;
		EventCtrl		mOnSelectChange;
	};

	class ToolBarSeparatorItemImpl:public ToolBarItemImpl
	{
	public:
		virtual void		OnRender(IGraph2D* graph);
		virtual void		CalculateSize(s32 parentHeight);
	};
}

#endif _Tian_201443221329_H_