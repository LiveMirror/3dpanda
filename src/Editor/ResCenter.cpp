#include "ResCenter.h"
#include "DlgChooseRes.h"

namespace editor
{
	ResCenter::ResCenter( void )
	{

	}

	void ResCenter::InitUI( IUiManager* uiMgr )
	{
		mDlgChoose = new DlgChooseRes;
		mDlgChoose->Init(uiMgr);
	}

	EventRes& ResCenter::OnResChoosed()
	{
		mDlgChoose->mOnResChoosed.RemoveAll();
		return mDlgChoose->mOnResChoosed;
	}

	void ResCenter::ChooseRes( s32 filter/* = -1 */)
	{
		mDlgChoose->ShowDlg(filter);
	}
}