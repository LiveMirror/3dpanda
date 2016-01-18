#include "DlgEvnSet.h"
#include "Editor.h"

namespace editor
{
	DlgEvnSet::DlgEvnSet( void )
	{

	}

	void DlgEvnSet::InitUI( IUiManager* uiMgr )
	{
		mDlg = uiMgr->CreateDialogs();
		mDlg->SetSize(300, 220);
		mDlg->SetText(_T("参数设置"));
		s32 x = uiMgr->GetWidth() - mDlg->GetSize().width;
		s32 y = uiMgr->GetHeight() - mDlg->GetSize().height;
		mDlg->SetPos(x / 2, y / 2);
		mDlg->SetVisible(false);

		y = 10;
		s32 offsetX1 = 10;
		s32 offsetX2 = 90;
		mCbLight = uiMgr->CreateCheckBox(mDlg);
		mCbLight->SetText(_T("启用灯光"));
		mCbLight->SetPos(offsetX1, y);

		y += 30;
		ILabel* lb = uiMgr->CreateLabel(mDlg);
		lb->SetText(_T("融合时间"));
		lb->SetPos(offsetX1, y);
		mTbBlendTime = uiMgr->CreateTextBox(mDlg);
		mTbBlendTime->SetPos(offsetX2, y);
		mTbBlendTime->SetSize(50, 25);
		mTbBlendTime->SetText(_T("0.5"));

		IButton* btn = uiMgr->CreateButton(mDlg);
		btn->SetText(_T("确定"));
		btn->SetPos(mTbBlendTime->GetPos().x + mTbBlendTime->GetSize().width + 10, y);
		btn->SetSize(50, 25);
		btn->OnClick().Add(this, &DlgEvnSet::OnBtnBlendTimeClick);

		y += 30;
		lb = uiMgr->CreateLabel(mDlg);
		lb->SetText(_T("景深"));
		lb->SetPos(offsetX1, y);

		mLbDepth = uiMgr->CreateLabel(mDlg);
		mLbDepth->SetText(_T("10"));
		mLbDepth->SetPos(mDlg->GetSize().width - mLbDepth->GetSize().width - 10, y);

		y += 30;
		mSbDepth = uiMgr->CreateSliderBar(mDlg);
		mSbDepth->SetSize(mDlg->GetSize().width - 20, 10);
		mSbDepth->SetMaximum(179);
		mSbDepth->SetValue(9);
		mSbDepth->SetPos(10, y);
		//mSbDepth->OnValueChanged().Add(this, &DlgCameraSet::OnRotateChange);
	}

	void DlgEvnSet::ShowDlg( void )
	{
		mDlg->DoMode();
	}

	bool DlgEvnSet::OnBtnBlendTimeClick( IControl* pCtrl )
	{
		Editor::Singleton()->mEvnConfig.blendTime = StringUtils::StrToF32(mTbBlendTime->GetText().c_str());
		mDlg->CloseDlg();
		return true;
	}
}