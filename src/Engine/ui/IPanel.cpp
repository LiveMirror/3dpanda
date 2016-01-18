#include "ui/IPanel.h"
#include "PanelImpl.h"

namespace panda
{
	IPanel::IPanel( void )
		:IControl(new PanelImpl)
	{

	}

	IPanel::IPanel( PanelImpl* impl )
		:IControl(impl)
	{

	}

	void IPanel::AddChild( IControl* ctrl )
	{
		PanelImpl* impl = (PanelImpl*)mImpl;
		impl->AddChild(ctrl);
	}

	bool IPanel::HasChild( IControl* ctrl )
	{
		PanelImpl* impl = (PanelImpl*)mImpl;
		return impl->HasChild(ctrl);
	}

	void IPanel::RemoveChild( IControl* ctrl )
	{
		PanelImpl* impl = (PanelImpl*)mImpl;
		impl->RemoveChild(ctrl);
	}
}