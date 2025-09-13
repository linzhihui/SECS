#include "stdafx.h"
#include "secs_DemoEquipment.h"
#include "secs_DemoEquipmentDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Csecs_DemoEquipmentDlg::Csecs_DemoEquipmentDlg(CWnd* pParent )
: CDialog(Csecs_DemoEquipmentDlg::IDD, pParent), 
   CEquipmentTCP(Passive)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csecs_DemoEquipmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_STATIC_SHOWPANEL, m_panel);
	DDX_Control(pDX, IDC_EDIT1, m_edit_log);
}

BEGIN_MESSAGE_MAP(Csecs_DemoEquipmentDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_S1F1, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS1f1)
	ON_BN_CLICKED(IDC_BTN_S1F3, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS1f3)
	ON_BN_CLICKED(IDC_BTN_S1F11, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS1f11)
	ON_BN_CLICKED(IDC_BTN_S1F13, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS1f13)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_S2F17, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS2f17)
	ON_BN_CLICKED(IDC_BTN_S7F1, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS7f1)
	ON_BN_CLICKED(IDC_BTN_S7F3, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS7f3)
	ON_BN_CLICKED(IDC_BTN_S7F5, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS7f5)
	ON_BN_CLICKED(IDC_BTN_S12F3, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS12f3)
	ON_BN_CLICKED(IDC_BTN_S12F15, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS12f15)
	ON_BN_CLICKED(IDC_BTN_S12F1, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS12f1)
	ON_BN_CLICKED(IDC_BTN_S12F9, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS12f9)
	ON_BN_CLICKED(IDC_BTN_S14F1, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS14f1)
	ON_BN_CLICKED(IDC_BTN_S6F11, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS6f11)
	ON_BN_CLICKED(IDC_BTN_S6F1, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS6f1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_S5F1, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS5f1)

	ON_BN_CLICKED(IDC_BTN_S6F11Clear, &Csecs_DemoEquipmentDlg::OnBnClickedBtnS5f1clear)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_LIST, &Csecs_DemoEquipmentDlg::OnBnClickedButtonClearList)
	ON_BN_CLICKED(IDC_BUTTON_linktest_req, &Csecs_DemoEquipmentDlg::OnBnClickedButtonlinktestreq)
	ON_BN_CLICKED(IDC_BUTTON_Linktest_rsp, &Csecs_DemoEquipmentDlg::OnBnClickedButtonLinktestrsp)
	ON_BN_CLICKED(IDC_BUTTON_Select_rsp, &Csecs_DemoEquipmentDlg::OnBnClickedButtonSelectrsp)
	ON_BN_CLICKED(IDC_BUTTON_Deselect_rsp, &Csecs_DemoEquipmentDlg::OnBnClickedButtonDeselectrsp)


	//两个SECS相关的消息 TRACE ,Alarm
	ON_MESSAGE(WM_S6F1_TRACEDATA, &Csecs_DemoEquipmentDlg::OnS6f1TraceData)
	ON_MESSAGE(WM_S5F1_ALARMREPORT, &Csecs_DemoEquipmentDlg::OnAlarmReport)

END_MESSAGE_MAP()


BOOL Csecs_DemoEquipmentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	::CreateDirectory(_T(".\\INI"), NULL);

	InitSecs();
	OpenLogFile();

	SetIcon(m_hIcon, TRUE);		
	SetIcon(m_hIcon, FALSE);

	CString text = _T("MES_SECS_EQP模拟端-设备端-Passive模式");
	SetWindowText(text);
	return TRUE;  
}


void Csecs_DemoEquipmentDlg::OnClose()
{
	UnInitSecs();
	CloseLogFile();

	CDialog::OnClose();
}


void Csecs_DemoEquipmentDlg::OnTimer(UINT_PTR nIDEvent)
{
	S6F1TraceData(nIDEvent);

	CDialog::OnTimer(nIDEvent);
}

void Csecs_DemoEquipmentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

HCURSOR Csecs_DemoEquipmentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Send S1F1
void Csecs_DemoEquipmentDlg::OnBnClickedBtnS1f1()
{
	HSMSHeader head = {0};
	get_header_of_Data_message_primary(head, true,	1, 1);
	if (m_Mode == Active)
		Send((char*)&head, sizeof(head), m_hComm);
}

//Send S1F3
void Csecs_DemoEquipmentDlg::OnBnClickedBtnS1f3()
{
	HSMSHeader head = {0};
	get_header_of_Data_message_primary(head, true,	1, 3);
	if (m_Mode == Active)
		Send((char*)&head, sizeof(head), m_hComm);
}

//Send S1F11
void Csecs_DemoEquipmentDlg::OnBnClickedBtnS1f11()
{
	HSMSHeader head = {0};
	get_header_of_Data_message_primary(head, true,	1, 11);
	if (m_Mode == Active)
		Send((char*)&head, sizeof(head), m_hComm);
}

