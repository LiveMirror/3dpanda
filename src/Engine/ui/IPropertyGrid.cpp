#include "ui/IPropertyGrid.h"
#include "PropertyGridImpl.h"
#include "PropertyGridItemImpl.h"

namespace panda
{
	IPropertyGridItem::IPropertyGridItem( PropertyGridItemImpl* impl )
		:mImpl(impl)
	{

	}
	
	IPropertyGridItem::~IPropertyGridItem( void )
	{
		delete mImpl;
	}

	void IPropertyGridItem::SetName( const tstring& name )
	{
		mImpl->mName = name;
	}

	const tstring& IPropertyGridItem::GetName( void ) const
	{
		return mImpl->mName;
	}

	bool IPropertyGridItem::IsReadOnly( void ) const
	{
		return mImpl->mReadOnly;
	}

	void IPropertyGridItem::SetReadOnly( bool readOnly )
	{
		mImpl->mReadOnly = readOnly;
	}

	PropertyGridType::eValue IPropertyGridItem::GetType( void ) const
	{
		return mImpl->mType;
	}

	void IPropertyGridItem::RefreshValue( void )
	{
		mImpl->ToString(mImpl->mValueStr);
	}


	/************************************** IPropertyGridItemS32 *******************************************/

	IPropertyGridItemS32::IPropertyGridItemS32( void )
		:IPropertyGridItem(new PropertyGridItemS32Impl)
	{

	}

	PropertyS32& IPropertyGridItemS32::GetAttr( void )
	{
		return ((PropertyGridItemS32Impl*)mImpl)->mAttr;
	}


	/*************************************** IPropertyGridItem3F ******************************************/
	IPropertyGridItemF32::IPropertyGridItemF32( void )
		:IPropertyGridItem(new PropertyGridItemF32Impl)
	{

	}

	PropertyF32& IPropertyGridItemF32::GetAttr( void )
	{
		return ((PropertyGridItemF32Impl*)mImpl)->mAttr;
	}

	/*************************************** IPropertyGridItem3F ******************************************/

	IPropertyGridItem3F::IPropertyGridItem3F( void )
		:IPropertyGridItem(new PropertyGridItem3FImpl)
	{

	}

	Property3F& IPropertyGridItem3F::GetAttr( void )
	{
		return ((PropertyGridItem3FImpl*)mImpl)->mAttr;
	}

	/*************************************** IPropertyGridItem4F ******************************************/

	IPropertyGridItem4F::IPropertyGridItem4F( void )
		:IPropertyGridItem(new PropertyGridItem4FImpl)
	{

	}

	Property4F& IPropertyGridItem4F::GetAttr( void )
	{
		return ((PropertyGridItem4FImpl*)mImpl)->mAttr;
	}

	/**************************************  IPropertyGridItemString *******************************************/

	IPropertyGridItemString::IPropertyGridItemString( void )
		:IPropertyGridItem(new PropertyGridItemStringImpl)
	{

	}

	PropertyString& IPropertyGridItemString::GetAttr( void )
	{
		return ((PropertyGridItemStringImpl*)mImpl)->mAttr;
	}

	/**************************************  IPropertyGridItemBool *******************************************/
	IPropertyGridItemBool::IPropertyGridItemBool( void )
		:IPropertyGridItem(new PropertyGridItemBoolImpl)
	{
		
	}

	PropertyBool& IPropertyGridItemBool::GetAttr( void )
	{
		return ((PropertyGridItemBoolImpl*)mImpl)->mAttr;
	}

	/***************************************** IPropertyGrid **************************************************/
#define Ptr		((PropertyGridImpl*)mImpl)
	IPropertyGrid::IPropertyGrid( void )
		:IPanel(new PropertyGridImpl)
	{

	}

	IPropertyGrid::IPropertyGrid( PropertyGridImpl* impl )
		:IPanel(impl)
	{

	}

	IPropertyGridItemS32* IPropertyGrid::AddItemS32( const tstring& name )
	{
		return Ptr->AddItemS32(name);
	}

	IPropertyGridItemF32* IPropertyGrid::AddItemF32( const tstring& name )
	{
		return Ptr->AddItemF32(name);
	}

	IPropertyGridItem3F* IPropertyGrid::AddItem3F( const tstring& name )
	{
		return Ptr->AddItem3F(name);
	}

	IPropertyGridItem4F* IPropertyGrid::AddItem4F( const tstring& name )
	{
		return Ptr->AddItem4F(name);
	}

	IPropertyGridItemString* IPropertyGrid::AddItemString( const tstring& name )
	{
		return Ptr->AddItemString(name);
	}
	
	IPropertyGridItemBool* IPropertyGrid::AddItemBool( const tstring& name )
	{
		return Ptr->AddItemBool(name);
	}

	void IPropertyGrid::ClearItem( void )
	{
		Ptr->ClearItem();
	}


}