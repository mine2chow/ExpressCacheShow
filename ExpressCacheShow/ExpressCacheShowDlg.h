
// ExpressCacheShowDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CExpressCacheShowDlg �Ի���
class CExpressCacheShowDlg : public CDialogEx
{
private:
	BOOL GetInfo(CString &str);
	CString headerInfo;
// ����
public:
	CExpressCacheShowDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXPRESSCACHESHOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_main_info;
	CProgressCtrl m_readP;
	CProgressCtrl m_writeP;
	CStatic m_readValue;
	CStatic m_writeValue;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
friend unsigned __stdcall Fresh(void * pParam);
afx_msg void OnBnClickedCommand();
};
