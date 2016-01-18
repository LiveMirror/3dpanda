#include "FrameUI.h"
#include "ScenePage.h"
#include "PropertyPage.h"
#include "ResView/ResPage.h"
#include "Editor.h"
#include "DlgCameraSet.h"
#include "DlgEvnSet.h"
#include "DlgRenderSet.h"

namespace editor
{
	FrameUI::FrameUI( IUiManager* uiMgr, IPanda* engine)
		:mUiMgr(uiMgr),
		mEngine(engine),
		mSelectBtn(NULL),
		mOldPage(NULL)
	{
		
	}

	void FrameUI::InitUI( void )
	{
		mBackGround = mUiMgr->CreatePanel();
		mBackGround->SetSize(mUiMgr->GetWidth(), mUiMgr->GetHeight());
		mBackGround->SetBackColor(0x0);
		mBackGround->OnMouseMove().Add(this, &FrameUI::OnMouseMove);
		mBackGround->OnMouseDown().Add(this, &FrameUI::OnMouseDown);
		mBackGround->OnMouseUp().Add(this, &FrameUI::OnMouseUp);
		mBackGround->OnMouseWheel().Add(this, &FrameUI::OnMouseWheel);

		InitToolBar();
		InitTabCtrl();
	}

	void FrameUI::InitToolBar( void )
	{
		mDlgCameraSet = new DlgCameraSet;
		mDlgCameraSet->InitUI(mUiMgr);

		mDlgEvnSet = new DlgEvnSet;
		mDlgEvnSet->InitUI(mUiMgr);

		mDlgRenderSet = new DlgRenderSet;
		mDlgRenderSet->InitUI(mUiMgr);

		mToolBar = mUiMgr->CreateToolBar();
		mToolBar->SetSize(mUiMgr->GetWidth(), 25);

		IToolBarItem* toolItem = mToolBar->AddToolItem(_T(""), IToolBarItem::Separator);
		
		toolItem = mToolBar->AddToolItem(_T("新建"));
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/new.png")));

		toolItem = mToolBar->AddToolItem(_T("打开"));
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/open.png")));

		toolItem = mToolBar->AddToolItem(_T("保存"));
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/save.png")));

		mToolBar->AddToolItem(_T(""), IToolBarItem::Separator);

		IToolBarToggleButton* toggleBtn;
		toolItem = mToolBar->AddToolItem(_T("指针"), IToolBarItem::ToggleButton);
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/point.png")));
		toggleBtn = (IToolBarToggleButton*)toolItem;
		toggleBtn->OnSelectChanged().Add(this, &FrameUI::OnSelectedChanged);

		toolItem = mToolBar->AddToolItem(_T("移动"), IToolBarItem::ToggleButton);
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/move.png")));
		toggleBtn = (IToolBarToggleButton*)toolItem;
		toggleBtn->OnSelectChanged().Add(this, &FrameUI::OnSelectedChanged);

		toolItem = mToolBar->AddToolItem(_T("旋转"), IToolBarItem::ToggleButton);
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/rotation.png")));
		toggleBtn = (IToolBarToggleButton*)toolItem;
		toggleBtn->OnSelectChanged().Add(this, &FrameUI::OnSelectedChanged);

		toolItem = mToolBar->AddToolItem(_T("缩放"), IToolBarItem::ToggleButton);
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/scale.png")));
		toggleBtn = (IToolBarToggleButton*)toolItem;
		toggleBtn->OnSelectChanged().Add(this, &FrameUI::OnSelectedChanged);

		mToolBar->AddToolItem(_T(""), IToolBarItem::Separator);

		toolItem = mToolBar->AddToolItem(_T("网格显示"), IToolBarItem::ToggleButton);
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/grid.png")));
		toggleBtn = (IToolBarToggleButton*)toolItem;
		toggleBtn->OnSelectChanged().Add(this, &FrameUI::OnGridClick);

		toolItem = mToolBar->AddToolItem(_T("摄相机设置"));
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/camera.png")));
		toolItem->OnClick().Add(this, &FrameUI::OnCameraSetClick);

		toolItem = mToolBar->AddToolItem(_T("渲染设置"));
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/render.png")));
		toolItem->OnClick().Add(this, &FrameUI::OnRenderSetClick);

		toolItem = mToolBar->AddToolItem(_T("全局设置"));
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/EnvSet.png")));
		toolItem->OnClick().Add(this, &FrameUI::OnEvnSetClick);

		mToolBar->AddToolItem(_T(""), IToolBarItem::Separator);
		toolItem = mToolBar->AddToolItem(_T("帮助"));
		toolItem->SetBackImage(mEngine->GetResMgr()->LoadTexture(_T("../media/about.png")));
	}

	void FrameUI::InitTabCtrl( void )
	{
		mTabCtrl = mUiMgr->CreateTabCtrl();
		mTabCtrl->SetSize(250, mUiMgr->GetHeight() - 26);
		mTabCtrl->SetPos(mUiMgr->GetWidth() - mTabCtrl->GetSize().width - 1, 25);
		mTabCtrl->OnSelPageChanged().Add(this, &FrameUI::OnPageSelChanged);

		AddAttriPage(_T("资源"), new ResPage);
		AddAttriPage(_T("场景"), new ScenePage);
		AddAttriPage(_T("属性"), new PropertyPage);

		OnPageSelChanged(mTabCtrl);
	}

