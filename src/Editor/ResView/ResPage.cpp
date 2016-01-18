#include "ResPage.h"
#include "../Editor.h"
#include "../ResCenter.h"
#include "Resview.h"
#include "MeshView.h"
#include "MatView.h"
#include "EffectView.h"

namespace editor
{
	ResPage::ResPage( void ):mCurView(NULL)
	{

	}

	void ResPage::InitUI( ITabPage* page )
	{
		__super::InitUI(page);
		mUiMgr = page->GetUiMgr();
		mToolBar = mUiMgr->CreateToolBar(page);
		mToolBar->SetSize(page->GetSize().width, 25);

		IToolBarItem* toolItem = mToolBar->AddToolItem(_T("打开"));
		toolItem->SetBackImage(TheEngine()->GetResMgr()->LoadTexture(_T("../media/open.png")));
		toolItem->OnClick().Add(this, &ResPage::OnOpenClick);

		toolItem = mToolBar->AddToolItem(_T("新建资源"));
		toolItem->SetBackImage(TheEngine()->GetResMgr()->LoadTexture(_T("../media/new.png")));
		toolItem->OnClick().Add(this, &ResPage::OnNewClick);

		toolItem = mToolBar->AddToolItem(_T("保存资源"));
		toolItem->SetBackImage(TheEngine()->GetResMgr()->LoadTexture(_T("../media/save.png")));
		toolItem->OnClick().Add(this, &ResPage::OnSaveClick);

		mMenu = mUiMgr->CreateMenu();
		mMenu->AddItem(_T("新建模型"));
		IMenuItem* item = mMenu->AddItem(_T("新建材质"));
		IMenuItem* newItem;

		newItem = item->AddItem(_T("模型材质"));
		newItem->SetUserData(MaterialType::Type_StaticMesh);
		newItem->OnClick().Add(this, &ResPage::OnNewMat);
		
		newItem = item->AddItem(_T("骨骼动画材质"));
		newItem->SetUserData(MaterialType::Type_SknMesh);
		newItem->OnClick().Add(this, &ResPage::OnNewMat);

		item->AddItem(_T("水材质"));
		item->AddItem(_T("地形材质"));
		mMenu->AddItem(_T("新建骨骼动画"));


		item = mMenu->AddItem(_T("新建特效"));
		item->OnClick().Add(this, &ResPage::OnNewEffect);


		RegestView(ResType::ResType_Mesh, new MeshView);
		RegestView(ResType::ResType_Material, new MatView);
		RegestView(ResType::ResType_Effect, new EffectView);

		mMeshObj = Editor::Singleton()->GetSceneMgr()->CreateMeshObject();
	}

	bool ResPage::OnOpenClick( IControl* pCtrl )
	{
		Editor::Singleton()->GetResCenter()->OnResChoosed().Add(this, &ResPage::OnResChoosed);
		Editor::Singleton()->GetResCenter()->ChooseRes();
		return true;
	}

	void ResPage::OnResChoosed( Resource res )
	{
		if (res.IsNull())
		{
			return;
		}
		std::map<s32, ResView*>::iterator it = mViews.find(res->GetResType());
		if(it != mViews.end())
		{
			if(NULL != mCurView)
			{
				mCurView->Show(false);
			}
			mCurView = it->second;
			mCurView->Show(true);
			mCurView->OnResChoosed(res);
		}
	}

	void ResPage::RegestView( ResType::eValue type, ResView* pView )
	{
		mViews[type] = pView;
		pView->mPanel = mUiMgr->CreatePanel(mPage);
		pView->mPanel->SetVisible(false);
		pView->mPanel->SetPos(0, 25);
		pView->mPanel->SetSize(mPage->GetSize().width, mPage->GetSize().height - 25);
		pView->mSceneNode = mRootNode->GetSceneMgr()->CreateNode(mRootNode);
		pView->mSceneNode->SetVisible(false);
		pView->InitUI(mUiMgr);
	}

	bool ResPage::OnNewClick( IControl* pCtrl)
	{
		Vector2Dn p = pCtrl->PointToScreen(0, 0);
		mMenu->ShowMenu(p.x, p.y + pCtrl->GetSize().height);
		return true;
	}

	void ResPage::OnMouseDown( MouseEventArgs& e )
	{
		if(NULL != mCurView)
		{
			mCurView->OnMouseDown(e);
		}
	}

	void ResPage::OnMouseUp( MouseEventArgs& e )
	{
		if(NULL != mCurView)
		{
			mCurView->OnMouseUp(e);
		}
	}

	void ResPage::OnMouseMove( MouseEventArgs& e )
	{
		if(NULL != mCurView)
		{
			mCurView->OnMouseMove(e);
		}
	}

	bool ResPage::OnSaveClick( IControl* pCtrl )
	{
		if(NULL != mCurView)
		{
			mCurView->OnSaveClick();
		}
		return true;
	}

	void ResPage::OnSelected( IAttrPage* prePage )
	{
		if(NULL != mCurView)
		{
			mCurView->Show(true);
		}

	}

	void ResPage::OnLostSelected( IAttrPage* curPage )
	{
		if(NULL != mCurView)
		{
			mCurView->Show(false);
		}
	}

	bool ResPage::OnNewMat( IControl* pCtrl )
	{
		mNewType = (MaterialType::eValue)pCtrl->GetUserData();
		Editor::Singleton()->GetDlgInput()->SetTitle(_T("输入材质名称"));
		Editor::Singleton()->GetDlgInput()->OnInputText().Add(this, &ResPage::OnMatNameInput);
		Editor::Singleton()->GetDlgInput()->ShowDlg();
		return true;
	}

	void ResPage::OnMatNameInput(const tstring& name )
	{
		ResMaterial mat = TheEngine()->GetResMgr()->CreateMaterial(mNewType);
		tstring ext = _T("");
		FileUtils::GetFileExtension(name, ext);
		if(0 == ext.size())
		{
			ext = name + _T(".material");
			mat->SetPath(ext.c_str());
		}
		else
		{
			mat->SetPath(name.c_str());
		}
		mat->Save();
		OnResChoosed(mat);
	}

	bool ResPage::OnNewEffect( IControl* pCtrl )
	{
		Editor::Singleton()->GetDlgInput()->SetTitle(_T("输入特效名称"));
		Editor::Singleton()->GetDlgInput()->OnInputText().Add(this, &ResPage::OnEffNameInput);
		Editor::Singleton()->GetDlgInput()->ShowDlg();
		return true;
	}

	void ResPage::OnEffNameInput( const tstring& name )
	{
		ResParticleSys par = TheEngine()->GetResMgr()->CreateParticleSys();
		tstring ext = _T("");
		FileUtils::GetFileExtension(name, ext);
		if(0 == ext.size())
		{
			ext = name + _T(".eff");
			par->SetPath(ext.c_str());
		}
		else
		{
			par->SetPath(name.c_str());
		}
		par->Save();
		OnResChoosed(par);
	}
}