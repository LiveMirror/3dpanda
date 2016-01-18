#include "ResTerrainImpl.h"
#include "ResourceMgr.h"
#include "VertexData.h"
#include "SubMesh.h"
#include "IndexData.h"
#include "FileStream.h"

namespace panda
{
	ResTerrainImpl::ResTerrainImpl( ResourceMgr* resMgr )
		:ResMeshImpl(resMgr)
	{
		mResType = ResType::ResType_Terrain;
	}

	void ResTerrainImpl::GenerateMesh()
	{
		mVertexData = new VertexData(mResMgr->GetDevice());

		mVertexData->mVertexCount = mWidth * mHeight;
		mVertexData->AddElement(0, 0, DeclareType::DECLTYPE_FLOAT3, 0, DeclareUsage::DECLUSAGE_POSITION, 0);
		mVertexData->AddElement(0, 12, DeclareType::DECLTYPE_UBYTE4, 0, DeclareUsage::DECLUSAGE_COLOR, 0);
		mVertexData->AddElement(0, 16, DeclareType::DECLTYPE_FLOAT3, 0, DeclareUsage::DECLUSAGE_NORMAL, 0);
		mVertexData->AddElement(0, 28, DeclareType::DECLTYPE_FLOAT2, 0, DeclareUsage::DECLUSAGE_TEXCOORD, 0);
		VertexData::HardwareBuffer* buffer = mVertexData->CreateHardwareBuffer(0, sizeof(TerrainVertex));

		// 构造顶点数据
		f32 x = -mTileSize * mWidth / 2;
		f32 y = -mTileSize * mHeight / 2;
		s32 index = 0;
		TerrainVertex* vb = (TerrainVertex*)buffer->LockBuffer();
		for (s32 row = 0; row < mHeight; row++)
		{
			y += mTileSize;
			x = -mTileSize * mWidth / 2;
			for (s32 col = 0; col < mWidth; col++)
			{
				TerrainVertex& temp = vb[index];
				temp.pos.x = x;
				temp.pos.y = 0;
				temp.pos.z = y;
				temp.normal.y = 1;
				temp.textureTens = 0x0;
				temp.u0 = (f32)col / mWidth;
				temp.v0 = (f32)row / mHeight;
				x += mTileSize;
				index++;
			}
		}
		buffer->Unlock();

		// 构造顶点索引数据
		SubMesh* pSM = CreateSubMesh();
		pSM->mUserSharedVertices = true;
		pSM->mIndexData = new IndexData(mResMgr->GetDevice());
		pSM->mIndexData->CreateHardwareBuffer((mWidth - 1) * (mHeight - 1) * 6, true);
		u32* ib = (u32*)pSM->mIndexData->LockBuffer();
		s32 startIndex = 0;
		index = 0;
		for (s32 row = 0; row < mHeight - 1; row++)
		{
			for (s32 col = 0; col < mWidth - 1; col++)
			{
				startIndex = row * mWidth + col;
				ib[index] = startIndex;
				ib[index + 1] = startIndex + mWidth;
				ib[index + 2] = startIndex + mWidth + 1;

				ib[index + 3] = startIndex;
				ib[index + 4] = startIndex + mWidth + 1;
				ib[index + 5] = startIndex + 1;
				index += 6;
			}
		}
		pSM->mIndexData->Unlock();
	}

	TerrainVertex* ResTerrainImpl::LockVertexBuffer( void )
	{
		return (TerrainVertex*)mVertexData->mBuffers[0]->LockBuffer();
	}

	TerrainVertex* ResTerrainImpl::LockVertexBuffer( u32 offset, u32 len )
	{
		return (TerrainVertex*)mVertexData->mBuffers[0]->LockBuffer(offset, len);
	}

	void ResTerrainImpl::UnLockBuffer( void )
	{
		mVertexData->mBuffers[0]->Unlock();
	}

