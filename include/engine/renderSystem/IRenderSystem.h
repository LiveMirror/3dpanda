////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2012-10-19 19:26:12
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_20121019192612_H_
#define	_Tian_20121019192612_H_

#include "Base/Struct.h"

namespace panda
{
	class IRenderWindow;

	/*
	* ��Ⱦϵͳ
	* ���ڹ�����Ⱦ����
	*/
	class IRenderSystem
	{
	public:
		//----------------------------------------
		//! ����һ����Ⱦ����
		virtual IRenderWindow*	CreateRenderWindow(RenderWindowParam* info = NULL) = 0;

		//-----------------------------------------
		//! �������б��Ϊ�Զ����µĴ���
		virtual void			UpdateWindows(void) = 0;

		//-----------------------------------------
		//! �߿�ģʽ
		virtual void			RenderWireframe(bool grid) = 0;
	};
}

#endif _Tian_20121019192612_H_