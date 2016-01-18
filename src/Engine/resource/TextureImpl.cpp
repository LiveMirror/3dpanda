#include "TextureImpl.h"
#include "resourcemgr.h"
#include <algorithm>

namespace panda
{
	TextureImpl::TextureImpl( ResourceMgr* resMgr )
		:ResourceImpl(resMgr),
		mTexPtr(NULL), mTexWidth(0), mTexHeight(0)
	{
		mResType = ResType::ResType_Texure;
	}

	TextureImpl::~TextureImpl( void )
	{
		UnLoad();
	}

	bool TextureImpl::_Load( void )
	{
		// 如果纹理是被创建的，不能被加载
		if (mIsCreater)
		{
			return true;
		}

		HRESULT hr = D3DXCreateTextureFromFile(mResMgr->mDevicePtr, mPath.c_str(), &mTexPtr);
		if (FAILED(hr))
		{
			return false;
		}

		// 计算纹理高宽
		D3DSURFACE_DESC desc;
		mTexPtr->GetLevelDesc(0, &desc);
		mTexWidth = desc.Width;
		mTexHeight = desc.Height;

		return true;
	}

	void TextureImpl::_UnLoad( void )
	{
		if (NULL != mTexPtr)
		{
			mTexPtr->Release();
			mTexPtr = NULL;
		}
	}

	void TextureImpl::_Save( const tchar* strPath )
	{
		tstring path;
		if (NULL == strPath)
		{
			if (mPath.empty())
			{
				return;
			}
			path = mPath;
		}
		else
		{
			path = strPath;
		}

		D3DXIMAGE_FILEFORMAT format = D3DXIFF_PNG;
		int index = (int) path.find_last_of(_T('.'));
		if (index >=0 )
		{
			index++;
			tstring ext = path.substr(index, path.size() - index);
			transform(ext.begin(), ext.end(), ext.begin(), toupper);

			if (ext.compare(_T("BMP")) == 0)
			{
				format = D3DXIFF_BMP;
			}
			else if (ext.compare(_T("PNG")) == 0)
			{
				format = D3DXIFF_PNG;
			}
			else if (ext.compare(_T("JPG")) == 0)
			{
				format = D3DXIFF_JPG;
			}
			else if (ext.compare(_T("TGA")) == 0)
			{
				format = D3DXIFF_TGA;
			}
			else if (ext.compare(_T("DDS")) == 0)
			{
				format = D3DXIFF_DDS;
			}
		}
		D3DXSaveTextureToFile(path.c_str(), format, mTexPtr, NULL);
	}

	IDirect3DTexture9* TextureImpl::GetTexPtr( void )
	{
		return mTexPtr;
	}
}