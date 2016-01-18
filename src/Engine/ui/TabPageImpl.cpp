#include "TabPageImpl.h"

namespace panda
{
	TabPageImpl::TabPageImpl( void )
	{
		mText = _T("tab page");
		mDrawBorder = false;
	}

	void TabPageImpl::OnRender( IGraph2D* graph )
	{

	}

	void TabPageImpl::SetToolTip( const tstring& str )
	{
		mToolTipStr = str;
	}

	const tstring& TabPageImpl::GetToolTip( void ) const
	{
		return mToolTipStr;
	}
}