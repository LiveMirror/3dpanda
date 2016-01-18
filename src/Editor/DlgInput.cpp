#include "DlgInput.h"

namespace editor
{
	DlgInput::DlgInput( void )
	{
		
	}

	void DlgInput::SetTitle( const tstring& title )
	{
		mDlg->SetText(title);
	}

	EventString& DlgInput::OnInputText( void )
	{
		mOnInputText.RemoveAll();
		return mOnInputText;
	}

	void DlgInput::InitUI( IUiManager* uiMgr )
	{
		mDlg = uiMgr->CreateDialogs();
		mDlg->SetSize(300, 110);
		mDlg->SetText(_T("Input string"));
		s32 x = uiMgr->GetWidth() - mDlg->GetSize().width;
		s32 y = uiMgr->GetHeight() - mDlg->GetSize().height;
		mDlg->SetPos(x / 2 - 50, y / 2);
		mDlg->SetVisible(false);

		y = 10;
		mTbInput = uiMgr->CreateTextBox(mDlg);
		mTbInput->SetPos(10, y);
		mTbInput->SetSize(mDlg->GetSize().width - 20, 25);

		y += 35;
		IButton* btn = uiMgr->CreateButton(mDlg);
		btn->SetPos((mDlg->GetSize().width - btn->GetSize().width) / 2, y);
		btn->SetText(_T("È·¶¨"));
		btn->OnClick().Add(this, &DlgInput::OnOkClick);

	}

	void DlgInput::ShowDlg( void )
	{
		mTbInput->SetText(_T(""));
		mDlg->DoMode();
	}

	void DlgInput::ShowDlg( const tstring& text )
	{
		mTbInput->SetText(text);
		mDlg->DoMode();
	}

	bool DlgInput::OnOkClick( IControl* pCtrl )
	{
		if(!mTbInput->GetText().empty())
		{
			mOnInputText(mTbInput->GetText());
			mDlg->CloseDlg();
		}
		return true;
	}
}
