#include "ToolBarItemImpl.h"
#include "renderSystem/IGraph2D.h"
#include "ui/IFont.h"

namespace panda
{
	enum AniType
	{
		AniType_None,
		AniType_MouseEnter,
		AniType_MouseLeave,
	};

	ToolBarItemImpl::ToolBarItemImpl( void )
	{
		mDrawBorder = false;
	}

	void ToolBarItemImpl::OnRender( IGraph2D* graph )
	{
		graph->DrawString(mFont, 1, 1, mRect.size.width - 2, mRect.size.height, mText, mTextColor);
	}

	void ToolBarItemImpl::CalculateSize( s32 parentHeight )
	{
		Rect r;
		mFont->MeasureString(mText, r);
		SetSize(r.size.width + 2, parentHeight - 2);
	}


	/********************************  ToolBarButtonItemImpl  **********************************************/

	ToolBarButtonItemImpl::ToolBarButtonItemImpl( void )
		:mMouseDown(false)
	{
		mBackColor = 0x6f254e85;
		mBackColor2 = 0x8f2b7fdb;
		mAniState = AniType_None;
		mAniAlpha = 0;
	}

	void ToolBarButtonItemImpl::OnRender( IGraph2D* graph )
	{
		Color c = mBackColor;
		c.A = (u8)(c.A * mAniAlpha);
		Color c2 = mBackColor2;
		c2.A = (u8)(c2.A * mAniAlpha);
		graph->FillRect(0, 0, mRect.size.width, mRect.size.height, c, c2);
		
		if(!mBackImage.IsNull())
		{
			if(mEnable)
			{
				if(mMouseDown)
				{
					graph->DrawImage(mBackImage.Get(), 3, 3, mRect.size.width - 6, mRect.size.height - 6);
				}
				else
				{
					graph->DrawImage(mBackImage.Get(), 2, 2, mRect.size.width - 4, mRect.size.height - 4);
				}
			}
			else
			{
				// ͼƬ�䰵
				graph->DrawImage(mBackImage.Get(), 3, 3, mRect.size.width - 6, mRect.size.height - 6, 0xff787878);
			}
		}
		
		c = mBorderColor;
		c.A = (u8)(c.A * mAniAlpha);
		graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, c);
	}

	void ToolBarButtonItemImpl::OnMouseDown( MouseEventArgs& e )
	{
		__super::OnMouseDown(e);

		if(e.button & MouseButtons::LButton)
		{
			mMouseDown = true;
		}
	}

	void ToolBarButtonItemImpl::OnMouseUp( MouseEventArgs& e )
	{
		__super::OnMouseUp(e);
		if(e.button & MouseButtons::LButton)
		{
			mMouseDown = false;
		}
	}

	void ToolBarButtonItemImpl::CalculateSize( s32 parentHeight )
	{
		SetSize(parentHeight - 2, parentHeight - 2);
		SetToolTip(mText);
	}

	void ToolBarButtonItemImpl::OnMouseEnter( void )
	{
		__super::OnMouseEnter();
		mAniState = AniType_MouseEnter;
	}

	void ToolBarButtonItemImpl::OnMouseLevae( void )
	{
		__super::OnMouseLevae();
		if(mAniState == AniType_None)
		{
			mAniState = AniType_MouseLeave;
		}
	}

	void ToolBarButtonItemImpl::Update( s32 tick )
	{
		switch(mAniState)
		{
		case AniType_None:
			{
				return;
			}
		case AniType_MouseEnter:
			{
				mAniAlpha += 0.002f * tick;
				if(mAniAlpha >= 1.0f)
				{
					mAniAlpha = 1.0f;
					if(mMouseOn)
					{
						mAniState = AniType_None;
					}
					else
					{
						mAniState = AniType_MouseLeave;
					}
				}
				break;
			}
		case AniType_MouseLeave:
			{
				mAniAlpha -= 0.002f * tick;
				if(mAniAlpha <= 0)
				{
					mAniAlpha = 0;
					mAniState = AniType_None;
				}
				break;
			}
		}
	}
	/********************************  ToolBarSeparatorItemImpl  **********************************************/

	void ToolBarSeparatorItemImpl::OnRender( IGraph2D* graph )
	{
		graph->DrawLine(3, 4, 3, mRect.size.height - 4, mBorderColor, 1);
	}

	void ToolBarSeparatorItemImpl::CalculateSize( s32 parentHeight )
	{
		SetSize(5, parentHeight - 2);
	}

	/********************************  ToolBarToggleButton  **********************************************/

	ToolBarToggleButton::ToolBarToggleButton( void )
		:mSelected(false)
	{

	}

	void ToolBarToggleButton::OnMouseClick( MouseEventArgs& e )
	{
		mSelected = !mSelected;
		mOnSelectChange(mThis);
	}

	void ToolBarToggleButton::OnRender( IGraph2D* graph )
	{
		if(mSelected)
		{
			graph->FillRect(1, 1, mRect.size.width - 2, mRect.size.height - 2, 0x780000ff);
			graph->DrawRect(1, 1, mRect.size.width - 2, mRect.size.height - 2, mBorderColor);
		}
		Color c = mBackColor;
		c.A = (u8)(c.A * mAniAlpha);
		Color c2 = mBackColor2;
		c2.A = (u8)(c2.A * mAniAlpha);
		graph->FillRect(0, 0, mRect.size.width, mRect.size.height, c, c2);

		if(!mBackImage.IsNull())
		{
			if(mEnable)
			{
				if(mMouseDown)
				{
					graph->DrawImage(mBackImage.Get(), 3, 3, mRect.size.width - 6, mRect.size.height - 6);
				}
				else
				{
					graph->DrawImage(mBackImage.Get(), 2, 2, mRect.size.width - 4, mRect.size.height - 4);
				}
			}
			else
			{
				// ͼƬ�䰵
				graph->DrawImage(mBackImage.Get(), 3, 3, mRect.size.width - 6, mRect.size.height - 6, 0xff787878);
			}
		}

		c = mBorderColor;
		c.A = (u8)(c.A * mAniAlpha);
		graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, c);
	}
}