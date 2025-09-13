#include "stdafx.h"
#include "secs_DemoEquipment.h"
#include "secs_DemoEquipmentDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CMainClassName::OpenLogFile()
{
	::GetLocalTime(&m_stNow);

	m_SecsLogfile.Format(_T(".\\ini\\secs_eqp_%02d%02d%02d%02d.log"), m_stNow.wYear,
		m_stNow.wMonth, m_stNow.wDay, m_stNow.wHour);

	BOOL bRet = m_logfile.Open(m_SecsLogfile,
		CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone);


	if (bRet)
	{
		m_logfile.SeekToEnd();
		m_logInit = true;
		memcpy(&m_stOld, &m_stNow, sizeof(SYSTEMTIME));
	}
	else
	{
		m_logInit = false;
	}
}

void CMainClassName::ParseToLogfile(HSMSHeader *pHdr)
{
	CString outTxt;
	ItemData item;

	bool bSuc = GetDataType(pHdr, item);

	if (false == bSuc)
	{
		outTxt = "<Header Only>\r\n";
		return;
	}

	if (LIST == item.format)
	{
		CStringA liststr;
		liststr.Format("  <L, %d", item.len);
		AppendLog(liststr, true);

		eFormatCode outFC;
		int outLen, ItemCnts = item.len;
		ListItemData *Entry1 = item.data;
		ListItemData *Entry2 = Entry1;

		for (int i = 0; i < ItemCnts; i++)
		{
			Entry2 = GetChildSiblingItem_N(Entry2, outFC, outLen);

			if (LIST == outFC)
			{
				liststr.Format("    <L, %d", outLen);
				AppendLog(liststr, true);
				int ItemCnts_2 = outLen;

				for (int i_2 = 0; i_2 < ItemCnts_2; i_2++)
				{
					Entry2 = GetChildSiblingItem_N(Entry2, outFC, outLen);

					if (LIST == outFC)
					{
						liststr.Format("      <L, %d", outLen);
						AppendLog(liststr, true);
						int ItemCnts_3 = outLen;

						for (int i_3 = 0; i_3 < ItemCnts_3; i_3++)
						{
							Entry2 = GetChildSiblingItem_N(Entry2, outFC, outLen);

							if (LIST == outFC)
							{
								liststr.Format("        <L, %d", outLen);
								AppendLog(liststr, true);
								int ItemCnts_4 = outLen;

								for (int i_4 = 0; i_4 < ItemCnts_4; i_4++)
								{
									Entry2 = GetChildSiblingItem_N(Entry2, outFC, outLen);

									if (LIST == outFC)
									{
										liststr.Format("          <L, %d", outLen);
										AppendLog(liststr, true);
										int ItemCnts_5 = outLen;

										for (int i_5 = 0; i_5 < ItemCnts_5; i_5++)
										{
											Entry2 = GetChildSiblingItem_N(Entry2, outFC, outLen);
											if (LIST == outFC)
											{
												//大于5层嵌套列表不处理啦
											}
											else
											{
												GenerateLogString(Entry2, outFC, outLen, 6);
												Entry2 += outLen;
											}
										}

										AppendLog("          >", true);
									}
									else
									{
										GenerateLogString(Entry2, outFC, outLen, 5);
										Entry2 += outLen;
									}
								}
								AppendLog("        >", true);
							}
							else
							{
								GenerateLogString(Entry2, outFC, outLen, 4);
								Entry2 += outLen;
							}

						}
						AppendLog("      >", true);
					}
					else
					{
						GenerateLogString(Entry2, outFC, outLen, 3);
						Entry2 += outLen;
					}
				}

				AppendLog("    >", true);
			}
			else
			{
				GenerateLogString(Entry2, outFC, outLen, 2);
				Entry2 += outLen;
			}

		}//for
		AppendLog("  >", true);
	}
	else
	{// item
		GenerateLogString(item, 1);
	}
}


void CMainClassName::CloseLogFile()
{
	m_logInit = false;
	if (m_logfile.m_hFile != INVALID_HANDLE_VALUE)
	{
		m_logfile.Close();
	}
}

void CMainClassName::GenerateLogString(ListItemData* entry,
	eFormatCode fc,
	int Len,
	int blanks)
{
	TCHAR buf[4096] = { 0 };
	memcpy(buf, entry, Len);
	USES_CONVERSION;
	CStringA str, typestr;

	for (int i = 0; i < blanks; i++)
	{
		str += "  ";
	}

	str += "<";

	switch (fc)
	{
	case BINARY://BINARY
		if (1 == Len)
		{
			typestr.Format("B,%d,%d", Len, Get_INT_1B(entry));
		}
		else
		{

			BYTE *p = (BYTE*)entry;
			CStringA bstr, text;
			int k = 0;
			for (int i = 0; i < Len; i++)
			{
				bstr.Format("%02x", *p);
				p++;  k++;
				text += bstr;	text += " ";
				if (k == 16)  { k = 0;	text += "\r\n"; }
				bstr.Empty();
			}

			typestr.Format("B,%d,%s", Len, text);
		}
		break;
	case BOOLEAN_://Boolean
		typestr.Format("Boolean,%d,\'%d\'", Len, Get_INT_1B(entry));
		break;
	case ASCII: //ASCII
		typestr.Format("ASCII,%d,\'%s\'", Len, buf);
		break;
	case JIS8:  //JIS-8
		typestr.Format("JIS8,%d,\'%s\'", Len, buf);
		break;
	case CHAR_2B: //2-byte character
		typestr.Format("CHAR_2B,%d,\'%s\'", Len / 2, buf);
		break;
	case INT_8B: //8-byte integer(signed)
		typestr.Format("I8,%d,\'%d\'", Len / 8, Get_INT_8B(entry));
		break;
	case INT_1B:  //1-byte integer(signed)
		typestr.Format("I1,%d,\'%d\'", Len, Get_INT_1B(entry));
		break;
	case INT_2B: //2-byte integer(signed)
		typestr.Format("I2,%d,\'%d\'", Len / 2, Get_INT_2B(entry));
		break;
	case INT_4B:  //4-byte integer(signed)
		typestr.Format("I4,%d,\'%d\'", Len / 4, Get_INT_4B(entry));
		break;
	case FLOAT_8B: //8-byte floating point
		typestr.Format("F8,%d,\'%.3f\'", Len / 8, Get_FLOAT_8B(entry));
		break;
	case FLOAT_4B: //4-byte floating point
		typestr.Format("F4,%d,\'%.3f\'", Len / 4, Get_FLOAT_4B(entry));
		break;
	case UINT_8B:   //8-byte integer(unsigned)
		typestr.Format("U8,%d,\'%d\'", Len / 8, Get_UINT_8B(entry));
		break;
	case UINT_1B:   //1-byte integer(unsigned)
		typestr.Format("U1,%d,\'%d\'", Len, Get_UINT_1B(entry));
		break;
	case UINT_2B: //2-byte integer(unsigned)
		typestr.Format("U2,%d,\'%d\'", Len / 2, Get_UINT_2B(entry));
		break;
	case UINT_4B:  //4-byte integer(unsigned)
		typestr.Format("U4,%d,\'%d\'", Len / 4, Get_UINT_4B(entry));
		break;
	}

	str += typestr;
	str += ">";

	AppendLog(str, true);

}

void  CMainClassName::GenerateLogString(ItemData &item,
	int blanks)
{
	GenerateLogString(item.data, item.format, item.len, blanks);
}