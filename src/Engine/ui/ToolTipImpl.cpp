#include "ToolTipImpl.h"
#include "renderSystem/IGraph2D.h"
#include "ui/IFont.h"

namespace panda
{
	ToolTipImpl::ToolTipImpl( void )
	{
		mIsVisible = false;
		mBackColor = 0xff254e85;
	}

	void ToolTipImpl::SetText( const tstring& text )
	{
		__super::SetText(text);
		Rect r;
		mFont->MeasureString(mText, r);
		mRect.size.width = r.size.width + 2;
		mRect.size.height = r.size.height + 2;
	}

	void ToolTipImpl::ShowTip( s32 x, s32 y )
	{
		mRect.pos.x = x;
		mRect.pos.y = y;
		mIsVisible = true;
	}

	void ToolTipImpl::OnRender( IGraph2D* graph )
	{
		graph->FillRect(mRect.pos.x, mRect.pos.y, mRect.size.width, mRect.size.height, mBackColor);
		graph->DrawString(mFont, mRect.pos.x + 2, mRect.pos.y, mRect.size.width, mRect.size.height, mText, mTextColor, FontFormat::VCENTER);
		graph->DrawRect(mRect.pos.x, mRect.pos.y, mRect.size.width, mRect.size.height, mBorderColor);
	}
}