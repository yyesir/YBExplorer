
// YBExplorerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YBExplorer.h"
#include "YBExplorerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CYBExplorerDlg 对话框

int CYBExplorerDlg::m_iOnce = 0;

CYBExplorerDlg::CYBExplorerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYBExplorerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYBExplorerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeCtrl);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CYBExplorerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CYBExplorerDlg::OnNMDblclkTree1)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, &CYBExplorerDlg::OnTvnItemexpandingTree1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CYBExplorerDlg::OnNMRClickList1)
	ON_COMMAND(ID_32770, &CYBExplorerDlg::On32770)
	ON_COMMAND(ID_32771, &CYBExplorerDlg::On32771)
	ON_COMMAND(ID_32772, &CYBExplorerDlg::On32772)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CYBExplorerDlg::OnNMRClickTree1)
	ON_COMMAND(ID_TREE_32778, &CYBExplorerDlg::OnTree32778)
	ON_COMMAND(ID_TREE_32775, &CYBExplorerDlg::OnTree32775)
	ON_COMMAND(ID_TREE_32776, &CYBExplorerDlg::OnTree32776)
	ON_COMMAND(ID_TREE_32777, &CYBExplorerDlg::OnTree32777)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, &CYBExplorerDlg::OnTvnEndlabeleditTree1)
END_MESSAGE_MAP()


// CYBExplorerDlg 消息处理程序

BOOL CYBExplorerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	initDrives();
	initTreeCtrl();
	initListCtrl();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CYBExplorerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CYBExplorerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CYBExplorerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CYBExplorerDlg::OnOk() {}

void CYBExplorerDlg::OnCancel() {}

void CYBExplorerDlg::OnClose()
{
	m_treeCtrl.DeleteAllItems();
	m_listCtrl.DeleteAllItems();
	memset(m_hRoot, 0, sizeof(m_hRoot));
	EndDialog(IDCANCEL);    //关闭窗口
	CDialogEx::OnClose();
}

void CYBExplorerDlg::initDrives()
{
	int nPos = 0;
	UINT nCount = 0;
	CString strDrive = L"?:\\";
	DWORD dwDriveList = ::GetLogicalDrives();
	CString cTmp;
	while (dwDriveList)
	{
		if (dwDriveList & 1)
		{
			cTmp = strDrive;
			strDrive.SetAt(0, 0x41 + nPos);
			if (getDrives(strDrive))
				nCount++;
		}
		dwDriveList >>= 1;
		nPos++;
	}
	return;
}

BOOL CYBExplorerDlg::getDrives(CString strDrive)
{
	UINT nType = ::GetDriveType((LPCTSTR)strDrive);
	UINT nDrive = (UINT)strDrive[0] - 0x41;
	switch (nType)
	{
	case DRIVE_REMOVABLE:
		break;
	case DRIVE_FIXED:
		m_vecDrives.push_back(strDrive);
		break;
	case DRIVE_REMOTE:
		break;
	case DRIVE_CDROM:
		break;
	case DRIVE_RAMDISK:
		break;
	default:
		return FALSE;
	}
	return true;
}

void CYBExplorerDlg::initTreeCtrl()
{
	m_iOnce = 1;
	TCHAR MyDir[_MAX_PATH];
	SHGetSpecialFolderPath(this->GetSafeHwnd(), MyDir, CSIDL_DESKTOP, 0);
	m_strDesktopPath = MyDir;
	HTREEITEM hItem = m_treeCtrl.InsertItem(L"桌面", 0, 0);
	m_treeCtrl.SelectItem(hItem);
	myTreeNode treeNode(L"桌面", MyDir, hItem);
	m_treeRootNode[hItem] = treeNode;
	if (m_vecDrives.size() > 0 && m_vecDrives.size() < 10)
	{
		for (size_t i = 0; i < m_vecDrives.size();i++)
		{
			if (m_vecDrives[i] == "C:\\")
			{
				hItem = m_treeCtrl.InsertItem(L"C盘", 0, 0);
				myTreeNode treeNode(L"C盘", m_vecDrives[i], hItem);
				m_treeRootNode[hItem] = treeNode;
				continue;
			}
			else if (m_vecDrives[i] == "D:\\")
			{
				hItem = m_treeCtrl.InsertItem(L"D盘", 0, 0);
				myTreeNode treeNode(L"D盘", m_vecDrives[i], hItem);
				m_treeRootNode[hItem] = treeNode;
				continue;
			}
			else if (m_vecDrives[i] == "E:\\")
			{
				hItem = m_treeCtrl.InsertItem(L"E盘", 0, 0);
				myTreeNode treeNode(L"E盘", m_vecDrives[i], hItem);
				m_treeRootNode[hItem] = treeNode;
				continue;
			}
			else if (m_vecDrives[i] == "F:\\")
			{
				hItem = m_treeCtrl.InsertItem(L"F盘", 0, 0);
				myTreeNode treeNode(L"F盘", m_vecDrives[i], hItem);
				m_treeRootNode[hItem] = treeNode;
				continue;
			}
		}
	}
	std::map<HTREEITEM, myTreeNode>::iterator iter = m_treeRootNode.begin();
	for (; iter != m_treeRootNode.end();iter++)
	{
		setCtrlData(iter->first, iter->second.m_strPath);
	}
}

