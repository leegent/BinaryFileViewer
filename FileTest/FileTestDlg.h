
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
	CFile file;
	//�Ƿ��Ѿ���¼
	bool hasLogined;
	bool checkLogin(CString today);

	int count;
	// �����Լ���
	CEdit m_instrument;
};
