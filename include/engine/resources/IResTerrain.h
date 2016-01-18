////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-5-15 22:23:39
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014515222339_H_
#define	_Tian_2014515222339_H_

#include "IResMesh.h"

namespace panda
{
	class ResTerrainImpl;
	class IResTerrain:public IResMesh
	{
	public:
		IResTerrain(ResTerrainImpl* pImpl);

		virtual s32				GetWidth(void);
		virtual s32				GetHeight(void);
		virtual f32				GetTileSize(void);

		//! ��ȡ������ĳ��߶�
		virtual f32				GetHeight(f32 x, f32 y);
		//! ��ȡĳ��߶�
		//! �ⲿ���붥������,����Ƶ��lockbuffer
		virtual f32				GetHeight(f32 x, f32 y, TerrainVertex* vb);

		virtual TerrainVertex*	LockVertexBuffer(void);
		virtual TerrainVertex*	LockVertexBuffer(u32 offset, u32 len);
		virtual void			UnLockBuffer(void);
	};
}

#endif _Tian_2014515222339_H_