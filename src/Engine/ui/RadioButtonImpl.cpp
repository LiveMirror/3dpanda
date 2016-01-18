#include "RadioButtonImpl.h"
#include "ui/IFont.h"
#include "renderSystem/IGraph2D.h"
#include "panelimpl.h"
#include "ui/IPanel.h"

namespace panda
{
	RadioButtonImpl::RadioButtonImpl( void )
		:mChecked(false)
	{
		mDrawBorder = false;
	}

	void RadioButtonImpl::SetText( const tstring& text )
	{
		__super::SetText(text);
		Rect r;
		mFont->MeasureString(mText, r);
		mRect.size.height = r.size.height + 2;
		mRect.size.width = r.size.width + 2 + mRect.size.height;
	}

	void RadioButtonImpl::OnRender( IGraph2D* graph )
	{
		s32 h = mRect.size.height / 2;
		if(mMouseOn)
		{
			Color temp = mBorderColor;
			temp.A *= 0.5f;
			graph->DrawCircle(h, h, h - 3, temp, 2);
		}
		if(mChecked)
		{
			graph->FillCircle(h, h, h - 6, mBorderColor);
		}
		graph->DrawCircle(h, h, h - 3, mBorderColor);
		graph->DrawString(mFont, mRect.size.height, 0, mRect.size.width - mRect.size.height, mRect.size.height, mText, mTextColor);
	}

	void RadioButtonImpl::OnMouseClick( void )
	{
		if(mChecked)
		{
			return;
		}
		if(NULL == mParent)
		{
			return;
		}

		PanelImpl* impl = (PanelImpl*)mParent->mImpl;
		if(NULL != impl->mRadioButton)
		{
			impl->mRadioButton->_SetCheck(false);
		}
		impl->mRadioButton = this;
		_SetCheck(true);
	}

	void RadioButtonImpl::_SetCheck( bool check )
	{
		mChecked = check;
		mOnCheckedChange(mThis, 0, 0);
	}
}