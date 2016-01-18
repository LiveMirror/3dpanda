#include "ui/ITextBox.h"
#include "Textboximpl.h"

#define Ptr		((TextBoxImpl*)mImpl)

namespace panda
{
	ITextBox::ITextBox( void )
		:IControl(new TextBoxImpl)
	{

	}

	ITextBox::ITextBox( TextBoxImpl* impl )
		:IControl(impl)
	{

	}

	void ITextBox::ReplaceSelectedText( const tstring& str )
	{

	}

	void ITextBox::Select( s32 beginIndex, s32 len )
	{

	}

	void ITextBox::SelectAll( void )
	{

	}

	void ITextBox::SetPasswordChar( tchar c )
	{

	}

	void ITextBox::ScrollToCaret( void )
	{

	}

	void ITextBox::SetReadOnly( bool readOnly )
	{

	}

	void ITextBox::Undo( void )
	{

	}

	void ITextBox::Copy( void )
	{

	}

	void ITextBox::Cut( void )
	{

	}

	void ITextBox::Paste( void )
	{

	}

}