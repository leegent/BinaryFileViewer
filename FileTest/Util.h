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
	//ÐòÁÐ»¯º¯Êý
	virtual void Serialize(CArchive& ar);
	CString getData();
};