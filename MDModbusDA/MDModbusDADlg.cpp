
// MDModbusDADlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MDModbusDA.h"
#include "MDModbusDADlg.h"
#include "afxdialogex.h"

//#include "DeviceRtdbAPI.h"

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


// CMDModbusDADlg 对话框



CMDModbusDADlg::CMDModbusDADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MDMODBUSDA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMDModbusDADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CMDModbusDADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMDModbusDADlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CMDModbusDADlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_LOG, &CMDModbusDADlg::OnBnClickedButtonClearLog)
	ON_MESSAGE(WM_STATUS_CHANGE, &CMDModbusDADlg::OnStatusChange)
	ON_MESSAGE(WM_DATA_CHANGE, &CMDModbusDADlg::OnDataChange)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT_SYMLINKSERVER, &CMDModbusDADlg::OnBnClickedButtonConnectSymlinkserver)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_SYMLINKSERVER, &CMDModbusDADlg::OnBnClickedButtonDisconnectSymlinkserver)
	ON_EN_CHANGE(IDC_EDIT_LOG, &CMDModbusDADlg::OnEnChangeEditLog)

	ON_MESSAGE(WM_YYMSG_APPEND_LOGBOX, &CMDModbusDADlg::AppendTextToLogBox)
END_MESSAGE_MAP()


// CMDModbusDADlg 消息处理程序

BOOL CMDModbusDADlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_IPADDRESS_AGILOR_IP)->SetWindowText("127.0.0.1");
	GetDlgItem(IDC_EDIT_AGILOR_PORT)->SetWindowText("700");
	GetDlgItem(IDC_EDIT_DEVICENAME)->SetWindowText("BACNET");
	

	GetDlgItem(IDC_IPADDRESS_IP_SYMLINK)->SetWindowText("192.168.10.245");
	GetDlgItem(IDC_EDIT_PORT_SYMLINK)->SetWindowText("9230");
	GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText("LNUser");
	

	m_pLink = CreateSymLinkApi(0);
	m_pLink->SetCallerPtr(this);
	m_pLink->SetStatusChangeFunc(apiStatusChange);
	m_pLink->SetDataChangeFunc(apiDataChange);
	m_pLink->SetSLEventChangeFunc(apiSLEventChange);
	m_pLink->SetChangeBufStatus(1);
	m_pLink->SetTxSaveBufStatus(1);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMDModbusDADlg::apiStatusChange(void *v1, void *v2, int nStatus)
{
	CSymLinkApi *pLink = (CSymLinkApi *)v1;
	CMDModbusDADlg *pThis = (CMDModbusDADlg *)v2;

	pThis->PostMessage(WM_STATUS_CHANGE, nStatus, 0);
}

void CMDModbusDADlg::apiDataChange(void *v1, void *v2, int nCount, int *pChange)
{
	CSymLinkApi *pLink = (CSymLinkApi *)v1;
	CMDModbusDADlg *pThis = (CMDModbusDADlg *)v2;

	pThis->PostMessage(WM_DATA_CHANGE, nCount, 0);
}

void CMDModbusDADlg::apiSLEventChange(void *v1, void *v2, int nCount)
{
	CSymLinkApi *pLink = (CSymLinkApi *)v1;
	CMDModbusDADlg *pThis = (CMDModbusDADlg *)v2;
}

void CMDModbusDADlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMDModbusDADlg::OnPaint()
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
HCURSOR CMDModbusDADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// agilor code: rtdb server callback function - new target
void __stdcall OnNewTagNodeArrive(LPTAGNODE, LPCTSTR) {

}
// agilor code: rtdb server callback function - remove target
void __stdcall OnRemoveTagNode(LPTAGNODE, LPCTSTR) {

}
// agilor code: rtdb server callback function - set target new value
void __stdcall OnSetDeviceTagValue(LPTAGVALUELOCAL val, LPCTSTR deviceName) {
	CString csInfo;
	csInfo.Format("[Debug] Received Value, source name: %s\r\n", val->szTagSource);
	::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);

	if (val->cTagType == 'S') {
		// String as Enum
		DRTDB_MD_SendNewValues((LPSTR)deviceName, val, 1);
		DRTDB_MD_Flush((LPSTR)deviceName);
		return;
	}

	CString errorInfo;
	if (m_pLink == nullptr) {
		errorInfo.Format("[Error] GetDbTagDataByName. Called at line %d, in the %s file. SymLink is not connected, m_pLink is nullptr.\r\n", __LINE__, __FILE__);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&errorInfo);
		return;
	}

	SymLinkApiData data;
	int nRet = 0, nResult = 0;
	SymLinkApiString err;
	// Get data
	nRet = m_pLink->GetDbTagDataByName(val->szTagSource, data);
	if (nRet != 0) {
		errorInfo.Format("[Error] GetDbTagDataByName. The return code is %d. Called at line %d, in the %s file.\r\n", nRet, __LINE__, __FILE__);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&errorInfo);
		return;
	}
	//change data
	switch (val->cTagType)
	{
	case 'R':
		data = val->fValue;
		break;
	case 'S':
		data = val->szValue;
		break;
	case 'L':
		data = val->lValue;
		break;
	default:
		errorInfo.Format("[Error] Switch run to default. The tag type is %c. Called at line %d, in the %s file.\r\n", val->cTagType, __LINE__, __FILE__);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&errorInfo);
		return;
	}
	// set data, try 3 times
	int i = 0;
	for (; i < 3; i++)
	{
		nRet = m_pLink->SetDbTagDataByName(val->szTagSource, data, &nResult, &err);
		if (nRet == 0) {
			break;
		}
		else {
			errorInfo.Format("[Warning] Try %dth SetDbTagDataByName. The return code is %d. Called at line %d, in the %s file.\r\n", i, nRet, __LINE__, __FILE__);
			::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&errorInfo);
			::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&err);
		}
	}
	if (i < 3) {
		errorInfo.Format("[Success] Try %dth SetDbTagDataByName Success.\r\n", i);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&errorInfo);
	}
	else {
		errorInfo.Format("[Error] SetDbTagDataByName Failed, TagName: %s.\r\n", val->szTagSource);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&errorInfo);
	}
}
// agilor code: rtdb server callback function - get target value
void __stdcall OnGetDeviceTagValue(LPTAGNODE, LPCTSTR) {

}
// agilor code: connect rtdb server
void CMDModbusDADlg::OnBnClickedButtonConnect()
{
	// get value cstring
	CString agilorIp, agilorPort, deviceName;
	GetDlgItem(IDC_IPADDRESS_AGILOR_IP)->GetWindowText(agilorIp);
	GetDlgItem(IDC_EDIT_AGILOR_PORT)->GetWindowText(agilorPort);
	GetDlgItem(IDC_EDIT_DEVICENAME)->GetWindowText(deviceName);
	UINT portNum = atoi(agilorPort);

	CString csInfo;
	// connect rtdb server
	int res = DRTDB_RegisterDevice((LPSTR)(LPCSTR)agilorIp, portNum, (LPSTR)(LPCSTR)deviceName);
	if (res == 0) {
		// success
		// GetDlgItem(IDC_EDIT_DEVICENAME)->SetWindowText("");

		// set callback function
		DRTDB_MD_SetCallBackFunction((LPSTR)(LPCSTR)deviceName, OnNewTagNodeArrive, OnRemoveTagNode, OnSetDeviceTagValue, OnGetDeviceTagValue);
		
		// print log
		csInfo.Format("[Info] Register Device Success\r\n");
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);

		// add string to combo box
		((CComboBox *)GetDlgItem(IDC_COMBO_DEVICES))->AddString(deviceName);
		((CComboBox *)GetDlgItem(IDC_COMBO_DEVICES))->SelectString(0, deviceName);
	}
	else {
		// failed, print log
		csInfo.Format("[Error] Register Device Error. Called at line %d, in the %s file.\r\n", __LINE__, __FILE__);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
	}
}
// agilor code: disconnect rtdb server
void CMDModbusDADlg::OnBnClickedButtonDisconnect()
{
	CString csInfo;
	// get value cstring
	CString deviceName;
	((CComboBox *)GetDlgItem(IDC_COMBO_DEVICES))->GetWindowText(deviceName);
	// disconnect rtdv server
	int res = DRTDB_MD_UnregisterDevice((LPSTR)(LPCSTR)deviceName, "停止数据采集", 0);
	if (res == 0) {
		// success, print log
		csInfo.Format("[Info] Unregister Device Success\r\n");
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
		// delete string from combo box
		((CComboBox *)GetDlgItem(IDC_COMBO_DEVICES))->DeleteString(((CComboBox *)GetDlgItem(IDC_COMBO_DEVICES))->FindString(0, deviceName));
		((CComboBox *)GetDlgItem(IDC_COMBO_DEVICES))->SetCurSel(0);
	}
	else {
		// failed, print log
		csInfo.Format("[Error] Unregister Device Error. Called at line %d, in the %s file.\r\n", __LINE__, __FILE__);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
	}
}