//Send S1F13
void Csecs_DemoEquipmentDlg::OnBnClickedBtnS1f13()
{
	
	char MDLN[32] = {0};
	char SOFTREV[32] = {0};
	char *sendbuf = NULL;
	int outbuflen = 0;
	DWORD dwRet = 0;

	BYTE COMMACK = 0;//0=Accepted,1=Denied.Try Again.

	SenderBuffer sender(this);
	HSMSHeader header= {0};


	strcpy(MDLN, "MDLN");
	strcpy(SOFTREV, "v2.0.1.9");

	sender.Begin();

	get_header_of_Data_message_primary(header, true, 1, 13);

	sender.Add_HSMSHeader(&header);
	sender.Add_LIST_Header(2);

	sender.BeginList();

	sender.Add_ITEM_Header(ASCII,  strlen(MDLN));
	sender.Add_ASCII(MDLN,  strlen(MDLN));

	sender.Add_ITEM_Header(ASCII,  strlen(SOFTREV));
	sender.Add_ASCII(SOFTREV,  strlen(SOFTREV));

	sender.EndList();

	sender.End();

	int outlen = 0;
	char *buf = sender.getSendBuffer(outlen);
	Send(buf, outlen, m_hComm);
}


//Datetime request, Equipment->Host
void Csecs_DemoEquipmentDlg::OnBnClickedBtnS2f17()
{
	HSMSHeader header = {0};
	get_header_of_Data_message_primary(header, true, 2, 17);
	Send((char*)&header, sizeof(header), m_hComm);
}

void Csecs_DemoEquipmentDlg::OnBnClickedBtnS7f1()
{
	char PPID[64] = {0};
	unsigned short LENGTH = 16;


	strcpy(PPID, "secs_ppid");
	

	SenderBuffer sender(this);
	HSMSHeader header = {0};

	get_header_of_Data_message_primary(header, true, 7, 1);

	sender.Begin();
	sender.Add_HSMSHeader(&header);
	sender.Add_LIST_Header(2);

	sender.Add_ITEM_Header(ASCII, strlen(PPID));
	sender.Add_ASCII(PPID,  strlen(PPID));

	sender.Add_ITEM_Header(UINT_2B, UINT_2B_LEN);
	sender.Add_UINT_2B(LENGTH);

	sender.End();

	int outlen = 0;
	char *buf = sender.getSendBuffer(outlen);
	Send(buf, outlen, m_hComm);

}

void Csecs_DemoEquipmentDlg::OnBnClickedBtnS7f3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Csecs_DemoEquipmentDlg::OnBnClickedBtnS7f5()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Csecs_DemoEquipmentDlg::OnBnClickedBtnS12f3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Csecs_DemoEquipmentDlg::OnBnClickedBtnS12f15()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Csecs_DemoEquipmentDlg::OnBnClickedBtnS12f1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Csecs_DemoEquipmentDlg::OnBnClickedBtnS12f9()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Csecs_DemoEquipmentDlg::OnBnClickedBtnS14f1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Csecs_DemoEquipmentDlg::OnBnClickedBtnS6f1()
{
	AfxMessageBox(_T("HOST端发送S2F23定义好的TRID与关联的SVID列表以及采样周期等信息后，自动周期性上报"));
	return ;

	//TEST 
	SenderBuffer sender(this);
	HSMSHeader header;
	
	sender.Begin();

	get_header_of_Data_message_primary(header,true, 6, 1);

	sender.Add_HSMSHeader(&header);

	sender.Add_LIST_Header(4);

	sender.BeginList();

	sender.Add_ITEM_Header(UINT_2B,UINT_2B_LEN);
	sender.Add_UINT_2B(0);

	sender.Add_ITEM_Header(UINT_2B,UINT_2B_LEN);
	sender.Add_UINT_2B(0);

	SYSTEMTIME st;
	GetLocalTime(&st);
	char buf[32] = {0};
	sprintf(buf, "%02d%02d%02d%02d%02d%02d",
		(st.wYear%100), st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	sender.Add_ITEM_Header(ASCII, strlen(buf));
	sender.Add_ASCII(buf);

	sender.Add_LIST_Header(1);
	sender.BeginList();
	sender.Add_ITEM_Header(ASCII,1);
	sender.Add_ASCII("",0);
	sender.EndList();

	sender.EndList();
	sender.End();

	int outlen = 0;
	char *pbuf = sender.getSendBuffer(outlen);
	Send(pbuf, outlen, m_hComm);
}


void Csecs_DemoEquipmentDlg::OnBnClickedBtnS6f11()
{
	int nCEID = 1;
	S6F11EventReport(nCEID);
}



HBRUSH Csecs_DemoEquipmentDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);
	int id = pWnd->GetDlgCtrlID();
	if (IDC_STATIC_SHOWPANEL == id)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	return hbr;
}

