#include "ui/IPictureBox.h"
#include "PictureBoxImpl.h"

namespace panda
{
	IPictureBox::IPictureBox( void )
		:IControl(new PictureBoxImpl)
	{

	}

	IPictureBox::IPictureBox( PictureBoxImpl* impl )
		:IControl(impl)
	{

	}
}