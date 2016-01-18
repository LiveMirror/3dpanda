#include "uiManager.h"
#include "ui/IControl.h"
#include "ui/IPanel.h"
#include "ui/IPictureBox.h"
#include "ui/Imenu.h"
#include "ui/IButton.h"
#include "ui/ICombobox.h"
#include "ui/ITextbox.h"
#include "ui/ILabel.h"
#include "ui/IScrollBar.h"
#include "ui/ICheckbox.h"
#include "ui/IProgressbar.h"
#include "ui/IDialog.h"
#include "ui/IListbox.h"
#include "ui/ISliderBar.h"
#include "ui/ITabCtrl.h"
#include "ui/IRadioButton.h"
#include "ui/IToolBar.h"
#include "ui/ITreeView.h"
#include "ui/IListView.h"
#include "ui/IFoldPanel.h"
#include "ui/IPropertyGrid.h"

#include "Font.h"
#include "ControlImpl.h"
#include "MenuImpl.h"
#include "ComboBoxImpl.h"
#include "TooltipImpl.h"

#include "../renderSystem/Graph2D.h"
#include "../renderSystem/RenderSystem.h"


namespace panda
{
	uiManager::uiManager( RenderSystem* renderSys )
		:mRenderSys(renderSys),
		mMouseOn(NULL),
		mPopupCtrl(NULL),
		mCapture(NULL),
		mLaskTick(0),
		mFocus(NULL),
		mMouseOverTime(0),
		mHasNoticeHover(false),
		mModeDialog(false)
	{
		mDefaultFont = this->CeateFont(20, 7, _T("Î¢ÈíÑÅºÚ"), 530);//»ª¿µÍÞÍÞÌåW5
		mToolTip = new ToolTipImpl;
		mToolTip->OnBindUiMgr(this);
		mToolTip->mFont = mDefaultFont;
	}

	void uiManager::Render( IGraph2D* graph , s32 tick)
	{
		s32 passTime = tick - mLaskTick;
		mMouseOverTime += passTime;
		if(mMouseOverTime >= 500 && NULL != mMouseOn && !mHasNoticeHover)
		{
			mHasNoticeHover = true;
			MouseEventArgs e;
			e.x = mOldPoint.x;
			e.y = mOldPoint.y;
			mMouseOn->mImpl->OnMouseHover(e);
			mMouseOn->mImpl->mOnMouseHover(mMouseOn, e);

			if(!mMouseOn->mImpl->mTipText.empty())
			{
				mToolTip->SetText(mMouseOn->mImpl->mTipText);
				Vector2Dn p = mMouseOn->PointToScreen(mOldPoint.x, mOldPoint.y);
				mToolTip->ShowTip(p.x, p.y + 20);
			}
		}
		mLaskTick = tick;
		((Graph2D*)graph)->BenginGraph(mClientRect.size.width, mClientRect.size.height);
		IControl* pCtrl;
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			pCtrl = *it;
			pCtrl->mImpl->Update(passTime);
			pCtrl->mImpl->Draw(mClientRect, graph);
			it++;
		}