void CYBExplorerDlg::initListCtrl() 
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);// 获取当前窗口style 
	lStyle &= ~LVS_TYPEMASK; // 清除显示方式位 
	lStyle |= LVS_REPORT; // 设置style 
	SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);// 设置style 
	lStyle = GetWindowLong(m_treeCtrl.m_hWnd, GWL_STYLE);// 获取当前窗口style
	lStyle |= TVS_HASBUTTONS;
	lStyle |= TVS_HASLINES;
	lStyle |= TVS_LINESATROOT;
	lStyle |= TVS_EDITLABELS;
	SetWindowLong(m_treeCtrl.m_hWnd, GWL_STYLE, lStyle);
	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	m_listCtrl.SetExtendedStyle(dwStyle); // 设置扩展风格 
	m_listCtrl.InsertColumn(0, L"文件名", LVCFMT_LEFT, 300, -1);
	m_listCtrl.InsertColumn(1, L"文件大小", LVCFMT_LEFT, 150, -1);
	m_listCtrl.InsertColumn(2, L"最后修改日期", LVCFMT_LEFT, 350, -1);
}

LPTSTR CYBExplorerDlg::GetNTS(CString cString)
{
	LPTSTR lpsz = new TCHAR[cString.GetLength() + 1];
	_tcscpy(lpsz, cString);
	return lpsz;
}

BOOL CYBExplorerDlg::IsDriveNode(HTREEITEM hItem)
{
	return (m_treeCtrl.GetParentItem(hItem) == NULL) ? TRUE : FALSE;
}

CString CYBExplorerDlg::GetPathFromItem(HTREEITEM hItem)
{
	CString strPathName;
	while (hItem != NULL)
	{
		CString string = m_treeCtrl.GetItemText(hItem);
		if (string == "桌面")
		{
			string = m_strDesktopPath;
		}
		else if (string == "C盘")
		{
			string = "C:\\";
		}
		else if (string == "D盘")
		{
			string = "D:\\";
		}
		else if (string == "E盘")
		{
			string = "E:\\";
		}
		else if (string == "F盘")
		{
			string = "F:\\";
		}
		if ((string.Right(1) != "\\") && !strPathName.IsEmpty())
			string += "\\";
		strPathName = string + strPathName;
		hItem = m_treeCtrl.GetParentItem(hItem);
	}
	return strPathName;
}

BOOL CYBExplorerDlg::IsPathValid(CString &strPathName)
{
	if (strPathName.GetLength() == 3)
		return TRUE;
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	BOOL bResult = FALSE;
	if ((hFind = ::FindFirstFile((LPCTSTR)strPathName, &fd)) != INVALID_HANDLE_VALUE)
	{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			bResult = TRUE;
		else
			::CloseHandle(hFind);
	}
	return bResult;
}

void CYBExplorerDlg::initListCtrl(WIN32_FIND_DATA *fd, CString sPath)
{
	LV_ITEM lvitem;
	char sNumBuff[100];
	int iActualItem;
	CString sText;
	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvitem.iItem = 0;
	lvitem.iSubItem = 0;
	if (sPath.Right(2) == "\\")
		lvitem.pszText = GetNTS(/*sPath + */fd->cFileName);
	else
		lvitem.pszText = GetNTS(/*sPath + L"\\" + */fd->cFileName);
	iActualItem = m_listCtrl.InsertItem(&lvitem);
	if (fd->nFileSizeLow != 0)
		_ltoa((long)fd->nFileSizeLow, sNumBuff, 10);
	else
		strcpy(sNumBuff, "");
	size_t len = strlen(sNumBuff) + 1;
	size_t converted = 0;
	wchar_t *WStr = NULL;
	WStr = (wchar_t*)malloc(len*sizeof(wchar_t));
	mbstowcs_s(&converted, WStr, len, sNumBuff, _TRUNCATE);
	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = iActualItem;
	lvitem.iSubItem = 1;
	lvitem.pszText = WStr;
	m_listCtrl.SetItem(&lvitem);
	free(WStr);
	WStr = NULL;
	// Add Time column
	CTime refTime;
	refTime = fd->ftCreationTime;
	sText = refTime.Format("%b-%d-%Y");
	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = iActualItem;
	lvitem.iSubItem = 2;
	lvitem.pszText = sText.GetBuffer(sText.GetLength());
	m_listCtrl.SetItem(&lvitem);
}

