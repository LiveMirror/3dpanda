////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-14 22:12:05
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014414221205_H_
#define	_Tian_2014414221205_H_

#include "IPanda.h"
#include "IGame.h"
#include "DlgInput.h"
using namespace panda;

namespace editor
{
	struct	CameraParam
	{
		s32		moveStep;
		s32		wheelStep;
		s32		rotateStep;
	};

	struct	EvnParam
	{
		f32		blendTime;
	};

	class FrameUI;
	class ResCenter;
	class Level;
	class Editor
	{
	public:
		static Editor*	Singleton();
		Editor(void);

		ResCenter*		GetResCenter(void);
		IResMgr*		GetResMgr(void);
		IRenderSystem*	GetRenderSystem(void);
		ISceneMgr*		GetSceneMgr(void);
		ICamera*		GetCamera(void);
		DlgInput*		GetDlgInput(void);
		CameraParam&	GetCameraConfig(void);

		void			OpenLevel(ILevel* level);
		EventLevel&		OnLevelOpen(void);

		void			Run(void);
	public:
		static Editor*	gEditor;
		IPanda*			mEngine;
		ISceneMgr*		mSceneMgr;
		ICamera*		mCamera;
		CameraParam		mCameraConfig;
		EvnParam		mEvnConfig;
		ResCenter*		mResCenter;
		FrameUI*		mFrameUI;
		DlgInput		mDlgInput;

		IGame*			mGame;
		ILevel*			mLevel;
		IMeshObject*	mTerObj;
		EventLevel		mOnLevelOpen;
	};
}

#endif _Tian_2014414221205_H_