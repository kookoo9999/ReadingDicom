// LoginDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "DICOMViewer.h"
#include "LoginDlg.h"
#include "afxdialogex.h"

#include "DVManager.h"


// LoginDlg 대화 상자

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_LoginPW(_T(""))
{

}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LGID, m_LoginID);
	DDX_Text(pDX, IDC_EDIT_LGPW, m_LoginPW);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
//	ON_BN_CLICKED(IDOK, &LoginDlg::OnBnClickedLogin)
	//ON_BN_CLICKED(IDC_DB_CON_TEST, &LoginDlg::OnBnClickedDbConTest)
//	ON_BN_CLICKED(IDOK, &LoginDlg::OnBnClickedOk)
//	ON_BN_CLICKED(IDC_DB_CON_TEST, &LoginDlg::OnClickedDbConTest)
//	ON_BN_CLICKED(IDC_Get_Mac, &LoginDlg::OnBnClickedGetMac)
//	ON_BN_CLICKED(IDC_BUTTON1, &LoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &LoginDlg::OnBnClickedOk)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()




//void LoginDlg::OnBnClickedLogin()
//{
//	
//
//	/*if (!mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, 0, 0)) //연결
//	{
//		MessageBox(TEXT("DB 접속에 실패했습니다."), TEXT("접속 에러"), MB_OK);
//		TRACE("Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
//	}
//	else
//	{
//		mysql_query(&mysql, "set names euckr"); //한글 인식
//		TRACE("DB 연결 성공");
//	}
//
//	mysql_close(&mysql);*/
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}




//void LoginDlg::OnBnClickedOk()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialogEx::OnOK();
//}


