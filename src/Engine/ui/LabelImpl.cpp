#include "LabelImpl.h"
#include "ui/IFont.h"
#include "renderSystem/IGraph2D.h"

namespace panda
{
	LabelImpl::LabelImpl( void )
	{
		mDrawBorder = false;
	}

	void LabelImpl::SetText( const tstring& text )
	{
		__super::SetText(text);
		Rect r;
		mFont->MeasureString(mText, r);
		mRect.size.width = r.size.width + 2;
		mRect.size.height = r.size.height + 2;
	}

	void LabelImpl::OnRender( IGraph2D* graph )
	{
		graph->DrawString(mFont, 0, 0, mRect.size.width, mRect.size.height, mText, mTextColor);
	}
}