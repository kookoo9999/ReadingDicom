#pragma once
/*
#include "mysql_include/mysql.h"
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"\mysql_lib\\libmysql.lib")*/
/*#define DB_HOST "db.plannerclinics.com"
#define DB_USER "plannerclinic"
#define DB_PASS "jung2143822@"
#define DB_NAME "dbplannerclinic"
*/

// LoginDlg 대화 상자

class LoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LoginDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedLogin();

	//afx_msg void OnBnClickedDbConTest();
//	afx_msg void OnBnClickedOk();
//	afx_msg void OnClickedDbConTest();
//	afx_msg void OnBnClickedGetMac();
	static void GetMac();
	CString m_LoginID;
//	afx_msg void OnBnClickedButton1();

	CString m_LoginPW;
	afx_msg void OnBnClickedOk();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
