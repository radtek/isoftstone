
#ifndef _VARIANT_H
#define _VARIANT_H


#include <Ice/Config.h>
#include <Ice/Ice.h>
#include <Ice/Stream.h>
#include "LcshUtil.h"


using namespace Ice;


struct HiBinary	//二进制串
{
	void*	   m_pBinary;
	Ice::Int   m_nBinaryLength;
};

inline bool assign(char*& left,const char* right);
inline bool assign(LCSH::Time& left,const LCSH::Time& right);

template<class T>
inline bool assign(HiBinary& left,const HiBinary& right);

template<class T>
inline bool assign(HiBinary& left,const std::vector<T>& right);

#define OperatorCompare(ret,v,oper) \
{ \
	switch( type() ) \
	{ \
	case LCSH::EnumDataTypeBool :		ret = toBool() oper v.toBool();		break; \
	case LCSH::EnumDataTypeByte :		ret = toByte() oper v.toByte();		break; \
	case LCSH::EnumDataTypeShort :	ret = toShort() oper v.toShort();	break; \
	case LCSH::EnumDataTypeInt :		ret = toInt() oper v.toInt();		break; \
	case LCSH::EnumDataTypeLong :		ret = toLong() oper v.toLong();		break; \
	case LCSH::EnumDataTypeFloat :	ret = toFloat() oper v.toFloat();	break; \
	case LCSH::EnumDataTypeDouble :	ret = toDouble() oper v.toDouble();	break; \
	case LCSH::EnumDataTypeString :	ret = toString() oper v.toString();	break; \
	default: break;	 \
	} \
}

#define VectorConstructor(enumType,vecSeq) \
{ \
	clear(); \
	m_byDataType = enumType; \
	assign( m_binaryValue ,vecSeq); \
	return *this; \
}


class HiVariant
{
public:


private:
	LCSH::EDataType  m_byDataType;

	union
	{
		bool m_boolValue;
		Byte m_byteValue;
		Short m_shortValue;
		Int m_intValue;
		Long m_longValue;
		Float m_flatValue;
		Double m_doubleValue;
		
		char*  m_stringValue;
		LCSH::Time m_timeValue;
		HiBinary  m_binaryValue;
	};

public:

	// 构造方法

	HiVariant();
	~HiVariant();
	HiVariant(const HiVariant& v);
	explicit HiVariant(const bool& v);	
	explicit HiVariant(const Ice::Byte& v);
	explicit HiVariant(const Ice::Short& v);
	explicit HiVariant(const Ice::Int& v);
	explicit HiVariant(const Ice::Float& v);
	explicit HiVariant(const Ice::Long& v);
	explicit HiVariant(const Ice::Double& v);
	explicit HiVariant(const char* v);
	explicit HiVariant(const std::string& v);
	explicit HiVariant(const LCSH::Time& v);

	template<class T>
	HiVariant(const std::vector< T >& v)
	{
		*this = v;
	}

public:

	// 复制操作

	HiVariant& operator=(const HiVariant& v) ;
	HiVariant& operator=(const bool& v) ;
	HiVariant& operator=(const Ice::Byte& v);
	HiVariant& operator=(const Ice::Short& v);
	HiVariant& operator=(const Ice::Int& v);
	HiVariant& operator=(const Ice::Float& v);
	HiVariant& operator=(const Ice::Long& v);
	HiVariant& operator=(const Ice::Double& v);
	HiVariant& operator=(const char* v);
	HiVariant& operator=(const std::string& v);
	HiVariant& operator=(const LCSH::Time v);

	HiVariant& operator=(const std::vector< bool >& v);
	HiVariant& operator=(const std::vector< Byte >& v);
	HiVariant& operator=(const std::vector< Short >& v);
	HiVariant& operator=(const std::vector< Int >& v);
	HiVariant& operator=(const std::vector< Long >& v);
	HiVariant& operator=(const std::vector< Float >& v);
	HiVariant& operator=(const std::vector< Double >& v);


	void swap(HiVariant& v);

	// 比较操作
	bool operator==( const HiVariant& ) const;
	bool operator!=( const HiVariant& ) const;
	bool operator<=( const HiVariant& ) const;
	bool operator<( const  HiVariant& ) const;

	//常用方法

	LCSH::EDataType type() const ;
	bool isValid();
	void clear();
	static const char* typeName( const LCSH::EDataType& typ );
	const char* typeName();