//void LoginDlg::OnClickedDbConTest()
//{
//	mysql_init(&mysql);  //mysql 초기화
//	CString edit_id;	//edit 컨트롤 ID값 변수
//	CString edit_pw;	//eidt 컨트롤 password값 변수
//	
//	GetDlgItemText(IDC_EDIT_LGID, edit_id); //edit컨트롤 값 변수에 저장
//	GetDlgItemText(IDC_EDIT_LGPW, edit_pw); 
//	//test.Format(_T("%s"), m_LoginID);
//	//AfxMessageBox(id);
//
//
//	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) //mysql 연결
//
//	{
//		
//		AfxMessageBox(LP(mysql_error(&mysql)), MB_OK); //실패시 에러메시지
//
//	}
//
//
//	else 
//
//	{
//
//		mysql_query(&mysql, "set names euckr"); //한글 인식
//
//		AfxMessageBox(_T("DB 연결 성공"), MB_OK);
//
//		CString query_edit_mac; //mac주소 찾은값 db에 추가하는 쿼리
//		CString query_check_member; //id,pw비교하는 쿼리
//		CString strMac; //mac값 저장
//
//
//
//		query_check_member.Format(_T("select mb_id from g5_member where (mb_id='%s' and mb_password = password('%s'))"),edit_id, edit_pw);
//		//query_check_member.Format(_T("update g5_member set mb_10='sdsd' where mb_id = 'kkm5583'"));
//		AfxMessageBox(query_check_member);
//		mysql_query(&mysql, (CW2A)query_check_member); //id,pw비교하는 쿼리 전송
//		int count; //row갯수 저장할 변수
//		m_res = mysql_store_result(&mysql); //쿼리실행결과 저장
//
//		row = mysql_fetch_row(m_res); //result set에서 하나의 row를 불러온다
//		//fields = mysql_num_fields(m_res);
//		
//		count = mysql_num_rows(m_res); //쿼리실행결과 row의 갯수카운트 
//
//		if (count==1) //0이면 null 1이면 id,pw값 일치 
//		{
//			//mysql_free_result(m_res); //결과에 할당된 메모리 해제
//			AfxMessageBox(_T("ID,PW 일치"));
//			
//			
//			DWORD size = sizeof(PIP_ADAPTER_INFO);
//
//			PIP_ADAPTER_INFO Info;
//
//			ZeroMemory(&Info, size);
//
//			int result = GetAdaptersInfo(Info, &size);        // 첫번째 랜카드 MAC address 가져오기
//
//			if (result == ERROR_BUFFER_OVERFLOW)    // GetAdaptersInfo가 메모리가 부족하면 재 할당하고 재호출
//			{
//				Info = (PIP_ADAPTER_INFO)malloc(size);
//				GetAdaptersInfo(Info, &size);
//			}
//
//			if (!Info) {
//				AfxMessageBox(strMac);
//				//return strMac;
//				//getMacAdd = strMac;
//
//			}
//			strMac.Format(_T("%0.2X-%0.2X-%0.2X-%0.2X-%0.2X-%0.2X"), Info->Address[0], Info->Address[1], Info->Address[2], Info->Address[3], Info->Address[4], Info->Address[5]);
//			AfxMessageBox(strMac);
//
//			CString checkMAC; //mac존재확인 쿼리
//			//checkMAC.Format(_T("select mb_10 from g5_member where mb_id = '%s' and mb_10 = null"), edit_id); //mac 존재 확인 쿼리
//			checkMAC.Format(_T("select mb_10 from g5_member where mb_id='%s' and mb_10 <>''"),edit_id);
//			mysql_query(&mysql, (CW2A)checkMAC);
//			AfxMessageBox(checkMAC);
//			
//			int rcount;
//			m_res = mysql_store_result(&mysql); //쿼리실행결과 저장
//			rcount = mysql_num_rows(m_res); //쿼리실행결과 row의 갯수카운트 
//			if (rcount == 1) //있을 시 비교
//			{
//				//mysql_free_result(m_res); //결과에 할당된 메모리 해제
//				AfxMessageBox(_T("등록된 MAC이 있습니다"));				
//				CString compareMAC;
//				compareMAC.Format(_T("select * from g5_member where mb_10 = '%s' and mb_id = '%s'"), strMac, edit_id);
//				
//				//AfxMessageBox(strMac);
//				mysql_query(&mysql, (CW2A)compareMAC);
//				int lcount;
//				m_res = mysql_store_result(&mysql); //쿼리실행결과 저장
//				lcount = mysql_num_rows(m_res); //쿼리실행결과 row의 갯수카운트 
//				if (lcount == 0) AfxMessageBox(_T("MAC이 일치하지 않습니다."));
//				else AfxMessageBox(_T("MAC이 일치합니다."));
//				mysql_close(&mysql);
//			}
//			else //없을시 추가
//			{
//				
//
//				
//				AfxMessageBox(_T("등록된 MAC이 없어 추가합니다"));
//
//				query_edit_mac.Format(_T("update g5_member set mb_10 = '%s' where mb_id='%s'"), strMac, edit_id);
//				AfxMessageBox(strMac);
//				//AfxMessageBox(strMac);
//				//query = "update g5_member set mb_10 = 'sdf' where mb_id='kkm5583'";
//				//char* szQuery = (CW2A)query;
//				//AfxMessageBox((LPCTSTR)szQuery);
//				//AfxMessageBox(query);
//				//update g5_member set mb_10 = 'kk11' where mb_id='kkm5583' kkm5583=m_LoginID
//				if (mysql_query(&mysql, (CW2A)query_edit_mac) == 0)
//				{
//					AfxMessageBox(_T("데이터반영 성공"));
//					AfxMessageBox((LPCTSTR)query_edit_mac);
//				}
//				else
//				{
//					AfxMessageBox(_T("데이터반영 실패"));
//					//AfxMessageBox(LPCTSTR(mysql_error(&mysql)), MB_OK);
//					AfxMessageBox((LPCTSTR)query_edit_mac);
//				}
//				//if(!mysql_query()
//
//				mysql_close(&mysql);
//				CDialogEx::OnOK();
//			}
//		}
//		else
//		{
//			AfxMessageBox(_T("로그인실패"));
//			AfxMessageBox(_T("ID,PW 확인해주세요"));
//			mysql_close(&mysql);
//		}
//	}
//	
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}