void Csecs_DemoEquipmentDlg::OnBnClickedBtnS5f1()
{
	int AlarmCnt = GetALIDCount();
	for (int i = 0; i < AlarmCnt; i++)
	{
		ALID *p = GetALID(1000 + i);
		if (p)
		{
			S5F1AlarmReport(true, p->ALID);
		}
	
	}
}


void Csecs_DemoEquipmentDlg::OnBnClickedBtnS5f1clear()
{
	ALID *p = GetALID(1002);
	if (p)
	{
		S5F1AlarmReport(false, p->ALID);
	}

}

void Csecs_DemoEquipmentDlg::OnBnClickedButtonClearList()
{
	m_list.ResetContent();
	m_edit_log.SetWindowText(_T(""));
}

void Csecs_DemoEquipmentDlg::OnBnClickedButtonlinktestreq()
{
	HSMSHeader header = {0};
	get_header_of_Linktest_req(header);
	Send((char*)&header, sizeof(header),  m_hComm);
}

void Csecs_DemoEquipmentDlg::OnBnClickedButtonLinktestrsp()
{
	HSMSHeader header = {0};
	get_header_of_Linktest_rsp(header);
	Send((char*)&header, sizeof(header),  m_hComm);
}

void Csecs_DemoEquipmentDlg::OnBnClickedButtonSelectrsp()
{

}

void Csecs_DemoEquipmentDlg::OnBnClickedButtonDeselectrsp()
{

}

void Csecs_DemoEquipmentDlg::AppendLog(CString logA, bool bAdd2Edit)
{
	CCriticalSection cs;
	CSingleLock lock(&cs);

	//USES_CONVERSION;
	CString log(logA);
	lock.Lock();
	if (m_logInit)
	{
		m_logfile.WriteString(log);
		m_logfile.WriteString(_T("\r\n"));
		m_logfile.Flush();

		if (bAdd2Edit)
		{
			log += _T("\r\n");
			int length = m_edit_log.GetWindowTextLength();
			m_edit_log.SetSel(length, length);
			m_edit_log.ReplaceSel(log);
		}

		::GetLocalTime(&m_stNow);
		if (m_stNow.wHour != m_stOld.wHour)
		{
			CloseLogFile();
			OpenLogFile();
		}
	}
	lock.Unlock();
}

//添加到列表里面显示，添加到日志
//与界面相关的处理
void Csecs_DemoEquipmentDlg::Append(HSMSHeader *pHdr,
	bool SendRecv)
{
	CCriticalSection cs;
	CSingleLock lock(&cs);
	lock.Lock();
	CHsmsHdrTool tool;
	int len = tool.GetBodyLength(*pHdr);
	BYTE *p = (BYTE*)pHdr;
	p += 4;
	CStringA str, text, logstr;
	int k = 0;

	text.Format("%s", SendRecv ? "Send:" : "Recv:");
	logstr = text;

	///USES_CONVERSION;
	for (int i = 0; i < len; i++)
	{
		str.Format("%02x", *p);
		p++;  k++;
		text += str;		text += " ";
		if (k == 16)		{ k = 0;	m_list.AddString(text); text.Empty(); }
		str.Empty();
	}

	SYSTEMTIME st;
	::GetLocalTime(&st);

	char *comments[] =
	{
		"Data_message",
		"Select_req",
		"Select_rsp",
		"Deselect_req",
		"Deselect_rsp",
		"Linktest_req",
		"Linktest_rsp",
		"Reject_req",
		"Not_used",
		"Separate_req",
	};

	bool bDataMsg = false;

	bool bLegal = (pHdr->SType >= 0 && pHdr->SType <= 9);
	if (false == bLegal)
	{
		goto lExit;
	}

	if (Data_message == pHdr->SType)
	{
		bDataMsg = true;
		UINT Sn = getStreamNum(*pHdr);
		UINT Fn = getFunctionNum(*pHdr);
		bool W = getReplyFlag(*pHdr);
		if (W)
			str.Format(" =%dbytes  [S%dF%dW] , {%02d:%02d:%02d:%03dms}", len, Sn, Fn, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		else
			str.Format(" =%dbytes  [S%dF%d] , {%02d:%02d:%02d:%03dms}", len, Sn, Fn, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	}
	else
	{
		str.Format(" =%dbytes [%s] , {%02d:%02d:%02d:%03dms}", len, comments[pHdr->SType], st.wHour, st.wMinute,
			st.wSecond, st.wMilliseconds);
	}
	text += str;
	m_list.AddString(text);

	logstr += str;
	AppendLog(logstr, bDataMsg);

	ParseToLogfile(pHdr);

	int nCount = m_list.GetCount();
	m_list.SetTopIndex(nCount - 1);

	if (nCount > 100)
	{
		OnBnClickedButtonClearList();
	}
lExit:
	lock.Unlock();
}