//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/16 15:37:33_
// ����:  
//

#ifndef _TERVIEW_2014516153733_
#define _TERVIEW_2014516153733_

#include "SceneView.h"
#include <vector>

namespace editor
{
	class DlgBlendMat;
	class IBrush;
	class TextureBrush;
	class FlatBrush;
	class TerView:public SceneView
	{
	public:
		TerView(void);
		virtual void		InitUI(IUiManager* uiMgr, ISceneNode* pNode);
		virtual void		OnMouseMove(MouseEventArgs& e);
		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseUp(MouseEventArgs& e);
	public:
		bool				OnRadiusChange(IControl* pCtrl);
		bool				OnInsideRadiusChange(IControl* pCtrl);
		bool				OnValueChange(IControl* pCtrl);
		bool				OnBrushChange(IControl* pCtrl);
		bool				OnTextChange(IControl* pCtrl);
		bool				OnAddClick(IControl* pCtrl);
		bool				OnEditClick(IControl* pCtrl);
		bool				OnDelClick(IControl* pCtrl);
		
		void				RegestBrush(IBrush* brush);
		void				UpdateBrush(f32 x, f32 y);

		void				RefreshMat(void);
	public:
		typedef std::vector<IBrush*>	BrushList;
		BrushList			mBrushs;
		IBrush*				mCurBrush;
		Vector2Df			mOldPos;

		DlgBlendMat*		mDlgBlendMat;
		FlatBrush*			mBrushFlat;
		TextureBrush*		mBrushTex;
		IMeshObject*		mBrushObj;		// ˢ�ӳ�������
		ResMesh				mBrushMesh;		// ����ˢ��ģ��
		ISubMesh*			mOutSubMesh;	// ��Ȧ
		ISubMesh*			mInsideSubMesh;	// ��Ȧ

		IComboBox*			mCbBrushType;
		ISliderBar*			mSdRadius;
		ILabel*				mLbRadius;
		ISliderBar*			mSdInRadius;
		ILabel*				mLbInRadius;
		ISliderBar*			mSdValue;
		ILabel*				mLbValue;

		IListBox*			mLbTexture;
	};
}

#endif // _TERVIEW_2014516153733_