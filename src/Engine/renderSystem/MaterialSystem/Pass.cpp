#include "Pass.h"
#include "FileStream.h"
#include "../../resource/MaterialImpl.h"
#include "../../resource/TextureImpl.h"

#include "TechniqueImpl.h"
#include "../RenderSystem.h"
#include "Resources/ITexture.h"
#include "../../Scene/CameraImpl.h"
#include "../../Scene/SubMeshObject.h"


namespace panda
{
	Pass::Pass(IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr)
		:mD3dDevice(d3dDevice),
		mRenderMgr(renderMgr),
		mVertexShader(NULL),
		mPixelShader(NULL),
		mVConstTable(NULL),
		mPConstTable(NULL)
	{

	}

	Pass::~Pass()
	{	
		mVertexShader->Release();
		mPixelShader->Release();
		mVConstTable->Release();
		mPConstTable->Release();
	}

	bool Pass::LoadVertexShader( const tstring& file )
	{
		FileStream f;
		if(f.Open(file.c_str()))
		{
			u32 len = f.GetFileSize();
			char* buf = new char[len + 1];
			f.Read(buf, len);
			buf[len] = 0;
			mVertexShader = mRenderMgr->CreateVertexShader(buf, len, "Main", this);
			delete[] buf;
			if (NULL != mVertexShader)
			{
				GetVsHandles();
			}
			return mVertexShader != NULL;
		}
		return false;
	}

	bool Pass::LoadPixelShader( const tstring& file )
	{
		FileStream f;
		if(f.Open(file.c_str()))
		{
			u32 len = f.GetFileSize();
			char* buf = new char[len + 1];
			f.Read(buf, len);
			buf[len] = 0;
			mPixelShader = mRenderMgr->CreatePixelShader(buf, len, "Main", this);
			delete[] buf;
			if(NULL != mPixelShader)
			{
				GetPsHandles();
			}
			return mPixelShader != NULL;
		}
		return false;
	}

	void Pass::GetVsHandles( void )
	{
		mHandleWorldMatrix = mVConstTable->GetConstantByName(0, "mWorldMatrix");
		mHandleViewProj = mVConstTable->GetConstantByName(0, "mViewProj");
		mHandleEyePos = mVConstTable->GetConstantByName(0, "mEyePos");
		_GetVsHandles();
	}

	void Pass::GetPsHandles( void )
	{
		mHandleDiffuseTex = mPConstTable->GetConstantByName(0, "DiffuseTexSampler");
		mHandleNormalTex = mPConstTable->GetConstantByName(0, "NormalTexSampler");
		mHandleEnvColor = mPConstTable->GetConstantByName(0, "mEvnColor");
		mHandleDirLightColor = mPConstTable->GetConstantByName(0, "mLightColor");
		mHandleLightDir = mPConstTable->GetConstantByName(0, "mLightDir");
		_GetPsHandles();
	}

	void Pass::_GetVsHandles( void )
	{
		// do nothing here
	}

	void Pass::_GetPsHandles( void )
	{
		// do nothing here
	}

	void Pass::SetMatrixArr( IDirect3DDevice9* d3dDevice, Matrix44f* pMatrix, u32 count )
	{
		D3DXHANDLE handle = mVConstTable->GetConstantByName(0, "mWorldMatrixArray");
		HRESULT hr = mVConstTable->SetMatrixArray(d3dDevice, handle, (const D3DXMATRIX*)pMatrix, count);
	}

	void Pass::SetPsTex( D3DXHANDLE handle, IDirect3DTexture9* tex )
	{
		if(handle)
		{
			D3DXCONSTANT_DESC  Samp0_Handle_Desc;
			u32 count;
			mPConstTable->GetConstantDesc( handle, &Samp0_Handle_Desc, &count );
			mD3dDevice->SetTexture( Samp0_Handle_Desc.RegisterIndex, tex);
		}
	}

	void Pass::SetVsTex( D3DXHANDLE handle, IDirect3DTexture9* tex )
	{
		if(handle)
		{
			D3DXCONSTANT_DESC  Samp0_Handle_Desc;
			u32 count;
			mVConstTable->GetConstantDesc( handle, &Samp0_Handle_Desc, &count );
			mD3dDevice->SetTexture( Samp0_Handle_Desc.RegisterIndex, tex);
		}
	}

	void Pass::DrawRenderObject( Renderable* pObject, CameraImpl* pCamera)
	{

	}

	void Pass::SetParam( MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject)
	{
		// set viewpro matrix
		mVConstTable->SetMatrix(mD3dDevice, mHandleViewProj, (const D3DXMATRIX*)&pCamera->GetViewProMatrix());

		// set the world matrix
		mVConstTable->SetMatrix(mD3dDevice, mHandleWorldMatrix, (const D3DXMATRIX*)&pObject->GetWorldTransforms());

		// set diffuse texture
		if (!mat->mDiffuseTex.IsNull())
		{
			IDirect3DTexture9* tex = ((TextureImpl*)mat->mDiffuseTex->mImpl)->GetTexPtr();
			SetPsTex(mHandleDiffuseTex, tex);
		}

		if(!mat->mNormalMap.IsNull())
		{
			IDirect3DTexture9* tex = ((TextureImpl*)mat->mNormalMap->mImpl)->GetTexPtr();
			SetPsTex(mHandleNormalTex, tex);
		}

		if(NULL != mHandleEyePos)
		{
			mVConstTable->SetFloatArray(mD3dDevice, mHandleEyePos, (f32*)&pCamera->mPosition, 3);
		}

		if (NULL != mHandleEnvColor)
		{
			Vector3Df v(0.5f, 0.5f, 0.5f);
			mPConstTable->SetFloatArray(mD3dDevice, mHandleEnvColor, (f32*)&v, 3);
		}
		if (NULL != mHandleDirLightColor)
		{
			Vector3Df v(0.5f, 0.5f, 0.5f);
			mPConstTable->SetFloatArray(mD3dDevice, mHandleDirLightColor, (f32*)&v, 3);
		}
		if (NULL != mHandleLightDir)
		{
			Vector3Df v(0, 0, -1);
			mPConstTable->SetFloatArray(mD3dDevice, mHandleLightDir, (f32*)&v, 3);
		}

		_SetParam(mat, pCamera, pObject);
	}

	void Pass::_SetParam( MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject )
	{
		// do nothing
	}
}