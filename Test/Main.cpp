#include"Test.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)

{
	CPaintManagerUI::SetInstance(hInstance);


	Test* pFrame = new Test();

	if (pFrame == NULL) return 0;

	pFrame->Create(NULL, _T("test"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 451, 320);

	pFrame->CenterWindow();//���д���λ��

	::ShowWindow(*pFrame, SW_SHOW);//��ʾ����

	CPaintManagerUI::MessageLoop();//����duilib����Ϣѭ����ͨ��������Windows�ǻ�����Ϣ���ƵĲ���ϵͳ

	return 0;
}