#include "TerView.h"
#include "HeightBrush.h"
#include "../Editor.h"
#include "TextureBrush.h"
#include "SmoothBrush.h"
#include "dlgblendmat.h"
#include "FlatBrush.h"

namespace editor
{
	TerView::TerView( void )
		:mCurBrush(NULL),
		mDlgBlendMat(NULL)
	{
		mName = _T("地形编辑");
	}

	void TerView::InitUI( IUiManager* uiMgr, ISceneNode* pNode)
	{
		mDlgBlendMat = new DlgBlendMat;
		mDlgBlendMat->mCreater = this;
		mDlgBlendMat->Init(uiMgr);

		s32 x1 = 10;
		s32 y = 10;
		ILabel* lb = uiMgr->CreateLabel(mPage);
		lb->SetText(_T("笔刷类型"));
		lb->SetPos(x1, y);

		mCbBrushType = uiMgr->CreateComboBox(mPage);
		mCbBrushType->SetPos(x1 + lb->GetSize().width + 10, y);
		mCbBrushType->SetSize(120, 25);
		mCbBrushType->AddItem(_T("指针"));
		RegestBrush(new HeightBrush);
		mBrushFlat = new FlatBrush;
		RegestBrush(mBrushFlat);
		RegestBrush(new SmoothBrush);
		mBrushTex = new TextureBrush;
		RegestBrush(mBrushTex);
		mCbBrushType->SetSelItem(0);
		mCbBrushType->OnSelectedChange().Add(this, &TerView::OnBrushChange);

		y += 30;
		lb = uiMgr->CreateLabel(mPage);
		lb->SetText(_T("半径"));
		lb->SetPos(10, y);

		mLbRadius = uiMgr->CreateLabel(mPage);
		mLbRadius->SetText(_T("10"));
		mLbRadius->SetPos(mPage->GetSize().width - mLbRadius->GetSize().width - 10, y);

		y += 30;
		mSdRadius = uiMgr->CreateSliderBar(mPage);
		mSdRadius->SetSize(mPage->GetSize().width - 20, 10);
		mSdRadius->SetMaximum(499);
		mSdRadius->SetValue(9);
		mSdRadius->SetPos(10, y);
		mSdRadius->SetEnable(false);
		mSdRadius->OnValueChanged().Add(this, &TerView::OnRadiusChange);

		y += 30;
		lb = uiMgr->CreateLabel(mPage);
		lb->SetText(_T("内径"));
		lb->SetPos(10, y);

		mLbInRadius = uiMgr->CreateLabel(mPage);
		mLbInRadius->SetText(_T("10"));
		mLbInRadius->SetPos(mPage->GetSize().width - mLbInRadius->GetSize().width - 10, y);

		y += 30;
		mSdInRadius = uiMgr->CreateSliderBar(mPage);
		mSdInRadius->SetSize(mPage->GetSize().width - 20, 10);
		mSdInRadius->SetMaximum(499);
		mSdInRadius->SetValue(9);
		mSdInRadius->SetPos(10, y);
		mSdInRadius->SetEnable(false);
		mSdInRadius->OnValueChanged().Add(this, &TerView::OnInsideRadiusChange);

		y += 30;
		lb = uiMgr->CreateLabel(mPage);
		lb->SetText(_T("值"));
		lb->SetPos(10, y);

		mLbValue = uiMgr->CreateLabel(mPage);
		mLbValue->SetText(_T("10"));
		mLbValue->SetPos(mPage->GetSize().width - mLbValue->GetSize().width - 10, y);

		y += 30;
		mSdValue = uiMgr->CreateSliderBar(mPage);
		mSdValue->SetSize(mPage->GetSize().width - 20, 10);
		mSdValue->SetMaximum(200);
		mSdValue->SetValue(110);
		mSdValue->SetPos(10, y);
		mSdValue->SetEnable(false);
		mSdValue->OnValueChanged().Add(this, &TerView::OnValueChange);

		y += 30;
		lb = uiMgr->CreateLabel(mPage);
		lb->SetText(_T("纹理融合"));
		lb->SetPos(x1, y);

		y += 30;
		mLbTexture = uiMgr->CreateListBox(mPage);
		mLbTexture->SetSize(mPage->GetSize().width - 20, 150);
		mLbTexture->SetPos(10, y);
		mLbTexture->OnSelectedChange().Add(this, &TerView::OnTextChange);

		y += 160;
		s32 x = 10;
		IButton* btn = uiMgr->CreateButton(mPage);
		btn->SetSize(50, 20);
		btn->SetText(_T("添加"));
		btn->OnClick().Add(this, &TerView::OnAddClick);
		btn->SetPos(x, y);

		x += 70;
		btn = uiMgr->CreateButton(mPage);
		btn->SetSize(50, 20);
		btn->SetText(_T("编辑"));
		btn->OnClick().Add(this, &TerView::OnEditClick);
		btn->SetPos(x, y);

		x += 70;
		btn = uiMgr->CreateButton(mPage);
		btn->SetSize(50, 20);
		btn->SetText(_T("删除"));
		btn->OnClick().Add(this, &TerView::OnDelClick);
		btn->SetPos(x, y);

		// 创建地形笔刷模型
		IResMgr* resMgr = Editor::Singleton()->GetResMgr();
		
		mBrushObj = Editor::Singleton()->GetSceneMgr()->CreateMeshObject();
		mBrushObj->SetName(_T("BrushObj"));
		mBrushObj->SetVisible(false);
		pNode->AttachObject(mBrushObj);
		ResMaterial lineMat = resMgr->CreateMaterial(MaterialType::Type_Line);
		mBrushMesh = resMgr->CreateMesh();
		mOutSubMesh = mBrushMesh->CreateSubMesh();
		u32 num = 62;
		mOutSubMesh->SetRenderOperation(RenderOperation::OT_LINE_STRIP);
		mOutSubMesh->SetVertexCount(num);
		mOutSubMesh->CreateVertexBuffer(0, sizeof(Vector3Df));
		mOutSubMesh->AddElement(0, 0, DeclareType::DECLTYPE_FLOAT3, DeclareUsage::DECLUSAGE_POSITION, 0);

		mInsideSubMesh = mBrushMesh->CreateSubMesh();
		mInsideSubMesh->SetRenderOperation(RenderOperation::OT_LINE_STRIP);
		mInsideSubMesh->SetVertexCount(num);
		mInsideSubMesh->CreateVertexBuffer(0, sizeof(Vector3Df));
		mInsideSubMesh->AddElement(0, 0, DeclareType::DECLTYPE_FLOAT3, DeclareUsage::DECLUSAGE_POSITION, 0);
		mOutSubMesh->SetIndexCount(num + 1, false);
		mInsideSubMesh->SetIndexCount(num + 1, false);
		s16* ib = (s16*)mOutSubMesh->LockIndexBuffer();
		s16* ib2 = (s16*)mInsideSubMesh->LockIndexBuffer();
		for (u32 i = 0; i < num; i++)
		{
			ib[i] = i;
			ib2[i] = i;
		}
		ib[num] = 0;
		ib2[num] = 0;
		mOutSubMesh->UnLockIndexBuffer();
		mInsideSubMesh->UnLockIndexBuffer();

		mBrushObj->BindResMesh(mBrushMesh);
		mBrushObj->SetMaterial(lineMat);
	}

