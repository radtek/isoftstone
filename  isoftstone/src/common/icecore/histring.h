#ifndef _HiSTRING_H_
#define _HiSTRING_H_

#include "icecore.h"
#include "iestypedef.h"
#include <map>
#include <functional>
#include <Ice/Ice.h>

namespace HiRTDB {

class HiString;

// 字符串内容只在构造函数传入
// 线程安全，只在 ref()/deref() 线程保护
class LIB_ICECORE_EXPORT HiStringData
{
	// 为了 HiString::makeSharedNull() 内部能够声明静态对象
	friend class HiString;

public:
	HiStringData(void);
	HiStringData(const Jchar* szData, Juint32 uLength);

	HiStringData(Jchar* szData, Juint32 uLength, Jboolean bDeepCopy);
	// 字符拼接
	HiStringData(const Jchar* szData1, Juint32 uLength1, const Jchar* szData2, Juint32 nLength2);

	void ref(void);
	void deref(void);

	Juint32 length(void) const;
	const Jchar* getRef(void) const;

	// 大小写敏感比较
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

	// 引用计数
	Juint32 m_nCount;

	// 空字符串时，m_pData 固定指向 s_null
	static const Jchar s_null[1];

};

// 字符串
// 使用隐式共享
// 多个线程访问同一个字符串对象，不是线程安全
class LIB_ICECORE_EXPORT HiString
{
public:
	HiString(void);
	~HiString(void);

	HiString(const HiString& right);
	HiString(const std::string& right);
	// 此处传入的必须是 local8Bit 类型
	HiString(const Jchar* szData);
	// bDeepCopy=JTRUE，对 szData 字符串是否进行深拷贝
	// bDeepCopy=JFALSE，直接 HiStringData::m_pData=szData，外部保证 szData 是 new[]，由本类负责 delete[]
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

	// 大小写敏感比较
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
	// 设置数据
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

	// 正常情况下，字符串最大长度
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



// 大小写不敏感比较
struct lessNoCase_HiString : public std::binary_function<HiString, HiString, bool>
{
	bool operator()(const HiString& left, const HiString& right) const
	{
		return (left.compareNoCase(right) < 0);
	}
};

// 大小写不敏感比较
struct lessNoCase_String : public std::binary_function<const Jchar*, const Jchar*, bool>
{
	//##ModelId=41D4AEAC02CF
	bool operator()(const Jchar* left, const Jchar* right) const
	{
		return (strcmp(left, right) < 0);
	}
};

// 大小写敏感比较
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
