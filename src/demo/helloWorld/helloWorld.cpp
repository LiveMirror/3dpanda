#include "IPanda.h"

using namespace panda;

ICamera*	pCamera;

class MyEvent
{
public:
	MyEvent()
	{
		mTestValue = 10;
	}

	bool	OnHelpClick(IControl* ctrl, MouseEventArgs& e)
	{
		Vector2Dn p = ctrl->PointToScreen(0, 0);
		mMenu->ShowMenu(p.x, p.y + ctrl->GetSize().height);
		return true;
	}

	void	SetValue(s32 v)
	{
		mTestValue = v;
	}

	s32		GetValue(void)const
	{
		return mTestValue;
	}

	void	SetString(const Vector3Df& v)
	{
		mTestV = v;
	}

	const Vector3Df& GetString(void)
	{
		return mTestV;
	}

	bool	ShowWindowClick(IControl* ctrl, MouseEventArgs& e)
	{
		pDialog->DoMode();
		return true;
	}

	bool	OnExitClick(IControl* ctrl, MouseEventArgs& e)
	{
		exit(0);
	}
	IDialog* pDialog;
	IMenu*	mMenu;

	s32	mTestValue;
	Vector3Df mTestV;
};


int __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	MyEvent* myDeal = new MyEvent;

	IPanda* pEngine = TheEngine();
	RenderWindowParam param;
	//param.bBoder = false;
	param.strTitle = _T("Hello World");
	IRenderWindow* pWindow = pEngine->InitDevice(&param);
	if(NULL == pWindow)
	{
		return 0;
	}

	IPropertyGrid* test = pWindow->GetUiManager()->CreatePropertyGrid();
	IPropertyGridItemS32* gridItem = test->AddItemS32(_T("s32"));
	gridItem->GetAttr().InitAttr(myDeal, &MyEvent::SetValue, &MyEvent::GetValue);

	gridItem->GetAttr().SetValue(_T("40"));

	/*IPropertyGridItem<MyEvent, s32>* gridItem = test->AddPropertyItem(_T("dd"), myDeal, &MyEvent::SetValue, &MyEvent::GetValue);

	tstring str;
	gridItem->mAttr->ToString(str);
	gridItem->mAttr->SetValue(_T("50"));
	gridItem->mAttr->ToString(str);

	IPropertyGridItem<MyEvent, const Vector3Df&>* gridItem2 = test->AddPropertyItem(_T("dd"), myDeal, &MyEvent::SetString, &MyEvent::GetString);
	gridItem2->mAttr->ToString(str);
	gridItem2->mAttr->SetValue(_T("10.0, 11.3, 12.9"));
	gridItem2->mAttr->ToString(str);*/


	// 创建场景管理器
	ISceneMgr* pSceneMgr = pEngine->CreateSceneMgr();
	pCamera = pSceneMgr->CreateCamera();
	pCamera->SetPosition(0, 0, 100);
	pCamera->SetLookAt(0,0,0);
	pCamera->SetUp(0,1,0);
	pWindow->SetCamera(pCamera);

	IResMgr* pResMgr = pEngine->GetResMgr();
	ResMesh pMesh = pResMgr->LoadMesh(_T("../media/penguin.hymesh"));
	bool b = pMesh->Load();

	IMeshObject* pMeshObj = pSceneMgr->CreateMeshObject();
	pMeshObj->BindResMesh(pMesh);

	ISceneNode* pNode = pSceneMgr->CreateNode();
	pNode->AttachObject(pMeshObj);

	// 创建UI
	ITabCtrl* pTabCtrl = pWindow->GetUiManager()->CreateTabCtrl();
	pTabCtrl->SetSize(200, pWindow->GetHeight() - 36);
	pTabCtrl->SetPos(pWindow->GetWidth() - pTabCtrl->GetSize().width - 2, 34);
	ITabPage* page1 = pTabCtrl->AddPage(_T("选择框"));
	ITabPage* page2 = pTabCtrl->AddPage(_T("滚动条"));
	ITabPage* page3 = pTabCtrl->AddPage(_T("其他"));
	
	page1->SetToolTip(_T("选择框"));
	page2->SetToolTip(_T("滚动条"));
	page3->SetToolTip(_T("其他"));
	
	s32 y = 200;
	IButton* pBtn = pWindow->GetUiManager()->CreateButton();
	pBtn->SetText(_T("开始游戏"));
	pBtn->SetSize(100, 30);
	pBtn->SetPos((pWindow->GetWidth() - 100) / 2, y);
	pBtn->SetToolTip(_T("开始游戏"));
	pBtn->SetEnable(false);

	y += 50;
	pBtn = pWindow->GetUiManager()->CreateButton();
	pBtn->SetText(_T("游戏设置"));
	pBtn->SetSize(100, 30);
	pBtn->SetPos((pWindow->GetWidth() - 100) / 2, y);
	pBtn->OnMouseClick().Add(myDeal, &MyEvent::ShowWindowClick);
	pBtn->SetToolTip(_T("游戏设置"));

	y += 50;
	pBtn = pWindow->GetUiManager()->CreateButton();
	pBtn->SetText(_T("退出游戏"));
	pBtn->SetSize(100, 30);
	pBtn->SetPos((pWindow->GetWidth() - 100) / 2, y);
	pBtn->OnMouseClick().Add(myDeal, &MyEvent::OnExitClick);
	pBtn->SetToolTip(_T("退出"));

	myDeal->mMenu = pWindow->GetUiManager()->CreateMenu();
	myDeal->mMenu->AddItem(_T("关于作者"));

	IDialog* pDialog = pWindow->GetUiManager()->CreateDialogs();
	pDialog->SetPos(10, 250);
	myDeal->pDialog = pDialog;
	ResTexture tex = pEngine->GetResMgr()->LoadTexture(_T("../media/logo.png"));
	tex->Load();

	pWindow->GetUiManager()->CreateTextBox(pDialog)->SetPos(150, 10);

	pWindow->GetUiManager()->CreateCheckBox(page1)->SetPos(10, 10);
	pWindow->GetUiManager()->CreateCheckBox(page1)->SetPos(10, 35);

	pWindow->GetUiManager()->CreateProgressBar(page2)->SetPos(0, 20);

	IListBox* listBox = pWindow->GetUiManager()->CreateListBox(pDialog);
	listBox->SetPos(10, 80);
	listBox->AddItem(_T("Item1"))->SetImage(tex);
	listBox->AddItem(_T("Item2"))->SetImage(tex);
	listBox->AddItem(_T("Item3"))->SetImage(tex);

	pWindow->GetUiManager()->CreateSliderBar(pDialog)->SetPos(10, 50);

	pWindow->GetUiManager()->CreateRadioButton(page1)->SetPos(10, 60);
	pWindow->GetUiManager()->CreateRadioButton(page1)->SetPos(10, 85);
	pWindow->GetUiManager()->CreateRadioButton(page1)->SetPos(10, 110);

	IComboBox* comboBox = pWindow->GetUiManager()->CreateComboBox(pDialog);
	comboBox->SetPos(10, 10);
	comboBox->AddItem(_T("combItem1"));
	comboBox->AddItem(_T("combItem2"));
	comboBox->AddItem(_T("combItem3"));
	comboBox->AddItem(_T("combItem4"));
	comboBox->AddItem(_T("combItem5"));
	comboBox->AddItem(_T("combItem6"));
	comboBox->AddItem(_T("combItem7"));
	comboBox->AddItem(_T("combItem8"));

	IToolBar* toolbar = pWindow->GetUiManager()->CreateToolBar();
	toolbar->SetSize(pWindow->GetWidth(), 25);
	toolbar->SetPos(0, 0);

	IToolBarItem* toolItem = toolbar->AddToolItem(_T("Open File"));
	toolItem->SetBackImage(pEngine->GetResMgr()->LoadTexture(_T("../media/open.png")));

	toolItem = toolbar->AddToolItem(_T("New File"));
	toolItem->SetBackImage(pEngine->GetResMgr()->LoadTexture(_T("../media/new.png")));
	toolItem->SetEnable(false);

	toolItem = toolbar->AddToolItem(_T("Save"));
	toolItem->SetBackImage(pEngine->GetResMgr()->LoadTexture(_T("../media/save.png")));

	toolbar->AddToolItem(_T(""), IToolBarItem::Separator);

	toolItem = toolbar->AddToolItem(_T("帮助"));
	toolItem->SetBackImage(pEngine->GetResMgr()->LoadTexture(_T("../media/about.png")));
	toolItem->OnMouseClick().Add(myDeal, &MyEvent::OnHelpClick);

	ILabel* lb = pWindow->GetUiManager()->CreateLabel();
	lb->SetPos(10, 35);
	lb->SetText(_T("Label Control Test"));

	IScrollBar* bar = pWindow->GetUiManager()->CreateScrollBar(page2);
	bar->SetPos(25, 50);
	bar->SetSize(10, 300);

	IPictureBox* pBox = pWindow->GetUiManager()->CreatePictureBox();
	pBox->SetSize(64, 64);
	pBox->SetPos( pWindow->GetWidth() - 74, pWindow->GetHeight() - 74);
	pBox->SetBackImage(tex);

	IListView* treeList = pWindow->GetUiManager()->CreateListView();
	treeList->SetPos(50,50);
	treeList->AddItem(_T("test"))->SetBackImage(pEngine->GetResMgr()->LoadTexture(_T("../media/about.png")));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));
	treeList->AddItem(_T("test"));


	ITreeView* treeView = pWindow->GetUiManager()->CreateTreeView(page3);
	treeView->SetSize(180, 490);
	treeView->SetPos(10, 10);
	treeView->AddItem(_T("根节点"));
	ITreeViewItem* treeNode = treeView->AddItem(_T("节点2"));
	treeNode->AddItem(_T("Node2-1"));
	treeNode->AddItem(_T("Node2-2"));
	treeNode->AddItem(_T("Node2-3"));
	treeNode->AddItem(_T("Node2-4"));
	treeNode->AddItem(_T("Node2-5"));
	treeNode->AddItem(_T("Node2-6"));
	treeNode->AddItem(_T("Node2-7"));
	treeNode->AddItem(_T("Node2-8"));
	treeNode = treeView->AddItem(_T("Node3"));
	treeNode->AddItem(_T("Node3-1"));
	treeNode->AddItem(_T("Node3-2"));
	treeNode->AddItem(_T("Node3-3"));
	treeNode->AddItem(_T("Node3-4"));
	treeNode->AddItem(_T("Node3-5"));
	treeNode->AddItem(_T("Node3-6"));
	treeNode->AddItem(_T("Node3-7"));
	treeNode = treeNode->AddItem(_T("Node3-2"));
	treeNode->AddItem(_T("Node3-2-1"));
	treeNode->AddItem(_T("Node3-2-2"));
	treeNode->AddItem(_T("Node3-2-3"));
	treeNode->AddItem(_T("Node3-2-4"));
	treeNode->AddItem(_T("Node3-2-5"));
	treeNode->AddItem(_T("Node3-2-6"));
	treeNode->AddItem(_T("Node3-2-7"));
	treeNode->Collapse();
	treeNode = treeView->AddItem(_T("Node4"));
	treeNode->AddItem(_T("Node4-1"));
	treeNode->AddItem(_T("Node4-2"));
	treeNode->AddItem(_T("Node4-3"));

	IMenuItem* item = myDeal->mMenu->AddItem(_T("关于游戏"));
	item->AddItem(_T("aaa"));
	item->AddItem(_T("bbb"));
	item->AddItem(_T("ccc"));
	item->AddItem(_T("ddd"));
	item->AddItem(_T("eeee"));
	item->AddItem(_T("ffffff"));
	myDeal->mMenu->AddItem(_T("-"));
	item = myDeal->mMenu->AddItem(_T("操作说明"));
	item->AddItem(_T("aaa"));
	item->AddItem(_T("bbb"));
	item->AddItem(_T("ccc"));
	item = item->AddItem(_T("dfsd"));
	item = item->AddItem(_T("dddd"));
	item->AddItem(_T("eeee"));
	item = item->AddItem(_T("ffff"));
	item->AddItem(_T("ee11ee"));
	item->AddItem(_T("ee12ee"));
	item->AddItem(_T("ee13ee"));
	item->AddItem(_T("ee14ee"));
	item->AddItem(_T("ee15ee"));
	item = item->AddItem(_T("ffff"));
	item->AddItem(_T("eeee"));
	item = item->AddItem(_T("ffff"));
	item->AddItem(_T("eeee"));
	item = item->AddItem(_T("ffff"));

	myDeal->mMenu->AddItem(_T("dasdfsd"));
	pEngine->Run();

	return 0;
}