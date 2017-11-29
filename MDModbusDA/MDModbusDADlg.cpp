
// MDModbusDADlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MDModbusDA.h"
#include "MDModbusDADlg.h"
#include "afxdialogex.h"

//#include "DeviceRtdbAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMDModbusDADlg �Ի���



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


// CMDModbusDADlg ��Ϣ�������

BOOL CMDModbusDADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMDModbusDADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	int res = DRTDB_MD_UnregisterDevice((LPSTR)(LPCSTR)deviceName, "ֹͣ���ݲɼ�", 0);
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
			csInfo.Format("��¼�ɹ����û���%s\r\n", login_username);
		else
			csInfo.Format("��¼ʧ�ܣ�ԭ��%s\r\n", GetErrInfo(m_pLink->GetLastErr()));

		::SendMessage(::FindWindow(NULL, "MDModbusDA"), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&csInfo);
	}
	CString csInfo;
	csInfo.Format("[״̬�仯] %s\r\n", GetStatusInfo((int)wParam));
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
			//��ȡ�仯����
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
		// ��ȡ����ʧ��!
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
		csInfo.Format("[���ݱ仯] Tag-1-Value��%lf\r\n[���ݱ仯] Type��%s\r\n", pData->GetDouble(), GetDataType(pData->Type));
	} else {
		csInfo.Format("[���ݱ仯] Tag Name:%s\r\nTag Value��%lf\r\n[���ݱ仯] Type��%s\r\n", sTagName.GetStr(), pData->GetDouble(), GetDataType(pData->Type));
	}
	*/
}

// symlink code
CString CMDModbusDADlg::GetErrInfo(int nRet)
{
	CString csRet;
	switch (nRet) {
	case SYMAPI_ERR_OK:
		csRet = "�ɹ�";
		break;
	case SYMAPI_ERR_TIMEOUT:
		csRet = "��ʼ����ʱ";
		break;
	case SYMAPI_ERR_UNCOMPRESS:
		csRet = "���ݽ�ѹ��ʧ��";
		break;
	case SYMAPI_ERR_VER:
		csRet = "���ݿ�汾�仯";
		break;
	case SYMAPI_ERR_CONNECT:
		csRet = "δִ�����Ӳ���";
		break;
	case SYMAPI_ERR_INIT:
		csRet = "��ʼ��δ���";
		break;
	case SYMAPI_ERR_FIND:
		csRet = "δ�ҵ����ݵ�";
		break;
	case SYMAPI_ERR_PARAM:
		csRet = "��������";
		break;
	case SYMAPI_ERR_CMDBUF:
		csRet = "����������";
		break;
	case SYMAPI_ERR_CMDTIME:
		csRet = "ִ�����ʱ";
		break;
	case SYMAPI_ERR_CMDERR:
		csRet = "�����ִ�д���";
		break;
	case SYMAPI_ERR_DISABLE:
		csRet = "���ܱ���ֹ";
		break;
	case SYMAPI_ERR_LOGIN_FAIL:
		csRet = "�û���¼ʧ��";
		break;
	case SYMAPI_ERR_LOGIN_USER:
		csRet = "�û�������";
		break;
	case SYMAPI_ERR_LOGIN_PASS:
		csRet = "�������";
		break;
	case SYMAPI_ERR_LOGIN_INV:
		csRet = "�û�����ֹ";
		break;
	case SYMAPI_ERR_LOGIN_DIS:
		csRet = "�û������Ƶ�¼";
		break;
	case SYMAPI_ERR_LOGIN_RE:
		csRet = "�û��Ѿ���¼";
		break;
	case SYMAPI_ERR_LOGIN_NULL:
		csRet = "�û�ʧЧ��Ҫ���µ�¼";
		break;
	case SYMAPI_ERR_LOGIN_VER:
		csRet = "API�汾��һ��";
		break;
	default:
		csRet = "δ֪����";
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
		csRet = "״̬����";
		break;
	case SYMAPI_STATUS_NOCONNECT:
		csRet = "��ʼ״̬";
		break;
	case SYMAPI_STATUS_DISCONNECT:
		csRet = "��·�Ͽ�";
		break;
	case SYMAPI_STATUS_CONNECTING:
		csRet = "��·������...";
		break;
	case SYMAPI_STATUS_CONNECTED:
		csRet = "��·���ӳɹ�";
		break;
	case SYMAPI_STATUS_LOGIN:
		csRet = "���͵�¼����";
		break;
	case SYMAPI_STATUS_LOGIN_OK:
		csRet = "��¼�ɹ�";
		break;
	case SYMAPI_STATUS_LOGIN_FAIL:
		csRet = "��¼ʧ��";
		break;
	case SYMAPI_STATUS_REQCONFIG:
		csRet = "������������";
		break;
	case SYMAPI_STATUS_REQCONFIG_OK:
		csRet = "��ȡ���óɹ�";
		break;
	case SYMAPI_STATUS_REQCONFIG_FAIL:
		csRet = "��ȡ����ʧ��";
		break;
	case SYMAPI_STATUS_REQALL:
		csRet = "������������";
		break;
	case SYMAPI_STATUS_REQALL_OK:
		csRet = "���ٳɹ�";
		break;
	case SYMAPI_STATUS_REQALL_FAIL:
		csRet = "����ʧ��";
		break;
	case SYMAPI_STATUS_VER:
		csRet = "���ݿ�汾�����ı�";
		break;
	case SYMAPI_STATUS_TX:
		csRet = "�ж��߻�������";
		break;
	default:
		csRet = "δ֪״̬";
		break;
	}
	return csRet;
}
// symlink code
CString CMDModbusDADlg::GetTagType(int nTagType, int nDataType)
{
	switch (nTagType) {
	case 1:
		return "ģ����";
		break;
	case 2:
		return "������";
		break;
	case 3:
		return "�ź���";
		break;
	case 4:
		return "������";
		break;
	case 5:
		return "�ַ���";
		break;
	case 6:
		return "������";
		break;
	case 7:
		return "���ݿ�";
		break;
	case 8:
		return "�¼���";
		break;
	case 9:
		return "�豸��";
		break;
	case 10:
	{
		CString csInfo;
		csInfo.Format("ϵͳ����(%s)", GetDataType(nDataType));
		return csInfo;
		break;
	}
	case 11:
	case 12:
	case 13:
	{
		CString csInfo;
		csInfo.Format("��������(%s)", GetDataType(nDataType));
		return csInfo;
		break;
	}
	}
	return "δ֪";
}
// symlink code
CString CMDModbusDADlg::GetDataType(int nDataType)
{
	switch (nDataType) {
	case 1:
		return "����";
	case 2:
		return "ʵ��";
	case 3:
		return "�ַ���";
	}
	return "δ֪";
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
		csInfo.Format("[Error] %s is connected��not again.\r\n", connStr);
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
