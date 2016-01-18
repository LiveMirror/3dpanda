#include "DlgTerInfo.h"
#include "Editor.h"
#include "ResCenter.h"
#include "ILevel.h"

namespace editor
{
	void DlgTerInfo::Init(IUiManager* uiMgr)
	{
		mDlgNewTer = uiMgr->CreateDialogs();
		mDlgNewTer->SetSize(300, 250);
		mDlgNewTer->SetText(_T("地形信息"));
		s32 x = uiMgr->GetWidth() - mDlgNewTer->GetSize().width;
		s32 y = uiMgr->GetHeight() - mDlgNewTer->GetSize().height;
		mDlgNewTer->SetPos(x / 2, y / 2);
		mDlgNewTer->SetVisible(false);

		x = 10;
		y = 10;
		ILabel* lb = uiMgr->CreateLabel(mDlgNewTer);
		lb->SetText(_T("宽:"));
		lb->SetPos(x, y);

		x += lb->GetSize().width + 10;
		mTbWidth = uiMgr->CreateTextBox(mDlgNewTer);
		mTbWidth->SetText(_T("256"));
		mTbWidth->SetPos(x, y);
		mTbWidth->SetSize(50, 25);

		x += mTbWidth->GetSize().width + 30;
		lb = uiMgr->CreateLabel(mDlgNewTer);
		lb->SetText(_T("高:"));
		lb->SetPos(x, y);

		x += lb->GetSize().width + 10;
		mTbHeight = uiMgr->CreateTextBox(mDlgNewTer);
		mTbHeight->SetText(_T("256"));
		mTbHeight->SetPos(x, y);
		mTbHeight->SetSize(50, 25);

		x = 10;
		y += 40;
		lb = uiMgr->CreateLabel(mDlgNewTer);
		lb->SetText(_T("网格大小:"));
		lb->SetPos(x, y);

		x += lb->GetSize().width + 10;
		mTbTileSize = uiMgr->CreateTextBox(mDlgNewTer);
		mTbTileSize->SetText(_T("20"));
		mTbTileSize->SetPos(x, y);
		mTbTileSize->SetSize(50, 25);

		x = 10;
		y += 40;
		lb = uiMgr->CreateLabel(mDlgNewTer);
		lb->SetText(_T("纹理:"));
		lb->SetPos(10, y);

		x += lb->GetSize().width + 10;
		mPbImage = uiMgr->CreatePictureBox(mDlgNewTer);
		mPbImage->SetPos(x, y);
		mPbImage->SetSize(64, 64);
		mPbImage->SetDrawBorder(true);

		x += mPbImage->GetSize().width + 10;
		IButton* btn = uiMgr->CreateButton(mDlgNewTer);
		btn->SetPos(x, y);
		btn->SetSize(30, 20);
		btn->SetText(_T("..."));
		btn->OnClick().Add(this, &DlgTerInfo::OnTexClick);

		x += btn->GetSize().width + 30;
		lb = uiMgr->CreateLabel(mDlgNewTer);
		lb->SetText(_T("缩放:"));
		lb->SetPos(x, y);

		x += lb->GetSize().width + 10;
		mTbSclae = uiMgr->CreateTextBox(mDlgNewTer);
		mTbSclae->SetText(_T("10"));
		mTbSclae->SetPos(x, y);
		mTbSclae->SetSize(50, 25);

		y += 80;
		x = 50;
		btn = uiMgr->CreateButton(mDlgNewTer);
		btn->SetPos(x, y);
		btn->SetSize(80, 25);
		btn->SetText(_T("确定"));
		btn->OnClick().Add(this, &DlgTerInfo::OnOkClick);

		x += 100;
		btn = uiMgr->CreateButton(mDlgNewTer);
		btn->SetPos(x, y);
		btn->SetSize(80, 25);
		btn->SetText(_T("取消"));
		btn->OnClick().Add(this, &DlgTerInfo::OnCancelClick);
	}
	
	void DlgTerInfo::ShowDlg()
	{
		mDlgNewTer->DoMode();
	}

	bool DlgTerInfo::OnOkClick( IControl* pCtrl )
	{
		s32 width = StringUtils::StrToS32(mTbWidth->GetText().c_str());
		s32 height = StringUtils::StrToS32(mTbHeight->GetText().c_str());
		f32 tileSize = StringUtils::StrToF32(mTbTileSize->GetText().c_str());
		f32 sclae = StringUtils::StrToF32(mTbSclae->GetText().c_str());

		ILevel* pLevel = Editor::Singleton()->mGame->CreateLevel(width, height, tileSize);
		if(!mPbImage->GetBackImage().IsNull())
		{
			pLevel->GetMaterial()->SetDiffuseTex(mPbImage->GetBackImage());
		}
		pLevel->GetMaterial()->SetDiffuseScale(sclae);
		Editor::Singleton()->OpenLevel(pLevel);

		mDlgNewTer->CloseDlg();
		return true;
	}

	bool DlgTerInfo::OnCancelClick( IControl* pCtrl )
	{
		mDlgNewTer->CloseDlg();
		return true;
	}

	bool DlgTerInfo::OnTexClick( IControl* pCtrl )
	{
		Editor::Singleton()->GetResCenter()->OnResChoosed().Add(this, &DlgTerInfo::OnTextureChoosed);
		Editor::Singleton()->GetResCenter()->ChooseRes(ResType::ResType_Texure);
		return true;
	}

	void DlgTerInfo::OnTextureChoosed( Resource res )
	{
		mPbImage->SetBackImage(res);
	}
}