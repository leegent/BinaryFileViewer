
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
	CFile files[10];
	bool hasOpened = false;
	int getIndex();

	int count;
	// 输入合约编号
	CEdit m_instrument;
	// 数据所在文件夹
	CComboBox m_folder;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_write;
	CStatic m_state;
	// 交易日期
	CEdit m_tradeDay;
	// 开盘价
	CEdit m_openPrice;
	// 收盘价
	CEdit m_closePrice;
	// 最高价
	CEdit m_highest;
	// 最低价
	CEdit m_lowest;
	// 成交量
	CEdit m_volume;
};
