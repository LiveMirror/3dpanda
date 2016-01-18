//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 10:12:06_
// ����:  
//

#ifndef _RENDERQUEUE_201443101206_
#define _RENDERQUEUE_201443101206_

#include <list>
#include "Base/Config.h"

namespace panda
{
	class Renderable;
	/*
	*! ��Ⱦ����
	*/
	class RenderQueue
	{
	public:
		enum QueueIndex
		{
			NormalObject = 0,	// ������Ⱦ�Ķ���(��������Ӱ)
			ShadowObject,		// ������Ӱ�Ķ���
			AlphaObject,		// ͸������
			QueueCount
		};
		RenderQueue(void);

		//! ��ն���
		void			Clear();

		void			AddRenderObject(Renderable* pObject, RenderQueue::QueueIndex index);


	public:
		typedef std::list<Renderable*>	ObjectList;
		ObjectList		mQueues[RenderQueue::QueueCount];
	};
}

#endif // _RENDERQUEUE_201443101206_