void CMDModbusDADlg::OnBnClickedButtonClearLog()
{
	// clear log box
	((CEdit *)GetDlgItem(IDC_EDIT_LOG))->SetWindowText("");
}

// symlink code: status change handler function
afx_msg LRESULT CMDModbusDADlg::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == SYMAPI_STATUS_LOGIN_OK || wParam == SYMAPI_STATUS_LOGIN_FAIL) {
		CString csInfo;
		CString login_username = "Undefined";
		GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(login_username);
		if (wParam == SYMAPI_STATUS_LOGIN_OK)
			csInfo.Format("登录成功，用户：%s\r\n", login_username);
		else
			csInfo.Format("登录失败，原因：%s\r\n", GetErrInfo(m_pLink->GetLastErr()));

		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
	}
	CString csInfo;
	csInfo.Format("[状态变化] %s\r\n", GetStatusInfo((int)wParam));
	::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
	return 0;
}
// symlink code: data change handler function
afx_msg LRESULT CMDModbusDADlg::OnDataChange(WPARAM wParam, LPARAM lParam)
{
	BOOL bWhile = TRUE;
	while (bWhile) {
		int nCount = 100000;
		int *pHandle = new int[nCount];
		SymLinkApiData *pData = new SymLinkApiData[nCount];
		if (m_pLink->GetDbTagChange(pHandle, pData, nCount, -1) == SYMAPI_ERR_OK) {
			for (int i = 0; i < nCount; i++) {
				ShowAppData(pHandle[i], &pData[i], true);
			}
			//获取变化数据
			if (nCount == 0)
				bWhile = FALSE;
		}
		else {
			bWhile = FALSE;
		}
		delete[]pHandle;
		delete[]pData;
	}
	return 0;
}
// symlink code
void CMDModbusDADlg::ShowAppData(int nHandle, SymLinkApiData * pData, bool bRTData /*= true*/)
{
	// Data from device To agilor 

	CString csInfo;
	SymLinkApiString sTagName;
	int nRet = m_pLink->GetDbTagName(nHandle, sTagName);
	if (nRet != 0) {
		// 获取点名失败!
		csInfo.Format("[Error] Get Symlink point name failed. The return code is %d. Called at line %d, in the %s file.\r\n", nRet, __LINE__, __FILE__);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
		return;
	}
	TAG_VALUE_LOCAL target;
	strcpy(target.szTagSource, sTagName.GetStr());
	switch (pData->Type) {
	case 1:
		target.cTagType = 'L';
		target.lValue = pData->GetInt();
		break;
	case 2:
		target.cTagType = 'R';
		target.fValue = pData->GetDouble();
		break;
	case 3:
		target.cTagType = 'S';
		strcpy(target.szValue, pData->GetStr());
		break;
	default:
		csInfo.Format("[Error] Uncatchered data type: %d, Called at line %d, in the %s file.\r\n", pData->Type, __LINE__, __FILE__);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
		return;
	}
	CString deviceName;
	for (int i = 0; i < ((CComboBox *)GetDlgItem(IDC_COMBO_DEVICES))->GetCount(); i++) {
		((CComboBox *)GetDlgItem(IDC_COMBO_DEVICES))->GetLBText(i, deviceName);
		if (DRTDB_MD_SendNewValue((LPSTR)(LPCSTR)deviceName, target, true) == 0) {
			DRTDB_MD_Flush((LPSTR)(LPCSTR)deviceName);
			break;
		}
	}
	/*
	if (strcmp(sTagName.GetStr(), "C1.B1.Tag1") == 0) {
		csInfo.Format("[数据变化] Tag-1-Value：%lf\r\n[数据变化] Type：%s\r\n", pData->GetDouble(), GetDataType(pData->Type));
	} else {
		csInfo.Format("[数据变化] Tag Name:%s\r\nTag Value：%lf\r\n[数据变化] Type：%s\r\n", sTagName.GetStr(), pData->GetDouble(), GetDataType(pData->Type));
	}
	*/
}

