#pragma once
#include "afxwin.h"

#include "..\\..\\..\\include\\secs.h"

#define CMainClassName Csecs_DemoEquipmentDlg

#pragma warning  ( disable : 4996)

class Csecs_DemoEquipmentDlg : public CDialog, 
	public CEquipmentTCP 
{
// 构造
public:
	Csecs_DemoEquipmentDlg(CWnd* pParent = NULL);	// 标准构造函数

	enum { IDD = IDD_SECS_DEMOEQUIPMENT_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnS1f1();
	afx_msg void OnBnClickedBtnS1f3();
	afx_msg void OnBnClickedBtnS1f11();
	afx_msg void OnBnClickedBtnS1f13();
	afx_msg void OnBnClickedBtnS2f17();
	afx_msg void OnBnClickedBtnS5f1clear();
	afx_msg void OnBnClickedBtnS7f1();
	afx_msg void OnBnClickedBtnS7f3();
	afx_msg void OnBnClickedBtnS7f5();
	afx_msg void OnBnClickedBtnS12f3();
	afx_msg void OnBnClickedBtnS12f15();
	afx_msg void OnBnClickedBtnS12f1();
	afx_msg void OnBnClickedBtnS12f9();
	afx_msg void OnBnClickedBtnS14f1();
	afx_msg void OnBnClickedBtnS6f11();
	afx_msg void OnBnClickedBtnS6f1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnS5f1();
	afx_msg void OnBnClickedButtonClearList();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonlinktestreq();
	afx_msg void OnBnClickedButtonLinktestrsp();
	afx_msg void OnBnClickedButtonSelectrsp();
	afx_msg void OnBnClickedButtonDeselectrsp();
	
	DECLARE_MESSAGE_MAP()
private:

	//添加加日志到编辑框显示
	void AppendLog(CString text, bool bAdd2Edit = false);

	//添加到列表里面显示，添加到日志
	void Append(HSMSHeader *pHdr, bool SendRecv);

public:
	CListBox m_list;
	CStatic m_panel;
	CEdit m_edit_log;

	// --------------------------  分割线 ----------------------------------
private:
	// ------------ 以下这部分为 SECS 相关，可以整体复制到你自己项目里面使用 ---------------
	// 同时将本示例中的这3个文件 secs_Standard.cpp，secs_UserDef.cpp,secs_Logs.cpp
	// 可以直接剪切到你的工程里面使用

	void InitSecs();
	void UnInitSecs();

	int S2F21(HSMSHeader *pHdr, HCOMM hComm);
	int S2F41(HSMSHeader *pHdr, HCOMM hComm);
	int S10F3(HSMSHeader *pHdr, HCOMM hComm);

	//TRACE 消息
	LRESULT OnS6f1TraceData(WPARAM w, LPARAM l);

	//wParam = 1 报警触发，0=报警清除
	//lParam = ALID 报警ID;
	LRESULT OnAlarmReport(WPARAM w, LPARAM l);
private:
	// ------ UserDefined ------
	int SnFn_UserDef(HSMSHeader *pHdr, HCOMM hComm);
	int S1F65(HSMSHeader *pHdr, HCOMM hComm);
	int S1F69(HSMSHeader *pHdr, HCOMM hComm);
	
private:
	int data_message_proc(HSMSHeader *pHdr, HCOMM hComm);
	int Select_req_proc(HSMSHeader *pHdr, HCOMM hComm);
	int Select_rsp_proc(HSMSHeader *pHdr, HCOMM hComm);
	int Deselect_req_proc(HSMSHeader *pHdr, HCOMM hComm);
	int Deselect_rsp_proc(HSMSHeader *pHdr, HCOMM hComm);
	int Linktest_req_proc(HSMSHeader *pHdr, HCOMM hComm);
	int Linktest_rsp_proc(HSMSHeader *pHdr, HCOMM hComm);
	int Reject_req_proc(HSMSHeader *pHdr, HCOMM hComm);
	int Separate_req_proc(HSMSHeader *pHdr, HCOMM hComm);
	int Send(char *buf, int len, HCOMM hComm);
	void RestartTrace();

	// ------------ 以下这部分为 SECS 打印日志相关  ---------------
private:
	
	void OpenLogFile();
	void CloseLogFile();

	void ParseToLogfile(HSMSHeader *pHdr);
	
	void GenerateLogString(ItemData &item,int blanks);
	void GenerateLogString(ListItemData* entry, eFormatCode fc, int Len,int blanks);

private:
	CString m_SecsLogfile;
	CStdioFile m_logfile;
	bool m_logInit;
	SYSTEMTIME m_stNow;
	SYSTEMTIME m_stOld;
	
};
