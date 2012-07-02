#include "histring.h"
#include <algorithm>
#include <sstream>

using namespace std;

const Jchar HiRTDB::HiStringData::s_null[] = {""};
const HiRTDB::HiString HiRTDB::HiString::null;
//HiRTDB::HiStringData* HiRTDB::HiString::shared_null = NULL;
const Juint32 HiRTDB::HiString::s_uNormalStringMaxLength = 256;
HiRTDB::HiStringData::HiStringData(void)
: m_pData(s_null), m_uLength(0), m_nCount(1)
{
}

HiRTDB::HiStringData::HiStringData(const Jchar* szData, Juint32 uLength)
: m_pData(s_null), m_uLength(0), m_nCount(1)
{
	if (szData)
	{
		m_uLength = uLength;
		if (m_uLength > 0)
		{
			Jchar* pData = new Jchar[m_uLength+1];
			strncpy(pData, szData, m_uLength);
			pData[m_uLength] = 0;
			m_pData = pData;
		}
	}
}

HiRTDB::HiStringData::HiStringData(Jchar* szData, Juint32 uLength, Jboolean bDeepCopy)
: m_pData(s_null), m_uLength(0), m_nCount(1)
{
	if (szData)
	{
		m_uLength = uLength;
		if (m_uLength > 0)
		{
			if (bDeepCopy)
			{
				Jchar* pData = new Jchar[m_uLength+1];
				strncpy(pData, szData, m_uLength);
				pData[m_uLength] = 0;
				m_pData = pData;
			}
			else
			{
				m_pData = szData;
			}
		}
	}
}

HiRTDB::HiStringData::HiStringData(const Jchar* szData1, Juint32 uLength1, const Jchar* szData2, Juint32 uLength2)
: m_pData(s_null), m_uLength(0), m_nCount(1)
{
	if (szData1)
	{
		m_uLength = uLength1;
	}
	if (szData2)
	{
		m_uLength += uLength2;
	}
	if (m_uLength > 0)
	{
		Jchar* pData = new Jchar[m_uLength+1];
		pData[0] = 0;
		if (szData1)
		{
			strncpy(pData, szData1, uLength1);
		}
		if (szData2)
		{
			strncpy(pData+uLength1, szData2, uLength2);
		}
		pData[m_uLength] = 0;
		m_pData = pData;
	}
}

HiRTDB::HiStringData::~HiStringData(void)
{
	if (m_pData != s_null)
	{
		delete[] m_pData;
	}
}

void HiRTDB::HiStringData::ref(void)
{
	IceUtil::Mutex::Lock lock(m_mutex);

	++ m_nCount;
}

void HiRTDB::HiStringData::deref(void)
{
	Jboolean bDeleteSelf = JFALSE;
	{
		IceUtil::Mutex::Lock lock(m_mutex);

		bDeleteSelf = !(--m_nCount);
	}
	// 最后一个引用被释放，删除自己
	if (bDeleteSelf)
	{
		delete this;
	}
}

Juint32 HiRTDB::HiStringData::length(void) const
{
	return m_uLength;
}

const Jchar* HiRTDB::HiStringData::getRef(void) const
{
	return m_pData;
}

int HiRTDB::HiStringData::compare(const HiStringData & right) const
{
	return strcmp(m_pData, right.m_pData);
}

int HiRTDB::HiStringData::compare(const Jchar* szData) const
{
	return strcmp(m_pData, szData);
}

int HiRTDB::HiStringData::compareNoCase(const HiStringData & right) const
{
	return strcmp(m_pData, right.m_pData);
}

int HiRTDB::HiStringData::compareNoCase(const Jchar* szData) const
{
	return strcmp(m_pData, szData);
}

// HiString

HiRTDB::HiString::HiString(void)
: m_pStringData(getSharedNull())
{
	// 空对象不用增加引用计数
	//dataRef();
}

HiRTDB::HiString::HiString(const HiString& right)
: m_pStringData(right.m_pStringData)
{
	// 复制已经存在的对象，引用计数 +1
	dataRef();
}

HiRTDB::HiString::HiString(const std::string& right)
: m_pStringData(NULL)
{
	setData(right.c_str());
}

HiRTDB::HiString::HiString(const Jchar* szData)
: m_pStringData(NULL)
{
	setData(szData);
}

HiRTDB::HiString::HiString(Jchar* szData, Jboolean bDeepCopy)
: m_pStringData(NULL)
{
	setDataDeepCopy(szData, bDeepCopy);
}

HiRTDB::HiString::~HiString(void)
{
	dataDeref();
}

