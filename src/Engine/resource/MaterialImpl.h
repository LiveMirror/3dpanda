//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 11:38:06_
// 描述:  
//

#ifndef _MATERIALIMPL_201443113806_
#define _MATERIALIMPL_201443113806_

#include <vector>
#include "ResourceImpl.h"
#include "Resources/ResRefDefine.h"
#include "FileStream.h"

namespace panda
{
	class RenderSystem;
	class ITechnique;
	class ISceneObject;

	class MaterialImpl:public ResourceImpl
	{
	public:
		MaterialImpl(ResourceMgr* resMgr, RenderSystem* pRenderMgr);
		virtual ~MaterialImpl(void);

		// 当材质被绑定到模型上时的回调
		virtual void	OnBind(ISceneObject* tagert);

		virtual bool	_Load(void);
		virtual bool	_Load(FileStream& file);
		virtual void	_UnLoad(void);

		virtual ResMaterial		Clone(void);
		virtual void			_Save(const tchar* path);
		virtual void			_Save(FileStream& file);

		u16				GetNumTechniques(void);
		ITechnique*		GetTechnique(u16 index);
		ITechnique*		CreateTechnique(void);

		void			RemoveTechnique(ITechnique* technique);

	public:
		Mtrl				mMtr;				// 材质
		RenderSystem*		mRenderMgr;			// 当前渲染器
		ResTexture			mDiffuseTex;		// 漫反射贴图
		ResTexture			mNormalMap;			// 法线贴图
		MaterialType::eValue	mMatType;		// 材质类型

		typedef std::vector<ITechnique*>	TechniqueList;
		TechniqueList		mTechniques;

		bool				mReceiveShaows;		// 是否接收受阴影
		bool				mCastsShaows;		// 是否投射阴影
		bool				mTextureAlpha;		// 纹理透明
	};
}

#endif // _MATERIALIMPL_201443113806_