BOOL CYBExplorerDlg::HasSubdirectory(CString &strPathName)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	BOOL bResult = FALSE;
	CString strFileSpec = strPathName;
	if (strFileSpec.Right(1) != "\\")
		strFileSpec += "\\";
	strFileSpec += "*.*";
	if ((hFind = ::FindFirstFile((LPCTSTR)strFileSpec, &fd)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				CString strFileName = (LPCTSTR)&fd.cFileName;
				if ((strFileName != ".") && (strFileName != ".."))
					bResult = TRUE;
			}
		} while (::FindNextFile(hFind, &fd) && !bResult);
		::FindClose(hFind);
	}
	return bResult;
}

void CYBExplorerDlg::setChildrenData(HTREEITEM hItem, CString &strPathName)
{
	HasSubdirectory(strPathName);
}

void CYBExplorerDlg::setCtrlData(HTREEITEM hItem, CString &strPathName)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	CString strFileSpec = strPathName;
	if (strFileSpec.Right(1) != "\\")
		strFileSpec += "\\";
	strFileSpec += "*.*";
	if ((hFind = ::FindFirstFile((LPCTSTR)strFileSpec, &fd)) == INVALID_HANDLE_VALUE)
	{
		return ;
	}
	CWaitCursor wait;
	do
	{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			CString strFileName = (LPCTSTR)&fd.cFileName;
			if ((strFileName != ".") && (strFileName != "..") && (fd.dwFileAttributes != 22))
			{
				HTREEITEM hChild = m_treeCtrl.InsertItem((LPCTSTR)&fd.cFileName, hItem, TVI_SORT);
				CString strNewPathName = strPathName;
				if (strNewPathName.Right(1) != "\\")
					strNewPathName += "\\";
				strNewPathName += (LPCTSTR)&fd.cFileName;
				setChildrenData(hChild, strNewPathName);
			}
		}
		else
		{
			if (m_iOnce == 0)
				initListCtrl(&fd, strPathName);
		}
	} while (::FindNextFile(hFind, &fd));
	::FindClose(hFind);
}

UINT CYBExplorerDlg::DeleteChildren(HTREEITEM hItem)
{
	UINT nCount = 0;
	HTREEITEM hChild = m_treeCtrl.GetChildItem(hItem);
	while (hChild != NULL)
	{
		HTREEITEM hNextItem = m_treeCtrl.GetNextSiblingItem(hChild);
		m_treeCtrl.DeleteItem(hChild);
		hChild = hNextItem;
		nCount++;
	}
	return nCount;
}


void CYBExplorerDlg::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	if (m_treeCtrl.GetParentItem(hItem) != NULL)
	{
		m_iOnce = 0;
		m_listCtrl.DeleteAllItems();
		DeleteChildren(hItem);
		CString strText = GetPathFromItem(hItem);
		//初始化树根节点并转开根节点
		setCtrlData(hItem, strText);
	}	
	*pResult = 0;
}


void CYBExplorerDlg::OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void CYBExplorerDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{
		CMenu menu, *pPopup;
		menu.LoadMenu(IDR_MENU1);
		pPopup = menu.GetSubMenu(0);
		CPoint point;
		ClientToScreen(&point);
		GetCursorPos(&point);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	*pResult = 0;
}

//listctrl 复制
void CYBExplorerDlg::On32770()
{
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	m_strCopyPath = GetPathFromItem(hItem);
	int nRow = m_listCtrl.GetSelectionMark();
	if (m_strCopyPath.Right(1) != "\\")
		m_strCopyPath += "\\";
	m_strCopyPath += m_listCtrl.GetItemText(nRow, 0);
}

//listctrl 粘贴
void CYBExplorerDlg::On32771()
{
	if (!m_strCopyPath.IsEmpty())
	{
		HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
		CString strPath = GetPathFromItem(hItem);
		CString strText = strPath;
		if (strPath.Right(1) != "\\")
			strPath += "\\";
		strPath += m_strCopyPath.Mid(m_strCopyPath.ReverseFind('\\') + 1);
		if (CopyFile(m_strCopyPath, strPath, FALSE)) 
		{
			DeleteChildren(hItem);
			m_listCtrl.DeleteAllItems();
			setCtrlData(hItem, strText);
		}
	}
	else
	{
		MessageBox(L"请选择要复制的文件");
	}

}

