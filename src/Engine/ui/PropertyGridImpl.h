////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-29 21:09:16
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014529210916_H_
#define	_Tian_2014529210916_H_

#include "PanelImpl.h"

namespace panda
{
	class IPropertyGridItem;
	class IPropertyGridItemS32;
	class IPropertyGridItemF32;
	class IPropertyGridItem3F;
	class IPropertyGridItem4F;
	class IPropertyGridItemString;
	class IPropertyGridItemBool;
	class PropertyGridImpl:public PanelImpl
	{
	public:
		PropertyGridImpl(void);
		
		virtual void		OnRender(IGraph2D* graph);
		virtual void		OnMouseDown(MouseEventArgs& e);

		IPropertyGridItemS32*		AddItemS32(const tstring& name);
		IPropertyGridItemF32*		AddItemF32(const tstring& name);
		IPropertyGridItem3F*		AddItem3F(const tstring& name);
		IPropertyGridItem4F*		AddItem4F(const tstring& name);
		IPropertyGridItemString*	AddItemString(const tstring& name);
		IPropertyGridItemBool*		AddItemBool(const tstring& name);

		void				ClearItem(void);
		void				_AddItem(IPropertyGridItem* item);

	public:
		typedef	std::vector<IPropertyGridItem*>		GridItemList;

		GridItemList	mItems;
		s32				mItemHeight;
		s32				mNameWidth;
	};
}

#endif _Tian_2014529210916_H_