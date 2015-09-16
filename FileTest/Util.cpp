#include "stdafx.h"
#include "Util.h"

char * Util::CString2Char(CString cs) {
	int len = WideCharToMultiByte(CP_ACP, 0, cs, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, cs, -1, ptxtTemp, len, NULL, NULL);
	return ptxtTemp;
}

char Util::CString2SingleChar(CString cs)
{
	return CString2Char(cs)[0];
}

CString Util::Char2CString(char * c)
{
	CString cs = (CString)c;
	return cs;
}

CString Util::Double2CString(double d)
{
	CString cs;
	cs.Format(_T("%.1lf"), d);
	return cs;
}

CString Util::Int2CString(int n)
{
	char *c = Int2Char(n);
	return Char2CString(c);
}

char * Util::Int2Char(int n)
{
	char *p = new char[100];
	return _itoa(n, p, 10);
}

double Util::CString2Double(CString cs)
{
	return atof(Util::CString2Char(cs));
}

int Util::CString2Int(CString cs)
{
	char *c = CString2Char(cs);
	return atoi(c);
}


//保存交易数据的类，序列化函数实现
IMPLEMENT_SERIAL(KObject, CObject, 1)
void KObject::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		ar << this->time << this->openPrice << this->closePrice << this->maxPrice << this->floorPrice;
	}
	else
	{
		ar >> this->time >> this->openPrice >> this->closePrice >> this->maxPrice >> this->floorPrice;
	}
}

CString KObject::getData()
{
	CString data= Util::Int2CString(time);
	data.Append(_T(","));
	data.Append(Util::Double2CString(openPrice));
	data.Append(_T(","));
	data.Append(Util::Double2CString(closePrice));
	data.Append(_T(","));
	data.Append(Util::Double2CString(maxPrice));
	data.Append(_T(","));
	data.Append(Util::Double2CString(floorPrice));
	return data;
}

//日K线数据序列化
IMPLEMENT_SERIAL(KdObject, CObject, 1)
void KdObject::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		ar << this->date << this->OpenPrice << this->ClosePrice << this->HighestPrice << this->LowestPrice <<this->Volume;
	}
	else
	{
		ar >> this->date >> this->OpenPrice >> this->ClosePrice >> this->HighestPrice >> this->LowestPrice >> this->Volume;
	}
}
CString getData(KdObject *kd)
{
	CString data = kd->date;
	data.Append(_T(","));
	data.Append(Util::Double2CString(kd->OpenPrice));
	data.Append(_T(","));
	data.Append(Util::Double2CString(kd->ClosePrice));
	data.Append(_T(","));
	data.Append(Util::Double2CString(kd->HighestPrice));
	data.Append(_T(","));
	data.Append(Util::Double2CString(kd->LowestPrice));
	data.Append(_T(","));
	data.Append(Util::Int2CString(kd->Volume));
	return data;
}

//分时图数据序列化
IMPLEMENT_SERIAL(MarketObject, CObject, 1)
void MarketObject::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		ar << this->time << this->averagePrice << this->lastPrice << this->position << this->turnover << this->openTurnover;
	}
	else
	{
		ar >> this->time >> this->averagePrice >> this->lastPrice >> this->position >> this->turnover >> this->openTurnover;
	}
}