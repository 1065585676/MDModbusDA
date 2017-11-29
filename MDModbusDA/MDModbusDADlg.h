
// MDModbusDADlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include <unordered_map>

#include "DeviceRtdbAPI.h"
#include "SymLinkApi.h"

#define WM_STATUS_CHANGE		WM_USER+1010
#define WM_DATA_CHANGE			WM_USER+1011
#define WM_SLEVENT_CHANGE		WM_USER+1012
#define WM_TXSAVE_CHANGE		WM_USER+1013

#define WM_YYMSG_APPEND_LOGBOX	WM_USER+2017


static CSymLinkApi* m_pLink = nullptr;

// CMDModbusDADlg �Ի���
class CMDModbusDADlg : public CDialogEx
{
// ����
public:
	CMDModbusDADlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MDMODBUSDA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	static void apiStatusChange(void * v1, void * v2, int nStatus);
	static void apiDataChange(void * v1, void * v2, int nCount, int * pChange);
	static void apiSLEventChange(void * v1, void * v2, int nCount);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonClearLog();
	//CSymLinkApi* m_pLink;
protected:
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	CString GetErrInfo(int nRet);
	CString GetStatusInfo(int nStatus);
	CString GetTagType(int nTagType, int nDataType);
	CString GetDataType(int nDataType);
	afx_msg LRESULT OnDataChange(WPARAM wParam, LPARAM lParam);
	void ShowAppData(int nHandle, SymLinkApiData * pData, bool bRTData);
public:
	afx_msg void OnBnClickedButtonConnectSymlinkserver();
	afx_msg void OnBnClickedButtonDisconnectSymlinkserver();
	afx_msg void OnEnChangeEditLog();

	afx_msg LRESULT AppendTextToLogBox(WPARAM wParam, LPARAM lParam);
};

