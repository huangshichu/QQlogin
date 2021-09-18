#include"Test.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)

{
	CPaintManagerUI::SetInstance(hInstance);


	Test* pFrame = new Test();

	if (pFrame == NULL) return 0;

	pFrame->Create(NULL, _T("test"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 451, 320);

	pFrame->CenterWindow();//居中窗口位置

	::ShowWindow(*pFrame, SW_SHOW);//显示窗口

	CPaintManagerUI::MessageLoop();//开启duilib的消息循环，通用做法，Windows是基于消息机制的操作系统

	return 0;
}