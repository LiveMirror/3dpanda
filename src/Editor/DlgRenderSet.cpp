#include "DlgRenderSet.h"

namespace editor
{
	DlgRenderSet::DlgRenderSet( void )
	{

	}

	void DlgRenderSet::InitUI( IUiManager* uiMgr )
	{
		mDlg = uiMgr->CreateDialogs();
		mDlg->SetSize(300, 220);
		mDlg->SetText(_T("äÖÈ¾ÉèÖÃ"));
		s32 x = uiMgr->GetWidth() - mDlg->GetSize().width;
		s32 y = uiMgr->GetHeight() - mDlg->GetSize().height;
		mDlg->SetPos(x / 2, y / 2);
		mDlg->SetVisible(false);

		y = 10;
		s32 offsetX1 = 10;
		s32 offsetX2 = 90;

		IListBox* ppBox = uiMgr->CreateListBox(mDlg);
		ppBox->AddItem(_T("downFilter4"));
		ppBox->AddItem(_T("bloomH"));
		ppBox->AddItem(_T("bloomV"));
		ppBox->AddItem(_T("combine4"));
		ppBox->AddItem(_T("normalEdge"));
		ppBox->SetPos(offsetX1, y);
		ppBox->SetSize(120, mDlg->GetSize().height - 45);

		mLbEffects  = uiMgr->CreateListBox(mDlg);
		mLbEffects->SetSize(120, mDlg->GetSize().height - 45);
		mLbEffects->SetPos(mDlg->GetSize().width - 10 - ppBox->GetSize().width, y);

		y += ppBox->GetSize().height / 2 - 10;
		ILabel* lb = uiMgr->CreateLabel(mDlg);
		lb->SetText(_T("=>"));
		lb->SetPos(ppBox->GetSize().width + offsetX1 + 10, y);

	}

	void DlgRenderSet::ShowDlg( void )
	{
		mDlg->DoMode();
	}
}