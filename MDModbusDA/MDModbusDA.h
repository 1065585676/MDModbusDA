
// MDModbusDA.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMDModbusDAApp: 
// �йش����ʵ�֣������ MDModbusDA.cpp
//

class CMDModbusDAApp : public CWinApp
{
public:
	CMDModbusDAApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMDModbusDAApp theApp;