#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <afxmt.h>

class Csecs_DemoEquipmentApp : public CWinApp
{
public:
	Csecs_DemoEquipmentApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Csecs_DemoEquipmentApp theApp;