#include "TextBoxImpl.h"
#include "renderSystem/IGraph2D.h"
#include "ui/ifont.h"

namespace panda
{
	TextBoxImpl::TextBoxImpl( void )
		:mDrawCursor(true),
		mAniTime(0),
		mCursorPos(2),
		mCursorIndex(0),
		mSelectBegin(0),
		mSelectEnd(0),
		mPassWord(false),
		mMouseDown(false)
	{

	}

	void TextBoxImpl::OnRender( IGraph2D* graph )
	{
		if(mBackColor.A > 0)
		{
			graph->FillRect(0, 0, mRect.size.width, mRect.size.height, mBackColor);
		}

		if(mIsFocus && mDrawCursor)
		{
			graph->DrawLine(mCursorPos, 2, mCursorPos, mRect.size.height - 4, 0xffaFffFF);
		}

		if(mSelectBegin != mSelectEnd)
		{
			graph->FillRect(mSelectBeginPos, 1, mSelectEndPos - mSelectBeginPos, mRect.size.height - 2, 0x3fFFffFF);
		}

		if(!mText.empty())
		{
			graph->DrawString(mFont, 1, 0, mRect.size.width, mRect.size.height, mText, mTextColor, FontFormat::LEFT | FontFormat::VCENTER);
		}

		if(mMouseOn)
		{
			Color temp = mBorderColor;
			temp.A *= 0.5f;
			graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, temp, 2);
		}
	}

	void TextBoxImpl::Update( s32 tick )
	{
		mAniTime += tick;
		if(mDrawCursor)
		{
			if(mAniTime > 800)
			{
				mAniTime = 0;
				mDrawCursor = false;
			}
		}
		else
		{
			if(mAniTime > 500)
			{
				mAniTime = 0;
				mDrawCursor = true;
			}
		}
	}

	void TextBoxImpl::OnGotFocus( void )
	{
		mDrawCursor = true;
		mAniTime = 0;
	}

	void TextBoxImpl::OnLostFocus( void )
	{
		mDrawCursor = false;
	}

	void TextBoxImpl::OnKeyDown( KeyEventArgs& e )
	{
		IsInputKey(e.keyCode);
	}

	void TextBoxImpl::OnChar( s32 key )
	{
		if((key >= 32 && key <= 126)
			|| (key >= 0x4e00 && key <= 0x9fa5)
			|| (key >= 0x2E80 && key <= 0xA4CF)
			|| (key >= 0xFF00 && key <= 0xFFEF))	// È«½Ç
		{
			if(mSelectBegin != mSelectEnd)
			{
				mText.erase(mSelectBegin, mSelectEnd - mSelectBegin);
				mCursorIndex = mSelectBegin;
				mSelectEnd = mSelectBegin;
			}
			mText.insert(mCursorIndex, 1, (tchar)key);
			mCursorIndex++;
			OnTextChange();
			CalculateCursorPos();
		}
	}

	bool TextBoxImpl::IsInputKey( s32 key)
	{
		switch(key)
		{
		case VK_BACK:
			{
				if(mSelectBegin != mSelectEnd)
				{
					mText.erase(mSelectBegin, mSelectEnd - mSelectBegin);
					mCursorIndex = mSelectBegin;
					mSelectEnd = mSelectBegin;
					OnTextChange();
					CalculateCursorPos();
				}
				else if(mCursorIndex > 0)
				{
					mCursorIndex--;
					mText.erase(mCursorIndex, 1);
					OnTextChange();
					CalculateCursorPos();
				}
				return false;
			}
		case VK_DELETE:
			{
				if(mSelectBegin != mSelectEnd)
				{
					mText.erase(mSelectBegin, mSelectEnd - mSelectBegin);
					mCursorIndex = mSelectBegin;
					mSelectEnd = mSelectBegin;
					OnTextChange();
					CalculateCursorPos();
				}
				else if(mCursorIndex < mText.size())
				{
					mText.erase(mCursorIndex, 1);
					OnTextChange();
					CalculateCursorPos();
				}
				return false;
			}
		case VK_RIGHT:
			{
				if(mCursorIndex < mText.size())
				{
					mCursorIndex++;
					CalculateCursorPos();
				}
				return false;
			}
		case VK_LEFT:
			{
				if(mCursorIndex > 0)
				{
					mCursorIndex--;
					CalculateCursorPos();
				}
				return false;
			}
		case VK_HOME:
			{
				if(0 != mCursorIndex)
				{
					mCursorIndex = 0;
					CalculateCursorPos();
				}
				return false;
			}
		case VK_END:
			{
				if(mCursorIndex != mText.size())
				{
					mCursorIndex = mText.size();
					CalculateCursorPos();
				}
				return false;
			}
		case VK_SHIFT:
			{
				//mMouseDownIndex = mCursorIndex;
				return false;
			}
		case VK_RETURN:
		case VK_CONTROL:
			{
				return false;
			}
		}
		return true;
	}

	void TextBoxImpl::CalculateCursorPos( void )
	{
		Rect r;
		mFont->MeasureString(mText, r, mCursorIndex);
		mCursorPos = r.size.width + 1;
		mAniTime = 0;
		mDrawCursor = true;
	}

	void TextBoxImpl::OnMouseDown( MouseEventArgs& e )
	{
		__super::OnMouseDown(e);
		mSelectBegin = 0;
		mSelectEnd = 0;
		CalculateSelectPos();

		mMouseDown = true;
		s32 index = GetIndexFromPos(e.x, e.y);
		mMouseDownIndex = index;
		if(mCursorIndex != index)
		{
			mCursorIndex = index;
			CalculateCursorPos();
		}
	}

	panda::s32 TextBoxImpl::GetIndexFromPos( s32 x, s32 y )
	{
		s32 len = 0;
		Rect r;
		for(s32 i = 0; i < mText.size(); i++)
		{
			mFont->MeasureChar(mText[i], r);
			if(len + r.size.width > x)
			{
				return i;
			}
			len += r.size.width;
		}
		return mText.size();
	}

	void TextBoxImpl::OnMouseUp( MouseEventArgs& e )
	{
		mMouseDown = false;
	}

	void TextBoxImpl::OnMouseMove( MouseEventArgs& e )
	{
		if(e.button & MouseButtons::LButton)
		{
			s32 index = GetIndexFromPos(e.x, e.y);
			mSelectBegin = math::Min(index, mMouseDownIndex);
			mSelectEnd = math::Max(index, mMouseDownIndex);
			if(index != mCursorIndex)
			{
				mCursorIndex = index;
				CalculateCursorPos();
			}
			CalculateSelectPos();
		}
	}

	void TextBoxImpl::CalculateSelectPos( void )
	{
		if(mSelectBegin != mSelectEnd)
		{
			mSelectBeginPos = GetPosFromIndex(mSelectBegin);
			mSelectEndPos = GetPosFromIndex(mSelectEnd);
		}
	}

	s32 TextBoxImpl::GetPosFromIndex( s32 index )
	{
		Rect r;
		mFont->MeasureString(mText, r, index);
		return r.size.width;
	}

	void TextBoxImpl::OnTextChange( void )
	{

	}
}