HiRTDB::HiString& HiRTDB::HiString::operator=(const HiString& right)
{
	if (this != &right && m_pStringData != right.m_pStringData)
	{
		dataDeref();
		m_pStringData = right.m_pStringData;
		dataRef();
	}
	return *this;
}

HiRTDB::HiString& HiRTDB::HiString::operator=(const std::string& right)
{
	setData(right.c_str());
	return *this;
}

HiRTDB::HiString& HiRTDB::HiString::operator=(const Jchar* szData)
{
	setData(szData);
	return *this;
}

HiRTDB::HiString& HiRTDB::HiString::append(const HiString& right)
{
	appendData(right.m_pStringData->getRef(), right.m_pStringData->length());
	return *this;
}

HiRTDB::HiString& HiRTDB::HiString::append(const std::string& right)
{
	appendData(right.c_str());
	return *this;
}

HiRTDB::HiString& HiRTDB::HiString::append(const Jchar* szData)
{
	appendData(szData);
	return *this;
}

HiRTDB::HiString& HiRTDB::HiString::prepend(const HiString& right)
{
	prependData(right.m_pStringData->getRef(), right.m_pStringData->length());
	return *this;
}

HiRTDB::HiString& HiRTDB::HiString::prepend(const std::string& right)
{
	prependData(right.c_str());
	return *this;
}

HiRTDB::HiString& HiRTDB::HiString::prepend(const Jchar* szData)
{
	prependData(szData);
	return *this;
}

void HiRTDB::HiString::setData(const Jchar* szData)
{
	setData(szData, strlen(szData));
}

void HiRTDB::HiString::setData(const Jchar* szData, Juint32 uLength)
{
	if (szData != NULL && uLength > 0)
	{
		dataDeref();
		m_pStringData = new HiStringData(szData, uLength);
	}
	else
	{
		if (m_pStringData != getSharedNull())
		{
			dataDeref();
			m_pStringData = getSharedNull();
			// 空对象不用增加引用计数
			//dataRef();
		}
	}
}

void HiRTDB::HiString::setDataDeepCopy(Jchar* szData, Jboolean bDeepCopy)
{
	setDataDeepCopy(szData, strlen(szData), bDeepCopy);
}

void HiRTDB::HiString::setDataDeepCopy(Jchar* szData, Juint32 uLength, Jboolean bDeepCopy)
{
	if (szData != NULL && uLength > 0)
	{
		dataDeref();
		m_pStringData = new HiStringData(szData, uLength, bDeepCopy);
	}
	else
	{
		if (m_pStringData != getSharedNull())
		{
			dataDeref();
			m_pStringData = getSharedNull();
			// 空对象不用增加引用计数
			//dataRef();
		}
		if (szData != NULL && !bDeepCopy)
		{
			// 空字符串，删除外部申请的空间
			delete[] szData;
		}
	}
}

void HiRTDB::HiString::appendData(const Jchar* szData)
{
	appendData(szData, strlen(szData));
}

void HiRTDB::HiString::appendData(const Jchar* szData, Juint32 uLength)
{
	if (szData != NULL && uLength > 0)
	{
		HiStringData* pStringData = new HiStringData(m_pStringData->getRef(), m_pStringData->length(), szData, uLength);

		dataDeref();
		m_pStringData = pStringData;
	}
}

void HiRTDB::HiString::prependData(const Jchar* szData)
{
	prependData(szData, strlen(szData));
}

void HiRTDB::HiString::prependData(const Jchar* szData, Juint32 uLength)
{
	if (szData != NULL && uLength > 0)
	{
		HiStringData* pStringData = new HiStringData(szData, uLength, m_pStringData->getRef(), m_pStringData->length());

		dataDeref();
		m_pStringData = pStringData;
	}
}

HiRTDB::HiString::operator const Jchar*() const
{
	return m_pStringData->getRef();
}

const Jchar* HiRTDB::HiString::local8Bit(void) const
{
	return m_pStringData->getRef();
}

HiRTDB::HiString::operator std::string() const
{
	return std::string(m_pStringData->getRef());
}

std::string HiRTDB::HiString::toStdString(void) const
{
	return std::string(m_pStringData->getRef());
}

bool HiRTDB::HiString::isNull(void) const
{
	return (m_pStringData == getSharedNull());
}

bool HiRTDB::HiString::isEmpty(void) const
{
	return (m_pStringData->length() == 0);
}

Juint32 HiRTDB::HiString::length(void) const
{
	return m_pStringData->length();
}

bool HiRTDB::HiString::operator ==(const HiString& right) const
{
	return (m_pStringData->compare(*right.m_pStringData) == 0);
}

bool HiRTDB::HiString::operator ==(const Jchar* szData) const
{
	return (m_pStringData->compare(szData) == 0);
}

bool HiRTDB::HiString::operator !=(const HiString& right) const
{
	return !operator==(right);
}

