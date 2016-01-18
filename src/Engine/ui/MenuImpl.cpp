#include "MenuImpl.h"
#include "uiManager.h"
#include "../renderSystem/Graph2D.h"

namespace panda
{
	MenuImpl::MenuImpl( void )
	{
		mIsVisible = false;
		mDrawChild = true;
	}

	void MenuImpl::Draw( Rect& rect, IGraph2D* graph )
	{
		Graph2D* g = (Graph2D*)graph;
		g->PushOffset(mRect.pos);
		
		DrawChilds(0, 0, graph);

		if(mDrawBorder)
		{
			graph->DrawRect(0, 0, mRect.size.width, mChildHeight, mBorderColor, mBorderSize);
		}
		g->PopOffset(mRect.pos);
	}

	void MenuImpl::ShowMenu( s32 x, s32 y )
	{
		ClearDrawChild();
		mDrawChild = true;
		mUiMgr->SetPopUpCtrl(mThis);
		mRect.pos.x = x;
		mRect.pos.y = y;
	}
}