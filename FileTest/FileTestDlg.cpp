
// FileTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileTest.h"
#include "FileTestDlg.h"
#include "afxdialogex.h"
#include "Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileTestDlg �Ի���



CFileTestDlg::CFileTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILETEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_edit);
	DDX_Control(pDX, IDC_EDIT1, m_instrument);
}

BEGIN_MESSAGE_MAP(CFileTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CFileTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_WRITE, &CFileTestDlg::OnBnClickedWrite)
	ON_BN_CLICKED(IDC_READ, &CFileTestDlg::OnBnClickedRead)
END_MESSAGE_MAP()


// CFileTestDlg ��Ϣ�������

BOOL CFileTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	count = 1;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFileTestDlg::OnPaint()
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
HCURSOR CFileTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFileTestDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	exit(0);
}


void CFileTestDlg::OnBnClickedWrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	KObject kd1,kd2;
	kd1.num = count++;
	kd1.maxPrice = 3100.2 + count;
	kd1.floorPrice = 2991.5 + count;
	kd2.num = count++;
	kd2.maxPrice = 3100.2 + count;
	kd2.floorPrice = 2991.5 + count;
	BOOL bWorking = finder.FindFile(_T("..\\data\\IF1509.dat"));
	if (bWorking == false) 	//û�ҵ����򴴽������ǣ�һ��ͬ���ļ�
		file.Open(_T("..\\data\\IF1509.dat"), CFile::modeCreate | CFile::modeWrite);
	else //���򰴷Ǹ�дģʽ��
	{
		file.Open(_T("..\\data\\IF1509.dat"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite );
		file.SeekToEnd();
	}
	CArchive ar(&file, CArchive::store);
	ar << &kd1<<&kd2;
	ar.Close();
	file.Close();*/
}

void CFileTestDlg::OnBnClickedRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString filepath = _T("data\\k1min\\");
	CString ins;
	UpdateData(FALSE);
	m_instrument.GetWindowTextW(ins);
	if (ins.IsEmpty()) return;
	filepath.Append(ins);
	filepath.Append(_T(".dat"));
	BOOL bWorking = finder.FindFile(filepath);
	if (bWorking == false) return;
	file.Open(filepath, CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	KObject *kd1;
	CString cs("");	
	while (1) {
		try {
			kd1 = (KObject*)ar.ReadObject(RUNTIME_CLASS(KObject));
		}
		catch (...) {
			break;
		}
		cs.Append( kd1->getData());
		cs.Append(_T("\r\n"));		
	}
	m_edit.SetWindowTextW(cs);
	ar.Close();
	file.Close();
}