
// YBExplorer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYBExplorerApp: 
// �йش����ʵ�֣������ YBExplorer.cpp
//

class CYBExplorerApp : public CWinApp
{
public:
	CYBExplorerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYBExplorerApp theApp;