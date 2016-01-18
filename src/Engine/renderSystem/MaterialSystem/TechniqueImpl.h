//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 15:25:41_
// 描述:  
//

#ifndef _TECHNIQUEIMPL_201443152541_
#define _TECHNIQUEIMPL_201443152541_

#include "Base/Config.h"
#include <d3dx9.h>
#include <vector>

namespace panda
{
	struct PassType
	{
		enum eValue
		{
			type_StaticMesh,
			type_SknMesh,
			type_Line,
			type_Terrain,
			type_Water,
			type_Effect,
		};
	};

	class MaterialImpl;
	class SceneObjectImpl;
	class IPass;
	class ICamera;

	class TechniqueImpl
	{
	public:
		TechniqueImpl(IDirect3DDevice9* d3dDevice);
		~TechniqueImpl(void);

		u16			GetNumPasses(void);
		IPass*		GetPass(u16 index);


		IPass*		CreatePass(PassType::eValue type = PassType::type_StaticMesh);
		void		RemovePass(IPass* pass);

		virtual void			RenderObject(SceneObjectImpl* obj, ICamera* pCam);
	public:
		tstring				mName;
		IDirect3DDevice9*	mD3dDevice;
		typedef std::vector<IPass*>	PassList;
		PassList			mPasses;
		MaterialImpl*		mParent;
	};
}

#endif // _TECHNIQUEIMPL_201443152541_