		if(NULL != mPopupCtrl)
		{
			mPopupCtrl->mImpl->Update(passTime);
			mPopupCtrl->mImpl->Draw(mClientRect, graph);
		}
		if(NULL != mToolTip && mToolTip->mIsVisible)
		{
			mToolTip->OnRender(graph);
		}
	}

	void uiManager::AddChild( IControl* ctrl )
	{
		mChilds.push_back(ctrl);
	}

	IFont* uiManager::CeateFont( s32 height, s32 width, const tstring faceName , s32 weight, 
		bool italic /*= false*/, bool underline /*= false*/, bool strikeOut /*= false*/ )
	{
		Font* font = new Font;
		D3DXFONT_DESC lf;
		ZeroMemory(&lf , sizeof (D3DXFONT_DESC));
		lf.Width = width;
		lf.Height = height;
		lf.Weight = weight;
		lf.Italic = italic;
		lf.CharSet = DEFAULT_CHARSET;
		_tcscpy(lf.FaceName, faceName.c_str()); // font style
		D3DXCreateFontIndirect(mRenderSys->mDevicePtr, &lf, &font->mDxFont);
		return font;
	}

	IButton* uiManager::CreateButton( IPanel* parent /*= NULL*/ )
	{
		IButton* pBtn = new IButton;
		pBtn->mImpl->mFont = mDefaultFont;
		pBtn->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pBtn);
		}
		else
		{
			parent->AddChild(pBtn);
		}
		return pBtn;
	}

	IPictureBox* uiManager::CreatePictureBox( IPanel* parent /*= NULL*/ )
	{
		IPictureBox* pBox = new IPictureBox;
		pBox->mImpl->mFont = mDefaultFont;
		pBox->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pBox);
		}
		else
		{
			parent->AddChild(pBox);
		}
		return pBox;
	}

	IPanel* uiManager::CreatePanel( IPanel* parent /*= NULL*/ )
	{
		IPanel* pCtrl = new IPanel;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}


	IToolBar* uiManager::CreateToolBar( IPanel* parent /*= NULL*/ )
	{
		IToolBar* pCtrl = new IToolBar;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}


	IRadioButton* uiManager::CreateRadioButton( IPanel* parent /*= NULL*/ )
	{
		IRadioButton* pCtrl = new IRadioButton;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		pCtrl->SetText(_T("RadioButton"));
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}

	ITextBox* uiManager::CreateTextBox( IPanel* parent /*= NULL*/ )
	{
		ITextBox* pCtrl = new ITextBox;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}


	IFoldPanel* uiManager::CreateFoldPanel( IPanel* parent /*= NULL*/ )
	{
		IFoldPanel* pCtrl = new IFoldPanel;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}


	IPropertyGrid* uiManager::CreatePropertyGrid( IPanel* parent /*= NULL*/ )
	{
		IPropertyGrid* pCtrl = new IPropertyGrid;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}


	IDialog* uiManager::CreateDialogs( IPanel* parent /*= NULL*/ )
	{
		IDialog* pCtrl = new IDialog;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		return pCtrl;
	}

	ITabCtrl* uiManager::CreateTabCtrl( IPanel* parent /*= NULL*/ )
	{
		ITabCtrl* pCtrl = new ITabCtrl;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}

	IMenu* uiManager::CreateMenu( void )
	{
		IMenu* menu = new IMenu(this, new MenuImpl);
		menu->mImpl->mFont = mDefaultFont;
		return menu;
	}


	IComboBox* uiManager::CreateComboBox( IPanel* parent /*= NULL*/ )
	{
		IComboBox* comboBox = new IComboBox(new ComboBoxImpl);
		comboBox->mImpl->mFont = mDefaultFont;
		comboBox->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(comboBox);
		}
		else
		{
			parent->AddChild(comboBox);
		}
		return comboBox;
	}

	ILabel* uiManager::CreateLabel( IPanel* parent /*= NULL*/ )
	{
		ILabel* pCtrl = new ILabel;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}

	IScrollBar* uiManager::CreateScrollBar( IPanel* parent /*= NULL*/ )
	{
		IScrollBar* pCtrl = new IScrollBar;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}


	ITreeView* uiManager::CreateTreeView( IPanel* parent /*= NULL*/ )
	{
		ITreeView* pCtrl = new ITreeView;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}


	IProgressBar* uiManager::CreateProgressBar( IPanel* parent /*= NULL*/ )
	{
		IProgressBar* pCtrl = new IProgressBar;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}

	IListView* uiManager::CreateListView( IPanel* parent /*= NULL*/ )
	{
		IListView* pCtrl = new IListView;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}

	ICheckBox* uiManager::CreateCheckBox( IPanel* parent /*= NULL*/ )
	{
		ICheckBox* pCtrl = new ICheckBox;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		pCtrl->SetText(_T("CheckBox"));
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}

	ISliderBar* uiManager::CreateSliderBar( IPanel* parent /*= NULL*/ )
	{
		ISliderBar* pCtrl = new ISliderBar;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}


	IListBox* uiManager::CreateListBox( IPanel* parent /*= NULL*/ )
	{
		IListBox* pCtrl = new IListBox;
		pCtrl->mImpl->mFont = mDefaultFont;
		pCtrl->mImpl->OnBindUiMgr(this);
		if(NULL == parent)
		{
			mChilds.push_back(pCtrl);
		}
		else
		{
			parent->AddChild(pCtrl);
		}
		return pCtrl;
	}



	void uiManager::OnMouseMove( MouseEventArgs& e )
	{
		MouseEventArgs ne;
		ne.button = e.button;
		mMouseOverTime = 0;
		if( NULL != mCapture)
		{
			mOldPoint = mCapture->PointToClient(e.x, e.y);
			ne.x = mOldPoint.x;
			ne.y = mOldPoint.y;
			mCapture->mImpl->OnMouseMove(ne);
			mCapture->mImpl->mOnMouseMove(mCapture, ne);
			return;
		}
		IControl* mouseOn = NULL;
		if(NULL != mPopupCtrl)
		{
			mouseOn = mPopupCtrl->mImpl->HitTest(e.x, e.y, mOldPoint);
			ne.x = mOldPoint.x;
			ne.y = mOldPoint.y;
			if(NULL != mouseOn)
			{
				if(mouseOn == mMouseOn)
				{
					mMouseOn->mImpl->OnMouseMove(ne);
					mMouseOn->mImpl->mOnMouseMove(mMouseOn, ne);
					return;
				}
				else
				{
					if(NULL != mMouseOn && mMouseOn->mImpl->mEnable)
					{
						mMouseOn->mImpl->OnMouseLevae();
						mMouseOn->mImpl->mOnMouseLeave(mMouseOn);
					}
					if(mouseOn->mImpl->mEnable)
					{
						mouseOn->mImpl->OnMouseEnter();
						mouseOn->mImpl->mOnMouseEnter(mouseOn);
					}
					mMouseOn = mouseOn;
					return;
				}
			}
		}

		
		if(NULL != mModeDialog)
		{
			mouseOn = mModeDialog->mImpl->HitTest(e.x, e.y, mOldPoint);
		}
		else
		{
			IControl* pCtrl;
			CtrlList::reverse_iterator it = mChilds.rbegin();
			while (it != mChilds.rend())
			{
				pCtrl = *it;
				mouseOn = pCtrl->mImpl->HitTest(e.x, e.y, mOldPoint);
				if(NULL != mouseOn)
				{
					break;
				}
				it++;
			}
		}

		if(mMouseOn != mouseOn)
		{
			mHasNoticeHover = false;
			mToolTip->mIsVisible = false;
			if(NULL != mMouseOn && mMouseOn->mImpl->mEnable)
			{
				mMouseOn->mImpl->OnMouseLevae();
				mMouseOn->mImpl->mOnMouseLeave(mMouseOn);
			}
			mMouseOn = mouseOn;
			if(NULL != mMouseOn && mouseOn->mImpl->mEnable)
			{
				mOldPoint = mMouseOn->PointToClient(e.x, e.y);
				mouseOn->mImpl->OnMouseEnter();
				mouseOn->mImpl->mOnMouseEnter(mouseOn);
			}
		}
		else if(NULL != mMouseOn && mMouseOn->mImpl->mEnable)
		{
			mOldPoint = mMouseOn->PointToClient(e.x, e.y);
			ne.x = mOldPoint.x;
			ne.y = mOldPoint.y;
			mMouseOn->mImpl->OnMouseMove(ne);
			mMouseOn->mImpl->mOnMouseMove(mMouseOn, ne);
		}
	}

	void uiManager::OnMouseDown( MouseEventArgs& e )
	{
		mToolTip->mIsVisible = false;
		if(NULL != mPopupCtrl)
		{
			if(mMouseOn != mPopupCtrl && 
				(mMouseOn == NULL || !mMouseOn->mImpl->IsAncestor(mPopupCtrl)))
			{
				mPopupCtrl->mImpl->mIsVisible = false;
				mPopupCtrl = NULL;
			}
		}
		if(NULL != mMouseOn && mMouseOn->mImpl->mEnable)
		{
			Vector2Dn p = mMouseOn->PointToClient(e.x, e.y);
			SetCapture(mMouseOn);
			MouseEventArgs ne;
			ne.x = p.x;
			ne.y = p.y;
			ne.button = e.button;
			mMouseOn->mImpl->OnMouseDown(ne);
			mMouseOn->mImpl->mOnMouseDown(mMouseOn, ne);
		}
	}

	void uiManager::OnMouseDClick( MouseEventArgs& e )
	{
		mToolTip->mIsVisible = false;
		if(NULL != mPopupCtrl)
		{
			if(mMouseOn != mPopupCtrl && 
				(mMouseOn == NULL || !mMouseOn->mImpl->IsAncestor(mPopupCtrl)))
			{
				mPopupCtrl->mImpl->mIsVisible = false;
				mPopupCtrl = NULL;
			}
		}
		if(NULL != mMouseOn && mMouseOn->mImpl->mEnable)
		{
			Vector2Dn p = mMouseOn->PointToClient(e.x, e.y);
			MouseEventArgs ne;
			ne.x = p.x;
			ne.y = p.y;
			ne.button = e.button;
			mMouseOn->mImpl->OnMouseDClick(ne);
			//mMouseOn->mImpl->mOnMouseDown(mMouseOn, p.x, p.y);
		}
	}

	void uiManager::OnMouseUp( MouseEventArgs& e )
	{
		MouseEventArgs ne;
		if(NULL != mCapture)
		{
			Vector2Dn p = mCapture->PointToClient(e.x, e.y);
			ne.x = p.x;
			ne.y = p.y;
			ne.button = e.button;
			mCapture->mImpl->OnMouseUp(ne);
			mCapture->mImpl->mOnMouseUp(mCapture, ne);
			IControl* temp = mCapture;
			mCapture = NULL;
			OnMouseMove(e);
			if(temp == mMouseOn)
			{
				temp->mImpl->OnMouseClick(ne);
				temp->mImpl->mOnMouseClick(temp, ne);
			}
			
		}
		else if(NULL != mMouseOn && mMouseOn->mImpl->mEnable)
		{
			Vector2Dn p = mMouseOn->PointToClient(e.x, e.y);
			ne.x = p.x;
			ne.y = p.y;
			ne.button = e.button;
			mMouseOn->mImpl->OnMouseUp(ne);
			mMouseOn->mImpl->mOnMouseUp(mMouseOn, ne);
			mMouseOn->mImpl->mOnMouseClick(mMouseOn, ne);
		}
	}

	void uiManager::OnMouseWheel( MouseEventArgs& e )
	{
		if(NULL != mFocus)
		{
			Vector2Dn p = mFocus->PointToClient(e.x, e.y);
			MouseEventArgs ne;
			ne.x = p.x;
			ne.y = p.y;
			ne.button = e.button;
			ne.delta = e.delta;
			mFocus->mImpl->OnMouseWheel(ne);
			mFocus->mImpl->mOnMouseWheel(mFocus, ne);
		}
	}

	void uiManager::OnKeyDown( KeyEventArgs& e )
	{
		if(NULL != mFocus)
		{
			mFocus->mImpl->OnKeyDown(e);
			mFocus->mImpl->mOnKeyDown(mFocus, e);
		}
	}

	void uiManager::SetPopUpCtrl( IControl* pCtrl )
	{
		if(NULL != mPopupCtrl)
		{
			mPopupCtrl->mImpl->SetVisible(false);
		}
		mPopupCtrl = pCtrl;
		if(NULL != mPopupCtrl)
		{
			mPopupCtrl->mImpl->SetVisible(true);
		}
	}

	void uiManager::RealeseCapture( void )
	{
		mCapture = NULL;
	}

	void uiManager::SetCapture( IControl* pCtrl )
	{
		mCapture = pCtrl;
	}

	void uiManager::SetFocus( IControl* pCtrl )
	{
		if(pCtrl == mFocus)
		{
			return;
		}
		if(NULL != mFocus)
		{
			mFocus->mImpl->mIsFocus = false;
			mFocus->mImpl->OnLostFocus();
			mFocus->mImpl->mOnLostFocus(mFocus);
		}
		mFocus = pCtrl;
		if(NULL != mFocus)
		{
			mFocus->mImpl->mIsFocus = true;
			mFocus->mImpl->OnGotFocus();
			mFocus->mImpl->mOnGetFocus(mFocus);
		}
	}

	void uiManager::OnChar( s32 key )
	{
		if(NULL != mFocus)
		{
			mFocus->mImpl->OnChar(key);
		}
	}

	void uiManager::ResetHover( void )
	{
		mMouseOverTime = 0;
		mHasNoticeHover = false;
		mToolTip->mIsVisible = false;
	}

	void uiManager::DeviceLost( void )
	{
		((Font*)mDefaultFont)->mDxFont->OnLostDevice();
	}

	void uiManager::Resize( s32 width, s32 height )
	{
		mClientRect.size = Size(width, height);
		mOnResize(NULL, width, height);
	}

	void uiManager::ResetDevice( void )
	{
		((Font*)mDefaultFont)->mDxFont->OnResetDevice();
	}

	EventHandle& uiManager::OnResize( void )
	{
		return mOnResize;
	}

	void uiManager::SetModeDialog( IDialog* pDialog )
	{
		if(NULL != pDialog)
		{
			if(NULL != mModeDialog)
			{
				mModeDialogs.push_back(mModeDialog);
			}
			mModeDialog = pDialog;
			BringToFront(pDialog);
		}
		else
		{
			if (!mModeDialogs.empty())
			{
				mModeDialog = (IDialog*)*mModeDialogs.rbegin();
				BringToFront(pDialog);
				mModeDialogs.pop_back();
			}
			else
			{
				mModeDialog = NULL;
			}
		}
	}

	void uiManager::BringToFront( IControl* pCtrl )
	{
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			if(pCtrl == *it)
			{
				mChilds.erase(it);
				mChilds.push_back(pCtrl);
				return;
			}
			it++;
		}
	}

	void uiManager::SendToBack( IControl* pCtrl )
	{
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			if(pCtrl == *it)
			{
				mChilds.erase(it);
				mChilds.insert(mChilds.begin(), pCtrl);
				return;
			}
			it++;
		}
	}

	s32 uiManager::GetWidth( void ) const
	{
		return mClientRect.size.width;
	}

	s32 uiManager::GetHeight( void ) const
	{
		return mClientRect.size.height;
	}

	void uiManager::RemoveCtrl( IControl* ctrl )
	{
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			if(ctrl == *it)
			{
				mChilds.erase(it);
				return;
			}
			it++;
		}
	}

}