////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-29 22:04:50
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014529220450_H_
#define	_Tian_2014529220450_H_

#include "ui/IPropertyGrid.h"

namespace panda
{
	class uiManager;
	class PropertyGridImpl;
	class PropertyGridItemImpl
	{
	public:
		PropertyGridItemImpl(void);
		PropertyGridItemImpl(IControl* ctrl);
		virtual ~PropertyGridItemImpl(void);

		virtual	void	SetValue(const tstring& v);
		virtual void	ToString(tstring& outStr);

		virtual void	OnBindUiMgr(uiManager* uiMgr);

		bool			OnEditorEnd(IControl* pCtrl);
		bool			OnEditorKeyDown(IControl* pCtrl, KeyEventArgs& e);

		virtual IControl*		GetEditorCtrl(void);
	public:
		tstring			mName;
		
		bool			mReadOnly;
		tstring			mValueStr;
		IControl*		mEditorCtrl;
		PropertyGridImpl*			mParent;
		PropertyGridType::eValue	mType;
	};

	class PropertyGridItemS32Impl:public PropertyGridItemImpl
	{
	public:
		PropertyGridItemS32Impl(void);
		virtual	void	SetValue(const tstring& v);
		virtual void	ToString(tstring& outStr);
	public:
		PropertyS32		mAttr;
	};

	class PropertyGridItemF32Impl:public PropertyGridItemImpl
	{
	public:
		PropertyGridItemF32Impl(void);
		virtual	void	SetValue(const tstring& v);
		virtual void	ToString(tstring& outStr);
	public:
		PropertyF32		mAttr;
	};

	class PropertyGridItem3FImpl:public PropertyGridItemImpl
	{
	public:
		PropertyGridItem3FImpl(void);
		virtual	void	SetValue(const tstring& v);
		virtual void	ToString(tstring& outStr);
	public:
		Property3F		mAttr;
	};

	class PropertyGridItem4FImpl:public PropertyGridItemImpl
	{
	public:
		PropertyGridItem4FImpl(void);
		virtual	void	SetValue(const tstring& v);
		virtual void	ToString(tstring& outStr);
	public:
		Property4F		mAttr;
	};

	class PropertyGridItemStringImpl:public PropertyGridItemImpl
	{
	public:
		PropertyGridItemStringImpl(void);
		virtual	void	SetValue(const tstring& v);
		virtual void	ToString(tstring& outStr);
	public:
		PropertyString	mAttr;
	};

	class PropertyGridItemBoolImpl:public PropertyGridItemImpl
	{
	public:
		PropertyGridItemBoolImpl(void);
		virtual	void	SetValue(const tstring& v);
		virtual void	ToString(tstring& outStr);
		virtual void	OnBindUiMgr(uiManager* uiMgr);

		bool			OnEditorEnd(IControl* pCtrl);
	public:
		PropertyBool	mAttr;
	};
}

#endif _Tian_2014529220450_H_