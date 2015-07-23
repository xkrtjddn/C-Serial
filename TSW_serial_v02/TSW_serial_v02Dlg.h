
// TSW_serial_v02Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "Mycomm.h"


// CTSW_serial_v02Dlg 대화 상자
class CTSW_serial_v02Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMycomm* m_comm;
	char* Hex2String(char* toconv);
	LRESULT      OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT      OnReceive(WPARAM length, LPARAM lpara);
	CTSW_serial_v02Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TSW_SERIAL_V02_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL comport_state;
	// COM port 콤보박스의 리스트에 들어갈 변수
	CComboBox m_combo_comport_list;
	// Baud rate 콤보박스에 들어갈 변수
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
