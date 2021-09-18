#include "Test.h"

#include<wininet.h>//使用libcurl一直发生符号无法识别的错误
//即使使用vs2019管理程序包功能安装curl错误依然存在，故先用wininet代替一下发送http请求
#include<string>

using namespace DuiLib;

LPCTSTR Test::GetWindowClassName() const {
    return _T("Test"); 
};
UINT Test::GetClassStyle() const {
    return UI_CLASSSTYLE_FRAME | CS_DBLCLKS;
};

void Test::OnFinalMessage(HWND /*hWnd*/) {
    delete this; 
};

void Test::Init() {
    m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));
    m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
    m_pLoginBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("loginbtn")));
    m_pNameEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("name")));
    m_pPasswordEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("password")));
}


void Test::Notify(TNotifyUI& msg){
    if (msg.sType == _T("click")) {
        if (msg.pSender->GetName() == _T("closebtn")) {
            Close();
            return;
        }
        else if (msg.pSender->GetName() == _T("minbtn")) {
            SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
            return;
        }
        else if (msg.pSender->GetName() == _T("loginbtn")) {
            CDuiString name = m_pNameEdit->GetText();
            CDuiString password = m_pPasswordEdit->GetText();
            CDuiString s = "http://localhost:8081/UserController/login?user_name=";
            s = s + name + "&user_password=" + password;//拼接url
            urlopen(s);
        }
    }
}

void Test::urlopen(const _TCHAR* url)
{
    HINTERNET hSession = InternetOpen(_T("UrlTest"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (hSession != NULL)
    {
        HINTERNET hHttp = InternetOpenUrl(hSession, url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
        if (hHttp != NULL)
        {
            wprintf_s(L"%s\n", url);//L""定义宽字节字符串
            char Temp[1000];
            ULONG Number = 1;
            InternetReadFile(hHttp, Temp, 1000 - 1, &Number);
            Temp[Number] = '\0';
            if (Temp[0]=='T') {
                char show[9] = "登陆成功";
                ::MessageBox(NULL, Temp, _T("登录验证"), MB_OK);
            }
            else if (Temp[0]=='F') {
                char show[27] = "登陆失败，密码或用户名错误";
                ::MessageBox(NULL, Temp, _T("登录验证"), MB_OK);
            }
            InternetCloseHandle(hHttp);
            hHttp = NULL;
        }
        else {
            char show[21] = "登录失败，请检查网络";
            ::MessageBox(NULL, show, _T("登录验证"), MB_OK);
        }
        InternetCloseHandle(hSession);
        hSession = NULL;
    }
}

CDuiString Test::GetSkinFile()
{
    return _T("QQ.xml");
}

CDuiString Test::GetSkinFolder() {
    return _T("xml\\");
}

LRESULT Test::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_CREATE) {

        LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
        styleValue &= ~WS_CAPTION;//除去WS_CAPTION 样式  也就是窗口自带的标题栏和边框
        styleValue &= ~WS_THICKFRAME;//可调节边框   不除去该样式窗口上方会有白边 
        ::SetWindowLong(*this, GWL_STYLE, styleValue);
        CDuiString strResourcePath = m_pm.GetInstancePath();
        strResourcePath += GetSkinFolder().GetData();
        m_pm.SetResourcePath(strResourcePath.GetData());
        //设置xml路径

        m_pm.Init(m_hWnd);
        CDialogBuilder builder;//用于根据xml创建控件
        CControlUI* pRoot = builder.Create(GetSkinFile().GetData(),0, NULL, &m_pm);//获取xml创建控件
        ASSERT(pRoot && "Failed to parse XML");
        m_pm.AttachDialog(pRoot);//根控件绑定CPaintManagerUI对象
        m_pm.AddNotifier(this);// 添加Notify事件接口
        Init();//获取对应的控件
        return 0;
    }
    else if (uMsg == WM_DESTROY) {
        ::PostQuitMessage(0);
    }

    LRESULT lRes = 0;

    if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;

    return CWindowWnd::HandleMessage(uMsg, wParam, lParam);

    }