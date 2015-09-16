
// FileTestDlg.cpp : 实现文件
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


// CFileTestDlg 消息处理程序

BOOL CFileTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_folder.AddString(_T("分时图"));
	m_folder.AddString(_T("1分钟K线"));
	m_folder.AddString(_T("日K线"));
	m_folder.AddString(_T("临时分时图"));
	m_folder.AddString(_T("临时1分钟K线"));	
	m_folder.AddString(_T("快照"));
	m_folder.SetCurSel(0);
	//m_folder.SetWindowTextW(_T("分时图"));
	m_instrument.SetWindowTextW(_T("IF1509"));
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(FALSE);
	int sel = m_folder.GetCurSel();
	CString filepath = _T("data\\");
	CString ins;	
	m_instrument.GetWindowTextW(ins); 
	if (ins.IsEmpty()) return;
	if (sel == 0) {//分时图
		filepath.Append(_T("timeLine\\"));
		filepath.Append(ins);
		filepath.Append(_T(".dat"));
		BOOL bWorking = finder.FindFile(filepath);
		if (bWorking == false) return;
		files[0].Open(filepath, CFile::modeRead);
		CArchive ar(&files[0], CArchive::load);
		MarketObject *mo;
		CString cs("时间,均价,最新价,持仓量,成交量,起始持仓\r\n");
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
	else if (sel == 1) {//1分钟K线
		filepath.Append(_T("k1min\\"));
		filepath.Append(ins);
		filepath.Append(_T(".dat"));
		BOOL bWorking = finder.FindFile(filepath);
		if (bWorking == false) return;
		files[0].Open(filepath, CFile::modeRead);
		CArchive ar(&files[0], CArchive::load);
		KObject *kd1;
		CString cs("时间,开盘价,收盘价,最高价,最低价\r\n");
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
	else if (sel == 2) {//日K线
		filepath.Append(_T("kday\\"));
		filepath.Append(ins);
		filepath.Append(_T(".dat"));
		BOOL bWorking = finder.FindFile(filepath);
		if (bWorking == false) return;
		files[0].Open(filepath, CFile::modeRead);
		CArchive ar(&files[0], CArchive::load);
		KdObject *kd;
		CString cs("日期,开盘价,收盘价,最高价,最低价,成交量\r\n");
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
	else if (sel == 3) {//临时分时图
		filepath.Append(_T("tmp\\timeLine\\"));
		filepath.Append(ins);
		filepath.Append(_T(".dat"));
		BOOL bWorking = finder.FindFile(filepath);
		if (bWorking == false) return;
		files[0].Open(filepath, CFile::modeRead);
		CArchive ar(&files[0], CArchive::load);
		MarketObject *mo;
		CString cs("时间,均价,最新价,成交量,持仓量,起始成交\r\n");
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
	else if (sel == 4) {//临时1分钟K线
	}
	else if (sel == 5) {//快照
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
		CString showData = _T("合约 最新价 昨收盘 买一价 买一量 卖一价 卖一量 成交量 持仓 涨停价 跌停价 开盘价 最高价 最低价\r\n");
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MessageBox(_T("3秒"));
	//CDialogEx::OnTimer(nIDEvent);
}