	bool TerView::OnRadiusChange( IControl* pCtrl )
	{
		tstring str;
		StringUtils::S32ToStr(mSdRadius->GetValue() + 1, str);
		mLbRadius->SetText(str);
		mLbRadius->SetPos(mPage->GetSize().width - mLbRadius->GetSize().width - 10, mLbRadius->GetPos().y);
		if(mSdRadius->GetValue() + 1 < mSdInRadius->GetValue())
		{
			mSdInRadius->SetValue(mSdRadius->GetValue());
			OnInsideRadiusChange(mSdInRadius);
		}
		if(NULL != mCurBrush)
		{
			mCurBrush->SetRadius(mSdRadius->GetValue() + 1);
			UpdateBrush(mOldPos.x, mOldPos.y);
		}
		return true;
	}

	bool TerView::OnInsideRadiusChange( IControl* pCtrl )
	{
		tstring str;
		StringUtils::S32ToStr(mSdInRadius->GetValue(), str);
		mLbInRadius->SetText(str);
		mLbInRadius->SetPos(mPage->GetSize().width - mLbInRadius->GetSize().width - 10, mLbInRadius->GetPos().y);
		if(mSdInRadius->GetValue() > mSdRadius->GetValue())
		{
			mSdRadius->SetValue(mSdInRadius->GetValue() + 1);
			OnRadiusChange(mSdRadius);
		}
		if(NULL != mCurBrush)
		{
			mCurBrush->SetInsideRadius(mSdInRadius->GetValue());
			UpdateBrush(mOldPos.x, mOldPos.y);
		}
		return true;
	}

