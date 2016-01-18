#include "EntityView.h"

namespace editor
{
	EntityView::EntityView( void )
	{
		mName = _T("³¡¾°Îï¼þ");
	}

	void EntityView::InitUI( IUiManager* uiMgr, ISceneNode* pNode )
	{
		IFoldPanel* panel = uiMgr->CreateFoldPanel(mPage);
		panel->SetSize(mPage->GetSize().width, mPage->GetSize().height);

		IFoldPage* page = panel->AddPage(_T("Test1"));
		IButton* btn = uiMgr->CreateButton(page);
		btn->SetPos(20, 20);
		page = panel->AddPage(_T("Test2"));
		btn = uiMgr->CreateButton(page);
		btn->SetPos(20, 20);
		page = panel->AddPage(_T("Test3"));
		btn = uiMgr->CreateButton(page);
		btn->SetPos(20, 20);
		btn = uiMgr->CreateButton(page);
		btn->SetPos(20, 520);
	}
}