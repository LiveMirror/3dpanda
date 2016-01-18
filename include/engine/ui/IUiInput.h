////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-2-27 21:17:37
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014227211737_H_
#define	_Tian_2014227211737_H_

namespace panda
{
	/*
	* UI���������
	*/
	class IUiInput
	{
	public:
		virtual void	OnMouseMove(MouseEventArgs& e) = 0;
		virtual void	OnMouseDown(MouseEventArgs& e) = 0;
		virtual void	OnMouseDClick(MouseEventArgs& e) = 0;
		virtual void	OnMouseUp(MouseEventArgs& e) = 0;
		virtual void	OnMouseWheel(MouseEventArgs& e) = 0;
		virtual void	OnKeyDown(KeyEventArgs& e) = 0;
		virtual void	OnChar(s32 key) = 0;
	};
}

#endif _Tian_2014227211737_H_