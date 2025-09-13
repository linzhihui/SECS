#include "stdafx.h"
#include "secs_DemoEquipment.h"
#include "secs_DemoEquipmentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(Csecs_DemoEquipmentApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

Csecs_DemoEquipmentApp::Csecs_DemoEquipmentApp()
{
}

Csecs_DemoEquipmentApp theApp;

BOOL Csecs_DemoEquipmentApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	Csecs_DemoEquipmentDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	return FALSE;
}
