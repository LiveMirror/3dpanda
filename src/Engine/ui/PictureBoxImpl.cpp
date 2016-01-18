#include "PictureBoxImpl.h"
#include "renderSystem/IGraph2D.h"

namespace panda
{
	PictureBoxImpl::PictureBoxImpl( void )
	{
		mDrawBorder = false;
	}

	void PictureBoxImpl::OnRender( IGraph2D* graph )
	{
		graph->DrawImage(mBackImage.Get(), Vector2Dn(0, 0), mRect.size);
	}
}