	bool FrameUI::OnSelectedChanged( IControl* pCtrl )
	{
		if(pCtrl == (IControl*)mSelectBtn)
		{
			mSelectBtn->SetSelected(true);
			return true;
		}
		if(NULL != mSelectBtn)
		{
			mSelectBtn->SetSelected(false);
		}
		mSelectBtn = (IToolBarToggleButton*)pCtrl;
		return true;
	}

	void FrameUI::AddAttriPage( const tstring& name, IAttrPage* page )
	{
		ITabPage* p = mTabCtrl->AddPage(name);
		page->SetNode(Editor::Singleton()->GetSceneMgr()->CreateNode());
		p->SetUserData((s32)page);
		page->InitUI(p);
	}

	bool FrameUI::OnPageSelChanged( IControl* pCtrl )
	{
		IAttrPage* oldMod = NULL;
		ITabPage* page = mTabCtrl->GetSelPage();
		IAttrPage* newMod = (IAttrPage*)page->GetUserData();
		if(NULL != mOldPage)
		{
			oldMod = (IAttrPage*)mOldPage->GetUserData();
			oldMod->mRootNode->SetVisible(false);
			oldMod->OnLostSelected(newMod);
		}
		mOldPage = page;
		newMod->OnSelected(oldMod);
		newMod->mRootNode->SetVisible(true);
		return true;
	}

	bool FrameUI::OnMouseMove( IControl* pCtrl, MouseEventArgs& e )
	{
		if(e.button & MouseButtons::RButton)
		{
			ICamera* pCamera = Editor::Singleton()->GetCamera();
			if(e.button & MouseButtons::Contorl)
			{
				/*Vector3Df p = pCamera->GetPosition();
				p.RotateByY( 0.01f * (mOldPoint.x - e.x) * Editor::Singleton()->GetCameraConfig().rotateStep, pCamera->GetLookAt());
				p.RotateByX( 0.01f * (mOldPoint.y - e.y) * Editor::Singleton()->GetCameraConfig().rotateStep, pCamera->GetLookAt());
				pCamera->SetPosition(p);*/
				//ICamera* pCamera = editor::TheEditor()->GetCamera();
				pCamera->RotateByX((mOldPoint.y - e.y) / 100.0f);
				pCamera->RotateByY((e.x - mOldPoint.x) / 100.0f);
			}
			else
			{
				Vector3Df dir = pCamera->GetDirection();
				dir.Normalize();
				dir.y = 0;
				dir *= (e.y - mOldPoint.y) * 0.01 * Editor::Singleton()->GetCameraConfig().moveStep;
				pCamera->Walk(dir);

				dir = pCamera->GetRightDir();
				dir.Normalize();
				dir.y = 0;
				dir *= (e.x - mOldPoint.x) * 0.01 * Editor::Singleton()->GetCameraConfig().moveStep;
				pCamera->Walk(dir);
			}
			mOldPoint.x = e.x;
			mOldPoint.y = e.y;
		}
		else
		{
			if(NULL != mOldPage)
			{
				IAttrPage* page = (IAttrPage*)mOldPage->GetUserData();
				page->OnMouseMove(e);
			}
		}
		return true;
	}

	bool FrameUI::OnMouseDown( IControl* pCtrl, MouseEventArgs& e )
	{
		mOldPoint.x = e.x;
		mOldPoint.y = e.y;
		if(NULL != mOldPage)
		{
			IAttrPage* page = (IAttrPage*)mOldPage->GetUserData();
			page->OnMouseDown(e);
		}
		return true;
	}

	bool FrameUI::OnMouseUp( IControl* pCtrl, MouseEventArgs& e )
	{
		if(NULL != mOldPage)
		{
			IAttrPage* page = (IAttrPage*)mOldPage->GetUserData();
			page->OnMouseUp(e);
		}
		return true;
	}

	bool FrameUI::OnCameraSetClick( IControl* pCtrl )
	{
		mDlgCameraSet->ShowDlg();
		return true;
	}

	bool FrameUI::OnGridClick( IControl* pCtrl )
	{
		IToolBarToggleButton* toggleBtn = (IToolBarToggleButton*)pCtrl;
		Editor::Singleton()->GetRenderSystem()->RenderWireframe(toggleBtn->GetSelected());
		return true;
	}

	bool FrameUI::OnMouseWheel( IControl* pCtrl, MouseEventArgs& e )
	{
		ICamera* pCamera = Editor::Singleton()->GetCamera();
		Vector3Df dir = pCamera->GetDirection();
		dir.Normalize();
		if (e.delta > 0)
		{
			pCamera->Walk(dir * Editor::Singleton()->GetCameraConfig().wheelStep);
			//editor::TheEditor()->UpdateCameraInfo();
		}
		else
		{
			pCamera->Walk(-dir * Editor::Singleton()->GetCameraConfig().wheelStep);
			//editor::TheEditor()->UpdateCameraInfo();
		}
		return true;
	}

	bool FrameUI::OnEvnSetClick( IControl* pCtrl )
	{
		mDlgEvnSet->ShowDlg();
		return true;
	}

	bool FrameUI::OnRenderSetClick( IControl* pCtrl )
	{
		mDlgRenderSet->ShowDlg();
		return true;
	}
}