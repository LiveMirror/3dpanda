#include "DlgBlendMat.h"
#include "../Editor.h"
#include "../ResCenter.h"
#include "TerView.h"

namespace editor
{
	void DlgBlendMat::Init( IUiManager* uiMgr )
	{
		mDlg = uiMgr->CreateDialogs();
		mDlg->SetSize(300, 250);
		mDlg->SetText(_T("融合纹理"));
		s32 x = uiMgr->GetWidth() - mDlg->GetSize().width;
		s32 y = uiMgr->GetHeight() - mDlg->GetSize().height;
		mDlg->SetPos(x / 2, y / 2);
		mDlg->SetVisible(false);

		x = 10;
		y = 10;
		ILabel* lb = uiMgr->CreateLabel(mDlg);
		lb->SetText(_T("纹理:"));
		lb->SetPos(x, y);

		x += lb->GetSize().width + 10;
		mPbImage = uiMgr->CreatePictureBox(mDlg);
		mPbImage->SetPos(x, y);
		mPbImage->SetSize(86, 86);
		mPbImage->SetDrawBorder(true);

		x += mPbImage->GetSize().width + 10;
		IButton* btn = uiMgr->CreateButton(mDlg);
		btn->SetPos(x, y);
		btn->SetSize(30, 20);
		btn->SetText(_T("..."));
		btn->OnClick().Add(this, &DlgBlendMat::OnTexClick);

		x = 10;
		y += 100;
		lb = uiMgr->CreateLabel(mDlg);
		lb->SetText(_T("缩放:"));
		lb->SetPos(x, y);

		x += lb->GetSize().width + 10;
		mTbSclae = uiMgr->CreateTextBox(mDlg);
		mTbSclae->SetText(_T("10"));
		mTbSclae->SetPos(x, y);
		mTbSclae->SetSize(50, 25);

		y = mDlg->GetSize().height - 60;
		x = mDlg->GetSize().width - 145;
		btn = uiMgr->CreateButton(mDlg);
		btn->SetPos(x, y);
		btn->SetSize(60, 25);
		btn->SetText(_T("确定"));
		btn->OnClick().Add(this, &DlgBlendMat::OnOkClick);

		x += 70;
		btn = uiMgr->CreateButton(mDlg);
		btn->SetPos(x, y);
		btn->SetSize(60, 25);
		btn->SetText(_T("取消"));
		btn->OnClick().Add(this, &DlgBlendMat::OnCancelClick);
	}

	void DlgBlendMat::ShowDlg( void )
	{
		mDlg->DoMode();
	}

	bool DlgBlendMat::OnOkClick( IControl* pCtrl )
	{
		Editor* ptr = Editor::Singleton();
		if(mEditor)
		{
			ptr->mLevel->GetMaterial()->SetTexture(mCurIndex, mPbImage->GetBackImage());
		}
		else
		{
			ptr->mLevel->GetMaterial()->AddTexture(mPbImage->GetBackImage());
		}
		f32 scale = StringUtils::StrToF32(mTbSclae->GetText().c_str());
		ptr->mLevel->GetMaterial()->SetTextureScale(mCurIndex, scale);
		mCreater->RefreshMat();
		mDlg->CloseDlg();
		return true;
	}

	bool DlgBlendMat::OnCancelClick( IControl* pCtrl )
	{
		mDlg->CloseDlg();
		return true;
	}

	bool DlgBlendMat::OnTexClick( IControl* pCtrl )
	{
		Editor::Singleton()->GetResCenter()->OnResChoosed().Add(this, &DlgBlendMat::OnTextureChoosed);
		Editor::Singleton()->GetResCenter()->ChooseRes(ResType::ResType_Texure);
		return true;
	}

	void DlgBlendMat::OnTextureChoosed( Resource res )
	{
		mPbImage->SetBackImage(res);
	}
}