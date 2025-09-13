#include "stdafx.h"
#include "secs_DemoEquipment.h"
#include "secs_DemoEquipmentDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* --------------------------------------------------

本示例中的这3个文件
   secs_Standard.cpp
   secs_UserDef.cpp
   secs_Logs.cpp
可以直接剪切到你的工程里面使用

记得把 CMainClassName宏修改成你的主窗类名即可

----------------------------------------------------*/

#pragma comment(lib, "..\\..\\..\\DLL_lib\\vs2012\\32\\secs.lib")


void CMainClassName::InitSecs()
{
	SetSecsWnd(m_hWnd);
	Start();
	RestartTrace();
}

void CMainClassName::UnInitSecs()
{
	int TRIDCnt = GetTRIDCount();
	for (int i = 0; i < TRIDCnt; i++)
	{
		TRID *p = GetTRIDByIndex(i);
		if (p)
			KillTimer(p->TRID);
	}

	HSMSHeader head = { 0 };
	get_header_of_Deselect_req(head);
	if (m_Mode == Active)
		Send((char*)&head, sizeof(head), m_hComm);

	get_header_of_Separate_req(head);
	Send((char*)&head, sizeof(head), m_hComm);

	Stop();
}


//----------------- Standard ---------------


// Remote Command
//S2F21/F22,F41/F42, CMDA,HCAK (host command acknowlege code)
//     0 = Acknowlege, command has been performed
//     1 = Command does not exist
//     2 = Cannot perform now
//     3 = At least one parameter is invalid
//     4 = Acknowlege, command will be performed with completion signaled later.
//     5 = Rejected,already in a desired condition.
//     6 = No such object exists.
//    >=7 reserved.

int CMainClassName::S2F21(HSMSHeader *pHdr, HCOMM hComm)
{
	ItemData item;
	BYTE CMDA = 0;
	SenderBuffer sender(this);
	HSMSHeader header = (*pHdr);
	bool bRet = GetDataType(pHdr, item);
	bool bFindCmd = false;
	CStringA cmdstr;

	if (bRet && item.format == ASCII)
	{
		char *pdata = (char *)malloc(item.len + 1);
		ZeroMemory(pdata, item.len + 1);
		memcpy(pdata, item.data, item.len);
		CStringA data(pdata);

		data.Trim();	data.MakeUpper();

		if (bRet) cmdstr = "S2F21\n";

		if (-1 != data.Find("START"))
		{
			bFindCmd = true;
			//PostMessage(hWnd, WM_START, 0, 0);
			cmdstr += "Remote CMD: START\n";
		}
		else if (-1 != data.Find("STOP"))
		{
			bFindCmd = true;
			//PostMessage(hWnd, WM_STOP, 0, 0);
			cmdstr += "Remote CMD: STOP\n";
		}
	}

	sender.Begin();
	get_header_of_Data_message_reply(header);
	sender.Add_HSMSHeader(&header);

	sender.Add_ITEM_Header(BINARY, 1);
	bFindCmd ? CMDA = 0 : CMDA = 6;
	sender.Add_BINARY(CMDA);

	sender.End();

	int outlen = 0;
	char *buf = sender.getSendBuffer(outlen);
	Send(buf, outlen, hComm);
	//USES_CONVERSION;
	m_panel.SetWindowText(cmdstr);
	return 0;
}

