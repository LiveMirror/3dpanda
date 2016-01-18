#include "DlgChooseRes.h"
#include <algorithm>

namespace editor
{
	DlgChooseRes::DlgChooseRes( void )
	{
		mCurrentPath = _T("");
		mFilterType = -1;
	}

	void DlgChooseRes::Init( IUiManager* uiMgr )
	{
		mDlg = uiMgr->CreateDialogs();
		mDlg->SetSize(500, 350);
		mDlg->SetText(_T("选择资源"));
		s32 x = uiMgr->GetWidth() - mDlg->GetSize().width;
		s32 y = uiMgr->GetHeight() - mDlg->GetSize().height;
		mDlg->SetPos(x / 2 - 50, y / 2);
		mDlg->SetVisible(false);

		mLbType = uiMgr->CreateListBox(mDlg);
		mLbType->SetPos(0, 0);
		mLbType->SetSize(100, mDlg->GetSize().height - 25);
		mLbType->AddItem(_T("全部类型"));
		mLbType->AddItem(_T("纹理"));
		mLbType->AddItem(_T("材质"));
		mLbType->AddItem(_T("模型"));
		mLbType->AddItem(_T("骨骼动画"));
		mLbType->AddItem(_T("地形"));
		mLbType->AddItem(_T("特效"));
		mLbType->OnSelectedChange().Add(this, &DlgChooseRes::OnListSelectChanged);
		mLbType->SetSelItemIndex(0);

		mToolBar = uiMgr->CreateToolBar(mDlg);
		mToolBar->SetPos(100, 0);
		mToolBar->SetSize(mDlg->GetSize().width - 100, 25);
		IToolBarItem* btn = mToolBar->AddToolItem(_T("退后"));
		btn->SetBackImage(TheEngine()->GetResMgr()->LoadTexture(_T("../media/back.png")));
		btn->OnClick().Add(this, &DlgChooseRes::OnBackClick);

		mToolBar->AddToolItem(_T(""), IToolBarItem::Separator);

		/*btn = mToolBar->AddToolItem(_T("新建"));
		btn->SetBackImage(TheEngine()->GetResMgr()->LoadTexture(_T("../media/new.png")));
		btn->OnMouseClick().Add(this, &DlgChooseRes::OnNewClick);*/

		mMenu = uiMgr->CreateMenu();
		mMenu->AddItem(_T("新建模型"));
		mMenu->AddItem(_T("新建材质"));

		mLvRes = uiMgr->CreateListView(mDlg);
		mLvRes->SetItemSize(82, 82);
		mLvRes->SetPos(100, 25);
		mLvRes->SetSize(mDlg->GetSize().width - 100, mDlg->GetSize().height - 50);
		mLvRes->OnItemDClick().Add(this, &DlgChooseRes::OnItemDClick);

		mImgFolder = TheEngine()->GetResMgr()->LoadTexture(_T("../media/folder.png"));
		mImgMesh = TheEngine()->GetResMgr()->LoadTexture(_T("../media/mesh.png"));
		mImgMat = TheEngine()->GetResMgr()->LoadTexture(_T("../media/matBall.png"));
		mImgSkn = TheEngine()->GetResMgr()->LoadTexture(_T("../media/skeleton.png"));
		mImgTer = TheEngine()->GetResMgr()->LoadTexture(_T("../media/ter.png"));
		mImgEffect = TheEngine()->GetResMgr()->LoadTexture(_T("../media/effect.png"));
		FindFolder(_T(""));
	}

	void DlgChooseRes::ShowDlg( s32 filter )
	{
		if(-1 == filter)
		{
			mLbType->SetEnable(true);
			mLbType->SetSelItemIndex(0);
		}
		else
		{
			mLbType->SetEnable(false);
			mLbType->SetSelItemIndex(filter + 1);
		}
		if(mFilterType != filter)
		{
			mFilterType = filter;
			FindFolder(mCurrentPath);
		}
		mDlg->DoMode();
	}

