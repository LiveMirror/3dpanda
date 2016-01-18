////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-4-29 21:48:55
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014429214855_H_
#define	_Tian_2014429214855_H_

#include "Base/Config.h"
#include <d3dx9.h>
#include <vector>

namespace panda
{
	class IRenderTarget;
	class IPass;
	class RenderWindow;
	class IResMgr;
	class VertexData;
	class IndexData;
	class Effect
	{
	public:
		Effect(void);
		virtual ~Effect();
		void				Init(IDirect3DDevice9* device, IResMgr* pResMgr);

		void				AddPass(IPass* pass);
		void				RemovePass(IPass* pass);

		void				Resize(s32 width, s32 height);

		void				BeginEffect(void);
		void				EndEffect(void);

		void				OnLostDevice(void);

		IRenderTarget*		GetBackSurface(void);
	protected:
		IRenderTarget*		GetNextSurface(void);


	public:
		IDirect3DDevice9*	mDevice;
		typedef std::vector<IPass*>		PassList;
		PassList			mPasses;

		RenderWindow*		mParent;

		s32					mWidth;
		s32					mHeight;

		s8					mCurrentIndex;

		IRenderTarget*		mRT[2];			// �������ں��ڽ�������ȾĿ��
		int					mCurRt;

		IRenderTarget*		mColorMap;		// ��ɫ
		IRenderTarget*		mNormalMap;		// ����
		IRenderTarget*		mDepthMap;		// ���

		IDirect3DSurface9*	mOldColor0;
		IDirect3DSurface9*	mOldDepth;
		IDirect3DSurface9*	mOldColor1;
		IDirect3DSurface9*	mOldColor2;

		VertexData*			mVertexData;
		IndexData*			mIndexData;
	};
}

#endif _Tian_2014429214855_H_