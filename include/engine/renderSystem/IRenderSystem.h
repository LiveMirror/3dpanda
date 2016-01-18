////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2012-10-19 19:26:12
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_20121019192612_H_
#define	_Tian_20121019192612_H_

#include "Base/Struct.h"

namespace panda
{
	class IRenderWindow;

	/*
	* 渲染系统
	* 用于管理渲染窗口
	*/
	class IRenderSystem
	{
	public:
		//----------------------------------------
		//! 创建一个渲染窗口
		virtual IRenderWindow*	CreateRenderWindow(RenderWindowParam* info = NULL) = 0;

		//-----------------------------------------
		//! 更新所有标记为自动更新的窗口
		virtual void			UpdateWindows(void) = 0;

		//-----------------------------------------
		//! 线框模式
		virtual void			RenderWireframe(bool grid) = 0;
	};
}

#endif _Tian_20121019192612_H_