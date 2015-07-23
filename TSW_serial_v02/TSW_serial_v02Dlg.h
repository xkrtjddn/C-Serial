
// TSW_serial_v02Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "Mycomm.h"


// CTSW_serial_v02Dlg ��ȭ ����
class CTSW_serial_v02Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMycomm* m_comm;
	char* Hex2String(char* toconv);
	LRESULT      OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT      OnReceive(WPARAM length, LPARAM lpara);
	CTSW_serial_v02Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TSW_SERIAL_V02_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL comport_state;
	// COM port �޺��ڽ��� ����Ʈ�� �� ����
	CComboBox m_combo_comport_list;
	// Baud rate �޺��ڽ��� �� ����
	CComboBox m_combo_baudrate_list;
	CString m_str_comport;
	CString m_str_baudrate;
	CEdit m_edit_rcv_view;
	CEdit m_edit_send_data;
	afx_msg void OnBnClickedBtConnect();
	afx_msg void OnCbnSelchangeComboComport();
	afx_msg void OnCbnSelchangeComboBaudrate();
	afx_msg void OnBnClickedBtClear();
	afx_msg void OnBnClickedBtSend();
};
