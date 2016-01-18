#include "Editor.h"
#include "FrameUI.h"
#include "ResCenter.h"

namespace editor
{
	Editor* Editor::gEditor = NULL;
	Editor* Editor::Singleton()
	{
		return gEditor;
	}

	Editor::Editor( void )
		:mTerObj(NULL),
		mLevel(NULL)
	{
		if(NULL != gEditor)
		{
			throw "ÖØ¸´¹¹Ôì";
		}
		mCameraConfig.moveStep = 100;
		mCameraConfig.wheelStep = 100;
		mCameraConfig.rotateStep = 10;
		mEvnConfig.blendTime = 0.5f;
		gEditor = this;
	}

	void Editor::Run()
	{
		mEngine = TheEngine();
		RenderWindowParam param;
		param.strTitle = _T("Game Editor");
		IRenderWindow* pWindow = mEngine->InitDevice(&param);

		mSceneMgr = mEngine->CreateSceneMgr();
		mCamera = mSceneMgr->CreateCamera();
		mCamera->SetPosition(0, 0, 500);
		mCamera->SetLookAt(0,0,0);
		mCamera->SetUp(0,1,0);
		pWindow->SetCamera(mCamera);
		pWindow->SetBackColor(0xff565656);
		mGame = CreateIGame(mEngine);

		mFrameUI = new FrameUI(pWindow->GetUiManager(), mEngine);
		mFrameUI->InitUI();

		mResCenter = new ResCenter;
		mResCenter->InitUI(pWindow->GetUiManager());

		mDlgInput.InitUI(pWindow->GetUiManager());

		mEngine->Run();
	}

	ResCenter* Editor::GetResCenter( void )
	{
		return mResCenter;
	}

	ISceneMgr* Editor::GetSceneMgr( void )
	{
		return mSceneMgr;
	}

	ICamera* Editor::GetCamera( void )
	{
		return mCamera;
	}

	CameraParam& Editor::GetCameraConfig( void )
	{
		return mCameraConfig;
	}

	IRenderSystem* Editor::GetRenderSystem( void )
	{
		return mEngine->GetRenderSystem();
	}

	IResMgr* Editor::GetResMgr( void )
	{
		return mEngine->GetResMgr();
	}

	DlgInput* Editor::GetDlgInput( void )
	{
		return &mDlgInput;
	}

	EventLevel& Editor::OnLevelOpen( void )
	{
		return mOnLevelOpen;
	}

	void Editor::OpenLevel( ILevel* level )
	{
		if(mLevel == level || NULL == level)
		{
			return;
		}
		if(NULL != mLevel)
		{
			delete mLevel;
		}
		mLevel = level;

		if(!mLevel->GetTerrain().IsNull())
		{
			if(NULL == mTerObj)
			{
				mTerObj = mSceneMgr->CreateMeshObject();
			}
			mTerObj->BindResMesh(mLevel->GetTerrain());
			mTerObj->SetMaterial(mLevel->GetMaterial());
		}
		mOnLevelOpen(mLevel);
	}
}