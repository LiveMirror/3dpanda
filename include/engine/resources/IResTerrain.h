////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-15 22:23:39
// 描述:  
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

		//! 获取地形上某点高度
		virtual f32				GetHeight(f32 x, f32 y);
		//! 获取某点高度
		//! 外部传入顶点数据,避免频繁lockbuffer
		virtual f32				GetHeight(f32 x, f32 y, TerrainVertex* vb);

		virtual TerrainVertex*	LockVertexBuffer(void);
		virtual TerrainVertex*	LockVertexBuffer(u32 offset, u32 len);
		virtual void			UnLockBuffer(void);
	};
}

#endif _Tian_2014515222339_H_