bool HiRTDB::HiString::operator !=(const Jchar* szData) const
{
	return !operator==(szData);
}

bool HiRTDB::HiString::operator <(const HiString& right) const
{
	return (m_pStringData->compare(*right.m_pStringData) < 0);
}

bool HiRTDB::HiString::operator <(const Jchar* szData) const
{
	return (m_pStringData->compare(szData) < 0);
}

bool HiRTDB::HiString::operator <=(const HiString& right) const
{
	return !operator>(right);
}

bool HiRTDB::HiString::operator <=(const Jchar* szData) const
{
	return !operator>(szData);
}

bool HiRTDB::HiString::operator >(const HiString& right) const
{
	return (m_pStringData->compare(*right.m_pStringData) > 0);
}

bool HiRTDB::HiString::operator >(const Jchar* szData) const
{
	return (m_pStringData->compare(szData) > 0);
}

bool HiRTDB::HiString::operator >=(const HiString& right) const
{
	return !operator<(right);
}

bool HiRTDB::HiString::operator >=(const Jchar* szData) const
{
	return !operator<(szData);
}

int HiRTDB::HiString::compare(const HiString & right) const
{
	return m_pStringData->compare(*right.m_pStringData);
}

int HiRTDB::HiString::compare(const Jchar* szData) const
{
	return m_pStringData->compare(szData);
}

int HiRTDB::HiString::compareNoCase(const HiString & right) const
{
	return m_pStringData->compareNoCase(*right.m_pStringData);
}

int HiRTDB::HiString::compareNoCase(const Jchar* szData) const
{
	return m_pStringData->compareNoCase(szData);
}

HiRTDB::HiString HiRTDB::HiString::lower() const
{
	std::string str = toStdString();
	transform(str.begin(),str.end(),str.begin(),tolower);
	return HiString(str);
}

HiRTDB::HiString HiRTDB::HiString::upper() const
{
	std::string str = toStdString();
	transform(str.begin(),str.end(),str.begin(),toupper);
	return HiString(str);
}


template<class T>
T HiRTDB::HiString::toNumber(const std::string& str)
{
	stringstream ss;
	ss << str;
	T ret;
	ss >> ret;
	return ret;
}

template<class T>
T HiRTDB::HiString::toNumber(const char* str)
{
	stringstream ss;
	ss << str;
	T ret;
	ss >> ret;
	return ret;
}

int HiRTDB::HiString::toInt()
{
	return toNumber<int>(toStdString());
}

float HiRTDB::HiString::toFloat()
{
	return toNumber<float>(toStdString());
}

double HiRTDB::HiString::toDouble()
{
	return toNumber<double>(toStdString());
}

bool HiRTDB::HiString::toBool()
{
	int tmp = toNumber<int>(toStdString());
	return tmp == 0 ? false:true;
}

void HiRTDB::HiString::dataRef(void)
{
	// 如果是空对象，不用增加引用计数
	if (getSharedNull() != m_pStringData)
	{
		m_pStringData->ref();
	}
}

void HiRTDB::HiString::dataDeref(void)
{
	if (NULL != m_pStringData)
	{
		// 如果是空对象，不用减少引用计数
		if(getSharedNull() != m_pStringData)
		{
			m_pStringData->deref();
		}
		m_pStringData = NULL;
	}
}

HiRTDB::HiStringData* HiRTDB::HiString::makeSharedNull(void)
{
	// 这个对象的释放不是通过 deref() == 0 时释放
	static HiStringData data;
	//shared_null = &data;
	//return shared_null;
	return NULL;
}

template<class T>
HiRTDB::HiString HiRTDB::HiString::number(const T& value)
{
	std::string str;
	ostringstream ss;
	ss << value;
	ss >> str;
	return HiRTDB::HiString(str);
}


HiRTDB::HiString HiRTDB::operator+(const HiString& left, const HiString& right)
{
	HiString strRet = left;
	strRet.append(right);
	return strRet;
}

HiRTDB::HiString HiRTDB::operator+(const HiString& left, const std::string& right)
{
	HiString strRet = left;
	strRet.append(right);
	return strRet;
}

HiRTDB::HiString HiRTDB::operator+(const std::string& left, const HiString& right)
{
	HiString strRet = right;
	strRet.prepend(left);
	return strRet;
}

HiRTDB::HiString HiRTDB::operator+(const HiString& left, const Jchar* szData)
{
	HiString strRet = left;
	strRet.append(szData);
	return strRet;
}

HiRTDB::HiString HiRTDB::operator+(const Jchar* szData, const HiString& right)
{
	HiString strRet = right;
	strRet.prepend(szData);
	return strRet;
}
