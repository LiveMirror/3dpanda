#include "MeshView.h"
#include "../Editor.h"
#include "../ResCenter.h"

namespace editor
{
	MeshView::MeshView( void )
		:mMeshObj(NULL),
		mCurAni(NULL),
		mIsPlaying(false)
	{
		
	}

	void MeshView::InitUI( IUiManager* uiMgr )
	{
		__super::InitUI(uiMgr);
		mTabCtrl = uiMgr->CreateTabCtrl(mPanel);
		mTabCtrl->SetSize(mPanel->GetSize());

		InitInfoPage(uiMgr);
		InitSknPage(uiMgr);
		InitSknPanel(uiMgr);
		mMeshObj = Editor::Singleton()->GetSceneMgr()->CreateMeshObject();
	}

	void MeshView::InitInfoPage(IUiManager* uiMgr)
	{
		mMeshInfoPage = mTabCtrl->AddPage(_T("基本信息"));

		s32 posX = 60;
		s32 y = 5;
		ILabel* lb = uiMgr->CreateLabel(mMeshInfoPage);
		lb->SetPos(10, y);
		lb->SetText(_T("顶点数"));

		mLbVertexNum = uiMgr->CreateLabel(mMeshInfoPage);
		mLbVertexNum->SetPos(posX, y);
		mLbVertexNum->SetText(_T("0"));

		y += 20;
		lb = uiMgr->CreateLabel(mMeshInfoPage);
		lb->SetPos(10, y);
		lb->SetText(_T("面   数"));

		mLbFaceNum = uiMgr->CreateLabel(mMeshInfoPage);
		mLbFaceNum->SetPos(posX, y);
		mLbFaceNum->SetText(_T("0"));

		y += 20;
		lb = uiMgr->CreateLabel(mMeshInfoPage);
		lb->SetPos(10, y);
		lb->SetText(_T("子集数"));

		mLbSubsetNum = uiMgr->CreateLabel(mMeshInfoPage);
		mLbSubsetNum->SetPos(posX, y);
		mLbSubsetNum->SetText(_T("0"));
	}


	void MeshView::InitSknPanel( IUiManager* uiMgr )
	{
		mAniPanel = uiMgr->CreatePanel();
		mAniPanel->SetSize(uiMgr->GetWidth() - mPanel->GetSize().width - 1, 100);
		mAniPanel->SetPos(0, uiMgr->GetHeight() - mAniPanel->GetSize().height);
		mAniPanel->SetVisible(false);

		s32 y = 5;
		s32 offsetX1 = 5;
		ILabel* lb = uiMgr->CreateLabel(mAniPanel);
		lb->SetText(_T("动画"));
		lb->SetPos(offsetX1, y);
		
		mCbAnis = uiMgr->CreateComboBox(mAniPanel);
		mCbAnis->SetPos(offsetX1 + lb->GetSize().width + 10, + y);
		mCbAnis->OnSelectedChange().Add(this, &MeshView::OnAniChange);
		mCbAnis->SetNumOfShow(3);

		mBtnPlay = uiMgr->CreateButton(mAniPanel);
		mBtnPlay->SetPos(mCbAnis->GetPos().x + mCbAnis->GetSize().width + 10, y);
		mBtnPlay->SetText(_T("Play"));
		mImgPlay = TheEngine()->GetResMgr()->LoadTexture(_T("../media/play.png"));
		mImgPause = TheEngine()->GetResMgr()->LoadTexture(_T("../media/pause.png"));
		mBtnPlay->SetBackImage(mImgPlay);
		mBtnPlay->SetSize(25, 25);
		mBtnPlay->OnClick().Add(this, &MeshView::OnPlayClick);

		y += 30;
		lb = uiMgr->CreateLabel(mAniPanel);
		lb->SetText(_T("时间轴"));
		lb->SetPos(offsetX1, y);
		
		mLbTime = uiMgr->CreateLabel(mAniPanel);
		
		mLbTime->SetText(_T("0/100"));
		mLbTime->SetPos(mAniPanel->GetSize().width - mLbTime->GetSize().width - offsetX1, y);

		mCurAni = NULL;
		mNumFrame = 100;
		mSknMat = Editor::Singleton()->GetResMgr()->CreateMaterial(MaterialType::Type_SknMesh);

		y += 25;
		mSdTime = uiMgr->CreateSliderBar(mAniPanel);
		mSdTime->SetSize(mAniPanel->GetSize().width - offsetX1 * 2, 10);
		mSdTime->SetPos(offsetX1, y);
		mSdTime->SetMaximum(100);
		mSdTime->OnValueChanged().Add(this, &MeshView::OnTimeChange);
	}

