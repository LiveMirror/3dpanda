////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2012-10-23 23:31:21
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_20121023233121_H_
#define	_Tian_20121023233121_H_

#include <list>
#include <map>
#include "MeshSerialize.h"

namespace panda
{
	struct subMeshInfo
	{
		u16*		pIndexBuf;
		u32			indexCount;
		tstring		matrailName;
	};

	struct VertexBoneAssignment
	{
		u32 vertexIndex;
		u16 boneIndex;
		f32 weight;
	};

	class ResourceMgr;
	class ResMeshImpl;
	class VertexData;
	/*
	* ogre mesh��ʽģ�ͽ�����
	*/
	class OgreMeshSerialize:public MeshSerialize
	{
	public:
		typedef std::multimap<u32, VertexBoneAssignment> AssignmentList;
		
		// ����ģ��
		virtual bool	ImportMesh(FileStream& file, IResMesh* pMesh);

		void			readMesh(FileStream& file, IResMesh* pMesh);
		void			readSubMesh(FileStream& file, ResMeshImpl* pImpl);
		void			readGeometry(FileStream& file, ResMeshImpl* pMesh, VertexData* dest);
		void			readGeometryVertexDeclaration(FileStream& file, VertexData* dest);
		void			readGeometryVertexBuffer(FileStream& file, ResMeshImpl* pMesh, VertexData* dest);
		void			readBoundsInfo(FileStream& file);
		void			readSubMeshNameTable(FileStream& file);
		void			readSkeletonLink(FileStream& file, ResMeshImpl* pMesh);

		void			readMeshBoneAssignment(FileStream& file, ResMeshImpl* pMesh);

		// read a chunk header
		u16				readChunk(FileStream& file);
		// ����һ��Chunk�ļ�ͷ
		void			_turnBack(FileStream& file);

		// ���ݶ�������ݹ���ģ��
		// ��Ϊogre�Ĺ���Ȩ����Ϣû�кͶ������ݴ洢��һ��
		void			_CompileMesh(IResMesh* pMesh);

		// ���ݹ���������Ϣ, ���¹�����������
		void			_RebulidVertexData(VertexData* pData, AssignmentList* assigns);

		// ת��ogre��usage���嵽dx
		s16				_ConvertUsage(s16 ogreUsage);
	protected:
		s32				mStreamLen;
	};
}

#endif _Tian_20121023233121_H_