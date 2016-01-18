//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/24 14:10:21_
// 描述:  
//

#ifndef _EFFECTVIEW_2014524141021_
#define _EFFECTVIEW_2014524141021_

#include "ResView.h"

namespace editor
{
	class EffectView:public ResView
	{
	public:
		EffectView(void);
		virtual void	InitUI(IUiManager* uiMgr);
		virtual void	OnResChoosed(Resource res);
		virtual void	OnMouseMove(MouseEventArgs& e);
		virtual void	OnMouseDown(MouseEventArgs& e);
		virtual void	OnSaveClick(void);

	protected:
		void			InitPropertyUI(IFoldPage* page);
		void			InitEmitterUI(IFoldPage* page);
		void			InitAffectorUI(IFoldPage* page);

		void			OnSelTecqChange(IParticleTechnique* tecq);
		bool			_OnTecqSelChange(IControl* pCtrl);
		bool			OnTecqKeyDown(IControl* pCtrl, KeyEventArgs& e);
		void			OnSelEmitterChange(IParticleEmitter* emitter);
		bool			_OnEmitterSelChange(IControl* pCtrl);
		void			OnSelAffectorChange(IParticleAffector* affector);
		bool			_OnAffectorSelChange(IControl* pCtrl);

		bool			OnAddTecqClick(IControl* pCtrl);
		void			OnTecqNameInput(const tstring& name);

		bool			OnAddEmitterClick(IControl* pCtrl);
		void			OnEmitterInput(const tstring& name);

		bool			OnAddAffectClick(IControl* pCtrl);
		void			OnAffectInput(const tstring& name);
		
		bool			OnPlayClick(IControl* pCtrl);

	public:
		ResParticleSys			mCurEffect;
		IParticleTechnique*		mCurTecq;
		IParticleObject*		mParticleObject;

		IComboBox*		mCbEntityType;
		IListBox*		mLbEntitys;
		IFoldPanel*		mFpTechnique;

		// base
		ITextBox*		mTbTimeToLive;
		IButton*		mBtnPlay;
		ResTexture		mImgPlay;
		ResTexture		mImgPause;

		// info
		ILabel*			mLbTechType;

		// emitter
		IParticleEmitter*	mCurEmitter;
		IListBox*		mLbEmitters;
		IComboBox*		mCbEmitterType;
		IPropertyGrid*	mPgEmitter;

		// affector
		IParticleAffector*	mCurAffector;
		IListBox*		mLbAffectors;
		IComboBox*		mCbAffectorType;
		IPropertyGrid*	mPgAffector;
	};
}

#endif // _EFFECTVIEW_2014524141021_