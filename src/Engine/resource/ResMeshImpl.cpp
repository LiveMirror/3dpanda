#include "ResMeshImpl.h"
#include "FileStream.h"
#include <algorithm>
#include "MeshSerialize/MeshSerialize.h"

#include "ResourceMgr.h"
#include "SubMesh.h"
#include "VertexData.h"
#include "IndexData.h"
#include "meshserialize/ogremeshserialize.h"
#include "meshserialize/hymeshserialize.h"

namespace panda
{
	ResMeshImpl::ResMeshImpl( ResourceMgr* resMgr )
		:ResourceImpl(resMgr),
		mVertexData(NULL)
	{
		mResType = ResType::ResType_Mesh;
	}

	ResMeshImpl::~ResMeshImpl( void )
	{
		UnLoad();
	}

	bool ResMeshImpl::_Load( void )
	{
		// 根据后缀名判断格式
		tstring ext;
		FileStream::GetFileExtension(mPath, ext);

		// 将后缀到小写
		transform(ext.begin(), ext.end(), ext.begin(), tolower);

		// 查找相应的序列化器
		MeshSerialize* pLoader = _FindSerialize(ext);

		FileStream file;
		// 判断加载是否成功
		if(NULL == pLoader 
			|| !file.Open(mPath.c_str(), true)
			|| !pLoader->ImportMesh(file, (IResMesh*)mThis))
		{
			if(NULL != pLoader)
			{
				delete pLoader;
			}
			return false;
		}
		delete pLoader;
		UpdateAABB();
		return true;
	}

	void ResMeshImpl::_UnLoad( void )
	{
		if (NULL != mVertexData)
		{
			delete mVertexData;
			mVertexData = NULL;
		}
		SubMeshList::iterator itr = mSubMeshs.begin();
		while (itr != mSubMeshs.end())
		{
			delete *itr;
			itr++;
		}
	}

	const AABBOX& ResMeshImpl::GetAABBOX( void ) const
	{
		return mAABBOX;
	}

	void ResMeshImpl::UpdateAABB( void )
	{
		mAABBOX.ResetBox();
		if(NULL != mVertexData)
		{
			_UpdateAABB(mVertexData);
		}

		// 更新子模型包围盒
		SubMeshList::iterator itr = mSubMeshs.begin();
		while (itr != mSubMeshs.end())
		{
			if (NULL != (*itr)->mVertexData)
			{
				_UpdateAABB((*itr)->mVertexData);
			}
			itr++;
		}

		s32 i = 0;
	}

	void ResMeshImpl::UpdateNormals( void )
	{

	}

	s32 ResMeshImpl::GetVectorNum( void ) const
	{
		s32 num = 0;
		if(NULL != mVertexData)
		{
			num += mVertexData->mVertexCount;
		}

		// 计算子模型的顶点数
		SubMeshList::const_iterator itr = mSubMeshs.begin();
		while (itr != mSubMeshs.end())
		{
			if (NULL != (*itr)->mVertexData)
			{
				num += (*itr)->mVertexData->mVertexCount;
			}
			itr++;
		}
		return num;
	}

	s32 ResMeshImpl::GetTriangleNum( void ) const
	{
		s32 num = 0;
		SubMeshList::const_iterator itr = mSubMeshs.begin();
		while (itr != mSubMeshs.end())
		{
			num += (*itr)->mIndexData->mCount / 3;
			itr++;
		}
		return num;
	}

	u32 ResMeshImpl::GetSubSetNum( void ) const
	{
		return mSubMeshs.size();
	}

	MeshSerialize* ResMeshImpl::_FindSerialize( const tstring& ext )
	{
		if(ext.length() == 0 || ext == _T("3dm"))		// shine
		{

		}
		else if(ext == _T("mesh"))		// ogre
		{
			return new OgreMeshSerialize;
		}
		else if(ext == _T("hymesh"))
		{
			return new hyMeshSerialize;
		}
		//else if(ext == _T("3ds"))		// 3dmax
		//{
		//	return new _3dsSerialize;
		//}
		
		//else if (ext == _T("skn"))
		//{
		//	return new sknSerialize;
		//}
		//else if (ext == _T("msh"))
		//{
		//	return new mshSerialize;
		//}
		return NULL;
	}

