
// FileTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileTest.h"
#include "FileTestDlg.h"
#include "afxdialogex.h"
#include "Util.h"
#include <vector>
using namespace std;

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
	DDX_Control(pDX, IDC_COMBO1, m_folder);
	DDX_Control(pDX, IDC_WRITE, m_write);
	DDX_Control(pDX, IDC_STATIC_STATE, m_state);
	DDX_Control(pDX, IDC_EDIT2, m_tradeDay);
	DDX_Control(pDX, IDC_EDIT3, m_openPrice);
	DDX_Control(pDX, IDC_EDIT4, m_closePrice);
	DDX_Control(pDX, IDC_EDIT5, m_highest);
	DDX_Control(pDX, IDC_EDIT6, m_lowest);
	DDX_Control(pDX, IDC_EDIT7, m_volume);
}

BEGIN_MESSAGE_MAP(CFileTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CFileTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_WRITE, &CFileTestDlg::OnBnClickedWrite)
	ON_BN_CLICKED(IDC_READ, &CFileTestDlg::OnBnClickedRead)
	ON_WM_TIMER()
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
	m_folder.AddString(_T("��ʱͼ"));
	m_folder.AddString(_T("1����K��"));
	m_folder.AddString(_T("��K��"));
	m_folder.AddString(_T("��ʱ��ʱͼ"));
	m_folder.AddString(_T("��ʱ1����K��"));	
	m_folder.AddString(_T("����"));
	m_folder.SetCurSel(0);
	//m_folder.SetWindowTextW(_T("��ʱͼ"));
	m_instrument.SetWindowTextW(_T("IF1509"));
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

int CFileTestDlg::getIndex()
{
	int index = 5;
	if (!hasOpened) files[index].Open(_T("data\\tmp\\test.dat"), CFile::modeReadWrite | CFile::modeCreate);
	return index;
}

void CFileTestDlg::OnBnClickedWrite()
{
	CString instrument,o,c,h,l,v;
	m_instrument.GetWindowTextW(instrument);
	CString filepath = _T("data\\kday\\");
	filepath.Append(instrument);
	filepath.Append(_T(".dat"));
	CFile file;
	KdObject kd;
	m_tradeDay.GetWindowTextW(kd.date);
	m_openPrice.GetWindowTextW(o);
	m_closePrice.GetWindowTextW(c);
	m_highest.GetWindowTextW(h);
	m_lowest.GetWindowTextW(l);
	m_volume.GetWindowTextW(v);
	kd.OpenPrice = Util::CString2Double(o);
	kd.ClosePrice = Util::CString2Double(c);
	kd.HighestPrice = Util::CString2Double(h);
	kd.LowestPrice = Util::CString2Double(l);
	kd.Volume = Util::CString2Int(v);
	file.Open(filepath, CFile::modeCreate |CFile::modeNoTruncate | CFile::modeWrite);
	file.SeekToEnd();
	CArchive ar(&file, CArchive::store);
	ar << &kd;
	ar.Close();
	file.Close();
	m_tradeDay.SetWindowTextW(_T(""));
	m_openPrice.SetWindowTextW(_T(""));
	m_closePrice.SetWindowTextW(_T(""));
	m_highest.SetWindowTextW(_T(""));
	m_lowest.SetWindowTextW(_T(""));
	m_volume.SetWindowTextW(_T(""));
}

