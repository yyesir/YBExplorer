
// YBExplorerDlg.h : 头文件
//

#pragma once
#include <commctrl.h>
#include <vector>
#include "afxcmn.h"
#include <map>

// CYBExplorerDlg 对话框
class CYBExplorerDlg : public CDialogEx
{
private:
	class myTreeNode
	{
	public:
		myTreeNode() {}
		myTreeNode(const CString& strText, const CString& strPath, const HTREEITEM& hItem) 
		{ 
			m_strText = strText; 
			m_strPath = strPath;
			m_hItem = hItem;
		}
		virtual ~myTreeNode() {}
		CString		m_strText;//树根节点名称
		CString		m_strPath;//树根节点路径
		HTREEITEM	m_hItem;	//树根节点
	};
// 构造
public:
	CYBExplorerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YBEXPLORER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	void			initDrives();
	void			initTreeCtrl();
	void			initListCtrl();
	void			initListCtrl(WIN32_FIND_DATA *fd, CString sPath);
	BOOL			getDrives(CString strDrive);
	LPTSTR			GetNTS(CString cString);
	void			setCtrlData(HTREEITEM hItem, CString &strPathName);
	void			setChildrenData(HTREEITEM hItem, CString &strPathName);
	CString			GetPathFromItem(HTREEITEM hItem);
	BOOL			IsPathValid(CString &strPathName);
	BOOL			IsDriveNode(HTREEITEM hItem);
	BOOL			HasSubdirectory(CString &strPathName);
	UINT			DeleteChildren(HTREEITEM hItem);
	void			myCopyDirectory(CString& source, CString& target);
	void			myDeleteDirectory(CString& target);
private:
	static int						m_iOnce;
	std::vector<CString>			m_vecDrives;
	std::map<HTREEITEM, myTreeNode>	m_treeRootNode;
	HTREEITEM						m_hRoot[10];
	CString							m_strCopyPath;
	CString							m_strNodeCopyPath;
	CString							m_strDesktopPath;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnOk();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
private:
	CTreeCtrl m_treeCtrl;
	CListCtrl m_listCtrl;
public:
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On32770();
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTree32778();
	afx_msg void OnTree32775();
	afx_msg void OnTree32776();
	afx_msg void OnTree32777();
	afx_msg void OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