	bool ResTerrainImpl::Probe( const Ray& ray, ProbeResult& result)
	{
		// 用2分法求出交点
		Vector3Df startPos = ray.sPosition;
		Vector3Df endPos = ray.sPosition;

		if(startPos.y < mAABBOX.minPoint.y)
		{
			// the camera under the terrain
			return false;
		}
		else if(startPos.y > mAABBOX.maxPoint.y)
		{

			Vector3Df normal(0, 1, 0);
			Vector3Df pos(0, mAABBOX.maxPoint.y, 0);
			Plane plane(normal, pos);
			if(!plane.IntersectWithRay(ray.sPosition, ray.sDirction, startPos))
			{
				return false;
			}
			pos = Vector3Df(0, mAABBOX.minPoint.y, 0);
			plane = Plane(normal, pos);
			plane.IntersectWithRay(ray.sPosition, ray.sDirction, endPos);

			f32 height;
			Vector3Df mid;
			TerrainVertex* vb = LockVertexBuffer();
			mid = endPos;
			for (s32 i = 0; i < 32; i++)
			{
				mid = endPos - startPos;
				mid /= 2;
				mid = startPos + mid;
				height = GetHeight(mid.x, mid.z, vb);
				if(height > mid.y)
				{
					endPos = mid;
				}
				else
				{
					startPos = mid;
				}
			}
			UnLockBuffer();
			result.pos = mid;
			mid = mid - ray.sPosition;
			result.distance = mid.Length();
		}
		return true;
	}

	f32 ResTerrainImpl::GetHeight( f32 x, f32 y )
	{
		TerrainVertex* vb = LockVertexBuffer();
		f32 h = GetHeight(x, y, vb);
		UnLockBuffer();
		return h;
	}

	void ResTerrainImpl::GetIndexByPos( f32 x, f32 y, s32& col, s32& row)
	{
		col = (s32)(x / mTileSize) + mWidth / 2;
		row = (s32)(y / mTileSize) + mHeight / 2;
		if (col < 0)
		{
			col = 0;
		}
		else if (col >= mWidth)
		{
			col = mWidth - 1;
		}
		if (row < 0)
		{
			row = 0;
		}
		else if (row >= mHeight)
		{
			row = mHeight - 1;
		}
	}

	f32 ResTerrainImpl::GetHeight( f32 x, f32 y, TerrainVertex* vb )
	{
		f32 height;
		s32 col, row;
		GetIndexByPos(x, y, col, row);

		if (row == mHeight - 1)
		{
			return 0;
		}

		s32 index0 = row * mWidth + col;
		s32 index1 = index0 + mWidth;
		s32 index2 = index1 + 1;

		Vector3Df pos = mAABBOX.maxPoint;
		pos.y += 10;
		Vector3Df dir(0, -1, 0);
		Ray ray(pos, dir);
		f32 t, u, v;

		Vector3Df v0 = vb[index0].pos;
		Vector3Df v1 = vb[index1].pos;
		Vector3Df v2 = vb[index2].pos;
		if (ray.IntersectTriangle(v0, v1, v2, &t, &u, &v))
		{
			// 交点
			Vector3Df node = pos + dir * t;
			height = node.y;
		}
		else
		{
			index1 = index2;
			index2 = index0 + 1;
			v0 = vb[index0].pos;
			v1 = vb[index1].pos;
			v2 = vb[index2].pos;
			if(ray.IntersectTriangle(v0, v1, v2, &t, &u, &v))
			{
				// 交点
				Vector3Df node = pos + dir * t;
				height = node.y;
			}
			else
			{
				height = v0.y;
			}
		}
		return height;
	}

	void ResTerrainImpl::UpdateNormals( void )
	{
		TerrainVertex* vb = LockVertexBuffer();
		for (s32 row = 1; row < mHeight - 2; row++)
		{
			for (s32 col = 1; col < mWidth - 2; col++)
			{
				Vector3Df& sNormal = vb[row* mWidth + col].normal;
				sNormal.x = vb[(row-1)* mWidth + col].pos.y - vb[(row+1)* mWidth + col].pos.y;
				sNormal.y = 10;
				sNormal.z = vb[row* mWidth + col-1].pos.y - vb[row* mWidth + col+1].pos.y;

				sNormal.Normalize();	//归一化
			}
		}
		UnLockBuffer();
	}

	bool ResTerrainImpl::_Load( void )
	{
		FileStream file;
		if(!file.Open(mPath.c_str()))
		{
			return false;
		}

		s32 ver;
		file.Read(ver);
		if (ver != 123)
		{
			return false;
		}

		file.Read(mWidth);
		file.Read(mHeight);
		file.Read(mTileSize);

		GenerateMesh();

		s32 num = mWidth * mHeight;
		TerrainVertex* vb = LockVertexBuffer();
		for (s32 i = 0; i < num; i++)
		{
			file.Read(vb[i].pos.y);
			file.Read(vb[i].textureTens);
		}
		UnLockBuffer();

		UpdateAABB();
		UpdateNormals();
		return true;
	}
}