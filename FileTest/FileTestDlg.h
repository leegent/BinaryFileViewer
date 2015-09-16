
// FileTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CFileTestDlg �Ի���
class CFileTestDlg : public CDialogEx
{
// ����
public:
	CFileTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILETEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedRead();
	CEdit m_edit;
	//�ļ���Ա����
	//Ѱ���ļ�
	CFileFind finder;
	//�ļ�����
	CFile files[10];
	bool hasOpened = false;
	int getIndex();

	int count;
	// �����Լ���
	CEdit m_instrument;
	// ���������ļ���
	CComboBox m_folder;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_write;
	CStatic m_state;
	// ��������
	CEdit m_tradeDay;
	// ���̼�
	CEdit m_openPrice;
	// ���̼�
	CEdit m_closePrice;
	// ��߼�
	CEdit m_highest;
	// ��ͼ�
	CEdit m_lowest;
	// �ɽ���
	CEdit m_volume;
};
