#include "ProgressBarImpl.h"
#include "renderSystem/IGraph2D.h"

namespace panda
{
	ProgressBarImpl::ProgressBarImpl( void )
		:mValue(0.5f)
	{
		mBackColor2 = 0xaf254e85;
		mRect.size = Size(200, 12);
	}

	void ProgressBarImpl::OnRender( IGraph2D* graph )
	{
		s32 width = (s32)(mRect.size.width * mValue);
		graph->FillRect(2, 2, width - 4, mRect.size.height - 4, mBackColor2);
	}
}