//void LoginDlg::OnBnClickedGetMac()
//{
//	GetMac();
//}





void LoginDlg::GetMac()
{
	 CString strMac;
	
	//query.Format(_T("update g5_member set mb_10 = 'strMac' where mb_id = EDIT_LGID"));
	//query.Format(_T("update g5_member set mb_10 = '") + strMac + _T("' where mb_id = '") + IDC_EDIT_LGID + _T("'");
	//query.Format(LPCSTR("update g5_member set mb_10 = '" + strMac +"' where mb_id = '" +IDC_EDIT_LGID +"'"));
	
	DWORD size = sizeof(PIP_ADAPTER_INFO);

	PIP_ADAPTER_INFO Info;

	ZeroMemory(&Info, size);

	int result = GetAdaptersInfo(Info, &size);        // 첫번째 랜카드 MAC address 가져오기

	if (result == ERROR_BUFFER_OVERFLOW)    // GetAdaptersInfo가 메모리가 부족하면 재 할당하고 재호출
	{
		Info = (PIP_ADAPTER_INFO)malloc(size);
		GetAdaptersInfo(Info, &size);
	}

	if (!Info) {
		AfxMessageBox(strMac);
		//return strMac;
		//getMacAdd = strMac;
		
	}
	strMac.Format(_T("%0.2X-%0.2X-%0.2X-%0.2X-%0.2X-%0.2X"), Info->Address[0], Info->Address[1], Info->Address[2], Info->Address[3], Info->Address[4], Info->Address[5]);
	//getMacAdd = strMac;
	AfxMessageBox(strMac);
	//return strMac;

	//query.Format(_T("update g5_member set mb_10 = '%s' where mb_id = '%s'"), strMac, IDC_EDIT_LGID);
	//query.Format(_T("select mb_id,mb_10 from g5_member"));
	
	
	//mysql_query(&mysql, (LPSTR)(LPCTSTR)(query));
	


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//void LoginDlg::OnBnClickedButton1() //IDOK 테스트버전
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	//CString test = CT2A(m_LoginID);
//	CString id;
//	int fields;
//	GetDlgItemText(IDC_EDIT_LGID, id);
//	//test.Format(_T("%s"), m_LoginID);
//	AfxMessageBox(id);
//
//	mysql_init(&mysql);
//
//	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0))
//
//	{
//
//		AfxMessageBox(LP(mysql_error(&mysql)), MB_OK);
//
//	}
//	else
//	{		
//
//		CString check;
//		check.Format(_T("select mb_id from g5_member where mb_id='kkm5583'"));
//		AfxMessageBox(check);
//
//		if (mysql_query(&mysql, (CW2A)check) != 0)
//		{
//			AfxMessageBox(_T("전송실패"));
//		}
//		m_res = mysql_store_result(&mysql);
//		
//		row = mysql_fetch_row(m_res);
//		fields = mysql_num_fields(m_res);
//		int count;
//		count = mysql_num_rows(m_res);
//
//
//		if (count > 5) AfxMessageBox(_T("0보다 큼"));
//		else if(count==1) AfxMessageBox(_T("1임"));
//		else AfxMessageBox(_T("0이거나 0보다 작음"));
//
//
//		CString str;
//		str.Format((LPCTSTR)m_res);
//
//		AfxMessageBox(str);
//		
//
//
//
//		
//
//		
//
//	
//	
//
//		
//		//fields = mysql_num_fields(m_res);
//
//		
//		mysql_free_result(m_res);
//		mysql_close(&mysql);
//
//
//		/*CEdit *editbox = (CEdit *)GetDlgItem(IDC_EDIT_LGID);
//
//		CString str;
//		editbox->GetWindowText(str);
//
//		AfxMessageBox(str);*/
//
//
//
//	}
//}


void LoginDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//LoginDlg::OnClickedDbConTest();
	mysql_init(&mysql);  //mysql 초기화

	CString edit_id;	//edit 컨트롤 ID값 변수
	CString edit_pw;	//eidt 컨트롤 password값 변수

	GetDlgItemText(IDC_EDIT_LGID, edit_id); //edit컨트롤 값 변수에 저장
	GetDlgItemText(IDC_EDIT_LGPW, edit_pw);
	//test.Format(_T("%s"), m_LoginID);
	//AfxMessageBox(id);


	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) //mysql 연결

	{
		//DB연결실패
		AfxMessageBox(LP(mysql_error(&mysql)), MB_OK); //실패시 에러메시지
		

	}


	else

	{
		//DB연결 성공시
		mysql_query(&mysql, "set names euckr"); //한글 인식
		TRACE("DB Connect Success \n");
		//AfxMessageBox(_T("DB 연결 성공"), MB_OK);

		CString query_edit_mac; //mac주소 찾은값 db에 추가하는 쿼리
		CString query_check_member; //id,pw비교하는 쿼리
		CString strMac; //mac값 저장



		query_check_member.Format(_T("select mb_id from g5_member where (mb_id='%s' and mb_password = password('%s'))"), edit_id, edit_pw);
		//query_check_member.Format(_T("update g5_member set mb_10='sdsd' where mb_id = 'kkm5583'"));
		//AfxMessageBox(query_check_member);
		mysql_query(&mysql, (CW2A)query_check_member); //id,pw비교하는 쿼리 전송
		int count; //row갯수 저장할 변수
		m_res = mysql_store_result(&mysql); //쿼리실행결과 저장

		row = mysql_fetch_row(m_res); //result set에서 하나의 row를 불러온다
		//fields = mysql_num_fields(m_res);

		count = mysql_num_rows(m_res); //쿼리실행결과 row의 갯수카운트 
		//0이면 null 1이면 id,pw값 일치
		if (count == 1)  
		{
			//mysql_free_result(m_res); //결과에 할당된 메모리 해제
			//AfxMessageBox(_T("ID,PW 일치"));
			TRACE("ID & PW correct \n");

			//-----------------------여기서 Mac값 추출---------------------------------------

			DWORD size = sizeof(PIP_ADAPTER_INFO);

			PIP_ADAPTER_INFO Info;

			ZeroMemory(&Info, size);

			int result = GetAdaptersInfo(Info, &size);        // 첫번째 랜카드 MAC address 가져오기

			if (result == ERROR_BUFFER_OVERFLOW)    // GetAdaptersInfo가 메모리가 부족하면 재 할당하고 재호출
			{
				Info = (PIP_ADAPTER_INFO)malloc(size);
				GetAdaptersInfo(Info, &size);
			}

			if (!Info) {
				AfxMessageBox(strMac);
				//return strMac;
				//getMacAdd = strMac;

			}
			strMac.Format(_T("%0.2X-%0.2X-%0.2X-%0.2X-%0.2X-%0.2X"), Info->Address[0], Info->Address[1], Info->Address[2], Info->Address[3], Info->Address[4], Info->Address[5]);
			//AfxMessageBox(strMac);
			TRACE1("This PC's MAC : %s \n", strMac);
			//------------------Mac값 유무 확인----------------------------------

			CString checkMAC; //mac존재확인 쿼리
			//checkMAC.Format(_T("select mb_10 from g5_member where mb_id = '%s' and mb_10 = null"), edit_id); //mac 존재 확인 쿼리
			checkMAC.Format(_T("select mb_10 from g5_member where mb_id='%s' and mb_10 <>''"), edit_id);
			mysql_query(&mysql, (CW2A)checkMAC);
			//AfxMessageBox(checkMAC);

			

			int rcount;
			m_res = mysql_store_result(&mysql); //쿼리실행결과 저장
			rcount = mysql_num_rows(m_res); //쿼리실행결과 row의 갯수카운트 
			if (rcount == 1) //있을 시 비교
			{
				//mysql_free_result(m_res); //결과에 할당된 메모리 해제
				//AfxMessageBox(_T("등록된 MAC이 있습니다"));
				TRACE("MAC is exist");

				CString compareMAC; //Mac주소 비교하는 쿼리
				compareMAC.Format(_T("select * from g5_member where mb_10 = '%s' and mb_id = '%s'"), strMac, edit_id);

				//AfxMessageBox(strMac);
				mysql_query(&mysql, (CW2A)compareMAC);
				int lcount;
				m_res = mysql_store_result(&mysql); //쿼리실행결과 저장
				lcount = mysql_num_rows(m_res); //쿼리실행결과 row의 갯수카운트 

				
				if (lcount == 0)
				{
					AfxMessageBox(_T("계정에 등록된 주소와 일치하지 않습니다."));
					TRACE("MAC is different \n");
				}
				//else AfxMessageBox(_T("MAC이 일치합니다."));
				else 
				{
					mysql_close(&mysql);
					TRACE("MAC Address is true \n");
					AfxMessageBox(_T("환영합니다"));
					CDialogEx::OnOK();
				}
				mysql_close(&mysql);
			}
			else //없을시 추가
			{


				//단계확인용
				TRACE("MAC is different \n");
				AfxMessageBox(_T("처음 접속하셨으므로 주소등록을 진행합니다.\n     다른 환경에서 접속할 수 없습니다."));

				query_edit_mac.Format(_T("update g5_member set mb_10 = '%s' where mb_id='%s'"), strMac, edit_id);
				mysql_query(&mysql,(CW2A)query_edit_mac);
				//Mac값 출력
				//AfxMessageBox(strMac); 

				//AfxMessageBox(strMac);
				//query = "update g5_member set mb_10 = 'sdf' where mb_id='kkm5583'";
				//char* szQuery = (CW2A)query;
				//AfxMessageBox((LPCTSTR)szQuery);
				//AfxMessageBox(query);
				//update g5_member set mb_10 = 'kk11' where mb_id='kkm5583' kkm5583=m_LoginID

				/*쿼리테스트 부분-----------------------------------------------
				
				if (mysql_query(&mysql, (CW2A)query_edit_mac) == 0)
				{
					AfxMessageBox(_T("데이터반영 성공"));
					AfxMessageBox((LPCTSTR)query_edit_mac);
				}
				else
				{
					AfxMessageBox(_T("데이터반영 실패"));
					//AfxMessageBox(LPCTSTR(mysql_error(&mysql)), MB_OK);
					AfxMessageBox((LPCTSTR)query_edit_mac);
				}
				--------------------------------------------------------------------*/
				
				//if(!mysql_query()

				mysql_close(&mysql);
				AfxMessageBox(_T("환영합니다"));
				CDialogEx::OnOK();
			}
			
		}
		else
		{
			//AfxMessageBox(_T("로그인실패\n"));
			TRACE("ID or PW is different \n");
			AfxMessageBox(_T("계정 또는 비밀번호를 확인해주세요"));
			mysql_close(&mysql);
		}
		
	}
	
	//CDialogEx::OnOK();
}


void LoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nID == SC_CLOSE)
	{
		//종료버튼 눌릴 시
		CWnd *pWnd = AfxGetMainWnd();
		HWND hWnd = pWnd->m_hWnd;
		PostQuitMessage(WM_QUIT);
		//SendMessage(GetSafeHwnd(), WM_CLOSE, NULL);
		
	
		
	}
	CDialogEx::OnSysCommand(nID, lParam);
}


BOOL LoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GotoDlgCtrl(GetDlgItem(IDC_EDIT_LGID));
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return FALSE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
