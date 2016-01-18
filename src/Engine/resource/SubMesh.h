//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 11:00:28_
// 描述:  
//

#ifndef _SUBMESH_201443110028_
#define _SUBMESH_201443110028_

#include "Base/Config.h"
#include "Base/Struct.h"
#include "Resources/IResMesh.h"

namespace panda
{
	class IResMesh;
	class VertexData;
	class IndexData;
	class SubMesh:public ISubMesh
	{
	public:
		SubMesh(IResMesh* parent);
		~SubMesh(void);
		virtual	void						SetRenderOperation(RenderOperation::eValue op);
		virtual RenderOperation::eValue		GetRenderOperation(void)const;

		virtual void						SetVertexCount(s32 count);
		virtual void						SetIndexCount(s32 count, bool is32Bit);
		virtual void						CreateVertexBuffer(s32 sourceID, s32 vertexSize);
		virtual void						AddElement(s32 source, s32 offset, s8 dataType, s8 usage, s8 usageIndex);
		virtual void*						LockVertexBuffer(s32 sourceID);
		virtual void						UnLockVertexBuffer(s32 sourceID);

		virtual void*						LockIndexBuffer(void);
		virtual void						UnLockIndexBuffer(void);

	public:
		tstring						mMatrailName;
		IResMesh*					mParent;
		bool						mUserSharedVertices;
		VertexData*					mVertexData;
		IndexData*					mIndexData;
		RenderOperation::eValue		mRenderOp;

		void*						mUserData;
	};
}

#endif // _SUBMESH_201443110028_