#include "stdafx.h"
#include "Util.h"

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

CString MarketObject::getData()
{
	CString data = Util::Int2CString(time);
	data.Append(_T(","));
	data.Append(Util::Double2CString(averagePrice));
	data.Append(_T(","));
	data.Append(Util::Double2CString(lastPrice));
	data.Append(_T(","));
	data.Append(Util::Int2CString(position));
	data.Append(_T(","));
	data.Append(Util::Int2CString(turnover));
	data.Append(_T(","));
	data.Append(Util::Int2CString(openTurnover));
	return data;
}
