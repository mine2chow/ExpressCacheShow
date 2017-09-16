
// ExpressCacheShowDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CExpressCacheShowDlg 对话框
class CExpressCacheShowDlg : public CDialogEx
{
private:
	BOOL GetInfo(CString &str);
	CString headerInfo;
// 构造
public:
	CExpressCacheShowDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXPRESSCACHESHOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
