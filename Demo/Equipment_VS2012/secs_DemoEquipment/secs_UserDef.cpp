#include "stdafx.h"
#include "secs_DemoEquipment.h"
#include "secs_DemoEquipmentDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//����Զ������Ϣ��������ص�����

int CMainClassName::SnFn_UserDef(HSMSHeader *pHdr, HCOMM hComm)
{
	int ret = 0;


	int Sn = getStreamNum(*pHdr);
	int Fn = getFunctionNum(*pHdr);
	int nDeviceId = getDeviceId(*pHdr);

	switch (SnFn(Sn, Fn))
	{
	case SnFn(1, 65):
	{
		ret = S1F65(pHdr, hComm);
		break;
	}
	case SnFn(1, 69):
	{
		ret = S1F69(pHdr, hComm);
		break;
	}
	
	}

	return ret;
}

int  CMainClassName::S1F65(HSMSHeader *pHdr, HCOMM hComm)
{

	SenderBuffer sender(this);
	HSMSHeader header = (*pHdr);
	bool bNeedReplyFlag = getReplyFlag(*pHdr);

	//to-do
	//��д��Ĵ���

	return 0;
}

int  CMainClassName::S1F69(HSMSHeader *pHdr, HCOMM hComm)
{

	SenderBuffer sender(this);
	HSMSHeader header = (*pHdr);
	bool bNeedReplyFlag = getReplyFlag(*pHdr);

	//to-do
	//��д��Ĵ���

	return 0;
}
