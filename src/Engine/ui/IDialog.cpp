#include "ui/IDialog.h"
#include "Dialogimpl.h"

#define Ptr		((DialogImpl*)mImpl)

namespace panda
{
	IDialog::IDialog( void )
		:IPanel(new DialogImpl)
	{

	}

	IDialog::IDialog( DialogImpl* impl )
		:IPanel(impl)
	{

	}

	void IDialog::SetEnableMove( bool enable )
	{
		Ptr->mEnableMove = enable;
	}

	bool IDialog::GetEnableMove( void ) const
	{
		return Ptr->mEnableMove;
	}

	void IDialog::DoMode( void )
	{
		Ptr->DoMode();
	}

	void IDialog::CloseDlg( void )
	{
		Ptr->CloseDlg();
	}
}