	// 类型转换
	operator bool() const;
	operator Byte() const ;
	operator Short() const ;
	operator Int() const ;
	operator Float() const ;
	operator Long() const ;
	operator Double() const ;
	operator char*() const ;
	operator std::string() const;
	operator LCSH::Time() const;

	// 获取值

	bool  toBool() const;
	Byte  toByte() const;
	Short toShort() const;
	Int   toInt() const;
	Float toFloat() const;
	Long toLong() const;
	Double toDouble() const;
	char* toChar() const;
	std::string toString() const;
	LCSH::Time toTime() const;
	HiBinary toBinary() const;

	template<class T>
	void toVector(std::vector<T>& vecT) const
	{
		vecT.clear();
		if (m_byDataType >= LCSH::EnumDataTypeBoolSeq &&  m_byDataType<= LCSH::EnumDataTypeDoubleSeq )
		{
			Ice::Int nLength = m_binaryValue.m_nBinaryLength;
			vecT.resize( nLength );
			void* pos = NULL;
			if (nLength > 0)
			{
				pos = &vecT[0];
			}

			if (m_byDataType == LCSH::EnumDataTypeBoolSeq)
			{
				std::vector<Byte> vByte;
				vByte.resize( nLength );
				if (nLength > 0)
				{
					pos = &vByte[0];
				}
				memcpy(pos,m_binaryValue.m_pBinary,nLength * sizeof(Byte));
				for (Ice::Int i = 0 ; i < nLength ; i++)
				{
					vecT[i] = vByte[i];
				}
			}
			else
			{
			   memcpy(pos,m_binaryValue.m_pBinary,nLength * sizeof(T));
			}

		}
	}

	template<class T>
	std::vector<T> toVector() const
	{
		std::vector<T> vecT;
		toVector(vecT);
		return vecT;
	}

public:

	void ice_write(const ::Ice::OutputStreamPtr& out) const;
	void ice_read(const ::Ice::InputStreamPtr& in);

private:
	
	template<class T>
	void writeSeq(const ::Ice::OutputStreamPtr& out,const HiBinary& v) const;

	template<class T>
	void readSeq(const ::Ice::InputStreamPtr& in,HiBinary& v,bool isByte = false) const;

	void readByteSeq(const ::Ice::InputStreamPtr& in,HiBinary& v) const;
};


template<>
struct StreamTrait< HiVariant>
{
	static const ::Ice::StreamTraitType type = ::Ice::StreamTraitTypeStruct;
	static const int minWireSize = 1;
};

typedef ::std::vector< HiVariant> HiVariantSeq;

template<>
struct StreamTrait< HiVariantSeq>
{
	static const ::Ice::StreamTraitType type = ::Ice::StreamTraitTypeSequence;
	static const int minWireSize = 1;
};

template <class Stream>
inline Stream& operator<<(Stream& out,const LCSH::Time& v)
{
	out << "  " <<v.nSecond << "s" <<":" << v.sMillisecond << "ms" ;
	return out;
}

template <class Stream>
inline Stream& operator<<(Stream& out,const HiVariant& v)
{
	switch( v.type() )
	{
	case LCSH::EnumDataTypeBool :		out << v.toBool();	break;
	case LCSH::EnumDataTypeByte :		out << (Int)(v.toByte());	break; 
	case LCSH::EnumDataTypeShort :	out << v.toShort(); break;
	case LCSH::EnumDataTypeInt :		out << v.toInt();	break;
	case LCSH::EnumDataTypeLong :		out << v.toLong();	break;
	case LCSH::EnumDataTypeFloat :	out << v.toFloat(); break;
	case LCSH::EnumDataTypeDouble :	out << v.toDouble();break;
	case LCSH::EnumDataTypeString :	out << v.toString();break;
	case LCSH::EnumDataTypeTime :		
		{
			LCSH::Time t = v.toTime();
			out << t.nSecond << "s ";
			out << t.sMillisecond << "ms";
		}
		break;
	case LCSH::EnumDataTypeBoolSeq :
	case LCSH::EnumDataTypeByteSeq :
	case LCSH::EnumDataTypeShortSeq :
	case LCSH::EnumDataTypeIntSeq :	
	case LCSH::EnumDataTypeLongSeq :
	case LCSH::EnumDataTypeFloatSeq :
	case LCSH::EnumDataTypeDoubleSeq :
		{
			out << "Length" << v.toBinary().m_nBinaryLength;
		}
		break;
	default: break;
	}
	return out;
}


typedef std::less_equal< HiVariant > less_equal_HiVariant;
typedef std::less< HiVariant > less_HiVariant;


#endif //_VARIANT_H