int CMainClassName::S2F41(HSMSHeader *pHdr, HCOMM hComm)
{
	ItemData item;
	BYTE HCAK = 0;
	SenderBuffer sender(this);
	HSMSHeader header = (*pHdr);
	bool bRet = GetDataType(pHdr, item);
	bool bFindCmd = false;
	CStringA cmdstr;
	char CPNAME[256] = { 0 };
	char CPVAL[256] = { 0 };

	CStringA PPID; 
	CStringA LOTID;
	BYTE *pCount = NULL;
	int nCount = 0; 

	if (bRet && item.format == LIST)
	{
		bRet = FindFirstItem(pHdr, item);

		if (bRet) cmdstr = "S2F41\n";


		if (ASCII == item.format)
		{
			char *pdata = (char *)malloc(item.len + 1);
			ZeroMemory(pdata, item.len + 1);

			memcpy(pdata, item.data, item.len);

			CStringA data(pdata);

			data.Trim();	data.MakeUpper();
			if (-1 != data.Find("PP_SELECT"))
			{
				bFindCmd = true;

				//解析附带的3个参数
				bRet = FindNextItem(item);

				if (LIST == item.format && 1 == item.len)
				{
					int outLen;
					eFormatCode outFC;
					ListItemData *pdata = item.data;

					pdata = GetChildSiblingItem_N(pdata, outFC, outLen);

					//3个：Recipe， Lot，Count
					if (outFC == LIST && 3 == outLen)
					{
						int idx = outLen;

						while (idx-- > 0)
						{
							pdata = GetChildSiblingItem_N(pdata, outFC, outLen);

							////Parameter Name && Parameter Value
							if (outFC == LIST && 2 == outLen)
							{
								pdata = GetChildSiblingItem_N(pdata, outFC, outLen);
								memcpy(CPNAME, pdata, outLen); //Parameter Name
								pdata += outLen;
								pdata = GetChildSiblingItem_N(pdata, outFC, outLen);
								pCount = pdata;
								memcpy(CPVAL, pdata, outLen);  //Parameter Value
								pdata += outLen;
							}

							switch (idx)
							{
							case 2:
							{
								PPID = CPVAL; //
								break;
							}
							case 1:
							{
								LOTID = CPVAL; //
								break;
							}
							case 0:
							{
								nCount = Get_INT_4B(pCount); //
								break;
							}
							}
						}
					}
				}
			}
			else if (-1 != data.Find("START"))
			{
				bFindCmd = true;
				//::MessageBox(NULL, "Remote CMD: START", "EQP Demo", 0);
			}
			else if (-1 != data.Find("STOP"))
			{
				bFindCmd = true;
				//::MessageBox(NULL, "Remote CMD: STOP", "EQP Demo", 0);
			}
			else if (-1 != data.Find("PAUSE"))
			{
				bFindCmd = true;
				//::MessageBox(NULL, "Remote CMD: PAUSE", "EQP Demo", 0);
			}
			else if (-1 != data.Find("RESUME"))
			{
				bFindCmd = true;
				//::MessageBox(NULL, "Remote CMD: RESUME", "EQP Demo", 0);
			}
			else
			{
			}
		}
	}




	//以下部分是收到数据，给HOST的应答

	sender.Begin();

	get_header_of_Data_message_reply(header);

	sender.Add_HSMSHeader(&header);

	sender.Add_LIST_Header(2);

	sender.BeginList();

	sender.Add_ITEM_Header(BINARY, 1);
	bFindCmd ? HCAK = 0 : HCAK = 6;
	sender.Add_BINARY(HCAK);

	if (0 == strlen(CPNAME) && 0 == strlen(CPVAL))
	{
		sender.Add_LIST_Header(0);
		sender.BeginList();
		sender.EndList();
	}
	else
	{
		sender.Add_LIST_Header(1);
		sender.BeginList();

		sender.Add_LIST_Header(2);
		sender.BeginList();

		sender.Add_ITEM_Header(ASCII, strlen(CPNAME));
		sender.Add_ASCII(CPNAME);

		sender.Add_ITEM_Header(ASCII, strlen(CPVAL));
		sender.Add_ASCII(CPVAL);

		sender.EndList();
		sender.EndList();
	}

	sender.EndList();
	sender.End();

	int outlen = 0;
	char *buf = sender.getSendBuffer(outlen);
	Send(buf, outlen, hComm);

	///USES_CONVERSION;
	m_panel.SetWindowText(cmdstr);
	return 0;
}


//显示远程发来的消息并显示在面板上
int CMainClassName::S10F3(HSMSHeader *pHdr, HCOMM hComm)
{
	ItemData item;
	BYTE ACKC = 0;
	bool bFindCmd = false;
	SenderBuffer sender(this);
	HSMSHeader header = (*pHdr);
	bool bRet = GetDataType(pHdr, item);
	char buf[20480] = { 0 };
	CStringA str;

	if (LIST == item.format)
	{

		bool bRet = FindFirstItem(pHdr, item);
		if (bRet) str = "S10F3\n";

		while (bRet)
		{
			if (BINARY == item.format)
			{
				CStringA TID;
				TID.Format("TID: %d\n", GetIntData(INT_1B, item.data));
				str += TID;
				bFindCmd = true;
			}
			if (ASCII == item.format)
			{

				memcpy(buf, item.data, item.len);
				CString s(buf);
				str += "TEXT: ";
				str += s;
				str += "\n";
				bFindCmd = true;
			}

			bRet = FindNextItem(item);
		}
	}

	sender.Begin();
	get_header_of_Data_message_reply(header);
	sender.Add_HSMSHeader(&header);

	sender.Add_ITEM_Header(BINARY, 1);
	bFindCmd ? ACKC = 0 : ACKC = 1;
	sender.Add_BINARY(ACKC);

	sender.End();

	int outlen = 0;
	char *pbuf = sender.getSendBuffer(outlen);
	Send(pbuf, outlen, hComm);
	///USES_CONVERSION;
	m_panel.SetWindowText(str);
	return 0;
}


