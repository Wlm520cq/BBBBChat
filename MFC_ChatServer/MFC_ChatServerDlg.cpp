
// MFC_ChatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC_ChatServer.h"
#include "MFC_ChatServerDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_CHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMFCChatServerDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatServerDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMFCChatServerDlg::OnBnClickedClearBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CMFCChatServerDlg::OnBnClickedStopBtn)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CAL_BTN, &CMFCChatServerDlg::OnBnClickedCalBtn)
	ON_BN_CLICKED(IDC_MAIL_BTN, &CMFCChatServerDlg::OnBnClickedMailBtn)
	ON_BN_CLICKED(IDC_QQ_BTN, &CMFCChatServerDlg::OnBnClickedQqBtn)
	ON_BN_CLICKED(IDC_BAIDU_BTN, &CMFCChatServerDlg::OnBnClickedBaiduBtn)
END_MESSAGE_MAP()


// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	//当没有启动到服务器的时候，关闭、发送都是不可点击的
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(false);       //发送按钮
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(false);       //停止服务器
	GetDlgItem(IDC_START_BTN)->EnableWindow(true);       //启动服务器

	//添加颜色
	m_WordColorCombo.AddString(L"黑色");
	m_WordColorCombo.AddString(L"红色");
	m_WordColorCombo.AddString(L"蓝色");
	m_WordColorCombo.AddString(L"绿色");

	m_WordColorCombo.SetCurSel(0);

	SetDlgItemText(IDC_COLOR_COMBO, L"黑色");

	//设置固定的端口号
	GetDlgItem(IDC_PROT_EDIT)->SetWindowText(_T("5000"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatServerDlg::OnPaint()
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
		//第一步  确定目的区域    第二步  加载资源图片并且转化为内存设备  第三步 绘图
		//1.定义DC
		CPaintDC dc(this); // 用于绘制的设备上下文
		//2.确定绘制的（目的）区域
		CRect rect;
		GetClientRect(&rect);

		//3.定义并创建一个内存设备环境 创建兼容性DC （搭桥梁）
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);

		//4.载入资源图片
		CBitmap bmpBackGround;
		bmpBackGround.LoadBitmapW(IDB_HILL_BITMAP);

		//5.将图片资源载入到位图里面 BitMap 位图
		BITMAP bBitMap;
		bmpBackGround.GetBitmap(&bBitMap);

		//6.将位图选入临时的内存设备环境
		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackGround);

		//7.开始绘制
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp,
			0, 0, bBitMap.bmWidth, bBitMap.bmHeight, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//发送消息的函数（包装）
CString CMFCChatServerDlg::CatShowString(CString strInfo, CString strMsg)
{
	//时间 + 信息（昵称） + 消息
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X ");
	CString strShow;
	strShow = strTime + strShow;
	strShow += strInfo;
	strShow += strMsg;
	return strShow;
}

//启动服务器的处理函数
void CMFCChatServerDlg::OnBnClickedStartBtn()
{
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(true);       //发送按钮
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(true);       //停止服务器
	GetDlgItem(IDC_START_BTN)->EnableWindow(false);     //启动服务器

	// TODO: 在此添加控件通知处理程序代码
	TRACE("####OnBnClickedStartBtn");
	CString strPort;
	//重控件里面获取内容
	GetDlgItem(IDC_PROT_EDIT)->GetWindowText(strPort);

	//CString 转 char*
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	TRACE("szPort=%s", szPort);

	int iPort = _ttoi(strPort);
	//创建一个服务器 seversocket 对象
	m_server = new CServerSocket;
	//创建套接字  容错率
	if (!m_server->Create(iPort))
	{
		TRACE("服务器创建失败！%d", GetLastError());
		return;
	}
	else
	{
		TRACE("服务器创建成功！");
	}

	if (!m_server->Listen())
	{
		TRACE("没有监听到客服端的请求！%d", GetLastError());
		return;
	}
	else
	{
		TRACE("监听到客服端的请求！");
	}
#if 0
	CString str;
	//得到当前计算机的准确时间
	m_tm = CTime::GetCurrentTime();
	str = m_tm.Format("%X ");
	str += _T("建立服务器成功！");
#endif
	CString strShow;
	CString strInfo = _T(" ");
	CString strMsg = _T("建立服务端！ ");
	strShow = CatShowString(strInfo, strMsg);

	m_list.AddString(strShow);
	UpdateData(false);
}

//发送消息的处理函数
void CMFCChatServerDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	//1.获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SEND_EDIT)->GetWindowText(strTmpMsg);

	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	//2.发送消息给服务端
	m_chat->Send(szSendBuf, SEND_SERVER_BUF, 0);

	//3.显示到列表框中
	CString strShow;
	CString strInfo = _T("服务端: ");
	strShow = CatShowString(strInfo, strTmpMsg);

#if 0
	CString strShow = _T("服务端: ");
	CString strTime;
	m_tm = CTime::GetCurrentTime();
	strTime = m_tm.Format("%X ");
	strShow = strTime + strShow; //时间 + 我：内容
	strShow += strTmpMsg;
#endif

	m_list.AddString(strShow);

	UpdateData(false);

	//清空编辑框
	GetDlgItem(IDC_SEND_EDIT)->SetWindowText(_T(" "));
}

//清除屏幕内容的处理函数
void CMFCChatServerDlg::OnBnClickedClearBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatServerDlg::OnBnClickedStopBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.控件的控制
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(false);       //发送按钮
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(false);       //停止服务器
	GetDlgItem(IDC_START_BTN)->EnableWindow(true);       //启动服务器

	//2.回收资源
	m_server->Close();
	if (m_server != NULL)
	{
		delete m_server;
		m_server = NULL;
	}

	if (m_chat != NULL)
	{
		delete m_chat;
		m_chat = NULL;
	}
	//3.显示到列表框
	CString strShow;
	strShow = CatShowString(L" ", L"服务器已停止！");
	m_list.AddString(strShow);
	UpdateData(false);
}


HBRUSH CMFCChatServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CString strColor;
	m_WordColorCombo.GetWindowTextW(strColor);

	if (IDC_MSG_LIST == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID()) {
		if (strColor == L"黑色")
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		if (strColor == L"红色")
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		if (strColor == L"蓝色")
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		if (strColor == L"绿色")
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}
	return hbr;
}

//打开计算器的处理函数
void CMFCChatServerDlg::OnBnClickedCalBtn()
{
	ShellExecute(NULL, L"open", L"calc.exe", NULL, NULL, SW_SHOWNORMAL);
}

//打开邮箱的处理函数
void CMFCChatServerDlg::OnBnClickedMailBtn()
{
	ShellExecute(NULL, L"open", L"https://mail.qq.com", NULL, NULL, SW_SHOWNORMAL);
}

//打开 QQ 的处理函数
void CMFCChatServerDlg::OnBnClickedQqBtn()
{
	ShellExecute(NULL, L"open", L"C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedBaiduBtn()
{
	ShellExecute(NULL, L"open", L"https://www.baidu.com", NULL, NULL, SW_SHOWNORMAL);
}

//防止点击 回车键 退出程序的处理函数
BOOL CMFCChatServerDlg::PreTranslateMessage(MSG* pMsg)
{
	//规避回车键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return true;
	}

	//规避空格键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)
	{
		return true;
	}

	//添加快捷键
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetKeyState(VK_CONTROL) < 0)//Ctrl 是否按下
		{
			if (pMsg->wParam == 'X')
			{
				CDialogEx::OnOK();
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
