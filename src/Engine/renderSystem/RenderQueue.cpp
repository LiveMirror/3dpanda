#include "RenderQueue.h"

namespace panda
{
	RenderQueue::RenderQueue( void )
	{

	}

	void RenderQueue::Clear()
	{
		for(s32 i = 0; i < RenderQueue::QueueCount; i++)
		{
			mQueues[i].clear();
		}
	}

	void RenderQueue::AddRenderObject( Renderable* pObject, RenderQueue::QueueIndex index)
	{
		mQueues[index].push_back(pObject);
	}
}