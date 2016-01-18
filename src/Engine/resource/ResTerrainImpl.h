////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-5-15 22:34:46
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014515223446_H_
#define	_Tian_2014515223446_H_

#include "ResMeshImpl.h"

namespace panda
{
	/*
	*
	*/
	class ResTerrainImpl:public ResMeshImpl
	{
	public:
		ResTerrainImpl(ResourceMgr* resMgr);

		virtual bool	Probe(const Ray& ray, ProbeResult& result);
		virtual void	UpdateNormals(void);

		virtual bool	_Load(void);

		//! ���ݲ���,����ģ��
		void			GenerateMesh(void);
		TerrainVertex*	LockVertexBuffer(void);
		TerrainVertex*	LockVertexBuffer(u32 offset, u32 len);
		void			UnLockBuffer(void);

		//! ��ȡ������ĳ��߶�
		f32				GetHeight(f32 x, f32 y);
		//! �ⲿ���붥������,����Ƶ��lockbuffer
		f32				GetHeight(f32 x, f32 y, TerrainVertex* vb);

		void			GetIndexByPos(f32 x, f32 y, s32& col, s32& row);
	public:
		s32		mWidth;
		s32		mHeight;
		f32		mTileSize;
	};
}

#endif _Tian_2014515223446_H_