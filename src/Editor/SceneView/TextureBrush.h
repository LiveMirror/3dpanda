////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-5-16 23:27:20
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014516232720_H_
#define	_Tian_2014516232720_H_

#include "IBrush.h"

namespace editor
{
	/*
	*
	*/
	class TextureBrush:public IBrush
	{
	public:
		TextureBrush(void);

		virtual	void		OnPaint(f32 x, f32 y);

		virtual void		SetInsideRadius(s32 radius);
		virtual void		SetValue(f32 v);

		void				SetTextureIndex(s32 index);
	protected:
		s32			mTextureIndex;
		Color		mTensValue;
	};
}

#endif _Tian_2014516232720_H_