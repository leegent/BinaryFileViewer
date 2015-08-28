
// FileTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileTest.h"
#include "FileTestDlg.h"
#include "afxdialogex.h"
#include "Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileTestDlg 对话框



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


// CFileTestDlg 消息处理程序

BOOL CFileTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	count = 1;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFileTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFileTestDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	exit(0);
}


void CFileTestDlg::OnBnClickedWrite()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	KObject kd1,kd2;
	kd1.num = count++;
	kd1.maxPrice = 3100.2 + count;
	kd1.floorPrice = 2991.5 + count;
	kd2.num = count++;
	kd2.maxPrice = 3100.2 + count;
	kd2.floorPrice = 2991.5 + count;
	BOOL bWorking = finder.FindFile(_T("..\\data\\IF1509.dat"));
	if (bWorking == false) 	//没找到，则创建（覆盖）一个同名文件
		file.Open(_T("..\\data\\IF1509.dat"), CFile::modeCreate | CFile::modeWrite);
	else //否则按非覆写模式打开
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
	// TODO: 在此添加控件通知处理程序代码
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