	SubMesh* ResMeshImpl::CreateSubMesh( void )
	{
		SubMesh* pMesh = new SubMesh((IResMesh*)mThis);
		pMesh->mUserSharedVertices = false;
		mSubMeshs.push_back(pMesh);
		return pMesh;
	}

	ISubMesh* ResMeshImpl::GetSubMesh( u32 index ) const
	{
		if(index >= mSubMeshs.size())
		{
			return NULL;
		}
		return mSubMeshs[index];
	}

	void ResMeshImpl::_Save( const tchar* path )
	{
		FileStream file;
		if (!file.Open(path, false))
		{
			return;
		}
		//hyMeshSerialize* pSerialize = new hyMeshSerialize;
		//pSerialize->ExportMesh(file, (IResMesh*)mThisPtr);
	}

	void ResMeshImpl::_UpdateAABB( VertexData* buffer )
	{
		s32 offset;
		VertexData::HardwareBuffer* b = buffer->_FindPosBuffer(offset);
		u8* vb = (u8*)b->LockBuffer();
		s32 size = b->mVertexSize;
		for (u32 i = 0; i < buffer->mVertexCount; i++)
		{
			Vector3Df& pos = *(Vector3Df*)&vb[i * size + offset];
			mAABBOX += pos;
		}
		b->Unlock();
	}

	bool ResMeshImpl::_Intersects( const Ray& ray, VertexData* pData, IndexData* pIndex, ProbeResult& result)
	{
		f32 t, u, v;
		// 根据顶点的声明找到顶点位置数据
		s32 offset;
		s32 vertexSize;
		VertexData::HardwareBuffer* pBuffer = pData->_FindPosBuffer(offset);
		if (NULL == pBuffer)
		{
			return false;
		}
		vertexSize = pBuffer->mVertexSize;

		u8* vb = (u8*)pBuffer->LockBuffer();
		s32 num = pIndex->mCount / 3;
		s32 index = 0;
		if(pIndex->mIs32Bit)
		{
			// 顶点索引
			u32* ib = (u32*)pIndex->LockBuffer();
			for (s32 i = 0; i < num; i++)
			{
				Vector3Df& v0 = *(Vector3Df*)&(vb[ib[index] * vertexSize + offset]);
				Vector3Df& v1 = *(Vector3Df*)&(vb[ib[index + 1] * vertexSize + offset]);
				Vector3Df& v2 = *(Vector3Df*)&(vb[ib[index + 2] * vertexSize + offset]);

				if(ray.IntersectTriangle(v0, v1, v2, &t, &u, &v))
				{
					result.distance = t;
					result.pos = ray.sPosition + ray.sDirction * t;
					pIndex->Unlock();
					pBuffer->Unlock();
					return true;
				}
				index += 3;
			}
		}
		else
		{
			// 顶点索引
			u16* ib = (u16*)pIndex->LockBuffer();
			for (s32 i = 0; i < num; i++)
			{
				Vector3Df& v0 = *(Vector3Df*)&(vb[ib[index] * vertexSize + offset]);
				Vector3Df& v1 = *(Vector3Df*)&(vb[ib[index + 1] * vertexSize + offset]);
				Vector3Df& v2 = *(Vector3Df*)&(vb[ib[index + 2] * vertexSize + offset]);

				if(ray.IntersectTriangle(v0, v1, v2, &t, &u, &v))
				{
					result.distance = t;
					result.pos = ray.sPosition + ray.sDirction * t;
					pIndex->Unlock();
					pBuffer->Unlock();
					return true;
				}
				index += 3;
			}
		}
		pIndex->Unlock();
		pBuffer->Unlock();
		return false;
	}

	bool ResMeshImpl::Probe( const Ray& ray, ProbeResult& result)
	{
		SubMeshList::iterator itr = mSubMeshs.begin();
		while (itr != mSubMeshs.end())
		{
			VertexData* pVB = NULL;
			if ((*itr)->mUserSharedVertices)
			{
				pVB = mVertexData;
			}
			else
			{
				pVB = (*itr)->mVertexData;
			}
			if ( _Intersects(ray, pVB, (*itr)->mIndexData, result))
			{
				return true;
			}
			itr++;
		}
		return false;
	}
}