void CFileTestDlg::OnBnClickedRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(FALSE);
	int sel = m_folder.GetCurSel();
	CString filepath = _T("data\\");
	CString ins;	
	m_instrument.GetWindowTextW(ins); 
	if (ins.IsEmpty()) return;
	if (sel == 0) {//��ʱͼ
		filepath.Append(_T("timeLine\\"));
		filepath.Append(ins);
		filepath.Append(_T(".dat"));
		BOOL bWorking = finder.FindFile(filepath);
		if (bWorking == false) return;
		files[0].Open(filepath, CFile::modeRead);
		CArchive ar(&files[0], CArchive::load);
		MarketObject *mo;
		CString cs("ʱ��,����,���¼�,�ֲ���,�ɽ���,��ʼ�ֲ�\r\n");
		while (1) {
			try {
				mo = (MarketObject *)ar.ReadObject(RUNTIME_CLASS(MarketObject));
			}
			catch (...) {
				break;
			}
			cs.Append(Util::Int2CString(mo->time));
			cs.Append(_T(","));
			cs.Append(Util::Double2CString(mo->averagePrice));
			cs.Append(_T(","));
			cs.Append(Util::Double2CString(mo->lastPrice));
			cs.Append(_T(","));
			cs.Append(Util::Int2CString(mo->position));
			cs.Append(_T(","));
			cs.Append(Util::Int2CString(mo->turnover));
			cs.Append(_T(","));
			cs.Append(Util::Int2CString(mo->openTurnover));
			cs.Append(_T("\r\n"));
		}
		m_edit.SetWindowTextW(cs);
		ar.Close();
		files[0].Close();
		finder.Close();
	}
	else if (sel == 1) {//1����K��
		filepath.Append(_T("k1min\\"));
		filepath.Append(ins);
		filepath.Append(_T(".dat"));
		BOOL bWorking = finder.FindFile(filepath);
		if (bWorking == false) return;
		files[0].Open(filepath, CFile::modeRead);
		CArchive ar(&files[0], CArchive::load);
		KObject *kd1;
		CString cs("ʱ��,���̼�,���̼�,��߼�,��ͼ�\r\n");
		while (1) {
			try {
				kd1 = (KObject*)ar.ReadObject(RUNTIME_CLASS(KObject));
			}
			catch (...) {
				break;
			}
			cs.Append(kd1->getData());
			cs.Append(_T("\r\n"));
		}
		m_edit.SetWindowTextW(cs);
		ar.Close();
		files[0].Close();
		finder.Close();
	}
	else if (sel == 2) {//��K��
		filepath.Append(_T("kday\\"));
		filepath.Append(ins);
		filepath.Append(_T(".dat"));
		BOOL bWorking = finder.FindFile(filepath);
		if (bWorking == false) return;
		files[0].Open(filepath, CFile::modeRead);
		CArchive ar(&files[0], CArchive::load);
		KdObject *kd;
		CString cs("����,���̼�,���̼�,��߼�,��ͼ�,�ɽ���\r\n");
		while (1) {
			try {
				kd = (KdObject*)ar.ReadObject(RUNTIME_CLASS(KdObject));
			}
			catch (...) {
				break;
			}
			cs.Append(getData(kd));
			cs.Append(_T("\r\n"));
		}
		m_edit.SetWindowTextW(cs);
		ar.Close();
		files[0].Close();
		finder.Close();
	}
	else if (sel == 3) {//��ʱ��ʱͼ
		filepath.Append(_T("tmp\\timeLine\\"));
		filepath.Append(ins);
		filepath.Append(_T(".dat"));
		BOOL bWorking = finder.FindFile(filepath);
		if (bWorking == false) return;
		files[0].Open(filepath, CFile::modeRead);
		CArchive ar(&files[0], CArchive::load);
		MarketObject *mo;
		CString cs("ʱ��,����,���¼�,�ɽ���,�ֲ���,��ʼ�ɽ�\r\n");
		while (1) {
			try {
				mo = (MarketObject *)ar.ReadObject(RUNTIME_CLASS(MarketObject));
			}
			catch (...) {
				break;
			}
			cs.Append(Util::Int2CString(mo->time));
			cs.Append(_T(","));
			cs.Append(Util::Double2CString(mo->averagePrice));
			cs.Append(_T(","));
			cs.Append(Util::Double2CString(mo->lastPrice));
			cs.Append(_T(","));
			cs.Append(Util::Int2CString(mo->position));
			cs.Append(_T(","));
			cs.Append(Util::Int2CString(mo->turnover));
			cs.Append(_T(","));
			cs.Append(Util::Int2CString(mo->openTurnover));
			cs.Append(_T("\r\n"));
		}
		m_edit.SetWindowTextW(cs);
		ar.Close();
		files[0].Close();
		finder.Close();
	}
	else if (sel == 4) {//��ʱ1����K��
	}
	else if (sel == 5) {//����
		filepath.Append(_T("tmp\\snapshot\\"));
		filepath.Append(ins);
		filepath.Append(_T(".dat"));
		BOOL bWorking = finder.FindFile(filepath);
		if (bWorking == false) return;
		files[0].Open(filepath, CFile::modeRead);
		CArchive ar(&files[0], CArchive::load);
		CString instrument;
		CUstpFtdcDepthMarketDataField market;
		/*
		ar >> instrument >> market.LastPrice >> market.PreClosePrice
			>> market.AskPrice1 >> market.AskVolume1
			>> market.BidPrice1 >> market.BidVolume1
			>> market.Volume >> market.OpenInterest
			>> market.UpperLimitPrice >> market.LowerLimitPrice
			>> market.OpenPrice >> market.HighestPrice
			>> market.LowestPrice;
		CString showData = _T("��Լ ���¼� ������ ��һ�� ��һ�� ��һ�� ��һ�� �ɽ��� �ֲ� ��ͣ�� ��ͣ�� ���̼� ��߼� ��ͼ�\r\n");
		showData.Append(instrument);
		showData.Append(_T(" "));
		showData.Append(Util::Double2CString(market.LastPrice));
		showData.Append(_T(" "));
		showData.Append(Util::Double2CString(market.PreClosePrice));
		showData.Append(_T(" "));
		showData.Append(Util::Double2CString(market.AskPrice1));
		showData.Append(_T(" "));
		showData.Append(Util::Int2CString(market.AskVolume1));
		showData.Append(_T(" "));
		showData.Append(Util::Double2CString(market.BidPrice1));
		showData.Append(_T(" "));
		showData.Append(Util::Int2CString(market.BidVolume1));
		showData.Append(_T(" "));
		showData.Append(Util::Int2CString(market.Volume));
		showData.Append(_T(" "));
		showData.Append(Util::Int2CString(market.OpenInterest));
		showData.Append(_T(" "));
		showData.Append(Util::Double2CString(market.UpperLimitPrice));
		showData.Append(_T(" "));
		showData.Append(Util::Double2CString(market.LowerLimitPrice));
		showData.Append(_T(" "));
		showData.Append(Util::Double2CString(market.OpenPrice));
		showData.Append(_T(" "));
		showData.Append(Util::Double2CString(market.HighestPrice));
		showData.Append(_T(" "));
		showData.Append(Util::Double2CString(market.LowestPrice));
		
		m_edit.SetWindowTextW(showData);*/
		ar.Close();
		files[0].Close();
		finder.Close();
	}	
}



void CFileTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MessageBox(_T("3��"));
	//CDialogEx::OnTimer(nIDEvent);
}
