//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 10:12:06_
// 描述:  
//

#ifndef _RENDERQUEUE_201443101206_
#define _RENDERQUEUE_201443101206_

#include <list>
#include "Base/Config.h"

namespace panda
{
	class Renderable;
	/*
	*! 渲染队列
	*/
	class RenderQueue
	{
	public:
		enum QueueIndex
		{
			NormalObject = 0,	// 正常渲染的对象(不产生阴影)
			ShadowObject,		// 产生阴影的对象
			AlphaObject,		// 透明对象
			QueueCount
		};
		RenderQueue(void);

		//! 清空队列
		void			Clear();

		void			AddRenderObject(Renderable* pObject, RenderQueue::QueueIndex index);


	public:
		typedef std::list<Renderable*>	ObjectList;
		ObjectList		mQueues[RenderQueue::QueueCount];
	};
}

#endif // _RENDERQUEUE_201443101206_