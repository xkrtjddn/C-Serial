
// TSW_serial_v02Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TSW_serial_v02.h"
#include "TSW_serial_v02Dlg.h"
#include "afxdialogex.h"
#include <sstream>
//#include "libpq-fe.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTSW_serial_v02Dlg 대화 상자



CTSW_serial_v02Dlg::CTSW_serial_v02Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTSW_serial_v02Dlg::IDD, pParent)
	, m_str_comport(_T(""))
	, m_str_baudrate(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTSW_serial_v02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_combo_comport_list);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate_list);
	DDX_CBString(pDX, IDC_COMBO_COMPORT, m_str_comport);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_str_baudrate);
	DDX_Control(pDX, IDC_EDIT_RCV_VIEW, m_edit_rcv_view);
	DDX_Control(pDX, IDC_EDIT_SEND_DATA, m_edit_send_data);
}

BEGIN_MESSAGE_MAP(CTSW_serial_v02Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_MYCLOSE, &CTSW_serial_v02Dlg::OnThreadClosed)
	ON_MESSAGE(WM_MYRECEIVE, &CTSW_serial_v02Dlg::OnReceive)
	ON_BN_CLICKED(IDC_BT_CONNECT, &CTSW_serial_v02Dlg::OnBnClickedBtConnect)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPORT, &CTSW_serial_v02Dlg::OnCbnSelchangeComboComport)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUDRATE, &CTSW_serial_v02Dlg::OnCbnSelchangeComboBaudrate)
	ON_BN_CLICKED(IDC_BT_CLEAR, &CTSW_serial_v02Dlg::OnBnClickedBtClear)
	ON_BN_CLICKED(IDC_BT_SEND, &CTSW_serial_v02Dlg::OnBnClickedBtSend)
END_MESSAGE_MAP()


// CTSW_serial_v02Dlg 메시지 처리기

BOOL CTSW_serial_v02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 콤보박스에 리스트들 추가
	m_combo_comport_list.AddString(_T("COM1"));
	m_combo_comport_list.AddString(_T("COM2"));
	m_combo_comport_list.AddString(_T("COM3"));
	m_combo_comport_list.AddString(_T("COM4"));

	m_combo_baudrate_list.AddString(_T("9600"));
	m_combo_baudrate_list.AddString(_T("19200"));
	m_combo_baudrate_list.AddString(_T("38400"));
	m_combo_baudrate_list.AddString(_T("115200"));

	//초기 설정
	comport_state = false;
	GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
	m_str_comport = _T("COM3");
	m_str_baudrate = _T("38400");
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTSW_serial_v02Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTSW_serial_v02Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTSW_serial_v02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CTSW_serial_v02Dlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	//overlapped i/o 핸들을닫는다.
	((CMycomm*)lpara)->HandleClose();
	delete ((CMycomm*)lpara);

	return 0;
}

char* CTSW_serial_v02Dlg::Hex2String(char* toconv)
{
	
	return toconv;
}

//받는곳
LRESULT CTSW_serial_v02Dlg::OnReceive(WPARAM length, LPARAM lpara)
{
	//UpdateData(TRUE);//받는 데이터 타입을 알기 위해
	CString str, temp;
	byte data[5000];
	//int iSize = m_comm->Receive(data, length); //포트로 들어온 데이터 갯수

	if (m_comm)
	{
		m_comm->Receive(data, length); //length 길이만큼데이터를받는다.
		data[length] = _T('\0');
		//str += _T("\r\n");
		for (int i = 0; i<length; i++)
		{
			//str += data[i];
			//temp.Format("0x%02X\t", data[i]);
			temp.Format("%02X\t", data[i]);

			str += temp;
			//str.AppendChar(data[i]);
		}

		m_edit_rcv_view.ReplaceSel(str); //에디트박스에표시하기위함
		str = "";
		//UpdateData(FALSE);
		m_edit_rcv_view.LineScroll(m_edit_rcv_view.GetLineCount());
	}
	return 0;
}

