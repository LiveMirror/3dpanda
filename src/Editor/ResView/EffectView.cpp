#include "EffectView.h"
#include "../Editor.h"

namespace editor
{
	EffectView::EffectView( void )
		:mCurTecq(NULL),
		mParticleObject(NULL)
	{

	}
	
	void EffectView::InitUI( IUiManager* uiMgr )
	{
		s32 x1 = 10;
		s32 y = 10;
		
		mBtnPlay = uiMgr->CreateButton(mPanel);
		mBtnPlay->SetPos(x1, y);
		mBtnPlay->SetText(_T("Play"));
		mImgPlay = TheEngine()->GetResMgr()->LoadTexture(_T("../media/play.png"));
		mImgPause = TheEngine()->GetResMgr()->LoadTexture(_T("../media/pause.png"));
		mBtnPlay->SetBackImage(mImgPlay);
		mBtnPlay->SetSize(25, 25);
		mBtnPlay->OnClick().Add(this, &EffectView::OnPlayClick);

		x1 += 50;
		ICheckBox* cb = uiMgr->CreateCheckBox(mPanel);
		cb->SetText(_T("循环"));
		cb->SetPos(x1, y);
		cb->SetChecked(true);

		s32 x2 = cb->GetSize().width + x1 + 15;
		ILabel* lb = uiMgr->CreateLabel(mPanel);
		lb->SetText(_T("持续时间:"));
		lb->SetPos(x2, y);
		
		mTbTimeToLive = uiMgr->CreateTextBox(mPanel);
		mTbTimeToLive->SetSize(35, 25);
		mTbTimeToLive->SetPos(x2 + lb->GetSize().width + 10, y);

		x1 = 10;
		y += 35;
		lb = uiMgr->CreateLabel(mPanel);
		lb->SetText(_T("类型"));
		lb->SetPos(x1, y);

		mCbEntityType = uiMgr->CreateComboBox(mPanel);
		mCbEntityType->SetPos(x1 + lb->GetSize().width + 10, y);
		mCbEntityType->SetSize(100, 25);
		mCbEntityType->AddItem(_T("Billbord"))->SetUserData(ParticleRenderType::Billborad);
		mCbEntityType->AddItem(_T("Box"))->SetUserData(ParticleRenderType::Box);
		mCbEntityType->AddItem(_T("Ball"))->SetUserData(ParticleRenderType::Ball);
		mCbEntityType->AddItem(_T("Mesh"))->SetUserData(ParticleRenderType::Mesh);
		mCbEntityType->SetSelItem(0);

		IButton* btn = uiMgr->CreateButton(mPanel);
		btn->SetPos(mCbEntityType->GetPos().x + mCbEntityType->GetSize().width + 15, y);
		btn->SetSize(80, 25);
		btn->SetText(_T("add"));
		btn->OnClick().Add(this, &EffectView::OnAddTecqClick);

		y += 35;
		mLbEntitys = uiMgr->CreateListBox(mPanel);
		mLbEntitys->SetPos(5, y);
		mLbEntitys->SetSize(mPanel->GetSize().width - 10, 150);
		mLbEntitys->OnSelectedChange().Add(this, &EffectView::_OnTecqSelChange);
		mLbEntitys->OnKeyDown().Add(this, &EffectView::OnTecqKeyDown);

		y += mLbEntitys->GetSize().height + 10;
		mFpTechnique = uiMgr->CreateFoldPanel(mPanel);
		mFpTechnique->SetSize(mPanel->GetSize().width - 10, mPanel->GetSize().height - y - 10);
		mFpTechnique->SetPos(5, y);
		mFpTechnique->SetVisible(false);
		IFoldPage* panel = mFpTechnique->AddPage(_T("基本属性"));
		InitPropertyUI(panel);
		panel = mFpTechnique->AddPage(_T("发射器"));
		InitEmitterUI(panel);
		panel = mFpTechnique->AddPage(_T("效果器"));
		InitAffectorUI(panel);

		mParticleObject = Editor::Singleton()->GetSceneMgr()->CreateParticleObject();
	}

	void EffectView::OnResChoosed( Resource res )
	{
		if(mCurEffect == res)
		{
			return;
		}
		mCurEffect = res;
		mCurEffect->Load();
		mParticleObject->SetResParticl(mCurEffect);
		mSceneNode->AttachObject(mParticleObject);
	}

	void EffectView::OnMouseMove( MouseEventArgs& e )
	{

	}

	void EffectView::OnMouseDown( MouseEventArgs& e )
	{

	}

	void EffectView::OnSaveClick( void )
	{
		if(!mCurEffect.IsNull())
		{
			mCurEffect->Save();
		}
	}

