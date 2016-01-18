//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 11:38:06_
// ����:  
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

		// �����ʱ��󶨵�ģ����ʱ�Ļص�
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
		Mtrl				mMtr;				// ����
		RenderSystem*		mRenderMgr;			// ��ǰ��Ⱦ��
		ResTexture			mDiffuseTex;		// ��������ͼ
		ResTexture			mNormalMap;			// ������ͼ
		MaterialType::eValue	mMatType;		// ��������

		typedef std::vector<ITechnique*>	TechniqueList;
		TechniqueList		mTechniques;

		bool				mReceiveShaows;		// �Ƿ��������Ӱ
		bool				mCastsShaows;		// �Ƿ�Ͷ����Ӱ
		bool				mTextureAlpha;		// ����͸��
	};
}

#endif // _MATERIALIMPL_201443113806_