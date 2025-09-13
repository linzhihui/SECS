#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include <afxmt.h>

class Csecs_DemoEquipmentApp : public CWinApp
{
public:
	Csecs_DemoEquipmentApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern Csecs_DemoEquipmentApp theApp;