//listctrl 删除
void CYBExplorerDlg::On32772()
{
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	CString strPath = GetPathFromItem(hItem);
	CString strText = strPath;
	if (strPath.Right(1) != "\\")
		strPath += "\\";
	int nRow = m_listCtrl.GetSelectionMark();
	strPath += m_listCtrl.GetItemText(nRow, 0);
	if (MessageBox(L"确定要删除此文件吗？", L"温馨提示", MB_YESNO) == IDYES) 
	{
		if (DeleteFile(strPath)) 
		{
			DeleteChildren(hItem);
			m_listCtrl.DeleteAllItems();
			setCtrlData(hItem, strText);
			MessageBox(L"删除成功!");
		}
		else
		{
			MessageBox(L"删除失败!");
		}
	}
}

//双击展开树
void CYBExplorerDlg::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU2);
	pPopup = menu.GetSubMenu(0);
	CPoint point;
	ClientToScreen(&point);
	GetCursorPos(&point);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	*pResult = 0;
}

//treectrl 新建
void CYBExplorerDlg::OnTree32778()
{
	//新建
	//1、获取选中节点
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	//2、插入子节点
	HTREEITEM hNewChild = m_treeCtrl.InsertItem(L"新建文件夹", hItem);
	//3、设置子节点可以修改名称
	m_treeCtrl.SelectItem(hNewChild);
	CEdit* pEdit = m_treeCtrl.EditLabel(hNewChild);
}

//treectrl 复制
void CYBExplorerDlg::OnTree32775()
{
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	m_strNodeCopyPath = GetPathFromItem(hItem);
}

void CYBExplorerDlg::myCopyDirectory(CString& source, CString& target) 
{
	if (CreateDirectory(target, NULL))
	{
		CFileFind finder;
		CString path;
		path.Format(L"%s/*.*", source);
		BOOL bWorking = finder.FindFile(path);
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory() && !finder.IsDots())
			{
				myCopyDirectory(finder.GetFilePath(), target + "/" + finder.GetFileName());
			}
			else
			{
				CopyFile(finder.GetFilePath(), target + "/" + finder.GetFileName(),FALSE);
			}
		}
	}
}

//treectrl 粘贴
void CYBExplorerDlg::OnTree32776()
{
	if (!m_strNodeCopyPath.IsEmpty())
	{
		BeginWaitCursor();
		CString str = m_strNodeCopyPath.Mid(m_strNodeCopyPath.ReverseFind('\\')+1);
		HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
		CString strTargetPath = GetPathFromItem(hItem);
		if (strTargetPath.Right(1) != "\\")
			strTargetPath += "\\";
		myCopyDirectory(m_strNodeCopyPath, strTargetPath + str);
		DeleteChildren(hItem);
		m_listCtrl.DeleteAllItems();
		setCtrlData(hItem, strTargetPath);
		EndWaitCursor();
	}
}

void CYBExplorerDlg::myDeleteDirectory(CString& target)
{
	CFileFind finder;
	CString path;
	path.Format(L"%s/*.*", target);
	BOOL bWorking = finder.FindFile(path);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory() && !finder.IsDots())
		{
			myDeleteDirectory(finder.GetFilePath());
			RemoveDirectory(finder.GetFilePath());
		}
		else
		{
			DeleteFile(finder.GetFilePath());
		}
	}
	RemoveDirectory(target);
}

//treectrl 删除
void CYBExplorerDlg::OnTree32777()
{
	BeginWaitCursor();
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	if (m_treeCtrl.GetParentItem(hItem) == NULL)
	{
		MessageBox(L"不能删除根目录");
		return;
	}
	CString strTargetPath = GetPathFromItem(hItem);
	myDeleteDirectory(strTargetPath);
	hItem = m_treeCtrl.GetParentItem(hItem);
	DeleteChildren(hItem);
	m_listCtrl.DeleteAllItems();
	setCtrlData(hItem, GetPathFromItem(hItem));
	EndWaitCursor();
}

void CYBExplorerDlg::OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	if (m_treeCtrl.GetParentItem(pTVDispInfo->item.hItem) == NULL)
	{
		return;
	}
	if (pTVDispInfo->item.pszText != NULL && pTVDispInfo->item.pszText != L"新建文件夹")
	{
		m_treeCtrl.SetItemText(pTVDispInfo->item.hItem, pTVDispInfo->item.pszText);
		CString strText = GetPathFromItem(pTVDispInfo->item.hItem);
		if (!CreateDirectory(strText, NULL))
		{
			return;
		}
	}
	else
	{
		MessageBox(L"文件夹名不符合要求");
		m_treeCtrl.EditLabel(pTVDispInfo->item.hItem);
	}
	*pResult = 0;
}