	bool TerView::OnValueChange( IControl* pCtrl )
	{
		tstring str;
		StringUtils::S32ToStr(mSdValue->GetValue() - 100, str);
		mLbValue->SetText(str);
		mLbValue->SetPos(mPage->GetSize().width - mLbValue->GetSize().width - 10, mLbValue->GetPos().y);
		if(NULL != mCurBrush)
		{
			mCurBrush->SetValue(mSdValue->GetValue() - 100);
			UpdateBrush(mOldPos.x, mOldPos.y);
		}
		return true;
	}

	bool TerView::OnBrushChange( IControl* pCtrl )
	{
		IListBoxItem* item = mCbBrushType->GetSelItem();
		mCurBrush = (IBrush*)item->GetUserData();
		if(NULL != mCurBrush)
		{
			if(mCurBrush == mBrushTex)
			{
				mBrushTex->SetTextureIndex(mLbTexture->GetSelItemIndex());
			}

			mSdRadius->SetValue(mCurBrush->mRadius);
			OnRadiusChange(mSdRadius);

			mSdInRadius->SetValue(mCurBrush->mInsideRadius);
			OnInsideRadiusChange(mSdInRadius);

			mSdValue->SetValue(mCurBrush->mValue + 100);
			OnValueChange(mSdValue);
			mBrushObj->SetVisible(true);
			mSdRadius->SetEnable(true);
			mSdInRadius->SetEnable(true);
			mSdValue->SetEnable(true);
		}
		else
		{
			mBrushObj->SetVisible(false);
			mSdRadius->SetEnable(false);
			mSdInRadius->SetEnable(false);
			mSdValue->SetEnable(false);
		}
		return true;
	}

	void TerView::RegestBrush( IBrush* brush )
	{
		IListBoxItem* pItem = mCbBrushType->AddItem(brush->mName);
		pItem->SetUserData((s32)brush);
	}

	void TerView::OnMouseMove( MouseEventArgs& e )
	{
		Editor* ptr = Editor::Singleton();
		IMeshObject* pTerObj = ptr->mTerObj;
		if(NULL != ptr->mTerObj)
		{
			Ray ray = ptr->mCamera->MakeRay(e.x, e.y);
			ProbeResult r;
			if(pTerObj->Probe(ray, r))
			{
				mOldPos.x = r.pos.x;
				mOldPos.y = r.pos.z;
				UpdateBrush(r.pos.x, r.pos.z);
			}
		}

		if(e.button & MouseButtons::LButton)
		{
			if (NULL != mCurBrush)
			{
				if (!pTerObj->GetResMesh().IsNull())
				{
					Ray ray = ptr->GetCamera()->MakeRay(e.x, e.y);
					ProbeResult r;
					if(pTerObj->Probe(ray, r))
					{
						mCurBrush->OnPaint(r.pos.x, r.pos.z);
					}
				}
			}
		}
	}

	void TerView::UpdateBrush( f32 x, f32 y )
	{
		if(NULL == mCurBrush)
		{
			return;
		}
		Editor* ptr = Editor::Singleton();
		if(NULL == ptr->mLevel)
		{
			return;
		}

		TerrainVertex* terVb = ptr->mLevel->GetTerrain()->LockVertexBuffer();
		// 内径
		f32 r;
		if (mCurBrush->mInsideRadius > 0)
		{
			r = mCurBrush->mInsideRadius;
			mBrushObj->SetSubMeshVisible(1, true);
			Vector3Df* vb = (Vector3Df*)mInsideSubMesh->LockVertexBuffer(0);
			s32 index = 0;
			for (f32 i = 0; i < 6.2; i += 0.1f)
			{
				vb[index].x = math::Sin(i) * r + x;
				vb[index].z = math::Cos(i) * r + y;
				vb[index].y = ptr->mLevel->GetTerrain()->GetHeight(vb[index].x, vb[index].z, terVb) + 10;
				index++;
			}
			mInsideSubMesh->UnLockVertexBuffer(0);
		}
		else
		{
			mBrushObj->SetSubMeshVisible(1, false);
		}

		// 外径
		r = mCurBrush->mRadius;
		Vector3Df* vb = (Vector3Df*)mOutSubMesh->LockVertexBuffer(0);
		s32 index = 0;
		for (f32 i = 0; i < 6.2; i += 0.1f)
		{
			vb[index].x = math::Sin(i) * r + x;
			vb[index].z = math::Cos(i) * r + y;
			vb[index].y = ptr->mLevel->GetTerrain()->GetHeight(vb[index].x, vb[index].z, terVb) + 10;
			index++;
		}
		mOutSubMesh->UnLockVertexBuffer(0);
		ptr->mLevel->GetTerrain()->UnLockBuffer();
	}

