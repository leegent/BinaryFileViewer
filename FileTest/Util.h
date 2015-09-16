#pragma once
#include "stdafx.h"
#include "USTPFtdcUserApiStruct.h"
#include<cstring>

class Util {
public:
	static CString Char2CString(char *c);
	static CString Double2CString(double d);
	static CString Int2CString(int n);
	static char *Int2Char(int n);
	static double CString2Double(CString cs);
	static int CString2Int(CString cs);
	static char *CString2Char(CString cs);
	static char CString2SingleChar(CString cs);
};

class KObject :public CObject
{
	DECLARE_SERIAL(KObject)
public:
	int time;
	double openPrice;
	double closePrice;
	double maxPrice;
	double floorPrice;
	//序列化函数
	virtual void Serialize(CArchive& ar);
	CString getData();
};

class KdObject :public CObject
{
	DECLARE_SERIAL(KdObject)
public:
	CString date;
	double OpenPrice;
	double ClosePrice;
	double HighestPrice;
	double LowestPrice;
	int Volume;
	//序列化函数
	virtual void Serialize(CArchive& ar);
};

class MarketObject :public CObject
{
	DECLARE_SERIAL(MarketObject)
public:
	//时间
	int time;
	//均价：当天开盘至当时所有成交总金额除以成交总股数得到的平均价
	double averagePrice;
	//分时价：每分钟的最后一笔成交价
	double lastPrice;
	//持仓量
	int position;
	//成交量:这一分钟内的成交量
	int turnover;
	//这一分钟开始时的成交量
	int openTurnover;
	//序列化函数
	virtual void Serialize(CArchive& ar);
};

CString getData(KdObject *kd);