	void EffectView::InitPropertyUI( IFoldPage* page )
	{
		IUiManager* uiMgr = page->GetUiMgr();

		s32 x1 = 10;
		s32 y = 10;
		ILabel* lb = uiMgr->CreateLabel(page);
		lb->SetText(_T("类型"));
		lb->SetPos(x1, y);

		mLbTechType = uiMgr->CreateLabel(page);
		mLbTechType->SetPos(lb->GetSize().width + x1 + 10, y);
		mLbTechType->SetText(_T("-"));
	}

	void EffectView::InitEmitterUI( IFoldPage* page )
	{
		IUiManager* uiMgr = page->GetUiMgr();

		s32 x1 = 10;
		s32 y = 10;
		ILabel* lb = uiMgr->CreateLabel(page);
		lb->SetText(_T("类型"));
		lb->SetPos(x1, y);

		mCbEmitterType = uiMgr->CreateComboBox(page);
		mCbEmitterType->SetPos(x1 + lb->GetSize().width + 10, y);
		mCbEmitterType->SetSize(100, 25);
		mCbEmitterType->AddItem(_T("Point"))->SetUserData(ParticleEmitterType::Point);
		mCbEmitterType->AddItem(_T("Box"))->SetUserData(ParticleEmitterType::Box);
		mCbEmitterType->AddItem(_T("Ball"))->SetUserData(ParticleEmitterType::Ball);
		mCbEmitterType->AddItem(_T("Cylinder"))->SetUserData(ParticleEmitterType::Cylinder);
		mCbEmitterType->SetSelItem(0);

		IButton* btn = uiMgr->CreateButton(page);
		btn->SetPos(mCbEntityType->GetPos().x + mCbEmitterType->GetSize().width + 15, y);
		btn->SetSize(60, 25);
		btn->SetText(_T("add"));
		btn->OnClick().Add(this, &EffectView::OnAddEmitterClick);

		y += 35;
		mLbEmitters = uiMgr->CreateListBox(page);
		mLbEmitters->SetPos(5, y);
		mLbEmitters->SetSize(page->GetSize().width - 20, 150);
		mLbEmitters->OnSelectedChange().Add(this, &EffectView::_OnEmitterSelChange);

		y += mLbEmitters->GetSize().height + 10;
		lb = uiMgr->CreateLabel(page);
		lb->SetText(_T("属性:"));
		lb->SetPos(x1, y);

		y += 25;
		mPgEmitter = uiMgr->CreatePropertyGrid(page);
		mPgEmitter->SetSize(mLbEmitters->GetSize().width, 300);
		mPgEmitter->SetPos(5, y);
	}

	void EffectView::InitAffectorUI( IFoldPage* page )
	{
		IUiManager* uiMgr = page->GetUiMgr();

		s32 x1 = 10;
		s32 y = 10;
		ILabel* lb = uiMgr->CreateLabel(page);
		lb->SetText(_T("类型"));
		lb->SetPos(x1, y);

		mCbAffectorType = uiMgr->CreateComboBox(page);
		mCbAffectorType->SetPos(x1 + lb->GetSize().width + 10, y);
		mCbAffectorType->SetSize(100, 25);
		mCbAffectorType->AddItem(_T("Colour"))->SetUserData(ParticleAffectorType::Colour);
		mCbAffectorType->AddItem(_T("LinerForce"))->SetUserData(ParticleAffectorType::LinerForce);
		mCbAffectorType->SetSelItem(0);

		IButton* btn = uiMgr->CreateButton(page);
		btn->SetPos(mCbEntityType->GetPos().x + mCbAffectorType->GetSize().width + 15, y);
		btn->SetSize(60, 25);
		btn->SetText(_T("add"));
		btn->OnClick().Add(this, &EffectView::OnAddAffectClick);

		y += 35;
		mLbAffectors = uiMgr->CreateListBox(page);
		mLbAffectors->SetPos(5, y);
		mLbAffectors->SetSize(page->GetSize().width - 20, 150);
		mLbAffectors->OnSelectedChange().Add(this, &EffectView::_OnAffectorSelChange);

		y += mLbAffectors->GetSize().height + 10;
		lb = uiMgr->CreateLabel(page);
		lb->SetText(_T("属性:"));
		lb->SetPos(x1, y);

		y += 25;
		mPgAffector = uiMgr->CreatePropertyGrid(page);
		mPgAffector->SetSize(mLbAffectors->GetSize().width, 300);
		mPgAffector->SetPos(5, y);
	}

	bool EffectView::OnAddTecqClick( IControl* pCtrl )
	{
		Editor::Singleton()->GetDlgInput()->SetTitle(_T("输入名称"));
		Editor::Singleton()->GetDlgInput()->OnInputText().Add(this, &EffectView::OnTecqNameInput);
		Editor::Singleton()->GetDlgInput()->ShowDlg();
		return true;
	}

