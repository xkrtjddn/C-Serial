
// TSW_serial_v02.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTSW_serial_v02App:
// �� Ŭ������ ������ ���ؼ��� TSW_serial_v02.cpp�� �����Ͻʽÿ�.
//

class CTSW_serial_v02App : public CWinApp
{
public:
	CTSW_serial_v02App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTSW_serial_v02App theApp;