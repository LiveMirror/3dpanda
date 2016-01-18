#include "ResourceMgr.h"

#include "resources/ITexture.h"
#include "resources/IResMesh.h"
#include "resources/IMaterial.h"
#include "resources/IResTerrain.h"
#include "resources/IResSkeleton.h"
#include "resources/ITerrainMaterial.h"
#include "resources/IParticleSys.h"

#include "rendersystem/ITechnique.h"
#include "rendersystem/IPass.h"
#include "renderSystem/IRenderTarget.h"

#include "../rendersystem/materialsystem/passmgr.h"
#include "../renderSystem/RenderTargetImpl.h"
#include "../rendersystem/materialsystem/terpass.h"

#include "materialserialize/MaterialSerialize.h"

#include "TextureImpl.h"
#include "ResMeshImpl.h"
#include "MaterialImpl.h"
#include "ResSkeletonImpl.h"
#include "ResTerrainImpl.h"
#include "TerrainMaterialImpl.h"

#include "particlesysimpl.h"





namespace panda
{
	ResourceMgr::ResourceMgr(void)
		:mResCreateCount(0)
	{

	}

	ResourceMgr::~ResourceMgr( void )
	{

	}

	panda::ResTexture ResourceMgr::LoadTexture( const tchar* strPath )
	{
		// 查找资源是否已经创建
		ResMap::iterator it = mResources.find(strPath);
		if(it != mResources.end())
		{
			return (ITexture*)it->second;
		}
		TextureImpl* pImpl = new TextureImpl(this);
		ITexture* pTex = new ITexture(pImpl);
		pImpl->mPath = strPath;
		mResources[pImpl->mPath] = pTex;
		return pTex;
	}

	IDirect3DDevice9* ResourceMgr::GetDevice( void )
	{
		return mDevicePtr;
	}

	ResMesh ResourceMgr::CreateMesh( void )
	{
		ResMeshImpl* pImpl = new ResMeshImpl(this);
		pImpl->mResState = ResState::Loaded;
		tstring resName = _T("");
		_GetResName(resName);
		pImpl->mPath = resName;
		IResMesh* pMesh = new IResMesh(pImpl);
		mResources[resName] = pMesh;
		return pMesh;
	}

	ResMesh ResourceMgr::LoadMesh( const tchar* strPath )
	{
		// 查找资源是否已经创建
		ResMap::iterator it = mResources.find(strPath);
		if(it != mResources.end())
		{
			return (IResMesh*)it->second;
		}
		ResMeshImpl* pImpl = new ResMeshImpl(this);
		pImpl->mPath = strPath;
		IResMesh* pMesh = new IResMesh(pImpl);
		mResources[strPath] = pMesh;
		return pMesh;
	}

	void ResourceMgr::_GetResName( tstring& name )
	{
		name = _T("CreateRes");
		tchar buf[12] = {0};
		_stprintf_s(buf, 12, _T("%d"), mResCreateCount);
		name += buf;
		mResCreateCount++;
	}


	void ResourceMgr::BindDevice( IDirect3DDevice9* device )
	{
		mDevicePtr = device;

		mPassMgr = new PassMgr(this);
		mPassMgr->Init();

		mDefaultMat = CreateMaterial();
	}


	ResMaterial ResourceMgr::CreateMaterial( MaterialType::eValue type /*= MaterialType::Type_StaticMesh*/ )
	{
		if(NULL == mDevicePtr)
		{
			return NULL;
		}
		IMaterial* pMat = MaterialSerialize::CreateMaterial((MaterialType::eValue)type, this, mRenderMgr);
		MaterialImpl* pImpl = (MaterialImpl*)pMat->mImpl;
		pImpl->mIsCreater = true;
		pImpl->mResState = ResState::Loaded;
		pImpl->mDiffuseTex = LoadTexture(_T("../media/default.jpg"));
		pImpl->mDiffuseTex->Load();
		tstring resName = _T("");
		_GetResName(resName);
		pImpl->mPath = resName;
		mResources[resName] = pMat;
		return pMat;
	}

	ResMaterial ResourceMgr::GetDefaultMat( void )
	{
		return mDefaultMat;
	}

	ResMaterial ResourceMgr::LoadMaterial( const tchar* strPath )
	{
		// 查找资源是否已经创建
		ResMap::iterator it = mResources.find(strPath);
		if(it != mResources.end())
		{
			return (IMaterial*)it->second;
		}

		FileStream file;
		if (file.Open(strPath))
		{
			char mark[3];
			file.Read(mark, 3 * sizeof(char));
			if (mark[0] != 'm' 
				|| mark[1] != 'a'
				|| mark[2] != 't')
			{
				// 错误的文件头
				return NULL;
			}

			s32 ver;
			file.Read(ver);
			if (ver > 1)
			{
				// 不支持的文件版本
				return NULL;
			}
			s8 type;
			file.Read(type);

			IMaterial* pMat = MaterialSerialize::CreateMaterial((MaterialType::eValue)type, this, mRenderMgr);
			if(NULL != pMat)
			{
				pMat->mImpl->mPath = strPath;
			}
			return pMat;
		}
		return NULL;
	}

	IRenderTarget* ResourceMgr::CreateRenderTarget( s32 width, s32 height )
	{
		RenderTargetImpl* pImpl = new RenderTargetImpl(this);
		pImpl->mTexWidth = width;
		pImpl->mTexHeight = height;
		IRenderTarget* pTarget = new IRenderTarget(pImpl);
		pImpl->Resize();
		return pTarget;
	}

	ResSkeletion ResourceMgr::LoadSkeleton( const tchar* strPath )
	{
		// 查找资源是否已经创建
		ResMap::iterator it = mResources.find(strPath);
		if(it != mResources.end())
		{
			return (IResSkeleton*)it->second;
		}
		ResSkeletonImpl* pImpl = new ResSkeletonImpl(this);
		pImpl->mPath = strPath;
		IResSkeleton* pSkn = new IResSkeleton(pImpl);
		mResources[pImpl->mPath] = pSkn;
		return pSkn;
	}

	ResTerrain ResourceMgr::CreateTerrain( s32 width, s32 height, f32 tileSize )
	{
		ResTerrainImpl* pImpl = new ResTerrainImpl(this);
		pImpl->mWidth = width;
		pImpl->mHeight = height;
		pImpl->mTileSize = tileSize;

		// 生成模型
		pImpl->GenerateMesh();
		pImpl->UpdateAABB();
		pImpl->UpdateNormals();

		tstring resName = _T("");
		_GetResName(resName);
		pImpl->mPath = resName;
		IResTerrain* pTer = new IResTerrain(pImpl);
		mResources[resName] = pTer;
		return pTer;
	}

	ResTerrain ResourceMgr::LoadTerrian( const tchar* strPath )
	{
		throw 0;
	}

	ResParticleSys ResourceMgr::CreateParticleSys( void )
	{
		ParticleSysImpl* pImpl = new ParticleSysImpl(this);
		pImpl->mResState = ResState::Loaded;
		tstring resName = _T("");
		_GetResName(resName);
		pImpl->mPath = resName;
		IParticleSys* pPart = new IParticleSys(pImpl);
		mResources[resName] = pPart;
		return pPart;
	}

	ResParticleSys ResourceMgr::LoadParticleSys( const tchar* strPath )
	{
		throw 0;
	}
}