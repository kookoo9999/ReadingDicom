// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����




//#pragma comment(lib,"libmysql.lib")
//#pragma comment(lib,"ws2_32.lib")
//----------------------------------------------------------------------------


//ssss







#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#include <vtkAutoInit.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#define vtkRenderingCore_AUTOINIT 4(vtkRenderingOpenGL,vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingContextOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

//MYSQL ������� ----------------------------------------------------------

/*
#include "mysql_include\mysql.h"
#include <afxcontrolbars.h>
#pragma comment(lib,"mysql_lib\\libmysql.lib")
#pragma comment(lib,"ws2_32.lib")
*/
//DB���� �ʱ�ȭ ������� ----------------------------------------------------

//-----------------------------------------------------------------------------
/*static MYSQL_ROW row;		// mysql �� ���� �ô´�.

static MYSQL_RES *m_res;	// mysql�� ����� �޾ƿ´�

static MYSQL mysql;		// mysql�� ��ü���� ������ ����Ѵ�. 
*/

#include "mysql.h"

#include <WinSock2.h>
#include <iphlpapi.h>
#pragma comment(lib,"libmysql.lib")

#pragma comment(lib,"ws2_32.lib")

#pragma comment (lib, "Iphlpapi.lib")

#define DB_ADDRESS "db.plannerclinics.com"

#define DB_ID "plannerclinic"

#define DB_PASS "jung2143822@"

#define DB_NAME "dbplannerclinic"

extern MYSQL_ROW row; // mysql �� ���� �ô´�.

extern MYSQL_RES *m_res; // mysql�� ����� �޾ƿ´�

extern MYSQL mysql; // mysql�� ��ü���� ������ ����Ѵ�.


