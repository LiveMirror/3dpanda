#include "DlgCameraSet.h"
#include "Editor.h"

namespace editor
{
	DlgCameraSet::DlgCameraSet( void )
	{

	}

	void DlgCameraSet::InitUI( IUiManager* uiMgr )
	{
		mDlg = uiMgr->CreateDialogs();
		mDlg->SetSize(300, 220);
		mDlg->SetText(_T("摄像机设置"));
		s32 x = uiMgr->GetWidth() - mDlg->GetSize().width;
		s32 y = uiMgr->GetHeight() - mDlg->GetSize().height;
		mDlg->SetPos(x / 2, y / 2);
		mDlg->SetVisible(false);

		y = 15;
		ILabel* lb = uiMgr->CreateLabel(mDlg);
		lb->SetText(_T("鼠标移动步进"));
		lb->SetPos(10, y);

		mLbMove = uiMgr->CreateLabel(mDlg);
		mLbMove->SetText(_T("100"));
		mLbMove->SetPos(mDlg->GetSize().width - mLbMove->GetSize().width - 10, y);

		y += 30;
		mMoveStep = uiMgr->CreateSliderBar(mDlg);
		mMoveStep->SetSize(mDlg->GetSize().width - 20, 10);
		mMoveStep->SetMaximum(499);
		mMoveStep->SetValue(99);
		mMoveStep->SetPos(10, y);
		mMoveStep->OnValueChanged().Add(this, &DlgCameraSet::OnMoveChange);

		y += 30;
		lb = uiMgr->CreateLabel(mDlg);
		lb->SetText(_T("鼠标滚轮步进"));
		lb->SetPos(10, y);

		mLbWheel = uiMgr->CreateLabel(mDlg);
		mLbWheel->SetText(_T("100"));
		mLbWheel->SetPos(mDlg->GetSize().width - mLbMove->GetSize().width - 10, y);

		y += 30;
		mWheelStep = uiMgr->CreateSliderBar(mDlg);
		mWheelStep->SetSize(mDlg->GetSize().width - 20, 10);
		mWheelStep->SetMaximum(499);
		mWheelStep->SetValue(99);
		mWheelStep->SetPos(10, y);
		mWheelStep->OnValueChanged().Add(this, &DlgCameraSet::OnWheelChange);

		y += 30;
		lb = uiMgr->CreateLabel(mDlg);
		lb->SetText(_T("摄像机旋转步进"));
		lb->SetPos(10, y);

		mLbRotate = uiMgr->CreateLabel(mDlg);
		mLbRotate->SetText(_T("10"));
		mLbRotate->SetPos(mDlg->GetSize().width - mLbMove->GetSize().width - 10, y);

		y += 30;
		mRotateStep = uiMgr->CreateSliderBar(mDlg);
		mRotateStep->SetSize(mDlg->GetSize().width - 20, 10);
		mRotateStep->SetMaximum(179);
		mRotateStep->SetValue(9);
		mRotateStep->SetPos(10, y);
		mRotateStep->OnValueChanged().Add(this, &DlgCameraSet::OnRotateChange);
	}

	void DlgCameraSet::ShowDlg( void )
	{
		mDlg->DoMode();
	}

	bool DlgCameraSet::OnMoveChange( IControl* pCtrl )
	{
		tstring str;
		StringUtils::S32ToStr(mMoveStep->GetValue() + 1, str);
		mLbMove->SetText(str);
		mLbMove->SetPos(mDlg->GetSize().width - mLbMove->GetSize().width - 10, mLbMove->GetPos().y);
		Editor::Singleton()->GetCameraConfig().moveStep = mMoveStep->GetValue() + 1;
		return true;
	}

	bool DlgCameraSet::OnWheelChange( IControl* pCtrl )
	{
		tstring str;
		StringUtils::S32ToStr(mWheelStep->GetValue() + 1, str);
		mLbWheel->SetText(str);
		mLbWheel->SetPos(mDlg->GetSize().width - mLbWheel->GetSize().width - 10, mLbWheel->GetPos().y);
		Editor::Singleton()->GetCameraConfig().wheelStep = mWheelStep->GetValue() + 1;
		return true;
	}

	bool DlgCameraSet::OnRotateChange( IControl* pCtrl )
	{
		tstring str;
		StringUtils::S32ToStr(mRotateStep->GetValue() + 1, str);
		mLbRotate->SetText(str);
		mLbRotate->SetPos(mDlg->GetSize().width - mLbRotate->GetSize().width - 10, mLbRotate->GetPos().y);
		Editor::Singleton()->GetCameraConfig().rotateStep = mRotateStep->GetValue() + 1;
		return true;
	}
}