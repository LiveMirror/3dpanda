#include "IAttrPage.h"

namespace editor
{
	IAttrPage::IAttrPage( void )
		:mPage(NULL)
	{
		
	}

	void IAttrPage::SetNode( ISceneNode* node )
	{
		mRootNode = node;
		mRootNode->SetVisible(false);
	}

	void IAttrPage::InitUI( ITabPage* page )
	{
		mPage = page;
	}

	void IAttrPage::OnSelected( IAttrPage* prePage )
	{

	}

	void IAttrPage::OnLostSelected( IAttrPage* curPage )
	{

	}

	void IAttrPage::OnMouseDown( MouseEventArgs& e )
	{

	}

	void IAttrPage::OnMouseUp( MouseEventArgs& e )
	{

	}

	void IAttrPage::OnMouseMove( MouseEventArgs& e )
	{

	}
}