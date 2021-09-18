#pragma once
#include "StdAfx.h"

using namespace DuiLib;
#define WM_ADDLISTITEM WM_USER + 50

class Test : public CWindowWnd, public INotifyUI 
{
public:
	Test() { };
	void urlopen(const _TCHAR* url);
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND hWnd);
	void Init();
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	CDuiString GetSkinFile();
	CDuiString GetSkinFolder();
public:
	CPaintManagerUI m_pm;
private:
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMinBtn;
	CButtonUI* m_pLoginBtn;
	CEditUI* m_pNameEdit;
	CEditUI* m_pPasswordEdit;
};