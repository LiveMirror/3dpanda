#include "ui/ILabel.h"
#include "LabelImpl.h"

namespace panda
{
	ILabel::ILabel( void )
		:IControl(new LabelImpl)
	{

	}

	ILabel::ILabel( LabelImpl* impl )
		:IControl(impl)
	{

	}
}