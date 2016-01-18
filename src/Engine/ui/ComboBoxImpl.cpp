#include "ComboBoxImpl.h"
#include "renderSystem/IGraph2D.h"
#include "ui/ICombobox.h"
#include "ui/IListBox.h"
#include "ui/IScrollBar.h"
#include "uiManager.h"
#include "ListBoxImpl.h"


namespace panda
{
	ComboBoxImpl::ComboBoxImpl(void)
		:mMouseOn(false),
		mListBox(NULL),
		mSelItem(NULL),
		mNumOfShow(5)
	{
		mRect.size = Size(100, 25);
		mBackColor.A = 200;
	}

	void ComboBoxImpl::OnRender( IGraph2D* graph )
	{
		if(mBackColor.A > 0)
		{
			graph->FillRect(0, 0, mRect.size.width, mRect.size.height, mBackColor);
		}

		s32 y = mRect.size.height / 3;
		graph->DrawLine(mRect.size.width - 11, y, mRect.size.width - 5, y + 1, mBorderColor);
		graph->DrawLine(mRect.size.width - 11, y, mRect.size.width - 8, y * 2 - 1, mBorderColor);
		graph->DrawLine(mRect.size.width - 5, y, mRect.size.width - 8, y * 2 - 1, mBorderColor);

		if(NULL != mSelItem)
		{
			graph->DrawString(mFont, 2, 0, mRect.size.width, mRect.size.height, mSelItem->GetText(), mTextColor, FontFormat::VCENTER);
		}

		if(mMouseOn)
		{
			Color temp = mBorderColor;
			temp.A /= 2;
			graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, temp, 2);
		}
	}

	void ComboBoxImpl::OnBindUiMgr( uiManager* uiMgr )
	{
		__super::OnBindUiMgr(uiMgr);
		mListBox = new IListBox;
		mListBox->mImpl->mFont = mFont;
		mListBox->mImpl->mUiMgr = uiMgr;
		mListBox->SetSize(mRect.size.width, 25);
		mListBox->OnSelectedChange().Add(this, &ComboBoxImpl::OnSelectedChange);
		mListBox->OnMouseDown().Add(this, &ComboBoxImpl::OnListMouseDown);
	}

	IListBoxItem* ComboBoxImpl::AddItem( const tstring& text )
	{
		IListBoxItem* item = mListBox->AddItem(text);
		ResizeListCtrl();
		return item;
	}

	void ComboBoxImpl::OnMouseEnter()
	{
		mMouseOn = true;
	}

	void ComboBoxImpl::OnMouseLevae()
	{
		mMouseOn = false;
	}

	void ComboBoxImpl::OnMouseDown( MouseEventArgs& e )
	{
		__super::OnMouseDown(e);
		if(mListBox->GetItemNum() > 0)
		{
			Vector2Dn p = PointToScreen(0, 0);
			p.y += mRect.size.height;
			mListBox->SetPos(p);
			mUiMgr->SetPopUpCtrl(mListBox);
		}
	}

	bool ComboBoxImpl::OnSelectedChange( IControl* pCtrl)
	{
		IListBoxItem* item = mListBox->GetSelItem();
		if(item == mSelItem)
		{
			return true;
		}
		mSelItem = item;
		if(NULL != mSelItem)
		{
			mText = mSelItem->GetText();
			mOnSelChange(mThis);
		}
		return true;
	}

	bool ComboBoxImpl::OnListMouseDown( IControl* pCtrl, MouseEventArgs& e )
	{
		mUiMgr->SetPopUpCtrl(NULL);
		return true;
	}

	void ComboBoxImpl::Clear( void )
	{
		mListBox->Clear();
		mText = _T("");
		mSelItem = NULL;
		ResizeListCtrl();
	}

	void ComboBoxImpl::SetNumOfShow( u32 num )
	{
		if(mNumOfShow == num)
		{
			return;
		}
		mNumOfShow = num;
		ResizeListCtrl();
	}

	void ComboBoxImpl::ResizeListCtrl( void )
	{
		if(mListBox->GetItemNum() > mNumOfShow)
		{
			mListBox->SetSize(mRect.size.width, 25 * mNumOfShow);
		}
		else
		{
			mListBox->SetSize(mRect.size.width, 25 * mListBox->GetItemNum());
		}
	}

	void ComboBoxImpl::SetSize( s32 width, s32 height )
	{
		__super::SetSize(width, height);
		mListBox->SetSize(width, mListBox->GetSize().height);
	}

	void ComboBoxImpl::SetSelItem( s32 index )
	{
		SetSelItem(mListBox->GetItem(index));
	}

	void ComboBoxImpl::SetSelItem( IListBoxItem* item )
	{
		mSelItem = item;
		if(NULL != mSelItem)
		{
			mText = mSelItem->GetText();
		}
	}

	void ComboBoxImpl::OnMouseWheel( MouseEventArgs& e )
	{
		mListBox->mImpl->OnMouseWheel(e);
	}
}