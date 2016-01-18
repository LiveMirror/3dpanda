//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/22 10:36:51_
// ����:  
//

#ifndef _MATVIEW_2014422103651_
#define _MATVIEW_2014422103651_

#include "ResView.h"

namespace editor
{
	class MatView:public ResView
	{
	public:
		virtual void	InitUI(IUiManager* uiMgr);
		virtual void	OnResChoosed(Resource res);
		virtual void	OnMouseMove(MouseEventArgs& e);
		virtual void	OnMouseDown(MouseEventArgs& e);
		virtual void	OnSaveClick(void);
	protected:
		bool			OnChooseDiffuseImageClicked(IControl* pCtrl);
		bool			OnChooseNormalImageClicked(IControl* pCtrl);
		bool			OnChangeMesh(IControl* pCtrl);
		bool			OnUserDefaultMesh(IControl* pCtrl);
		void			OnTextureChoosed(Resource res);
		void			OnNormalTextureChoosed(Resource res);
		void			OnMeshChoosed(Resource res);
	public:
		ResMaterial		mCurRes;
		IMeshObject*	mMeshObj;
		ResMesh			mResBall;
		ILabel*			mLbMatType;
		IPictureBox*	mPbDiffuse;
		IPictureBox*	mPbNormal;
		Vector2Dn		mOldPoint;
	};
}

#endif // _MATVIEW_2014422103651_