// symlink code
CString CMDModbusDADlg::GetErrInfo(int nRet)
{
	CString csRet;
	switch (nRet) {
	case SYMAPI_ERR_OK:
		csRet = "成功";
		break;
	case SYMAPI_ERR_TIMEOUT:
		csRet = "初始化超时";
		break;
	case SYMAPI_ERR_UNCOMPRESS:
		csRet = "数据解压缩失败";
		break;
	case SYMAPI_ERR_VER:
		csRet = "数据库版本变化";
		break;
	case SYMAPI_ERR_CONNECT:
		csRet = "未执行连接操作";
		break;
	case SYMAPI_ERR_INIT:
		csRet = "初始化未完成";
		break;
	case SYMAPI_ERR_FIND:
		csRet = "未找到数据点";
		break;
	case SYMAPI_ERR_PARAM:
		csRet = "参数错误";
		break;
	case SYMAPI_ERR_CMDBUF:
		csRet = "命令队列溢出";
		break;
	case SYMAPI_ERR_CMDTIME:
		csRet = "执行命令超时";
		break;
	case SYMAPI_ERR_CMDERR:
		csRet = "命令返回执行错误";
		break;
	case SYMAPI_ERR_DISABLE:
		csRet = "功能被禁止";
		break;
	case SYMAPI_ERR_LOGIN_FAIL:
		csRet = "用户登录失败";
		break;
	case SYMAPI_ERR_LOGIN_USER:
		csRet = "用户不存在";
		break;
	case SYMAPI_ERR_LOGIN_PASS:
		csRet = "密码错误";
		break;
	case SYMAPI_ERR_LOGIN_INV:
		csRet = "用户被禁止";
		break;
	case SYMAPI_ERR_LOGIN_DIS:
		csRet = "用户被限制登录";
		break;
	case SYMAPI_ERR_LOGIN_RE:
		csRet = "用户已经登录";
		break;
	case SYMAPI_ERR_LOGIN_NULL:
		csRet = "用户失效需要重新登录";
		break;
	case SYMAPI_ERR_LOGIN_VER:
		csRet = "API版本不一致";
		break;
	default:
		csRet = "未知错误";
		break;
	}
	return csRet;
}
// symlink code
CString CMDModbusDADlg::GetStatusInfo(int nStatus)
{
	CString csRet;
	switch (nStatus) {
	case SYMAPI_STATUS_OK:
		csRet = "状态正常";
		break;
	case SYMAPI_STATUS_NOCONNECT:
		csRet = "初始状态";
		break;
	case SYMAPI_STATUS_DISCONNECT:
		csRet = "链路断开";
		break;
	case SYMAPI_STATUS_CONNECTING:
		csRet = "链路连接中...";
		break;
	case SYMAPI_STATUS_CONNECTED:
		csRet = "链路连接成功";
		break;
	case SYMAPI_STATUS_LOGIN:
		csRet = "发送登录命令";
		break;
	case SYMAPI_STATUS_LOGIN_OK:
		csRet = "登录成功";
		break;
	case SYMAPI_STATUS_LOGIN_FAIL:
		csRet = "登录失败";
		break;
	case SYMAPI_STATUS_REQCONFIG:
		csRet = "发送配置命令";
		break;
	case SYMAPI_STATUS_REQCONFIG_OK:
		csRet = "读取配置成功";
		break;
	case SYMAPI_STATUS_REQCONFIG_FAIL:
		csRet = "读取配置失败";
		break;
	case SYMAPI_STATUS_REQALL:
		csRet = "发送总召命令";
		break;
	case SYMAPI_STATUS_REQALL_OK:
		csRet = "总召成功";
		break;
	case SYMAPI_STATUS_REQALL_FAIL:
		csRet = "总召失败";
		break;
	case SYMAPI_STATUS_VER:
		csRet = "数据库版本发生改变";
		break;
	case SYMAPI_STATUS_TX:
		csRet = "有断线缓存数据";
		break;
	default:
		csRet = "未知状态";
		break;
	}
	return csRet;
}
// symlink code
CString CMDModbusDADlg::GetTagType(int nTagType, int nDataType)
{
	switch (nTagType) {
	case 1:
		return "模拟量";
		break;
	case 2:
		return "数字量";
		break;
	case 3:
		return "信号量";
		break;
	case 4:
		return "电能量";
		break;
	case 5:
		return "字符串";
		break;
	case 6:
		return "控制量";
		break;
	case 7:
		return "数据块";
		break;
	case 8:
		return "事件点";
		break;
	case 9:
		return "设备点";
		break;
	case 10:
	{
		CString csInfo;
		csInfo.Format("系统变量(%s)", GetDataType(nDataType));
		return csInfo;
		break;
	}
	case 11:
	case 12:
	case 13:
	{
		CString csInfo;
		csInfo.Format("对象属性(%s)", GetDataType(nDataType));
		return csInfo;
		break;
	}
	}
	return "未知";
}
// symlink code
CString CMDModbusDADlg::GetDataType(int nDataType)
{
	switch (nDataType) {
	case 1:
		return "整型";
	case 2:
		return "实型";
	case 3:
		return "字符串";
	}
	return "未知";
}