	void MeshView::InitSknPage( IUiManager* uiMgr )
	{
		ITabPage* page = mTabCtrl->AddPage(_T("动画"));

		s32 offsetX1 = 10;
		s32 offsetX2 = 90;
		s32 y = 10;
		IButton* btn = uiMgr->CreateButton(page);
		btn->SetSize(100, 25);
		btn->SetPos(offsetX1, y);
		btn->SetText(_T("修改动画资源"));
		btn->OnClick().Add(this, &MeshView::OnChooseSkn);

		btn = uiMgr->CreateButton(page);
		btn->SetSize(100, 25);
		btn->SetPos(page->GetSize().width - btn->GetSize().width - offsetX1, y);
		btn->SetText(_T("移除动画"));
		btn->OnClick().Add(this, &MeshView::OnRemoveSkn);

		y += 30;
		ILabel* lb = uiMgr->CreateLabel(page);
		lb->SetText(_T("骨骼信息"));
		lb->SetPos(offsetX1, y);

		y += 25;
		mTvBone = uiMgr->CreateTreeView(page);
		mTvBone->SetSize(page->GetSize().width - offsetX1 * 2, 300);
		mTvBone->SetPos(offsetX1, y);
		mTvBone->OnSelectedChange().Add(this, &MeshView::OnBoneSelecteChanged);
	}

	void MeshView::OnResChoosed( Resource res )
	{
		if(mCurRes == res)
		{
			return;
		}
		mCurRes = res;
		mCurRes->Load();
		mMeshObj->BindResMesh(mCurRes);
		mSceneNode->AttachObject(mMeshObj);

		tstring str;
		StringUtils::S32ToStr(mCurRes->GetVertexNum(), str);
		mLbVertexNum->SetText(str);
		StringUtils::S32ToStr(mCurRes->GetTriangleNum(), str);
		mLbFaceNum->SetText(str);
		StringUtils::S32ToStr(mMeshObj->GetNumSubset(), str);
		mLbSubsetNum->SetText(str);

		mCurAni = NULL;
		mTvBone->Clear();
		mCbAnis->Clear();

		UpdateSubMat();
	}

	bool MeshView::OnChooseMatClicked( IControl* pCtrl)
	{
		Editor::Singleton()->GetResCenter()->OnResChoosed().Add(this, &MeshView::OnMatChoosed);
		mCurSubIndex = pCtrl->GetUserData();
		Editor::Singleton()->GetResCenter()->ChooseRes(ResType::ResType_Material);
		return true;
	}

	void MeshView::OnMatChoosed( Resource res )
	{
		mMeshObj->SetMaterial(mCurSubIndex, res);
	}

	void MeshView::UpdateSubMat( void )
	{
		if(!mSubMat.empty())
		{
			std::list<MatItem>::iterator it = mSubMat.begin();
			while(it != mSubMat.end())
			{
				MatItem& item = *it;
				delete item.mBtnChoose;
				delete item.mLbText;
				delete item.mPbImage;
				it++;
			}
		}

		IUiManager* uiMgr = mMeshInfoPage->GetUiMgr();
		s32 posX = 60;
		s32 y = 100;
		for(u32 i = 0; i < mCurRes->GetSubSetNum(); i++)
		{
			MatItem item;
			item.mLbText = uiMgr->CreateLabel(mMeshInfoPage);
			item.mLbText->SetPos(10, y);
			item.mLbText->SetText(_T("子集"));

			item.mPbImage = uiMgr->CreatePictureBox(mMeshInfoPage);
			item.mPbImage->SetSize(64, 64);
			item.mPbImage->SetPos(posX, y);
			item.mPbImage->SetBackImage(mMeshObj->GetMaterial(i)->GetDiffuseTex());
			item.mPbImage->SetDrawBorder(true);

			item.mBtnChoose = uiMgr->CreateButton(mMeshInfoPage);
			item.mBtnChoose->SetPos(135, y);
			item.mBtnChoose->SetSize(50, 20);
			item.mBtnChoose->SetText(_T("修改"));
			item.mBtnChoose->SetUserData(i);
			item.mBtnChoose->OnClick().Add(this, &MeshView::OnChooseMatClicked);

			y += 80;
		}
	}

	bool MeshView::OnChooseSkn( IControl* pCtrl )
	{
		Editor::Singleton()->GetResCenter()->OnResChoosed().Add(this, &MeshView::OnSknChoosed);
		Editor::Singleton()->GetResCenter()->ChooseRes(ResType::ResType_Skeletion);
		return true;
	}

