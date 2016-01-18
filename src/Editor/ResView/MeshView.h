////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-21 23:23:01
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014421232301_H_
#define	_Tian_2014421232301_H_

#include "ResView.h"

namespace editor
{
	struct MatItem
	{
		ILabel*			mLbText;
		IPictureBox*	mPbImage;
		IButton*		mBtnChoose;
	};

	class MeshView:public ResView
	{
	public:
		MeshView(void);
		virtual void	InitUI(IUiManager* uiMgr);
		virtual void	OnResChoosed(Resource res);
		virtual void	Show(bool show);
	protected:
		void			InitInfoPage(IUiManager* uiMgr);
		void			InitSknPage(IUiManager* uiMgr);
		void			InitSknPanel(IUiManager* uiMgr);
		void			UpdateSubMat(void);
		bool			OnChooseMatClicked(IControl* pCtrl);
		void			OnMatChoosed(Resource res);
		bool			OnChooseSkn(IControl* pCtrl);
		bool			OnRemoveSkn(IControl* pCtrl);
		void			OnSknChoosed(Resource res);
		bool			OnTimeChange(IControl* pCtrl);

		bool			OnAniChange(IControl* pCtrl);

		bool			OnPlayClick(IControl* pCtrl);

		void			BuildBoneTree(ITreeViewItem* item, IBone* bone);
		bool			OnBoneSelecteChanged(IControl* pCtrl);
	public:
		ResMesh			mCurRes;
		IMeshObject*	mMeshObj;
		s32				mCurSubIndex;
		ITabCtrl*		mTabCtrl;
		ITabPage*		mMeshInfoPage;
		ILabel*			mLbVertexNum;
		ILabel*			mLbFaceNum;
		ILabel*			mLbSubsetNum;

		/*********************** Skn Page ********************/
		ITreeView*		mTvBone;
		
		/********************** ani Panel ********************/
		IPanel*			mAniPanel;
		ISliderBar*		mSdTime;
		ILabel*			mLbTime;
		IComboBox*		mCbAnis;
		s32				mNumFrame;
		ResMaterial		mSknMat;
		IAnimationEntity*	mCurAni;
		IButton*		mBtnPlay;
		bool			mIsPlaying;
		ResTexture		mImgPlay;
		ResTexture		mImgPause;
		std::list<MatItem>	mSubMat;
	};
}

#endif _Tian_2014421232301_H_