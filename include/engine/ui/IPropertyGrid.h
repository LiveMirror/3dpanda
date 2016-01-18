//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/29 15:53:52_
// 描述:  
//

#ifndef _IPROPERTYGRID_2014529155352_
#define _IPROPERTYGRID_2014529155352_

#include "Event.h"
#include "PropertyGridDefine.h"
#include "IPanel.h"

namespace panda
{
	class PropertyGridItemImpl;
	class IPropertyGridItem
	{
	public:
		virtual ~IPropertyGridItem(void);
		IPropertyGridItem(PropertyGridItemImpl* impl);
		virtual void			SetName(const tstring& name);
		virtual const tstring&	GetName(void)const;

		virtual bool			IsReadOnly(void)const;
		virtual void			SetReadOnly(bool readOnly);

		virtual void			RefreshValue(void);

		virtual PropertyGridType::eValue	GetType(void)const;
	public:
		PropertyGridItemImpl*	mImpl;
	};

	typedef PropertyAttr<s32>	PropertyS32;
	class IPropertyGridItemS32:public IPropertyGridItem
	{
	public:
		IPropertyGridItemS32(void);
		virtual PropertyS32&		GetAttr(void);

	};

	typedef PropertyAttr<f32>	PropertyF32;
	class IPropertyGridItemF32:public IPropertyGridItem
	{
	public:
		IPropertyGridItemF32(void);
		virtual PropertyF32&		GetAttr(void);
	};

	typedef PropertyAttr<const Vector3Df&>	Property3F;
	class IPropertyGridItem3F:public IPropertyGridItem
	{
	public:
		IPropertyGridItem3F(void);
		virtual Property3F&		GetAttr(void);
	};

	typedef PropertyAttr<const Colorf&>	Property4F;
	class IPropertyGridItem4F:public IPropertyGridItem
	{
	public:
		IPropertyGridItem4F(void);
		virtual Property4F&		GetAttr(void);
	};

	typedef PropertyAttr<const tstring&>	PropertyString;
	class IPropertyGridItemString:public IPropertyGridItem
	{
	public:
		IPropertyGridItemString(void);
		virtual PropertyString&		GetAttr(void);
	};

	typedef PropertyAttr<bool>				PropertyBool;
	class IPropertyGridItemBool:public IPropertyGridItem
	{
	public:
		IPropertyGridItemBool(void);
		virtual PropertyBool&		GetAttr(void);
	};

	class PropertyGridImpl;
	class IPropertyGrid:public IPanel
	{
	public:
		IPropertyGrid(void);
		IPropertyGrid(PropertyGridImpl* impl);

		virtual IPropertyGridItemS32*		AddItemS32(const tstring& name);
		virtual IPropertyGridItemF32*		AddItemF32(const tstring& name);
		virtual IPropertyGridItem3F*		AddItem3F(const tstring& name);
		virtual IPropertyGridItem4F*		AddItem4F(const tstring& name);
		virtual IPropertyGridItemString*	AddItemString(const tstring& name);
		virtual IPropertyGridItemBool*		AddItemBool(const tstring& name);

		virtual void		ClearItem(void);
	};
}

#endif // _IPROPERTYGRID_2014529155352_