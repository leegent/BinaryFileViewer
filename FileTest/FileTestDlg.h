
// FileTestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CFileTestDlg 对话框
class CFileTestDlg : public CDialogEx
{
// 构造
public:
	CFileTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILETEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedRead();
	CEdit m_edit;
	//文件成员变量
	//寻找文件
	CFileFind finder;
	//文件对象
	CFile file;
	//是否已经登录
	bool hasLogined;
	bool checkLogin(CString today);

	int count;
	// 输入合约编号
	CEdit m_instrument;
};