	void MeshView::OnSknChoosed( Resource res )
	{
		ResSkeletion skn = res;
		if(mMeshObj->GetSkeletion() == skn)
		{
			return;
		}
		skn->Load();
		mMeshObj->SetSkeletion(skn);
		mMeshObj->SetMaterial(mSknMat);
		s32 num = skn->GetNumAni();
		mCbAnis->Clear();
		for(s32 i = 0; i < num; i++)
		{
			mCbAnis->AddItem(skn->GetAniByIndex(i)->GetName());
		}

		mTvBone->Clear();
		IBone* bone = skn->GetRootBone();
		ITreeViewItem* item = mTvBone->AddItem(bone->GetName());
		BuildBoneTree(item, bone);
	}


	void MeshView::BuildBoneTree( ITreeViewItem* item, IBone* bone )
	{
		IBone* child;
		u32 num = bone->GetNumChildren();
		for(u32 i = 0; i < num; i++)
		{
			child = (IBone*)bone->GetChild(i);
			ITreeViewItem* treeItem = item->AddItem(child->GetName());
			treeItem->SetUserData(bone->GetHandle());
			BuildBoneTree(treeItem, child);
		}
	}

	void MeshView::Show( bool show )
	{
		__super::Show(show);
		mAniPanel->SetVisible(show);
	}

	bool MeshView::OnTimeChange( IControl* pCtrl )
	{
		tchar buf[20] = {0};
		s32 curFrame = mSdTime->GetValue();
		_stprintf_s(buf, 20, _T("%d/%d"), curFrame, mNumFrame);
		mLbTime->SetText(buf);
		mLbTime->SetPos(mAniPanel->GetSize().width - mLbTime->GetSize().width - 10, mLbTime->GetPos().y);

		if(NULL != mCurAni)
		{
			f32 time = (f32)curFrame / 30.0f;
			mCurAni->SetTimePos(time);
		}
		return true;
	}

	bool MeshView::OnAniChange( IControl* pCtrl )
	{
		mCurAni = mMeshObj->GetAnimationController()->GetEntity(mCbAnis->GetText());
		mNumFrame = mCurAni->GetLen() * 30;
		mSdTime->SetMaximum(mNumFrame);
		OnTimeChange(pCtrl);
		if(mIsPlaying)
		{
			mMeshObj->GetAnimationController()->Play(mCurAni, Editor::Singleton()->mEvnConfig.blendTime);
		}
		else
		{
			mMeshObj->GetAnimationController()->Reset();
			mMeshObj->GetAnimationController()->ManualAdd(mCurAni);
		}
		return true;
	}

	bool MeshView::OnPlayClick( IControl* pCtrl )
	{
		if(NULL == mMeshObj || NULL == mCurAni)
		{
			return true;
		}

		if(!mIsPlaying)
		{
			mBtnPlay->SetBackImage(mImgPause);
			mSdTime->SetEnable(false);
			mMeshObj->GetAnimationController()->Play(mCurAni, Editor::Singleton()->mEvnConfig.blendTime);
			mIsPlaying = true;
		}
		else
		{
			mBtnPlay->SetBackImage(mImgPlay);
			mSdTime->SetEnable(true);
			mMeshObj->GetAnimationController()->Reset();
			mMeshObj->GetAnimationController()->ManualAdd(mCurAni);
			f32 pos = mCurAni->GetTimePos();
			mSdTime->SetValue(pos * 30);
			OnTimeChange(pCtrl);
			mIsPlaying = false;
		}
		return true;
	}

	bool MeshView::OnBoneSelecteChanged( IControl* pCtrl )
	{
		if(NULL == mCurAni)
		{
			return true;
		}

		
		mSdTime->ClearTags();
		ITreeViewItem* item = mTvBone->GetSelected();
		if(NULL == item)
		{
			return true;
		}
		
		IAnimation* ani = mMeshObj->GetSkeletion()->GetAnimation(mCurAni->GetName());		
		s32 handel = item->GetUserData();
		INodeAnimationTrack* track = ani->GetNodeTrack(handel);
		if(NULL == track)
		{
			return true;
		}

		u16 num = track->GetNumKeyFrames();
		for(u16 i = 0; i < num; i++)
		{
			IKeyFrame* frame = track->GetKeyFrame(i);
			mSdTime->AddTag(frame->GetTime() * 30);
		}
		return true;
	}

	bool MeshView::OnRemoveSkn( IControl* pCtrl )
	{
		mMeshObj->SetSkeletion(NULL);
		return true;
	}
}