	void DlgChooseRes::FindFolder( const tstring& path )
	{
		mCurrentPath = path;
		mLvRes->ClearAll();

		WIN32_FIND_DATA FindFileData;
		tstring szFind = mCurrentPath;
		if(szFind.length() > 0)
		{
			szFind += _T("/*.*");
		}
		else
		{
			szFind += _T("*.*");
		}

		HANDLE hFind = ::FindFirstFile(szFind.c_str(), &FindFileData);
		if(INVALID_HANDLE_VALUE == hFind) return;
		while(true)
		{
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(FindFileData.cFileName[0] != '.')
				{
					IListViewItem* item = mLvRes->AddItem(FindFileData.cFileName);
					item->SetText(FindFileData.cFileName);
					item->SetBackImage(mImgFolder);
					item->SetUserData(-1);
				}
			}
			else
			{
				DealFile(FindFileData.cFileName);
			}
			if(!FindNextFile(hFind, &FindFileData))	break;
		}
	}

	void DlgChooseRes::DealFile( const tchar* name )
	{
		tstring fileName = name;
		tstring ext = _T("");
		tstring nameOutExt;
		FileUtils::GetFileExtension(fileName, ext);
		FileUtils::GetFileName(fileName, nameOutExt, false);

		tstring tip = fileName;

		s32 type = -1;

		ResTexture img;

		// 将后缀到小写
		transform(ext.begin(), ext.end(), ext.begin(), tolower);
		if(!mCurrentPath.empty())
		{
			fileName = mCurrentPath;
			fileName += _T("/");
			fileName += name;
		}
		if (ext == _T("mesh")
			|| ext == _T("hymesh"))
		{
			type = ResType::ResType_Mesh;
			img = mImgMesh;
			tip += _T("\nType:Mesh");
		}		
		else if (ext == _T("jpg")
			|| ext == _T("png")
			|| ext == _T("tga")
			|| ext == _T("bmp")
			|| ext == _T("dds"))
		{
			type = ResType::ResType_Texure;
			tip += _T("\nType:Texture");
			img = TheEngine()->GetResMgr()->LoadTexture(fileName.c_str());
		}
		else if (ext == _T("material"))
		{
			type = ResType::ResType_Material;
			img = mImgMat;
			tip += _T("\nType:Material");
		}
		else if (ext == _T("skeleton")
			|| ext == _T("hyskn"))
		{
			img = mImgSkn;
			type = ResType::ResType_Skeletion;
			tip += _T("\nType:Skn");
		}
		else if(ext == _T("ter"))
		{
			img = mImgTer;
			type = ResType::ResType_Terrain;
			tip += _T("\nType:Terrain");
		}
		else if(ext == _T("eff"))
		{
			img = mImgEffect;
			type = ResType::ResType_Effect;
			tip += _T("\nType:Effect");
		}

		if(type >= 0)
		{
			if(mFilterType < 0 || mFilterType == type)
			{
				IListViewItem* item = mLvRes->AddItem(nameOutExt);
				item->SetText(fileName);
				item->SetBackImage(img);
				item->SetUserData(type);
				item->SetToolTip(tip);
			}
		}
	}

	void DlgChooseRes::GoBack( void )
	{
		if(mCurrentPath.length() == 0)
		{
			return;
		}
		s32 index = mCurrentPath.find_last_of(_T('/'));
		if (index < 0)
		{
			FindFolder(_T(""));
		}
		else
		{
			FindFolder(mCurrentPath.substr(0, index).c_str());
		}
	}

	bool DlgChooseRes::OnBackClick( IControl* pCtrl)
	{
		GoBack();
		return true;
	}

	bool DlgChooseRes::OnListSelectChanged( IControl* pCtrl )
	{
		mFilterType = mLbType->GetSelItemIndex() - 1;
		FindFolder(mCurrentPath);
		return true;
	}

	bool DlgChooseRes::OnItemDClick( IControl* pItem )
	{
		IListViewItem* item = mLvRes->GetSelectedItem();
		s32 type = item->GetUserData();
		if(type < 0)
		{
			if(mCurrentPath.length() > 0)
			{
				mCurrentPath += _T("/");
			}
			mCurrentPath += item->GetText();
			FindFolder(mCurrentPath.c_str());
		}
		else
		{
			Resource res;
			tstring path = item->GetText();
			switch(item->GetUserData())
			{
				case ResType::ResType_Mesh:
					{
						res = TheEngine()->GetResMgr()->LoadMesh(path.c_str());
						break;
					}
				case ResType::ResType_Texure:
					{
						res = TheEngine()->GetResMgr()->LoadTexture(path.c_str());
						break;
					}
				case ResType::ResType_Material:
					{
						res = TheEngine()->GetResMgr()->LoadMaterial(path.c_str());
						break;
					}
				case ResType::ResType_Skeletion:
					{
						res = TheEngine()->GetResMgr()->LoadSkeleton(path.c_str());
						break;
					}
				case ResType::ResType_Effect:
					{
						break;
					}
			}
			mOnResChoosed(res);
			mDlg->CloseDlg();
		}
		return true;
	}

	bool DlgChooseRes::OnNewClick( IControl* pCtrl)
	{
		Vector2Dn p = pCtrl->PointToScreen(0, 0);
		mMenu->ShowMenu(p.x, p.y + pCtrl->GetSize().height);
		return true;
	}
}