#include "ScenePage.h"
#include "DlgTerInfo.h"
#include "Editor.h"
#include "sceneview/TerView.h"
#include "sceneview/EntityView.h"
#include "rescenter.h"

namespace editor
{
	ScenePage::ScenePage()
	{

	}

	void ScenePage::InitUI( ITabPage* page )
	{
		__super::InitUI(page);

		Editor::Singleton()->OnLevelOpen().Add(this, &ScenePage::OnOpenLevel);

		IUiManager* uiMgr = page->GetUiMgr();
		mToolBar = uiMgr->CreateToolBar(page);
		mToolBar->SetSize(page->GetSize().width, 25);

		IToolBarItem* toolItem = mToolBar->AddToolItem(_T("打开场景"));
		toolItem->SetBackImage(TheEngine()->GetResMgr()->LoadTexture(_T("../media/open.png")));
		toolItem->OnClick().Add(this, &ScenePage::OnOpenClick);

		toolItem = mToolBar->AddToolItem(_T("新建场景"));
		toolItem->SetBackImage(TheEngine()->GetResMgr()->LoadTexture(_T("../media/new.png")));
		toolItem->OnClick().Add(this, &ScenePage::OnNewClick);

		toolItem = mToolBar->AddToolItem(_T("保存场景"));
		toolItem->SetBackImage(TheEngine()->GetResMgr()->LoadTexture(_T("../media/save.png")));

		mTabCtrl = uiMgr->CreateTabCtrl(page);
		mTabCtrl->SetSize(page->GetSize().width, page->GetSize().height - 25);
		mTabCtrl->SetPos(0, 25);
		mCurView = new TerView;
		RegestView(mCurView);
		RegestView(new EntityView);

		mDlgTerInfo = new DlgTerInfo;
		mDlgTerInfo->Init(uiMgr);
	}

	bool ScenePage::OnNewClick( IControl* pCtrl)
	{
		mDlgTerInfo->ShowDlg();
		return true;
	}

	bool ScenePage::OnOpenClick( IControl* pCtrl )
	{
		Editor::Singleton()->GetResCenter()->OnResChoosed().Add(this, &ScenePage::OnResChoosed);
		Editor::Singleton()->GetResCenter()->ChooseRes( ResType::ResType_Terrain);
		return true;
	}
	
	void ScenePage::OnOpenLevel( ILevel* pLevel )
	{
		mRootNode->AttachObject(Editor::Singleton()->mTerObj);
	}

	/*void ScenePage::OnOpenTer( Resource ter )
	{
		mRootNode->AttachObject(Editor::Singleton()->mTerObj);
	}*/

	void ScenePage::RegestView( SceneView* pView )
	{
		pView->mPage = mTabCtrl->AddPage(pView->mName);
		pView->mPage->SetUserData((s32)pView);
		pView->InitUI(mPage->GetUiMgr(), mRootNode);
		mViews.push_back(pView);
	}

	void ScenePage::OnMouseMove( MouseEventArgs& e )
	{
		mCurView->OnMouseMove(e);
	}

	void ScenePage::OnMouseDown( MouseEventArgs& e )
	{
		mCurView->OnMouseDown(e);
	}

	void ScenePage::OnMouseUp( MouseEventArgs& e )
	{
		mCurView->OnMouseUp(e);
	}

	void ScenePage::OnResChoosed( Resource res )
	{
		//Editor::Singleton()->OpenTerrain(res);
	}

	bool ScenePage::OnSaveClick( IControl* pCtrl )
	{

		return true;
	}


}