	void TerView::OnMouseDown( MouseEventArgs& e )
	{
		if(e.button & MouseButtons::LButton)
		{
			Editor* ptr = Editor::Singleton();
			if (NULL != ptr->mLevel && NULL != mCurBrush)
			{
				Ray ray = ptr->GetCamera()->MakeRay(e.x, e.y);
				ProbeResult r;
				if(ptr->mTerObj->Probe(ray, r))
				{
					if(e.button & MouseButtons::Contorl)
					{
						if (mCurBrush == mBrushFlat)
						{
							mCurBrush->SetValue(r.pos.y);
							OnValueChange(mSdValue);
						}
					}
					mCurBrush->OnPaint(r.pos.x, r.pos.z);
				}
			}
		}
	}

	void TerView::OnMouseUp( MouseEventArgs& e )
	{
		if(e.button & MouseButtons::LButton)
		{
			Editor* ptr = Editor::Singleton();
			if (NULL != ptr->mLevel)
			{
				ptr->mLevel->GetTerrain()->UpdateAABB();
				ptr->mLevel->GetTerrain()->UpdateNormals();
				//ptr->SetTerrianDirty();
			}
		}
	}

	bool TerView::OnAddClick( IControl* pCtrl )
	{
		Editor* ptr = Editor::Singleton();
		if(NULL == ptr->mLevel)
		{
			return true;
		}
		mDlgBlendMat->mEditor = false;
		mDlgBlendMat->mCurIndex = ptr->mLevel->GetMaterial()->GetNumTexture();
		mDlgBlendMat->mPbImage->SetBackImage(NULL);
		mDlgBlendMat->ShowDlg();
		return true;
	}

	bool TerView::OnEditClick( IControl* pCtrl )
	{
		Editor* ptr = Editor::Singleton();
		s32 index = mLbTexture->GetSelItemIndex();
		if(NULL == ptr->mLevel || index < 0)
		{
			return true;
		}
		mDlgBlendMat->mCurIndex = index;
		mDlgBlendMat->mPbImage->SetBackImage(ptr->mLevel->GetMaterial()->GetTexture(index));
		f32 scale = ptr->mLevel->GetMaterial()->GetTextureScale(index);
		tstring str;
		StringUtils::F32ToStr(scale, str, 0);
		mDlgBlendMat->mTbSclae->SetText(str);
		mDlgBlendMat->mEditor = true;
		mDlgBlendMat->ShowDlg();
		return true;
	}

	bool TerView::OnDelClick( IControl* pCtrl )
	{
		Editor* ptr = Editor::Singleton();
		s32 selIndex = mLbTexture->GetSelItemIndex();
		if(NULL == ptr->mLevel || selIndex < 0)
		{
			return true;
		}
		ptr->mLevel->GetMaterial()->RemoveTexture(selIndex);
		RefreshMat();
		return true;
	}

	void TerView::RefreshMat( void )
	{
		Editor* ptr = Editor::Singleton();
		if(NULL == ptr->mLevel)
		{
			return;
		}
		s32 selIndex = mLbTexture->GetSelItemIndex();
		mLbTexture->Clear();
		u32 num = ptr->mLevel->GetMaterial()->GetNumTexture();
		for(u32 i = 0; i < num; i++)
		{
			ResTexture img = ptr->mLevel->GetMaterial()->GetTexture(i);
			mLbTexture->AddItem(img->GetResPath());
		}

		mLbTexture->SetSelItemIndex(selIndex);
	}

	bool TerView::OnTextChange( IControl* pCtrl )
	{
		mBrushTex->SetTextureIndex(mLbTexture->GetSelItemIndex());
		return true;
	}
}
