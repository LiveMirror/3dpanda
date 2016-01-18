////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-2 23:35:51
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201432233551_H_
#define	_Tian_201432233551_H_

#include "ControlImpl.h"

namespace panda
{
	/*
	*
	*/
	class TextBoxImpl:public ControlImpl
	{
	public:
		TextBoxImpl(void);

		virtual void			OnRender(IGraph2D* graph);
		virtual void			OnGotFocus(void);
		virtual void			OnLostFocus(void);
		virtual void			Update(s32 tick);
		virtual void			OnKeyDown(KeyEventArgs& e);
		virtual void			OnChar(s32 key);
		virtual void			OnMouseDown(MouseEventArgs& e);
		virtual void			OnMouseUp(MouseEventArgs& e);
		virtual void			OnMouseMove(MouseEventArgs& e);
		// Summary:
		//  Determines whether the specified key is an input key or a special key that requires preprocessing.
		bool					IsInputKey(s32 keyData);


		void			OnTextChange(void);
		
		void			CalculateCursorPos(void);
		void			CalculateSelectPos(void);
		s32				GetIndexFromPos(s32 x, s32 y);
		s32				GetPosFromIndex(s32 index);
	public:
		bool			mPassWord;
		s32				mAniTime;
		bool			mDrawCursor;
		bool			mMouseDown;
		s32				mCursorIndex;
		s32				mMouseDownIndex;
		s32				mCursorPos;
		s32				mSelectBegin;
		s32				mSelectEnd;
		s32				mSelectBeginPos;
		s32				mSelectEndPos;
	};
}

#endif _Tian_201432233551_H_