#include "MatView.h"
#include "../Editor.h"
#include "../ResCenter.h"

namespace editor
{
	void MatView::InitUI( IUiManager* uiMgr )
	{
		__super::InitUI(uiMgr);
		mMeshObj = Editor::Singleton()->GetSceneMgr()->CreateMeshObject();
		mResBall = Editor::Singleton()->GetResMgr()->LoadMesh(_T("../media/ball.mesh"));
		mResBall->Load();
		mMeshObj->BindResMesh(mResBall);

		s32 offsetX1 = 10;
		s32 offsetX2 = 90;
		s32 y = 10;
		IButton* btn = uiMgr->CreateButton(mPanel);
		btn->SetSize(100, 25);
		btn->SetPos(offsetX1, y);
		btn->SetText(_T("修改模型"));
		btn->OnClick().Add(this, &MatView::OnChangeMesh);

		btn = uiMgr->CreateButton(mPanel);
		btn->SetSize(100, 25);
		btn->SetPos(mPanel->GetSize().width - btn->GetSize().width - offsetX1, y);
		btn->SetText(_T("使用默认模型"));
		btn->OnClick().Add(this, &MatView::OnUserDefaultMesh);

		y += 30;
		ILabel* lb = uiMgr->CreateLabel(mPanel);
		lb->SetText(_T("材质类型"));
		lb->SetPos(offsetX1, y);
		mLbMatType = uiMgr->CreateLabel(mPanel);
		mLbMatType->SetPos(offsetX2, y);
		mLbMatType->SetText(_T("StaticMesh"));

		y += 30;
		lb = uiMgr->CreateLabel(mPanel);
		lb->SetText(_T("漫反射纹理"));
		lb->SetPos(offsetX1, y);

		mPbDiffuse = uiMgr->CreatePictureBox(mPanel);
		mPbDiffuse->SetSize(64, 64);
		mPbDiffuse->SetPos(offsetX2, y);
		mPbDiffuse->SetDrawBorder(true);

		btn = uiMgr->CreateButton(mPanel);
		btn->SetSize(50, 20);
		btn->SetPos(offsetX2 + 75, y);
		btn->SetText(_T("修改"));
		btn->OnClick().Add(this, &MatView::OnChooseDiffuseImageClicked);

		y += 80;
		lb = uiMgr->CreateLabel(mPanel);
		lb->SetText(_T("法线纹理"));
		lb->SetPos(offsetX1, y);

		mPbNormal = uiMgr->CreatePictureBox(mPanel);
		mPbNormal->SetSize(64, 64);
		mPbNormal->SetPos(offsetX2, y);
		mPbNormal->SetDrawBorder(true);

		btn = uiMgr->CreateButton(mPanel);
		btn->SetSize(50, 20);
		btn->SetPos(offsetX2 + 75, y);
		btn->SetText(_T("修改"));
		btn->OnClick().Add(this, &MatView::OnChooseNormalImageClicked);
	}

	void MatView::OnResChoosed( Resource res )
	{
		mCurRes = res;
		mCurRes->Load();
		mSceneNode->AttachObject(mMeshObj);
		mMeshObj->SetMaterial(mCurRes);
		mPbDiffuse->SetBackImage(mCurRes->GetDiffuseTex());
		mPbNormal->SetBackImage(mCurRes->GetNormalMap());
	}

	bool MatView::OnChooseDiffuseImageClicked( IControl* pCtrl )
	{
		Editor::Singleton()->GetResCenter()->OnResChoosed().Add(this, &MatView::OnTextureChoosed);
		Editor::Singleton()->GetResCenter()->ChooseRes(ResType::ResType_Texure);
		return true;
	}

	bool MatView::OnChooseNormalImageClicked( IControl* pCtrl )
	{
		Editor::Singleton()->GetResCenter()->OnResChoosed().Add(this, &MatView::OnNormalTextureChoosed);
		Editor::Singleton()->GetResCenter()->ChooseRes(ResType::ResType_Texure);
		return true;
	}

	void MatView::OnTextureChoosed( Resource res )
	{
		mCurRes->SetDiffuseTex(res);
		mPbDiffuse->SetBackImage(res);
	}

	bool MatView::OnUserDefaultMesh( IControl* pCtrl )
	{
		mMeshObj->BindResMesh(mResBall);
		mMeshObj->SetMaterial(mCurRes);
		return true;
	}

	bool MatView::OnChangeMesh( IControl* pCtrl )
	{
		Editor::Singleton()->GetResCenter()->OnResChoosed().Add(this, &MatView::OnMeshChoosed);
		Editor::Singleton()->GetResCenter()->ChooseRes(ResType::ResType_Mesh);
		return true;
	}

	void MatView::OnMeshChoosed( Resource res )
	{
		mMeshObj->BindResMesh(res);
		mMeshObj->SetMaterial(mCurRes);
	}

	void MatView::OnMouseMove( MouseEventArgs& e )
	{
		if (e.button & MouseButtons::LButton)
		{
			mSceneNode->RotateByX((mOldPoint.y - e.y) / 100.0f, TransformSpace::TS_PARENT);
			mSceneNode->RotateByY((e.x - mOldPoint.x) / 100.0f, TransformSpace::TS_PARENT);
			mOldPoint.x = e.x;
			mOldPoint.y = e.y;
		}
	}

	void MatView::OnMouseDown( MouseEventArgs& e )
	{
		mOldPoint.x = e.x;
		mOldPoint.y = e.y;
	}

	void MatView::OnNormalTextureChoosed( Resource res )
	{
		mCurRes->SetNormalMap(res);
		mPbNormal->SetBackImage(res);
	}

	void MatView::OnSaveClick( void )
	{
		if(!mCurRes.IsNull())
		{
			mCurRes->Save();
		}
	}
}