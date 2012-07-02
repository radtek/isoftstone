#ifndef _HiSTRING_H_
#define _HiSTRING_H_

#include "icecore.h"
#include "iestypedef.h"
#include <map>
#include <functional>
#include <Ice/Ice.h>

namespace HiRTDB {

class HiString;

// �ַ�������ֻ�ڹ��캯������
// �̰߳�ȫ��ֻ�� ref()/deref() �̱߳���
class LIB_ICECORE_EXPORT HiStringData
{
	// Ϊ�� HiString::makeSharedNull() �ڲ��ܹ�������̬����
	friend class HiString;

public:
	HiStringData(void);
	HiStringData(const Jchar* szData, Juint32 uLength);

	HiStringData(Jchar* szData, Juint32 uLength, Jboolean bDeepCopy);
	// �ַ�ƴ��
	HiStringData(const Jchar* szData1, Juint32 uLength1, const Jchar* szData2, Juint32 nLength2);

	void ref(void);
	void deref(void);

	Juint32 length(void) const;
	const Jchar* getRef(void) const;

	// ��Сд���бȽ�
	int compare(const HiStringData & right) const;
	int compare(const Jchar* szData) const;
	int compareNoCase(const HiStringData & right) const;
	int compareNoCase(const Jchar* szData) const;

private:
	~HiStringData(void);

	HiStringData( const HiStringData& );
	HiStringData& operator=( const HiStringData& );

	mutable IceUtil::Mutex m_mutex;

	const Jchar* m_pData;
	Juint32 m_uLength;

	// ���ü���
	Juint32 m_nCount;

	// ���ַ���ʱ��m_pData �̶�ָ�� s_null
	static const Jchar s_null[1];

};

// �ַ���
// ʹ����ʽ����
// ����̷߳���ͬһ���ַ������󣬲����̰߳�ȫ
class LIB_ICECORE_EXPORT HiString
{
public:
	HiString(void);
	~HiString(void);

	HiString(const HiString& right);
	HiString(const std::string& right);
	// �˴�����ı����� local8Bit ����
	HiString(const Jchar* szData);
	// bDeepCopy=JTRUE���� szData �ַ����Ƿ�������
	// bDeepCopy=JFALSE��ֱ�� HiStringData::m_pData=szData���ⲿ��֤ szData �� new[]���ɱ��ฺ�� delete[]
	HiString(Jchar* szData, Jboolean bDeepCopy);

	static const HiString null;

	HiString& operator=(const HiString& right);
	HiString& operator=(const std::string& right);
	HiString& operator=(const Jchar* szData);

	HiString& operator+=(const HiString& right)
	{
		return append(right);
	};
	HiString& operator+=(const std::string& right)
	{
		return append(right);
	};
	HiString& operator+=(const Jchar* szData)
	{
		return append(szData);
	};
	HiString& append(const HiString& right);
	HiString& append(const std::string& right);
	HiString& append(const Jchar* szData);
	HiString& prepend(const HiString& right);
	HiString& prepend(const std::string& right);
	HiString& prepend(const Jchar* szData);

	operator const Jchar*() const;
	const Jchar* local8Bit(void) const;
	operator std::string() const;
	std::string toStdString(void) const;

	bool isNull(void) const;
	bool isEmpty(void) const;
	Juint32 length(void) const;

	bool operator ==(const HiString& right) const;
	bool operator ==(const Jchar* szData) const;
	bool operator !=(const HiString& right) const;
	bool operator !=(const Jchar* szData) const;
	bool operator <(const HiString& right) const;
	bool operator <(const Jchar* szData) const;
	bool operator <=(const HiString& right) const;
	bool operator <=(const Jchar* szData) const;
	bool operator >(const HiString& right) const;
	bool operator >(const Jchar* szData) const;
	bool operator >=(const HiString& right) const;
	bool operator >=(const Jchar* szData) const;

	// ��Сд���бȽ�
	int compare(const HiString & right) const;
	int compare(const Jchar* szData) const;
	int compareNoCase(const HiString & right) const;
	int compareNoCase(const Jchar* szData) const;

	HiString lower(void) const;
	HiString upper(void) const;

	template<class T>
	T toNumber(const std::string& str);

	template<class T>
	T toNumber(const char* str);

	int toInt();

	float toFloat();

	double toDouble();

	bool toBool();

	template<class T>
	static HiString number(const T& value);

	template <class T>
	static std::string toString(T value)
	{
		std::string str;
		std::stringstream ss;
		ss << value;
		str = ss.str();
		return str;
	}

private:
	// ��������
	void setData(const Jchar* szData);
	void setData(const Jchar* szData, Juint32 uLength);
	void setDataDeepCopy(Jchar* szData, Jboolean bDeepCopy);
	void setDataDeepCopy(Jchar* szData, Juint32 uLength, Jboolean bDeepCopy);
	void appendData(const Jchar* szData);
	void appendData(const Jchar* szData, Juint32 uLength);
	void prependData(const Jchar* szData);
	void prependData(const Jchar* szData, Juint32 uLength);

	void dataRef(void);
	void dataDeref(void);

	//static HiStringData* shared_null;
	static HiStringData* getSharedNull(void)
	{
		//return shared_null ? shared_null : makeSharedNull();
		return NULL;
	};
	static HiStringData* makeSharedNull(void);

	// ��������£��ַ�����󳤶�
	static const Juint32 s_uNormalStringMaxLength;

	HiStringData* m_pStringData;

	friend LIB_ICECORE_EXPORT HiString operator+(const HiString& left, const HiString& right);
	friend LIB_ICECORE_EXPORT HiString operator+(const HiString& left, const std::string& right);
	friend LIB_ICECORE_EXPORT HiString operator+(const std::string& left, const HiString& right);
	friend LIB_ICECORE_EXPORT HiString operator+(const HiString& left, const Jchar* szData);
	friend LIB_ICECORE_EXPORT HiString operator+(const Jchar* szData, const HiString& right);
};

LIB_ICECORE_EXPORT HiString operator+(const HiString& left, const HiString& right);
LIB_ICECORE_EXPORT HiString operator+(const HiString& left, const std::string& right);
LIB_ICECORE_EXPORT HiString operator+(const std::string& left, const HiString& right);
LIB_ICECORE_EXPORT HiString operator+(const HiString& left, const Jchar* szData);
LIB_ICECORE_EXPORT HiString operator+(const Jchar* szData, const HiString& right);



// ��Сд�����бȽ�
struct lessNoCase_HiString : public std::binary_function<HiString, HiString, bool>
{
	bool operator()(const HiString& left, const HiString& right) const
	{
		return (left.compareNoCase(right) < 0);
	}
};

// ��Сд�����бȽ�
struct lessNoCase_String : public std::binary_function<const Jchar*, const Jchar*, bool>
{
	//##ModelId=41D4AEAC02CF
	bool operator()(const Jchar* left, const Jchar* right) const
	{
		return (strcmp(left, right) < 0);
	}
};

// ��Сд���бȽ�
struct less_String : public std::binary_function<const Jchar*, const Jchar*, bool>
{
	//##ModelId=40D03FFC0354
	bool operator()(const Jchar* left, const Jchar* right) const
	{
		return (strcmp(left, right) < 0);
	}
};


} // namespace escore

#endif // _HiSTRING_H_