	void EffectView::OnTecqNameInput( const tstring& name )
	{
		IParticleTechnique* tecq = mCurEffect->CreateTechnique(name);
		ParticleRenderType::eValue t = (ParticleRenderType::eValue)mCbEntityType->GetSelItem()->GetUserData();
		tecq->SetRender(t);
		IListBoxItem* item = mLbEntitys->AddItem(name);
		mLbEntitys->SetSelItemIndex(mLbEntitys->GetItemNum() - 1);

		mParticleObject->SetResParticl(NULL);
		mParticleObject->SetResParticl(mCurEffect);

		OnSelTecqChange(tecq);
	}

	bool EffectView::OnAddEmitterClick( IControl* pCtrl )
	{
		if(NULL != mCurTecq)
		{
			Editor::Singleton()->GetDlgInput()->SetTitle(_T("输入名称"));
			Editor::Singleton()->GetDlgInput()->OnInputText().Add(this, &EffectView::OnEmitterInput);
			Editor::Singleton()->GetDlgInput()->ShowDlg(_T("emitter"));
		}
		return true;
	}

	void EffectView::OnEmitterInput( const tstring& name )
	{
		ParticleEmitterType::eValue type = (ParticleEmitterType::eValue)mCbEmitterType->GetSelItem()->GetUserData();
		IParticleEmitter* pEmitter = mCurTecq->AddEmitter(type);
		if(NULL != pEmitter)
		{
			pEmitter->SetName(name);
			mLbEmitters->AddItem(name);
			mLbEmitters->SetSelItemIndex(mLbEmitters->GetItemNum() - 1);
			OnSelEmitterChange(pEmitter);
		}
	}

	bool EffectView::_OnTecqSelChange( IControl* pCtrl )
	{
		IParticleTechnique* tecq = mCurEffect->GetTechnique(mLbEntitys->GetSelItemIndex());
		OnSelTecqChange(tecq);
		return true;
	}

	void EffectView::OnSelTecqChange( IParticleTechnique* tecq )
	{
		if(tecq == mCurTecq)
		{
			return;
		}
		mCurTecq = tecq;
		mLbEmitters->Clear();
		mLbAffectors->Clear();

		if(NULL == mCurTecq)
		{
			mFpTechnique->SetVisible(false);
			return;
		}
		mFpTechnique->SetVisible(true);
		ParticleRenderType::eValue renderType = mCurTecq->GetRender()->GetType();
		switch(renderType)
		{
		case ParticleRenderType::Billborad:
			{
				mLbTechType->SetText(_T("Billborad"));
				break;
			}
		}

		u32 num = mCurTecq->GetNumEmitters();
		for(u32 i = 0; i < num; i++)
		{
			mLbEmitters->AddItem(mCurTecq->GetEmitter(i)->GetName());
		}
	}

	bool EffectView::OnAddAffectClick( IControl* pCtrl )
	{
		if(NULL != mCurTecq)
		{
			Editor::Singleton()->GetDlgInput()->SetTitle(_T("输入名称"));
			Editor::Singleton()->GetDlgInput()->OnInputText().Add(this, &EffectView::OnAffectInput);
			Editor::Singleton()->GetDlgInput()->ShowDlg(_T("affector"));
		}
		return true;
	}

	void EffectView::OnAffectInput( const tstring& name )
	{
		ParticleAffectorType::eValue type = (ParticleAffectorType::eValue)mCbAffectorType->GetSelItem()->GetUserData();
		IParticleAffector* pAffector = mCurTecq->AddAffector(type);
		if(NULL != pAffector)
		{
			pAffector->SetName(name);
			mLbAffectors->AddItem(name);
			mLbAffectors->SetSelItemIndex(mLbAffectors->GetItemNum() - 1);
			OnSelAffectorChange(pAffector);
		}
	}

	void EffectView::OnSelEmitterChange( IParticleEmitter* emitter )
	{
		mPgEmitter->ClearItem();
		mCurEmitter = emitter;
		if(NULL == mCurEmitter)
		{
			return;
		}
		IPropertyGridItem3F* item3F;
		item3F = mPgEmitter->AddItem3F(_T("位置"));
		item3F->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetPosition, &IParticleEmitter::GetPosition);
		item3F->RefreshValue();

