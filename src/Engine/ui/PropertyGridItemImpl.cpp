#include "base/Config.h"
#include "PropertyGridItemImpl.h"
#include "ui/ITextBox.h"
#include "ui/IComboBox.h"
#include "ControlImpl.h"
#include "uiManager.h"
#include "PropertyGridImpl.h"

namespace panda
{
	PropertyGridItemImpl::PropertyGridItemImpl( void )
		:mReadOnly(false)
	{
		mEditorCtrl = new ITextBox;
		mEditorCtrl->SetBackColor(0xff254e85);
		mEditorCtrl->OnLostFocus().Add(this, &PropertyGridItemImpl::OnEditorEnd);
		mEditorCtrl->OnKeyDown().Add(this, &PropertyGridItemImpl::OnEditorKeyDown);
	}

	PropertyGridItemImpl::PropertyGridItemImpl( IControl* ctrl )
		:mReadOnly(false),
		mEditorCtrl(ctrl)
	{

	}

	PropertyGridItemImpl::~PropertyGridItemImpl( void )
	{
		if(mEditorCtrl != NULL)
		{
			delete mEditorCtrl;
		}
	}

	IControl* PropertyGridItemImpl::GetEditorCtrl( void )
	{
		return mEditorCtrl;
	}

	void PropertyGridItemImpl::SetValue( const tstring& v )
	{
		ToString(mValueStr);
	}

	void PropertyGridItemImpl::ToString( tstring& outStr )
	{
		mEditorCtrl->SetText(mValueStr);
	}

	void PropertyGridItemImpl::OnBindUiMgr( uiManager* uiMgr )
	{
		mEditorCtrl->mImpl->mFont = uiMgr->mDefaultFont;
		mEditorCtrl->mImpl->OnBindUiMgr(uiMgr);
	}

	bool PropertyGridItemImpl::OnEditorEnd( IControl* pCtrl )
	{
		mParent->mChilds.clear();
		SetValue(mEditorCtrl->GetText());
		return true;
	}

	bool PropertyGridItemImpl::OnEditorKeyDown( IControl* pCtrl, KeyEventArgs& e )
	{
		if(e.keyCode == VK_RETURN)
		{
			OnEditorEnd(pCtrl);
		}
		return true;
	}

	

	/*****************************************************************/
	PropertyGridItemS32Impl::PropertyGridItemS32Impl( void )
	{
		mType = PropertyGridType::Type_S32;
	}

	void PropertyGridItemS32Impl::SetValue( const tstring& v )
	{
		mAttr.SetValue(v);
		__super::SetValue(v);
	}

	void PropertyGridItemS32Impl::ToString( tstring& outStr )
	{
		mAttr.ToString(outStr);
		__super::ToString(outStr);
	}


	/*****************************************************************/
	PropertyGridItem3FImpl::PropertyGridItem3FImpl( void )
	{
		mType = PropertyGridType::Type_Vector3Df;
	}

	void PropertyGridItem3FImpl::SetValue( const tstring& v )
	{
		mAttr.SetValue(v);
		__super::SetValue(v);
	}

	void PropertyGridItem3FImpl::ToString( tstring& outStr )
	{
		mAttr.ToString(outStr);
		__super::ToString(outStr);
	}

	/*****************************************************************/
	PropertyGridItem4FImpl::PropertyGridItem4FImpl( void )
	{
		mType = PropertyGridType::Type_4F32;
	}

	void PropertyGridItem4FImpl::SetValue( const tstring& v )
	{
		mAttr.SetValue(v);
		__super::SetValue(v);
	}

	void PropertyGridItem4FImpl::ToString( tstring& outStr )
	{
		mAttr.ToString(outStr);
		__super::ToString(outStr);
	}


	/*****************************************************************/
	PropertyGridItemStringImpl::PropertyGridItemStringImpl( void )
	{
		mType = PropertyGridType::Type_String;
	}

	void PropertyGridItemStringImpl::SetValue( const tstring& v )
	{
		mAttr.SetValue(v);
		__super::SetValue(v);
	}

	void PropertyGridItemStringImpl::ToString( tstring& outStr )
	{
		mAttr.ToString(outStr);
		__super::ToString(outStr);
	}

	/*****************************************************************/
	PropertyGridItemF32Impl::PropertyGridItemF32Impl( void )
	{
		mType = PropertyGridType::Type_F32;
	}

	void PropertyGridItemF32Impl::SetValue( const tstring& v )
	{
		mAttr.SetValue(v);
		__super::SetValue(v);
	}

	void PropertyGridItemF32Impl::ToString( tstring& outStr )
	{
		mAttr.ToString(outStr);
		__super::ToString(outStr);
	}

	/********************************** PropertyGridItemBoolImpl *******************************/
	PropertyGridItemBoolImpl::PropertyGridItemBoolImpl( void )
		:PropertyGridItemImpl(new IComboBox)
	{
		mType = PropertyGridType::Type_Bool;
	}

	void PropertyGridItemBoolImpl::SetValue( const tstring& v )
	{
		mAttr.SetValue(v);
		__super::SetValue(v);
		
	}

	void PropertyGridItemBoolImpl::ToString( tstring& outStr )
	{
		mAttr.ToString(outStr);
		IComboBox* cb = (IComboBox*)mEditorCtrl;
		if(mAttr.mFun->CallGetFun())
		{
			cb->SetSelItem(0);
		}
		else
		{
			cb->SetSelItem(1);
		}
	}

	void PropertyGridItemBoolImpl::OnBindUiMgr( uiManager* uiMgr )
	{
		__super::OnBindUiMgr(uiMgr);
		IComboBox* cb = (IComboBox*)mEditorCtrl;
		cb->SetBackColor(0xff254e85);
		cb->AddItem(_T("true"));
		cb->AddItem(_T("false"));
		cb->OnSelectedChange().Add(this, &PropertyGridItemBoolImpl::OnEditorEnd);
		cb->OnLostFocus().Add(this, &PropertyGridItemBoolImpl::OnEditorEnd);
	}

	bool PropertyGridItemBoolImpl::OnEditorEnd( IControl* pCtrl )
	{
		mParent->mChilds.clear();
		SetValue(mEditorCtrl->GetText());
		return true;
	}


}