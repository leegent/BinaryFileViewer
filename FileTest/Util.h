#pragma once
#include "stdafx.h"
#include<cstring>

class Util {
public:
	static CString Char2CString(char *c);
	static CString Double2CString(double d);
	static CString Int2CString(int n);
	static char *Int2Char(int n);
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
	CString getData();
};