//OPEN 버튼 클릭할 경우 실행
void CTSW_serial_v02Dlg::OnBnClickedBtConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (comport_state)
	{
		if (m_comm)        //컴포트가존재하면
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("COM 포트닫힘"));
			comport_state = false;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
			GetDlgItem(IDC_BT_SEND)->EnableWindow(false);
		}
	}
	else
	{
		m_comm = new CMycomm(_T("\\\\.\\") + m_str_comport, m_str_baudrate, _T("None"), _T("8 Bit"), _T("1 Bit"));         // initial Comm port
		if (m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
		{
			AfxMessageBox(_T("COM 포트열림"));
			comport_state = true;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("CLOSE"));
			GetDlgItem(IDC_BT_SEND)->EnableWindow(true);
		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}

	}
}


//COM port 콤보박스 변경시 실행
void CTSW_serial_v02Dlg::OnCbnSelchangeComboComport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(); //컨트롤 변수에 현재 값을 저장하는 역할을 한다.
}

//Baud rate 콤보박스 변경시 실행
void CTSW_serial_v02Dlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(); //컨트롤 변수에 현재 값을 저장하는 역할을 한다.
}

//Clear 버튼 클릭시 실행
void CTSW_serial_v02Dlg::OnBnClickedBtClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_EDIT_RCV_VIEW)->SetWindowText(_T(" ")); //에디트박스 화면을 공백으로 바꿈
}

//Send 버튼 클릭시 실행
void CTSW_serial_v02Dlg::OnBnClickedBtSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str, set;

	/////////////////////////////////////////////////////////////////////////////////////////////
	//DB TEST
	/////////////////////////////////////////////////////////////////////////////////////////////
	//PGconn * conn; // 데이터베이스 접속 디스트럽트 구조체 포인터
	//PGresult* res; // 질의 결과를 저장할 구조체 포인터
	/*
	char *pghost, *pgport, *pgoptions, *pgtty;
	char *dbName;
	int nFields; /* 필드의 갯수를 저장할 변수 
	int i, j;

	pghost = NULL;    /* 서버의 호스트 이름 
	pgport = NULL;    /* 서버 포트 
	pgoptions = NULL;    /* 서버로 전달할 특별한 옵션 
	pgtty = NULL;    /* 서버를 위한 디버깅 tty 
	dbName = "template1";    /* 접속할 임시 데이터베이스 

	/* 데이터베이스로 접속을 시도한다. 
	conn = PQsetdb(pghost, pgport, pgoptions, pgtty, dbName);

	/* 서버와의 접속이 성공적으로 이루어졌는지 검사한다.
	* 만일 실패하였다면 에러 메시지를 출력하고 종료한다. 
	if (PQstatus(conn) == CONNECTION_BAD)
	{
		fprintf(stderr, "Connection to database '＼s' failed.＼n", dbName);
		fprintf(stderr, "＼s", PQerrorMessage(conn));
		//exit_nicely(conn);
	}
	////////////////////////////////////////////////////////////////////////////////////////////*/


	//Edit text에 입력된 문자를 str로 저장
	GetDlgItem(IDC_EDIT_SEND_DATA)->GetWindowText(str);

	///////////////////////////////////////////////////////////////////////////////////////////
	//프로토콜에 명시 되어있는 시작과 끝부분을 변수에 저장 : 정수로 저장해야 해당 문자로 입력됨
	// 정수  :  문자
	// 0     :  NUL
	// 1     :  SOH
	// 2     :  STX
	// 3     :  ETX
	// 10    :  LF
	////////////////////////////////////////////////////////////////////////////////////////////
	char start[4], ETX, LF;
	start[0] = 2;
	start[1] = 1;
	start[2] = 2;
	start[3] = 0;
	ETX = 3;
	LF = 10;
	////////////////////////////////////////////////////////////////////////////////////////////

	//문자값으로 날려주기 때문에 ASCII 문자에 해당하는 부분을 쓰고 send로 날려야 함
	set = start + str + ETX + LF;
	m_comm->Send(set, set.GetLength());
}