LRESULT CMainClassName::OnAlarmReport(WPARAM w, LPARAM l)
{
	bool bSetOrClear = 1 == w;
	int ALID = l;
	S5F1AlarmReport(bSetOrClear, ALID);
	return 0;
}

LRESULT CMainClassName::OnS6f1TraceData(WPARAM w, LPARAM l)
{
	SetTimer(w, l * 1000, NULL);
	return 0;
}

void CMainClassName::RestartTrace()
{
	int TRIDCnt = GetTRIDCount();
	for (int i = 0; i < TRIDCnt; i++)
	{
		TRID *p = GetTRIDByIndex(i);
		if (NULL != p)
			SetTimer(p->TRID, p->DSPER * 1000, NULL);
	}
}

// 以下部分override基类的方法，仅仅为了截获数据，添加日志+添加列表显示
// 也就是 Append 这句。如果不需要截获，大可不必重写这部分基类方法。

int CMainClassName::Send(char *buf, int len, HCOMM hComm)
{
	int ret = __super::Send(buf, len, hComm);
	if (NULL != hComm)
		Append((HSMSHeader*)buf, true);
	return ret;
}


int CMainClassName::data_message_proc(HSMSHeader *pHdr, HCOMM hComm)
{
	Append(pHdr, false);

	int ret = __super::data_message_proc(pHdr, hComm);

	return ret;
}

int CMainClassName::Select_req_proc(HSMSHeader *pHdr, HCOMM hComm)
{
	Append(pHdr, false);
	int ret = __super::Select_req_proc(pHdr, hComm);

	return ret;
}

int CMainClassName::Select_rsp_proc(HSMSHeader *pHdr, HCOMM hComm)
{
	Append(pHdr, false);

	int ret = __super::Select_rsp_proc(pHdr, hComm);

	return ret;
}

int CMainClassName::Deselect_req_proc(HSMSHeader *pHdr, HCOMM hComm)
{
	Append(pHdr, false);

	int ret = __super::Deselect_req_proc(pHdr, hComm);


	int TRIDCnt = GetTRIDCount();
	for (int i = 0; i < TRIDCnt; i++)
	{
		TRID *p = GetTRIDByIndex(i);
		if (p)
			KillTimer(p->TRID);
	}

	return ret;
}

int CMainClassName::Deselect_rsp_proc(HSMSHeader *pHdr, HCOMM hComm)
{
	Append(pHdr, false);
	int ret = __super::Deselect_rsp_proc(pHdr, hComm);

	return ret;
}

int CMainClassName::Linktest_req_proc(HSMSHeader *pHdr, HCOMM hComm)
{
	Append(pHdr, false);
	int ret = __super::Linktest_req_proc(pHdr, hComm);

	return ret;
}

int CMainClassName::Linktest_rsp_proc(HSMSHeader *pHdr, HCOMM hComm)
{
	Append(pHdr, false);
	int ret = __super::Linktest_rsp_proc(pHdr, hComm);

	return ret;
}

int CMainClassName::Reject_req_proc(HSMSHeader *pHdr, HCOMM hComm)
{
	Append(pHdr, false);
	int ret = __super::Reject_req_proc(pHdr, hComm);

	return ret;
}

int CMainClassName::Separate_req_proc(HSMSHeader *pHdr, HCOMM hComm)
{
	Append(pHdr, false);
	int ret = __super::Separate_req_proc(pHdr, hComm);


	int TRIDCnt = GetTRIDCount();
	for (int i = 0; i < TRIDCnt; i++)
	{
		TRID *p = GetTRIDByIndex(i);
		if (p)
			KillTimer(p->TRID);
	}

	return ret;
}
