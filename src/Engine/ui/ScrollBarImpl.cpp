#include "ScrollBarImpl.h"
#include "renderSystem/IGraph2D.h"

namespace panda
{
	enum AniType
	{
		AniType_None,
		AniType_MouseEnter,
		AniType_MouseLeave,
	};

	ScrollBarImpl::ScrollBarImpl( void )
		:mMaximun(200),
		mValue(0),
		mMouseOn(false),
		mAniAlpha(0),
		mMouseDown(false),
		mBarHeight(10),
		mWheelStep(2)
	{
		mRect.size = Size(10, 100);
		mBorderColor.A = 0;
		mCurPosY = 0;
	}

	void ScrollBarImpl::SetMaximun( s32 v )
	{
		mMaximun = v;
		_UpdateBarHeight();
	}

	void ScrollBarImpl::SetValue( s32 v )
	{
		mValue = v;
		if (mValue < 0)
		{
			mValue = 0;
		}
		else if (mValue > mMaximun - mRect.size.height)
		{
			mValue = mMaximun - mRect.size.height;
		}
		_UpdateBarPos();
	}

	void ScrollBarImpl::OnRender( IGraph2D* graph )
	{
		Color temp = mBorderColor;
		if(mMouseOn)
		{
			temp.A *= 0.5f;
			graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, mBorderColor, 2);
		}
		temp.A = (mAniAlpha + 0.5f) * 255;
		graph->FillRect(2, mCurPosY + 2, mRect.size.width - 4, mBarHeight, temp);
	}

	void ScrollBarImpl::OnMouseEnter()
	{
		mMouseOn = true;
		mAniState = AniType_MouseEnter;
	}

	void ScrollBarImpl::OnMouseLevae()
	{
		mMouseOn = false;
		if(mAniState == AniType_None)
		{
			mAniState = AniType_MouseLeave;
		}
	}


	void ScrollBarImpl::Update( s32 tick )
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
				if(mAniAlpha >= 0.5f)
				{
					mAniAlpha = 0.5f;
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
				if(mAniAlpha <= 0)
				{
					mAniAlpha = 0;
					mAniState = AniType_None;
				}
				mBorderColor.A = mAniAlpha * 255;
				break;
			}
		}

	}

	void ScrollBarImpl::OnMouseMove( MouseEventArgs& e )
	{
		if(mMouseDown)
		{
			mCurPosY += (e.y - mMouseDownY);
			if(mCurPosY < 0)
			{
				mCurPosY = 0;
				_UpdateValue();
				return;
			}
			else if(mCurPosY > mMaxPosY)
			{
				mCurPosY = mMaxPosY;
				_UpdateValue();
				return;
			}
			_UpdateValue();
			mMouseDownY = e.y;
		}
	}

	void ScrollBarImpl::OnMouseDown( MouseEventArgs& e )
	{
		__super::OnMouseDown(e);
		mMouseDown = true;
		mMouseDownY = e.y;
	}

	void ScrollBarImpl::OnMouseUp( MouseEventArgs& e )
	{
		__super::OnMouseUp(e);
		mMouseDown = false;
	}

	void ScrollBarImpl::OnMouseWheel( MouseEventArgs& e )
	{
		__super::OnMouseWheel(e);
		if(e.delta > 0)
		{
			if(mCurPosY > 0)
			{
				mCurPosY -= mWheelStep;
				if(mCurPosY < 0)
				{
					mCurPosY = 0;
				}
				_UpdateValue();
			}
		}
		else
		{
			if(mCurPosY < mMaxPosY)
			{
				mCurPosY += mWheelStep;
				if(mCurPosY > mMaxPosY)
				{
					mCurPosY = mMaxPosY;
				}
				_UpdateValue();
			}
		}

	}

	void ScrollBarImpl::SetSize( s32 width, s32 height )
	{
		__super::SetSize(width, height);
		_UpdateBarHeight();
	}

	void ScrollBarImpl::_UpdateBarHeight( void )
	{
		if(mRect.size.height > mMaximun)
		{
			mMaximun = mRect.size.height;
		}
		mBarHeight = mRect.size.height * mRect.size.height / mMaximun;
		mMaxPosY = mRect.size.height - mBarHeight;
		mBarHeight -= 4;
	}

	void ScrollBarImpl::_UpdateBarPos( void )
	{
		mCurPosY = mValue * mRect.size.height / mMaximun;
	}

	void ScrollBarImpl::_UpdateValue( void )
	{
		mValue = mCurPosY * mMaximun / mRect.size.height;
		mOnValueChange(mThis, 0, 0);
	}


}