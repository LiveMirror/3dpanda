//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 10:54:31_
// ����:  
//

#ifndef _IRESMESH_201443105431_
#define _IRESMESH_201443105431_

#include "Base/AABBOX.h"
#include "IResource.h"

namespace panda
{
	class ISubMesh
	{
	public:
		virtual	void						SetRenderOperation(RenderOperation::eValue op) = 0;
		virtual RenderOperation::eValue		GetRenderOperation(void)const = 0;
		virtual void						SetVertexCount(s32 count) = 0;
		virtual void						SetIndexCount(s32 count, bool is32Bit) = 0;

		//! ����4��������������SetVertexCount�����
		//! dataType:DeclareType
		//! usage:DeclareUsage
		virtual void						AddElement(s32 source, s32 offset, s8 dataType, s8 usage, s8 usageIndex) = 0;
		virtual void						CreateVertexBuffer(s32 sourceID, s32 vertexSize) = 0;
		virtual void*						LockVertexBuffer(s32 sourceID) = 0;
		virtual void						UnLockVertexBuffer(s32 sourceID) = 0;

		//! �����2������������SetIndexCount�����
		virtual void*						LockIndexBuffer(void) = 0;
		virtual void						UnLockIndexBuffer(void) = 0;
	};

	class ResMeshImpl;
	class IResMesh:public IResource
	{
	public:
		IResMesh(ResMeshImpl* pImpl);

		//! ��ð�Χ��
		virtual const AABBOX&	GetAABBOX()const;

		//! ���°�Χ��
		virtual	void			UpdateAABB(void);

		//! ����ģ�ͷ���
		virtual void			UpdateNormals(void);

		//! ��ö������
		virtual s32				GetVertexNum(void) const;

		//! ��������θ���
		virtual s32				GetTriangleNum(void) const;

		//! ����Ӽ�����
		virtual u32				GetSubSetNum(void) const;

		//! �����ģ��
		virtual ISubMesh*		GetSubMesh(u32 index) const;

		//! ������ģ��
		virtual ISubMesh*		CreateSubMesh(void);
	};
}

#endif // _IRESMESH_201443105431_