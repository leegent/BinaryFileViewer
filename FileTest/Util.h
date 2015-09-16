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
	//���л�����
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
	//���л�����
	virtual void Serialize(CArchive& ar);
};

class MarketObject :public CObject
{
	DECLARE_SERIAL(MarketObject)
public:
	//ʱ��
	int time;
	//���ۣ����쿪������ʱ���гɽ��ܽ����Գɽ��ܹ����õ���ƽ����
	double averagePrice;
	//��ʱ�ۣ�ÿ���ӵ����һ�ʳɽ���
	double lastPrice;
	//�ֲ���
	int position;
	//�ɽ���:��һ�����ڵĳɽ���
	int turnover;
	//��һ���ӿ�ʼʱ�ĳɽ���
	int openTurnover;
	//���л�����
	virtual void Serialize(CArchive& ar);
};

CString getData(KdObject *kd);