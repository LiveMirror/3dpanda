//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 10:58:34_
// ����:  
//

#ifndef _RESMESHIMPL_201443105834_
#define _RESMESHIMPL_201443105834_

#include "Base/AABBOX.h"
#include "ResourceImpl.h"
#include <vector>

namespace panda
{
	class MeshSerialize;
	class VertexData;
	class IndexData;
	class ISubMesh;
	class SubMesh;

	class ResMeshImpl:public ResourceImpl
	{
	public:
		ResMeshImpl(ResourceMgr* resMgr);
		virtual ~ResMeshImpl(void);

		virtual bool	_Load(void);
		virtual void	_UnLoad(void);
		virtual void	_Save(const tchar* path);

		// ��ð�Χ��
		const AABBOX&	GetAABBOX(void)const;

		// ���°�Χ��
		void			UpdateAABB(void);

		// ����ģ�ͷ���
		virtual void	UpdateNormals(void);

		// ��ö������
		s32				GetVectorNum(void) const;

		// ��������θ���
		s32				GetTriangleNum(void) const;

		// ����Ӽ�����
		u32				GetSubSetNum(void) const;

		ISubMesh*		GetSubMesh(u32 index) const;

		//! ������mesh
		SubMesh*		CreateSubMesh(void);

	public:
		//! ̽���㷨д��ģ���У����ڲ�ͬģ���Լ��ڲ��Ż��㷨
		virtual bool	Probe(const Ray& ray, ProbeResult& result);

	protected:
		MeshSerialize*	_FindSerialize(const tstring& ext);
		void			_UpdateAABB(VertexData* buffer);

		//! �ж�IndexData�����ģ�������Ƿ���ray�����ཻ
		//! ���߱����Ǿ������������仯
		bool	_Intersects(const Ray& ray, VertexData* pData, IndexData* pIndex, ProbeResult& result);

	public:
		VertexData*		mVertexData;
		typedef std::vector<SubMesh*>		SubMeshList;
		SubMeshList		mSubMeshs;
		AABBOX			mAABBOX;		// ��Χ��
	};
}

#endif // _RESMESHIMPL_201443105834_