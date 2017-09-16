
// ExpressCacheShowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExpressCacheShow.h"
#include "ExpressCacheShowDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"

#include <wbemidl.h> 
#include <Wbemcli.h>
#pragma comment(lib,"Wbemuuid.lib")  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ECInfo;
	CString headerInfo;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedProcess();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ECINFO, m_ECInfo);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PROCESS, &CAboutDlg::OnBnClickedProcess)
END_MESSAGE_MAP()


// CExpressCacheShowDlg �Ի���




CExpressCacheShowDlg::CExpressCacheShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExpressCacheShowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExpressCacheShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_INFO, m_main_info);
	DDX_Control(pDX, IDC_PROGRESS1, m_readP);
	DDX_Control(pDX, IDC_PROGRESS2, m_writeP);
	DDX_Control(pDX, IDC_READ_P, m_readValue);
	DDX_Control(pDX, IDC_WRITE_P, m_writeValue);
}

BEGIN_MESSAGE_MAP(CExpressCacheShowDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_COMMAND, &CExpressCacheShowDlg::OnBnClickedCommand)
END_MESSAGE_MAP()


// CExpressCacheShowDlg ��Ϣ�������
unsigned __stdcall Fresh(void * pParam)
{
	while(1)
	{
	CExpressCacheShowDlg *Dlg = (CExpressCacheShowDlg *)pParam;
	CString str;
	if(Dlg->GetInfo(str)!=0)
	{
		int index = str.Find(L"EC Cache Info");
		if(index!=-1)
		{
			CString headerInfo = str.Left(index);
			CString mainInfo = str.Right(str.GetLength() - index);

			int index2 = mainInfo.Find(L"Cache Read Percent",0);
			/*int temp_index = index2;
			while(temp_index!=-1)
			{
				index2 = temp_index;
				temp_index = mainInfo.Find(L"Cache Read Percent",index2+1);
			}*/
			CString showInfo = mainInfo.Left(index2);
			CString percent = mainInfo.Right(mainInfo.GetLength() - index2);
			showInfo.Trim();

			//percent
			float readP,writeP;
			int read = percent.Find('%');
			CString readstr = percent.Mid(read - 5,5);
			int write=percent.ReverseFind('%');
			CString writestr = percent.Mid(write - 5,5);

			readP = _wtof(readstr.GetBuffer(0));
			writeP = _wtof(writestr.GetBuffer(0));

			Dlg->m_main_info.SetWindowTextW(showInfo);
			Dlg->m_readP.SetPos(readP);
			Dlg->m_readValue.SetWindowTextW(readstr+'%');
			Dlg->m_writeP.SetPos(writeP);
			Dlg->m_writeValue.SetWindowTextW(writestr+'%');
		}
		else
		{
			Dlg->m_main_info.SetWindowTextW(str);
		}
	}
	Sleep(5000);
	}
	return 1;
}

BOOL CExpressCacheShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_readP.SetRange(0,100);
	m_writeP.SetRange(0,100);

	////
		CString str;
	if(GetInfo(str)!=0)
	{
		int index = str.Find(L"EC Cache Info");
		if(index!=-1)
		{
			CString headerInfo1 = str.Left(index);
			headerInfo=headerInfo1;
			CString mainInfo = str.Right(str.GetLength() - index);

			int index2 = mainInfo.Find(L"Cache Read Percent",0);
			/*int temp_index = index2;
			while(temp_index!=-1)
			{
				index2 = temp_index;
				temp_index = mainInfo.Find(L"Cache Read Percent",index2+1);
			}*/
			CString showInfo = mainInfo.Left(index2);
			CString percent = mainInfo.Right(mainInfo.GetLength() - index2);
			showInfo.Trim();

			//percent
			float readP,writeP;
			int read = percent.Find('%');
			CString readstr = percent.Mid(read - 5,5);
			int write=percent.ReverseFind('%');
			CString writestr = percent.Mid(write - 5,5);

			readP = _wtof(readstr.GetBuffer(0));
			writeP = _wtof(writestr.GetBuffer(0));

			m_main_info.SetWindowTextW(showInfo);
			m_readP.SetPos(readP);
			m_readValue.SetWindowTextW(readstr+'%');
			m_writeP.SetPos(writeP);
			m_writeValue.SetWindowTextW(writestr+'%');
		}
		else
		{
			m_main_info.SetWindowTextW(str);
		}
	}
	////
	_beginthreadex( NULL, 0, &Fresh, (LPVOID)this, 0, 0 );
	//SetTimer(1,3000,NULL);
	//OnTimer(1);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CExpressCacheShowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.headerInfo = headerInfo;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExpressCacheShowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CExpressCacheShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��ȡ״̬����
