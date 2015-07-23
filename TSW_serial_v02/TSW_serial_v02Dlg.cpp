
// TSW_serial_v02Dlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CTSW_serial_v02Dlg ��ȭ ����



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


// CTSW_serial_v02Dlg �޽��� ó����

BOOL CTSW_serial_v02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// �޺��ڽ��� ����Ʈ�� �߰�
	m_combo_comport_list.AddString(_T("COM1"));
	m_combo_comport_list.AddString(_T("COM2"));
	m_combo_comport_list.AddString(_T("COM3"));
	m_combo_comport_list.AddString(_T("COM4"));

	m_combo_baudrate_list.AddString(_T("9600"));
	m_combo_baudrate_list.AddString(_T("19200"));
	m_combo_baudrate_list.AddString(_T("38400"));
	m_combo_baudrate_list.AddString(_T("115200"));

	//�ʱ� ����
	comport_state = false;
	GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
	m_str_comport = _T("COM3");
	m_str_baudrate = _T("38400");
	UpdateData(FALSE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTSW_serial_v02Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CTSW_serial_v02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CTSW_serial_v02Dlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	//overlapped i/o �ڵ����ݴ´�.
	((CMycomm*)lpara)->HandleClose();
	delete ((CMycomm*)lpara);

	return 0;
}

char* CTSW_serial_v02Dlg::Hex2String(char* toconv)
{
	
	return toconv;
}

//�޴°�
LRESULT CTSW_serial_v02Dlg::OnReceive(WPARAM length, LPARAM lpara)
{
	//UpdateData(TRUE);//�޴� ������ Ÿ���� �˱� ����
	CString str, temp;
	byte data[5000];
	//int iSize = m_comm->Receive(data, length); //��Ʈ�� ���� ������ ����

	if (m_comm)
	{
		m_comm->Receive(data, length); //length ���̸�ŭ�����͸��޴´�.
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

		m_edit_rcv_view.ReplaceSel(str); //����Ʈ�ڽ���ǥ���ϱ�����
		str = "";
		//UpdateData(FALSE);
		m_edit_rcv_view.LineScroll(m_edit_rcv_view.GetLineCount());
	}
	return 0;
}

//OPEN ��ư Ŭ���� ��� ����
void CTSW_serial_v02Dlg::OnBnClickedBtConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (comport_state)
	{
		if (m_comm)        //����Ʈ�������ϸ�
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("COM ��Ʈ����"));
			comport_state = false;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
			GetDlgItem(IDC_BT_SEND)->EnableWindow(false);
		}
	}
	else
	{
		m_comm = new CMycomm(_T("\\\\.\\") + m_str_comport, m_str_baudrate, _T("None"), _T("8 Bit"), _T("1 Bit"));         // initial Comm port
		if (m_comm->Create(GetSafeHwnd()) != 0) //�����Ʈ���������������ڵ����ѱ��.
		{
			AfxMessageBox(_T("COM ��Ʈ����"));
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


//COM port �޺��ڽ� ����� ����
void CTSW_serial_v02Dlg::OnCbnSelchangeComboComport()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(); //��Ʈ�� ������ ���� ���� �����ϴ� ������ �Ѵ�.
}

//Baud rate �޺��ڽ� ����� ����
void CTSW_serial_v02Dlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(); //��Ʈ�� ������ ���� ���� �����ϴ� ������ �Ѵ�.
}

//Clear ��ư Ŭ���� ����
void CTSW_serial_v02Dlg::OnBnClickedBtClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItem(IDC_EDIT_RCV_VIEW)->SetWindowText(_T(" ")); //����Ʈ�ڽ� ȭ���� �������� �ٲ�
}

//Send ��ư Ŭ���� ����
void CTSW_serial_v02Dlg::OnBnClickedBtSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str, set;

	/////////////////////////////////////////////////////////////////////////////////////////////
	//DB TEST
	/////////////////////////////////////////////////////////////////////////////////////////////
	//PGconn * conn; // �����ͺ��̽� ���� ��Ʈ��Ʈ ����ü ������
	//PGresult* res; // ���� ����� ������ ����ü ������
	/*
	char *pghost, *pgport, *pgoptions, *pgtty;
	char *dbName;
	int nFields; /* �ʵ��� ������ ������ ���� 
	int i, j;

	pghost = NULL;    /* ������ ȣ��Ʈ �̸� 
	pgport = NULL;    /* ���� ��Ʈ 
	pgoptions = NULL;    /* ������ ������ Ư���� �ɼ� 
	pgtty = NULL;    /* ������ ���� ����� tty 
	dbName = "template1";    /* ������ �ӽ� �����ͺ��̽� 

	/* �����ͺ��̽��� ������ �õ��Ѵ�. 
	conn = PQsetdb(pghost, pgport, pgoptions, pgtty, dbName);

	/* �������� ������ ���������� �̷�������� �˻��Ѵ�.
	* ���� �����Ͽ��ٸ� ���� �޽����� ����ϰ� �����Ѵ�. 
	if (PQstatus(conn) == CONNECTION_BAD)
	{
		fprintf(stderr, "Connection to database '��s' failed.��n", dbName);
		fprintf(stderr, "��s", PQerrorMessage(conn));
		//exit_nicely(conn);
	}
	////////////////////////////////////////////////////////////////////////////////////////////*/


	//Edit text�� �Էµ� ���ڸ� str�� ����
	GetDlgItem(IDC_EDIT_SEND_DATA)->GetWindowText(str);

	///////////////////////////////////////////////////////////////////////////////////////////
	//�������ݿ� ��� �Ǿ��ִ� ���۰� ���κ��� ������ ���� : ������ �����ؾ� �ش� ���ڷ� �Էµ�
	// ����  :  ����
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

	//���ڰ����� �����ֱ� ������ ASCII ���ڿ� �ش��ϴ� �κ��� ���� send�� ������ ��
	set = start + str + ETX + LF;
	m_comm->Send(set, set.GetLength());
}
