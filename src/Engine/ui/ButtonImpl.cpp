#include "ButtonImpl.h"
#include "renderSystem/IGraph2D.h"
#include "base/Vector2D.h"

namespace panda
{
	enum AniType
	{
		AniType_None,
		AniType_MouseEnter,
		AniType_MouseLeave,
	};

	ButtonImpl::ButtonImpl()
		:mMouseDown(false)
	{
		mText = _T("Button");
		mRect.size = Size(100, 25);
		mBackColor = 0x6f254e85;
		mBackColor2 = 0x8f2b7fdb;
		mAniAlpha = 0.5f;
		mBorderColor.A = 125;
		mAniState = AniType_None;
	}

	void ButtonImpl::OnRender( IGraph2D* graph )
	{
		if(mEnable)
		{
			graph->FillRect(0, 0, mRect.size.width, mRect.size.height, mBackColor, mBackColor2);

			Color textColor = mTextColor;
			textColor.A *= mAniAlpha;
			Color c = mBorderColor;
			c.A *= (mAniAlpha - 0.5f);
			graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, c, 2);
			if(mMouseDown)
			{
				c.A *= 0.5f;
				graph->DrawRect(2, 2, mRect.size.width - 4, mRect.size.height - 4, c, 1);
				c.A *= 0.3f;
				graph->DrawRect(3, 3, mRect.size.width - 6, mRect.size.height - 6, c, 1);
				if(!mBackImage.IsNull())
				{
					graph->DrawImage(mBackImage.Get(), 1, 1, mRect.size.width, mRect.size.height);
				}
				else
				{
					graph->DrawString(mFont, 1, 1, mRect.size.width, mRect.size.height, mText, textColor);
				}
			}
			else
			{
				if(!mBackImage.IsNull())
				{
					graph->DrawImage(mBackImage.Get(), 0, 0, mRect.size.width, mRect.size.height);
				}
				else
				{
					graph->DrawString(mFont, 0, 0, mRect.size.width, mRect.size.height, mText, textColor);
				}
			}
		}
		else
		{
			graph->FillRect(0, 0, mRect.size.width, mRect.size.height, 0x7f353535);
			graph->DrawString(mFont, 0, 0, mRect.size.width, mRect.size.height, mText, 0x7f565656);
		}
	}

	void ButtonImpl::OnMouseEnter(void)
	{
		__super::OnMouseEnter();
		mAniState = AniType_MouseEnter;
	}

	void ButtonImpl::OnMouseLevae(void)
	{
		__super::OnMouseLevae();
		if(mAniState == AniType_None)
		{
			mAniState = AniType_MouseLeave;
		}
	}

	void ButtonImpl::OnMouseDown( MouseEventArgs& e )
	{
		__super::OnMouseDown(e);
		if(e.button & MouseButtons::LButton)
		{
			mMouseDown = true;
		}
	}

	void ButtonImpl::OnMouseUp( MouseEventArgs& e )
	{
		if(e.button & MouseButtons::LButton)
		{
			mMouseDown = false;
		}
	}

	void ButtonImpl::Update( s32 tick )
	{
		switch(mAniState)
		{
		case AniType_None:
			{
				return;
			}
		case AniType_MouseEnter:
			{
				mAniAlpha += 0.001f * tick;
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
				mBorderColor.A = mAniAlpha * 255;
				break;
			}
		case AniType_MouseLeave:
			{
				mAniAlpha -= 0.001f * tick;
				if(mAniAlpha <= 0.5f)
				{
					mAniAlpha = 0.5f;
					mAniState = AniType_None;
				}
				mBorderColor.A = mAniAlpha * 255;
				break;
			}
		}
	}
}