BOOL CExpressCacheShowDlg::GetInfo(CString &str)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hWrite,hRead;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char buff[4096*25];
	DWORD dwReadBytes;

	ZeroMemory(buff,4096*25);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);

	if(!CreatePipe(&hRead,&hWrite,&sa,0))
	{
		MessageBox(L"Create Pipe Error!",L"",0);
		return 0;
	}

	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;

	LPTSTR pro=_tcsdup(TEXT("C:\\WINDOWS\\system32\\cmd.exe /c eccmd -info"));
	if(!CreateProcess(NULL,pro,NULL,NULL,TRUE,0,NULL,NULL,&si,&pi))
	{
		MessageBox(L"Create Process Error!",L"",0);
		return 0;
	}
	CloseHandle(hWrite);

	ReadFile(hRead,buff,4096,&dwReadBytes,NULL);
	str=buff;
	//MessageBox(str);
	return 1;
}

void CExpressCacheShowDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	if(GetInfo(str)!=0)
	{
		int index = str.Find(L"EC Cache Info");
		if(index!=-1)
		{
			CString headerInfo = str.Left(index);
			CString mainInfo = str.Right(str.GetLength() - index);

			int index2 = mainInfo.Find(L"Cache Read Percent",0);
			/*int temp_index = index2;
			while(temp_index!=-1)
			{
				index2 = temp_index;
				temp_index = mainInfo.Find(L"Cache Read Percent",index2+1);
			}*/
			CString showInfo = mainInfo.Left(index2);
			CString percent = mainInfo.Right(mainInfo.GetLength() - index2);
			showInfo.Trim();

			//percent
			float readP,writeP;
			int read = percent.Find('%');
			CString readstr = percent.Mid(read - 5,5);
			int write=percent.ReverseFind('%');
			CString writestr = percent.Mid(write - 5,5);

			readP = _wtof(readstr.GetBuffer(0));
			writeP = _wtof(writestr.GetBuffer(0));

			m_main_info.SetWindowTextW(showInfo);
			m_readP.SetPos(readP);
			m_readValue.SetWindowTextW(readstr+'%');
			m_writeP.SetPos(writeP);
			m_writeValue.SetWindowTextW(writestr+'%');
		}
		else
		{
			m_main_info.SetWindowTextW(str);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}



typedef struct _SmartAttriubtes //smart���Ը�ʽ
        {
            u_char attrib;
            u_char flags;
			u_char flags2;
            u_char value;
			u_char worst;
            u_char current;
            u_char current1;
            u_char current2;
            u_char current3;
            u_char current4;
            u_char current5;
            u_char current6;
        }SmartAttriubtes;
typedef struct _SmartInfo
{
	int Info_05;
	int Info_09;
	int Info_0C;
	int Info_AB;
	int Info_AC;
	int Info_AD;
	int Info_AE;
	int Info_BB;
	CString str;
}SmartInfo;
SmartInfo _getWmiInfo(IWbemClassObject *pClassObject, LPCTSTR lpszName)
{
	///////////////
	//SAFEARRAY *pvNames = NULL;
	//pClassObject->GetNames(NULL, WBEM_FLAG_ALWAYS | WBEM_MASK_CONDITION_ORIGIN, NULL, &pvNames);
	//////////////////
	SmartInfo returnInfo={-1,-1,-1,-1,-1,-1,-1,-1,L""};

    CComVariant varValue ;
	CComBSTR bstrName(lpszName);
 	CString str ;
	if( pClassObject->Get( bstrName , 0 , &varValue , NULL , 0 ) == S_OK )
	{		
		if( varValue.vt == VT_BSTR )	//�ַ���----��������
		{
			returnInfo.str = CString(varValue.bstrVal) ;
		}
		else 
		{
			BYTE *buf;

			SafeArrayAccessData(varValue.parray, (void **)&buf);
			SmartAttriubtes *smart_p;
			long iLowBound = 0 , iUpBound = 0 ;
			SafeArrayGetLBound( varValue.parray , 1 , &iLowBound ) ;
			SafeArrayGetUBound( varValue.parray , 1 , &iUpBound ) ;
			for(int i=iLowBound+2;i<=iUpBound;i+=sizeof(SmartAttriubtes))//������ʼ�����ֽڣ��汾�ţ�
			{ 
				smart_p = (SmartAttriubtes *)(buf+i);
				int current = (((int)smart_p->current3)<<24)+(((int)smart_p->current2)<<16)+(((int)smart_p->current1)<<8)+((int)smart_p->current);
				//cout<<(int)smart_p->attrib<<" "<<(int)smart_p->value<<" "<<(int)smart_p->worst<<" "<<current<<endl;
				switch((int)smart_p->attrib)
				{
					case 0x05:
						returnInfo.Info_05 = current;
						break;
					case 0x09:
						returnInfo.Info_09 = current;
						break;
					case 0x0C:
						returnInfo.Info_0C = current;
						break;
					case 0xAB:
						returnInfo.Info_AB = current;
						break;
					case 0xAC:
						returnInfo.Info_AC = current;
						break;
					case 0xAD:
						returnInfo.Info_AD = current;
						break;
					case 0xAE:
						returnInfo.Info_AE = current;
						break;
					case 0xBB:
						returnInfo.Info_BB = current;
						break;
					default:
						break;
				}
			}
			SafeArrayUnaccessData(varValue.parray);
		}
	}

	return returnInfo;
}

BOOL isSecurity = false;
SmartInfo GetSmartInfo( LPTSTR lpszClass, LPCTSTR lpszName)
{
	SmartInfo returnInfo={-1,-1,-1,-1,-1,-1,-1,-1,L""};
	// ��ʼ��COMģ��
	if (CoInitialize(NULL) != S_OK)
		return returnInfo;	

    // ��ȡ���� WMI Ȩ��

    if( CoInitializeSecurity( NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE,NULL, EOAC_NONE, 0 ) == S_OK || isSecurity)
	{
		// ͨ�� IWbemLocator �� IWbemServices ������ COM �ӿڷ��� WMI, ��ȡϵͳ��Ϣ
		isSecurity = true;
		CComPtr<IWbemLocator> spWbemLocator ;
		if( spWbemLocator.CoCreateInstance( CLSID_WbemAdministrativeLocator , 0 , CLSCTX_INPROC_SERVER| CLSCTX_LOCAL_SERVER ) == S_OK )
		{
			CComPtr<IWbemServices> spWbemServices ;
			CString strPath;
			if(wcscmp(lpszClass,L"Win32_DiskDrive")==0)
				strPath = L"root\\cimv2";
			else if(wcscmp(lpszClass,L"MSStorageDriver_FailurePredictData")==0)
				strPath = L"root\\wmi";
			BSTR path = strPath.AllocSysString();//BSTR
			if( spWbemLocator->ConnectServer( path , NULL, NULL, NULL, 0, NULL, NULL, &spWbemServices ) == S_OK )
			{
				// ����ָ����Ϣ

				USES_CONVERSION ;
				CComPtr<IEnumWbemClassObject> spEnumWbemClassObject ;
				CComBSTR bstrQuery ( L"Select * from " ) ;
				bstrQuery += T2OLE(lpszClass) ;
				if( spWbemServices->ExecQuery( L"WQL" , bstrQuery , WBEM_FLAG_RETURN_IMMEDIATELY , NULL, &spEnumWbemClassObject ) == S_OK )
				{
					ULONG uCount = 1, uReturned;
					CComPtr<IWbemClassObject> spClassObject ;
					if( spEnumWbemClassObject->Reset()  == S_OK )
					{
						int iEnumIdx = 0;
						if(spEnumWbemClassObject->Next( WBEM_INFINITE,uCount, &spClassObject, &uReturned) == S_OK )//������Ӳ��
						{
							spClassObject.Release();

							if/*while*/( spEnumWbemClassObject->Next( WBEM_INFINITE,uCount, &spClassObject, &uReturned) == S_OK )//�ڶ���Ӳ��
							{
								//SmartInfo tempInfo = _getWmiInfo( spClassObject, L"InterfaceType") ;
								//if(tempInfo.str != L"USB" )
								returnInfo = _getWmiInfo( spClassObject, lpszName) ;
								spClassObject.Release() ;
							}
						}
					}
				}
			}
			SysFreeString(path);
		}
	}

    CoUninitialize();

	return returnInfo;
}
BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ECInfo.SetWindowTextW(headerInfo);
	SmartInfo smartInfo;
	smartInfo = GetSmartInfo(L"Win32_DiskDrive", L"Model"/*L"PNPDeviceID"*/);
	if(smartInfo.str!=L"")
	{
		CString str;

		str = L"��ǰ���̽���״����";
		str+=smartInfo.str;
		str+=L"��";
		GetDlgItem(IDC_HEALTH_GROUP)->SetWindowTextW(str);
		smartInfo = GetSmartInfo(L"MSStorageDriver_FailurePredictData", L"VendorSpecific");	
		
		str.Format(L"%d",smartInfo.Info_05);
		GetDlgItem(IDC_HEALTH_05)->SetWindowTextW((smartInfo.Info_05==-1)?L"-":str);
		str.Format(L"%d",smartInfo.Info_09);
		GetDlgItem(IDC_HEALTH_09)->SetWindowTextW((smartInfo.Info_09==-1)?L"-":str);
		str.Format(L"%d",smartInfo.Info_0C);
		GetDlgItem(IDC_HEALTH_0C)->SetWindowTextW((smartInfo.Info_0C==-1)?L"-":str);
		str.Format(L"%d",smartInfo.Info_AB);
		GetDlgItem(IDC_HEALTH_AB)->SetWindowTextW((smartInfo.Info_AB==-1)?L"-":str);
		str.Format(L"%d",smartInfo.Info_AC);
		GetDlgItem(IDC_HEALTH_AC)->SetWindowTextW((smartInfo.Info_AC==-1)?L"-":str);
		str.Format(L"%d",smartInfo.Info_AD);
		GetDlgItem(IDC_HEALTH_AD)->SetWindowTextW((smartInfo.Info_AD==-1)?L"-":str);
		str.Format(L"%d",smartInfo.Info_AE);
		GetDlgItem(IDC_HEALTH_AE)->SetWindowTextW((smartInfo.Info_AE==-1)?L"-":str);
		str.Format(L"%d",smartInfo.Info_BB);
		GetDlgItem(IDC_HEALTH_BB)->SetWindowTextW((smartInfo.Info_BB==-1)?L"-":str);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CExpressCacheShowDlg::OnBnClickedCommand()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlgAbout;
	dlgAbout.headerInfo = headerInfo;
	dlgAbout.DoModal();
}


void CAboutDlg::OnBnClickedProcess()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL command1 = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	BOOL command2 = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	BOOL command3 = ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck();
	BOOL command4 = ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck();
	BOOL command5 = ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck();
	if(!command1&!command2&!command3&!command4&!command5)
	{
		MessageBox(L"�����ٹ�ѡһ�����",L"δ��ѡ�κ�����", MB_ICONEXCLAMATION );
		return;
	}
	if(command1 == BST_CHECKED)
	{
		//eccmd -PARTITION X: 1024
		CString par1,par2;
		GetDlgItem(IDC_EDIT3)->GetWindowTextW(par1);
		GetDlgItem(IDC_EDIT8)->GetWindowTextW(par2);

		_TCHAR par = par1.GetAt(0);
		CString command = L"/c eccmd -PARTITION ";
		command = command + par;
		command = command + L" ";
		command = command + par2;
		command = command + L" & pause";
		ShellExecute(NULL, L"open", L"cmd.exe",command , NULL, SW_SHOW);
		//MessageBox(command,0,0);
		
	}
	if(command2 == BST_CHECKED)
	{
		//eccmd -EXCLUDE X:
		CString partion;
		GetDlgItem(IDC_EDIT4)->GetWindowTextW(partion);
		if(partion == L"")
			MessageBox(L"�������̷���",L"���ٶ�ָ���̻���", MB_ICONEXCLAMATION );
		else
		{
			_TCHAR par = partion.GetAt(0);
			CString command = L"/c eccmd -EXCLUDE ";
			command = command + par;
			command = command + L": & pause";
			//MessageBox(command,0,0);
			ShellExecute(NULL, L"open", L"cmd.exe",command , NULL, SW_SHOW);
			//system("dir & pause");
		}
	}
	if(command3 == BST_CHECKED)
	{
		//eccmd -CLEAREXCLUSIONS
		CString command = L"/c eccmd -CLEAREXCLUSIONS & pause";

		ShellExecute(NULL, L"open", L"cmd.exe",command , NULL, SW_SHOW);
		//MessageBox(L"YES3",0,0);
	}
	if(command4 == BST_CHECKED)
	{
		//eccmd -FORMAT
		CString command = L"/c eccmd -FORMAT & pause";

		ShellExecute(NULL, L"open", L"cmd.exe",command , NULL, SW_SHOW);
		//MessageBox(L"YES4",0,0);
	}
	if(command5 == BST_CHECKED)
	{
		//eccmd -PRELOAD PATH USAGECOUNT
		CString par1,par2;
		GetDlgItem(IDC_EDIT7)->GetWindowTextW(par1);
		GetDlgItem(IDC_EDIT9)->GetWindowTextW(par2);
		if(par1 == L"")
			MessageBox(L"����������������",L"Ԥ�ȼ���ָ���ļ����ļ���", MB_ICONEXCLAMATION );
		else
		{
			CString command = L"/c eccmd -PRELOAD ";
			if(par1.GetAt(0)!='\"')
				command = command +L"\"";
			command = command + par1;
			if(par1.GetAt(par1.GetLength()-1)!='\"')
				command = command +L"\"";
			command = command + L" ";
			command = command + par2;
			command = command + L" & pause";
			ShellExecute(NULL, L"open", L"cmd.exe",command , NULL, SW_SHOW);
			//MessageBox(command,0,0);
		}
	}
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(false);
}
