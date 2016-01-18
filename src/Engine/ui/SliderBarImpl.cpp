#include "SliderBarImpl.h"
#include "renderSystem/IGraph2D.h"
#include "SliderBarTag.h"

namespace panda
{
	SliderBarImpl::SliderBarImpl( void )
		:mMaximun(100),
		mValue(0),
		mDropValue(false),
		mBarWidth(20)
	{
		mBackColor = 0xff254e85;
		mRect.size = Size(200, 10);
		mDrawBorder = false;
		_updateInfo();
	}

	void SliderBarImpl::OnRender( IGraph2D* graph )
	{
		s32 x = mValue * mPerWidth;
		s32 h = mRect.size.height;
		graph->FillRect(0, 1, mRect.size.width, h - 2, 0x5f000000);
		graph->DrawRect(0, 1, mRect.size.width, h - 2, 0x5f565656);

		_DrawTags(graph);

		if(mEnable)
		{
			graph->FillRect(x, 0 , mBarWidth, h, mBackColor);
			graph->DrawRect(x, 0 , mBarWidth, h, mBorderColor);
		}
		else
		{
			graph->FillRect(x, 0 , mBarWidth, h, 0x5f565656);
			graph->DrawRect(x, 0 , mBarWidth, h, 0x8f565656);
		}
		
		if(mMouseOn)
		{
			Color temp = mBorderColor;
			temp.A *= 0.5f;
			graph->DrawRect(x, 0 , mBarWidth, h, temp, 2);
		}
	}

	void SliderBarImpl::SetMaximun( s32 v )
	{
		mMaximun = v;
		if(mValue > mMaximun)
		{
			mValue = mMaximun;
		}
		_updateInfo();
	}

	void SliderBarImpl::SetValue( s32 v )
	{
		if(v < 0)
		{
			v = 0;
		}
		else if(v > mMaximun)
		{
			v = mMaximun;
		}
		if(v == mValue)
		{
			return;
		}
		mValue = v;
	}

	void SliderBarImpl::_updateInfo( void )
	{
		mPerWidth = (float)(mRect.size.width - mBarWidth) / mMaximun;
	}

	void SliderBarImpl::OnMouseDown( MouseEventArgs& e )
	{
		__super::OnMouseDown(e);
		mMouseDownX = e.x;
		mDropValue = true;
	}

	void SliderBarImpl::OnMouseUp( MouseEventArgs& e )
	{
		__super::OnMouseUp(e);
		mDropValue = false;
	}

	void SliderBarImpl::OnMouseMove( MouseEventArgs& e )
	{
		if(mDropValue && e.button & MouseButtons::LButton)
		{
			s32 vw = e.x - mMouseDownX;
			if(math::absValue(vw) >= mPerWidth)
			{
				s32 v = vw / mPerWidth;
				s32 temp = mValue + v;
				if(temp < 0)
				{
					temp = 0;
				}
				else if(temp > mMaximun)
				{
					temp = mMaximun;
				}
				if(temp != mValue)
				{
					mValue = temp;
					mMouseDownX = mValue * mPerWidth + mBarWidth / 2;
					mOnValueChange(mThis);
				}
			}
		}
	}

	ISliderBarTag* SliderBarImpl::AddTag( s32 v, s32 userData )
	{
		SliderBarTag* tag = new SliderBarTag;
		tag->mUserData = userData;
		tag->mValue = v;
		/*TagList::iterator it = mTags.begin();
		while(it != mTags.end())
		{
			if((*it)->mValue > v)
			{
				mTags.insert(it, tag);
				return tag;
			}
			it++;
		}*/
		mTags.push_back(tag);
		return tag;
	}

	void SliderBarImpl::_DrawTags( IGraph2D* graph )
	{
		s32 x, y;
		SliderBarTag* tag;
		TagList::iterator it = mTags.begin();
		while(it != mTags.end())
		{
			tag = *it;
			
			x = tag->mValue * mRect.size.width / mMaximun;
			x -= 2;
			graph->FillRect(x, 0, 5, mRect.size.height, tag->mColor);
			it++;
		}
	}

	void SliderBarImpl::ClearTags( void )
	{
		TagList::iterator it = mTags.begin();
		while(it != mTags.end())
		{
			delete *it;
			it++;
		}
		mTags.clear();
	}
}