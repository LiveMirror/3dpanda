#include "CheckBoxImpl.h"
#include "ui\ifont.h"
#include "renderSystem/IGraph2D.h"

namespace panda
{
	CheckBoxImpl::CheckBoxImpl( void )
		:mChecked(false)
	{
		mText = _T("CheckBox");
		mDrawBorder = false;
	}

	void CheckBoxImpl::SetText( const tstring& text )
	{
		__super::SetText(text);
		Rect r;
		mFont->MeasureString(mText, r);
		mRect.size.height = r.size.height + 2;
		mRect.size.width = r.size.width + 2 + mRect.size.height;
	}

	void CheckBoxImpl::OnRender( IGraph2D* graph )
	{
		if(mMouseOn)
		{
			Color temp = mBorderColor;
			temp.A /= 2;
			graph->DrawRect(3, 3, mRect.size.height - 6, mRect.size.height - 6, temp, 2);
		}
		if(mChecked)
		{
			graph->FillRect(7, 7, mRect.size.height - 14, mRect.size.height - 14, mBorderColor);
		}
		graph->DrawRect(3, 3, mRect.size.height - 6, mRect.size.height - 6, mBorderColor);
		graph->DrawString(mFont, mRect.size.height, 0, mRect.size.width - mRect.size.height, mRect.size.height, mText, mTextColor);
	}

	void CheckBoxImpl::OnMouseClick( MouseEventArgs& e )
	{
		mChecked = !mChecked;
	}
}