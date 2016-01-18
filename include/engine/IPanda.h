////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-20 21:31:03
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014220213103_H_
#define	_Tian_2014220213103_H_

#include "ui/IButton.h"
#include "ui/IPanel.h"
#include "ui/IPictureBox.h"
#include "ui/IMenu.h"
#include "ui/IComboBox.h"
#include "ui/ITextBox.h"
#include "ui/ILabel.h"
#include "ui/IScrollBar.h"
#include "ui/ICheckBox.h"
#include "ui/IProgressBar.h"
#include "ui/IDialog.h"
#include "ui/IListBox.h"
#include "ui/ISliderBar.h"
#include "ui/ITabCtrl.h"
#include "ui/IRadioButton.h"
#include "ui/IToolBar.h"
#include "ui/ITreeView.h"
#include "ui/IListView.h"
#include "ui/IFoldPanel.h"
#include "ui/IPropertyGrid.h"
#include "ui/IUiManager.h"

#include "base/Struct.h"
#include "renderSystem/IRenderWindow.h"
#include "renderSystem/IRenderSystem.h"

#include "animation/IKeyFrame.h"
#include "animation/IAnimation.h"
#include "animation/IAnimationTrack.h"
#include "animation/IAnimationEntity.h"
#include "animation/IAnimationController.h"

#include "particleSystem/IBillboardRender.h"
#include "particleSystem/IParticleAffector.h"
#include "particleSystem/ILinerForceAffector.h"
#include "particleSystem/IColourAffector.h"
#include "particleSystem/IParticleEmitter.h"
#include "particleSystem/IParticleTechnique.h"

#include "resources/ITexture.h"
#include "resources/IResMesh.h"
#include "resources/IMaterial.h"
#include "resources/ITerrainMaterial.h"
#include "resources/IResTerrain.h"
#include "resources/IResSkeleton.h"
#include "resources/IParticleSys.h"
#include "resources/IResMgr.h"

#include "scene/ICamera.h"
#include "scene/ISceneNode.h"
#include "scene/IBone.h"
#include "scene/IMeshObject.h"
#include "scene/IParticleObject.h"
#include "scene/ISceneMgr.h"

namespace panda
{
	/*
	*
	*/
	class IPanda
	{
	public:
		//-----------------------------------------
		//! 初始化渲染设备
		//! param device:IDirect3DDevice9
		virtual IRenderWindow*	InitDevice(RenderWindowParam* info = NULL, void* device = NULL) = 0;

		virtual IRenderSystem*	GetRenderSystem(void) = 0;
		virtual IResMgr*		GetResMgr(void) = 0;

		//-----------------------------------------
		//! 创建一个场景管理器
		//! 你需要手动调用ISceneMgr的Release方法是否它
		virtual ISceneMgr*		CreateSceneMgr(void) const = 0;

		//-----------------------------------------
		//! 进入消息循环
		virtual void			Run(void) = 0;

		//! 释放
		virtual void			Release(void) = 0;
	};

	extern "C" ENGINE_API IPanda*  TheEngine();
}

#endif _Tian_2014220213103_H_