// symlink code: connect symlink server
void CMDModbusDADlg::OnBnClickedButtonConnectSymlinkserver()
{
	CString csInfo;

	// get value cstring
	CString symLinkUsername, symLinkPassword, symLinkServerIp, symLinkServerPort;
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(symLinkUsername);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(symLinkPassword);
	GetDlgItem(IDC_IPADDRESS_IP_SYMLINK)->GetWindowText(symLinkServerIp);
	GetDlgItem(IDC_EDIT_PORT_SYMLINK)->GetWindowText(symLinkServerPort);
	UINT symLinkServerPortInt = atoi(symLinkServerPort);

	// check is connected
	CString connStr = symLinkServerIp + ":" + symLinkServerPort + "@" + symLinkUsername;
	if (((CComboBox *)GetDlgItem(IDC_COMBO_SYMLINKSERVERS))->FindString(0, connStr) >= 0) {
		// is connected, print log
		csInfo.Format("[Error] %s is connected，not again.\r\n", connStr);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
		return;
	}
	
	// TODO: only allow one connection client
	((CComboBox *)GetDlgItem(IDC_COMBO_SYMLINKSERVERS))->GetWindowText(connStr);
	if (connStr.IsEmpty() == false) {
		// more than one connection, print log
		csInfo.Format("[Waring] Current connection: %s. Not support connect more than one symlink client.\r\n", connStr);
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
		return;
	}

	// TODO: disconnect previous server connection
	m_pLink->DisConnect();

	// connect symlink server
	if (m_pLink->ConnectServer(symLinkServerIp, symLinkServerPortInt, symLinkUsername, symLinkPassword, 0) == false) {
		// failed, print log
		csInfo.Format("[Error] Connect symlink server failed.\r\n");
		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
		return;
	}

	// success, print log
	csInfo.Format("[Info] Connect symlink server success.\r\n");
	::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);

	// add string to combo box
	connStr = symLinkServerIp + ":" + symLinkServerPort + "@" + symLinkUsername;
	((CComboBox *)GetDlgItem(IDC_COMBO_SYMLINKSERVERS))->AddString(connStr);
	((CComboBox *)GetDlgItem(IDC_COMBO_SYMLINKSERVERS))->SelectString(0, connStr);
}

// symlink code: disconnect symlink server
void CMDModbusDADlg::OnBnClickedButtonDisconnectSymlinkserver()
{
	CString csInfo;
	// disconnect symlink server
	m_pLink->DisConnect();
	// print log
	csInfo.Format("[Info] Disconnect symlink server success.\r\n");
	::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
	// delete string from combo box
	CString connStr;
	((CComboBox *)GetDlgItem(IDC_COMBO_SYMLINKSERVERS))->GetWindowText(connStr);
	((CComboBox *)GetDlgItem(IDC_COMBO_SYMLINKSERVERS))->DeleteString(((CComboBox *)GetDlgItem(IDC_COMBO_SYMLINKSERVERS))->FindString(0, connStr));
	((CComboBox *)GetDlgItem(IDC_COMBO_SYMLINKSERVERS))->SetCurSel(0);
	/*
	// connStr parse out ip, port, username
	((CComboBox *)GetDlgItem(IDC_COMBO_SYMLINKSERVERS))->GetWindowText(connStr);
	CString symLinkUsername, symLinkServerIp;
	UINT symLinkServerPort;
	symLinkServerIp = connStr.Left(connStr.Find(':', 0));
	symLinkServerPort = atoi(connStr.Mid(connStr.Find(':', 0) + 1, connStr.Find('@', 0) - connStr.Find(':', 0) - 1));
	symLinkUsername = connStr.Right(connStr.GetLength() - connStr.Find('@', 0) - 1);
	*/
}


void CMDModbusDADlg::OnEnChangeEditLog()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (((CComboBox *)GetDlgItem(IDC_EDIT_LOG))->GetWindowTextLength() >= 50 * 100) {
		((CComboBox *)GetDlgItem(IDC_EDIT_LOG))->SetWindowText(_T(""));
	}
}

LRESULT CMDModbusDADlg::AppendTextToLogBox(WPARAM wParam, LPARAM lParam)
{
	CString msg = CString(((CString *)lParam)->GetString());
	int nLength = ((CEdit *)GetDlgItem(IDC_EDIT_LOG))->SendMessage(WM_GETTEXTLENGTH);
	((CEdit *)GetDlgItem(IDC_EDIT_LOG))->SetSel(nLength, nLength);
	((CEdit *)GetDlgItem(IDC_EDIT_LOG))->ReplaceSel(msg);
	return 0;
}
