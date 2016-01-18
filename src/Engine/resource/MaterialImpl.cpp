#include "MaterialImpl.h"
#include "ResourceMgr.h"
#include "Resources/ITexture.h"
#include "Resources/IMaterial.h"
#include "FileStream.h"
#include "../renderSystem/MaterialSystem/TechniqueImpl.h"
#include "rendersystem/ITechnique.h"

namespace panda
{
	MaterialImpl::MaterialImpl( ResourceMgr* resMgr , RenderSystem* pRenderMgr)
		:ResourceImpl(resMgr),
		mRenderMgr(pRenderMgr),
		mTextureAlpha(false)
	{
		mResType = ResType::ResType_Material;
		mMatType = MaterialType::Type_StaticMesh;
	}

	MaterialImpl::~MaterialImpl()
	{
		UnLoad();
	}

	bool MaterialImpl::_Load( void )
	{
		FileStream file;
		if (!file.Open(mPath.c_str()))
		{
			return false;
		}
		char mark[3];
		file.Read(mark, 3 * sizeof(char));
		if (mark[0] != 'm' 
			|| mark[1] != 'a'
			|| mark[2] != 't')
		{
			// 错误的文件头
			return false;
		}

		s32 ver;
		file.Read(ver);
		s8 type;
		file.Read(type);
		if (type != mMatType)
		{
			// 不匹配的类型
			return false;
		}

		bool b;

		// diffuse
		file.Read(b);
		tstring str;
		if(b)
		{
			file.ReadStr(str);
			mDiffuseTex = mResMgr->LoadTexture(str.c_str());
			mDiffuseTex->Load();
		}

		// normal map
		file.Read(b);
		if(b)
		{
			file.ReadStr(str);
			mNormalMap = mResMgr->LoadTexture(str.c_str());
			mNormalMap->Load();
		}
		return _Load(file);
	}

	bool MaterialImpl::_Load( FileStream& file )
	{
		return true;
	}

	void MaterialImpl::_UnLoad( void )
	{
		TechniqueList::iterator itr = mTechniques.begin();
		while (itr != mTechniques.end())
		{
			delete *itr;
			itr++;
		}
		mTechniques.clear();
	}

	void MaterialImpl::_Save( const tchar* path )
	{
		if (NULL == path)
		{
			path = mPath.c_str();
		}
		FileStream file;
		if(file.Open(path, false))
		{
			char mark = 'm';
			file.Write(mark);
			mark = 'a';
			file.Write(mark);
			mark = 't';
			file.Write(mark);

			// 版本号
			s32 ver = 1;
			file.Write(ver);

			// 材质类型
			s8 type = mMatType;
			file.Write(type);

			bool hasDiffuse = !mDiffuseTex.IsNull();
			file.Write(hasDiffuse);
			if (hasDiffuse)
			{
				tstring str = mDiffuseTex->GetResPath();
				file.WriteStr(str);
			}

			bool hasNormal = !mNormalMap.IsNull();
			file.Write(hasNormal);
			if (hasNormal)
			{
				tstring str = mNormalMap->GetResPath();
				file.WriteStr(str);
			}

			_Save(file);
		}
	}

	void MaterialImpl::_Save( FileStream& file )
	{
		// do nothing
	}

	u16 MaterialImpl::GetNumTechniques( void )
	{
		return mTechniques.size();
	}

	ITechnique* MaterialImpl::GetTechnique( u16 index )
	{
		if (index >= mTechniques.size())
		{
			return NULL;
		}
		return mTechniques[index];
	}

	ITechnique* MaterialImpl::CreateTechnique( void )
	{
		TechniqueImpl* pImpl = new TechniqueImpl(mResMgr->GetDevice());
		pImpl->mParent = this;
		ITechnique* pTemp = new ITechnique(pImpl);
		mTechniques.push_back(pTemp);
		return pTemp;
	}

	void MaterialImpl::RemoveTechnique( ITechnique* technique )
	{

	}

	ResMaterial MaterialImpl::Clone( void )
	{
		ResMaterial mat = mResMgr->CreateMaterial(mMatType);
		MaterialImpl* pImpl = (MaterialImpl*)mat->mImpl;
		pImpl->mDiffuseTex = mDiffuseTex;
		pImpl->mNormalMap = mNormalMap;
		return mat;
	}

	void MaterialImpl::OnBind( ISceneObject* tagert )
	{

	}
}