		item3F = mPgEmitter->AddItem3F(_T("方向"));
		item3F->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetDirection, &IParticleEmitter::GetDirection);
		item3F->RefreshValue();

		IPropertyGridItemS32* itemS32 = mPgEmitter->AddItemS32(_T("角度"));
		itemS32->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetAngle, &IParticleEmitter::GetAngle);
		itemS32->RefreshValue();

		IPropertyGridItemF32* itemF32 = mPgEmitter->AddItemF32(_T("最大速度"));
		itemF32->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetMaxSpeed, &IParticleEmitter::GetMaxSpeed);
		itemF32->RefreshValue();

		itemF32 = mPgEmitter->AddItemF32(_T("最小速度"));
		itemF32->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetMinSpeed, &IParticleEmitter::GetMinSpeed);
		itemF32->RefreshValue();

		IPropertyGridItemBool* itemBool = mPgEmitter->AddItemBool(_T("循环"));
		itemBool->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetLoop, &IParticleEmitter::GetLoop);
		itemBool->RefreshValue();

		item3F = mPgEmitter->AddItem3F(_T("最大尺寸"));
		item3F->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetParticleMaxSize, &IParticleEmitter::GetParticleMaxSize);
		item3F->RefreshValue();

		item3F = mPgEmitter->AddItem3F(_T("最小尺寸"));
		item3F->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetParticleMinSize, &IParticleEmitter::GetParticleMinSize);
		item3F->RefreshValue();

		/*itemS32 = mPgEmitter->AddItemS32(_T("最大值"));
		itemS32->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetMaxNum, &IParticleEmitter::GetMaxNum);
		itemS32->RefreshValue();

		itemS32 = mPgEmitter->AddItemS32(_T("最小值"));
		itemS32->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetMinNum, &IParticleEmitter::GetMinNum);
		itemS32->RefreshValue();*/

		itemS32 = mPgEmitter->AddItemS32(_T("发射速率"));
		itemS32->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetRate, &IParticleEmitter::GetRate);
		itemS32->RefreshValue();

		itemF32 = mPgEmitter->AddItemF32(_T("生命周期"));
		itemF32->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetTimeToLive, &IParticleEmitter::GetTimeToLive);
		itemF32->RefreshValue();

		IPropertyGridItem4F* itemColor = mPgEmitter->AddItem4F(_T("起始颜色"));
		itemColor->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetColorStart, &IParticleEmitter::GetColorStart);
		itemColor->RefreshValue();

		itemColor = mPgEmitter->AddItem4F(_T("结束颜色"));
		itemColor->GetAttr().InitAttr(mCurEmitter, &IParticleEmitter::SetColorEnd, &IParticleEmitter::GetColorEnd);
		itemColor->RefreshValue();

	}

	bool EffectView::_OnEmitterSelChange( IControl* pCtrl )
	{
		IParticleEmitter* emitter = mCurTecq->GetEmitter(mLbEmitters->GetSelItemIndex());
		OnSelEmitterChange(emitter);
		return true;
	}

	bool EffectView::OnPlayClick( IControl* pCtrl )
	{
		if(NULL == mParticleObject)
		{
			return true;
		}
		if (mParticleObject->IsPlay())
		{
			mParticleObject->Stop();
			mBtnPlay->SetBackImage(mImgPlay);
		}
		else
		{
			mParticleObject->Play();
			mBtnPlay->SetBackImage(mImgPause);
		}
		return true;
	}

	void EffectView::OnSelAffectorChange( IParticleAffector* affector )
	{
		mPgAffector->ClearItem();
		mCurAffector = affector;
		if(NULL == mCurAffector)
		{
			return;
		}
		switch(mCurAffector->GetType())
		{
		case ParticleAffectorType::LinerForce:
			{
				IPropertyGridItem3F* item3F = mPgAffector->AddItem3F(_T("ForceVector"));
				item3F->GetAttr().InitAttr((ILinerForceAffector*)mCurAffector, &ILinerForceAffector::SetForceVector, &ILinerForceAffector::GetForceVector);
				item3F->RefreshValue();
				break;
			}
		case ParticleAffectorType::Colour:
			{
				IPropertyGridItem4F* item4F = mPgAffector->AddItem4F(_T("ForceColor"));
				item4F->GetAttr().InitAttr((IColourAffector*)mCurAffector, &IColourAffector::SetColor, &IColourAffector::GetColor);
				item4F->RefreshValue();
				break;
			}
		}

	}

	bool EffectView::_OnAffectorSelChange( IControl* pCtrl )
	{
		IParticleAffector* affector = mCurTecq->GetAffector(mLbAffectors->GetSelItemIndex());
		OnSelAffectorChange(affector);
		return true;
	}

	bool EffectView::OnTecqKeyDown( IControl* pCtrl, KeyEventArgs& e )
	{
		if(e.keyCode == VK_DELETE)
		{
			s32 index = mLbEntitys->GetSelItemIndex();
			if(index >= 0)
			{
				mCurEffect->RemoveTechnique(index);
				mLbEntitys->RemoveItem(index);
				mParticleObject->SetResParticl(NULL);
				mParticleObject->SetResParticl(mCurEffect);
				if(index < mCurEffect->GetNumTechnique())
				{
					OnSelTecqChange(mCurEffect->GetTechnique(index));
				}
				else
				{
					OnSelTecqChange(mCurEffect->GetTechnique(index - 1));
				}
			}
		}
		return true;
	}
}