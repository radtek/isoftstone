

#include "variant.h"

static const char* const type_map[LCSH::EnumDataTypeDoubleSeq + 1] =
{
	0,
	"Bool",
	"Byte",
	"Short",
	"Int",
	"Long",
	"Float",
	"Double",
	"String",
	"Time",
	"BoolSequence",
	"ByteSequence",
	"ShortSequence",
	"IntSequence",
	"LongSequence",
	"FloatSequence",
	"DoubleSequence"
};


bool assign(char*& left,const char* right)
{
	size_t nLength = strlen(right);
	left = new char[nLength+1];
	memcpy(left, right, nLength);
	left[nLength] = '\0';
	return true;
}

bool assign(LCSH::Time& left,const LCSH::Time& right)
{
	left.nSecond = right.nSecond;
	left.sMillisecond = right.sMillisecond;
	return true;
}

template<class T>
bool assign(HiBinary& left,const HiBinary& right)
{
	Ice::Int nLength = right.m_nBinaryLength;
	left.m_nBinaryLength = nLength;
	left.m_pBinary = new T[nLength];
	memcpy(left.m_pBinary, right.m_pBinary, nLength*sizeof(T));
	left.m_nBinaryLength = nLength ;
	return true;
}

template<class T>
bool assign(HiBinary& left,const std::vector<T>& right)
{
	size_t nLength = right.size();
	const void* pos = NULL;
	if (nLength > 0)
	{
		pos = &right[0];
	}
	left.m_nBinaryLength = nLength;
	left.m_pBinary = new T[nLength];
	memcpy(left.m_pBinary, pos, nLength * sizeof(T));
	left.m_nBinaryLength = static_cast<Ice::Int>(nLength );
	return true;
}

HiVariant::HiVariant()
{
	m_byDataType = LCSH::EnumDataTypeEmpty;

}
HiVariant::~HiVariant()
{
	clear();
}


HiVariant::HiVariant(const HiVariant& v)
{
	*this = v;
}

HiVariant::HiVariant(const bool& v)
{
	*this = v;
}

HiVariant::HiVariant(const Ice::Byte& v)
{
	*this = v;
}

HiVariant::HiVariant(const Ice::Short& v)
{
	*this = v;
}

HiVariant::HiVariant(const Ice::Int& v)
{
	*this = v;
}

HiVariant::HiVariant(const Ice::Float& v)
{
	*this = v;
}

HiVariant::HiVariant(const Ice::Long& v)
{
	*this = v;
}

HiVariant::HiVariant(const Ice::Double& v)
{
	*this = v;
}

HiVariant::HiVariant(const char* v)
{
	*this = v;
}

HiVariant::HiVariant(const std::string& v)
{
	*this = v;
}

HiVariant::HiVariant(const LCSH::Time& v)
{
	*this = v;
}


HiVariant& HiVariant::operator=(const HiVariant& v)
{
	clear();
	m_byDataType = v.m_byDataType;
	switch(m_byDataType)
	{
	case LCSH::EnumDataTypeBool :			m_boolValue = v.m_boolValue;						break;
	case LCSH::EnumDataTypeByte :			m_byteValue = v.m_byteValue;						break; 
	case LCSH::EnumDataTypeShort :		m_shortValue = v.m_shortValue;							break;
	case LCSH::EnumDataTypeInt :			m_intValue = v.m_intValue;							break;
	case LCSH::EnumDataTypeLong :			m_longValue = v.m_longValue;						break;
	case LCSH::EnumDataTypeFloat :		m_flatValue = v.m_flatValue;							break;
	case LCSH::EnumDataTypeDouble :		m_doubleValue = v.m_doubleValue;						break;
	case LCSH::EnumDataTypeString :		assign(m_stringValue , v.m_stringValue);				break;
	case LCSH::EnumDataTypeTime :			assign(m_timeValue,v.m_timeValue);					break;
	case LCSH::EnumDataTypeBoolSeq :		
	case LCSH::EnumDataTypeByteSeq :		assign<Byte>(m_binaryValue , v.m_binaryValue);		break;
	case LCSH::EnumDataTypeShortSeq :		assign<Short>(m_binaryValue , v.m_binaryValue);		break;
	case LCSH::EnumDataTypeIntSeq :		assign<Int>(m_binaryValue , v.m_binaryValue);			break;
	case LCSH::EnumDataTypeLongSeq :		assign<Long>(m_binaryValue , v.m_binaryValue);		break;
	case LCSH::EnumDataTypeFloatSeq :		assign<Float>(m_binaryValue , v.m_binaryValue);		break;
	case LCSH::EnumDataTypeDoubleSeq :	assign<Double>(m_binaryValue , v.m_binaryValue);		break;
	default:
		break;
	}
	return *this;
}

HiVariant& HiVariant::operator=(const bool& v) 
{
	clear();
	m_byDataType = LCSH::EnumDataTypeBool;
	m_boolValue = v;
	return *this;
}

HiVariant& HiVariant::operator=(const Ice::Byte& v)
{
	clear();
	m_byDataType = LCSH::EnumDataTypeByte;
	m_byteValue = v;
	return *this;
}

HiVariant& HiVariant::operator=(const Ice::Short& v)
{
	clear();
	m_byDataType = LCSH::EnumDataTypeShort;
	m_shortValue = v;
	return *this;
}

HiVariant& HiVariant::operator=(const Ice::Int& v)
{
	clear();
	m_byDataType = LCSH::EnumDataTypeInt;
	m_intValue = v;
	return *this;
}

HiVariant& HiVariant::operator=(const Ice::Float& v)
{
	clear();
	m_byDataType = LCSH::EnumDataTypeFloat;
	m_flatValue = v;
	return *this;
}

HiVariant& HiVariant::operator=(const Ice::Long& v)
{
	clear();
	m_byDataType = LCSH::EnumDataTypeLong;
	m_longValue = v;
	return *this;
}

HiVariant& HiVariant::operator=(const Ice::Double& v)
{
	clear();
	m_byDataType = LCSH::EnumDataTypeDouble;
	m_doubleValue = v;
	return *this;
}

HiVariant& HiVariant::operator=(const char* v)
{
	clear();
	m_byDataType = LCSH::EnumDataTypeString;
	assign(m_stringValue,v);
	return *this;
}

HiVariant& HiVariant::operator=(const std::string& v)
{
	clear();
	*this = v.c_str();
	return *this;
}

HiVariant& HiVariant::operator=(const LCSH::Time v)
{
	clear();
	m_byDataType = LCSH::EnumDataTypeTime;
	assign(m_timeValue,v);
	return *this;
}

HiVariant& HiVariant::operator=(const std::vector< bool >& v)
{
	std::vector< Byte > vByte;
	vByte.resize(v.size());
	for ( size_t i = 0 ; i < v.size() ; i++)
	{
		vByte[i] = v[i] ? Byte(1) : Byte(0);
	}
	VectorConstructor(LCSH::EnumDataTypeBoolSeq,vByte);
}

HiVariant& HiVariant::operator=(const std::vector< Byte >& v)
{
	VectorConstructor(LCSH::EnumDataTypeByteSeq,v);
}


HiVariant& HiVariant::operator=(const std::vector< Short >& v)
{
	VectorConstructor(LCSH::EnumDataTypeShortSeq,v);
	return *this;
}

HiVariant& HiVariant::operator=(const std::vector< Int >& v)
{
	VectorConstructor(LCSH::EnumDataTypeIntSeq,v);
}

HiVariant& HiVariant::operator=(const std::vector< Long >& v)
{
	VectorConstructor(LCSH::EnumDataTypeLongSeq,v);

}

HiVariant& HiVariant::operator=(const std::vector< Float >& v)
{
	VectorConstructor(LCSH::EnumDataTypeFloatSeq,v);
}

HiVariant& HiVariant::operator=(const std::vector< Double >& v)
{
	VectorConstructor(LCSH::EnumDataTypeDoubleSeq,v);
}


void HiVariant::swap(HiVariant& v)
{
	HiVariant tmp = v;
	v = *this;
	*this = tmp;
}

bool HiVariant::operator==( const HiVariant &v ) const
{
	bool ret = false;
	if ( type() == v.type() )
	{
		OperatorCompare(ret,v,==);
	}
	return ret;
}

bool HiVariant::operator<=( const HiVariant& v) const
{
	bool ret = false;
	if ( type() == v.type() )
	{
		OperatorCompare(ret,v,<=);
	}
	return ret;
}

bool HiVariant::operator<( const HiVariant& v) const
{
	bool ret = false;
	if ( type() == v.type() )
	{
		OperatorCompare(ret,v,<);
	}
	return ret;
}

bool HiVariant::operator!=( const HiVariant &v ) const
{
	return !( v == *this );
}

bool  HiVariant::toBool() const
{
	return m_byDataType == LCSH::EnumDataTypeBool ? m_boolValue : false;
}

Byte  HiVariant::toByte() const
{
	return m_byDataType == LCSH::EnumDataTypeByte ? m_byteValue : 0; 
}

Short HiVariant::toShort() const
{
	return m_byDataType == LCSH::EnumDataTypeShort ? m_shortValue: 0;
}

Int   HiVariant::toInt() const
{
	return m_byDataType == LCSH::EnumDataTypeInt ? m_intValue : 0;
}

Float HiVariant::toFloat() const
{
	return m_byDataType == LCSH::EnumDataTypeFloat ? m_flatValue : 0;
}

Long  HiVariant::toLong() const
{
	return m_byDataType == LCSH::EnumDataTypeLong ? m_longValue : 0;
}

Double HiVariant::toDouble() const
{
	return m_byDataType == LCSH::EnumDataTypeDouble ? m_doubleValue : 0;
}

char* HiVariant::toChar() const
{
	return m_byDataType == LCSH::EnumDataTypeString ? m_stringValue : NULL;
}

std::string HiVariant::toString() const
{
	return m_byDataType == LCSH::EnumDataTypeString ? std::string(m_stringValue) : std::string("");
}

LCSH::Time HiVariant::toTime() const
{
	LCSH::Time t;
	t.nSecond = 0;
	t.sMillisecond = 0;
	return m_byDataType == LCSH::EnumDataTypeTime ? m_timeValue : t;
}

HiBinary HiVariant::toBinary() const
{
	HiBinary hb;
	hb.m_pBinary = NULL;
	hb.m_nBinaryLength = 0;
	if (m_byDataType >= LCSH::EnumDataTypeBoolSeq && m_byDataType <= LCSH::EnumDataTypeDoubleSeq)
	{
		return m_binaryValue;
	}
	else
	{
		return hb;
	}
}

LCSH::EDataType HiVariant::type() const
{
	return m_byDataType;
}

bool HiVariant::isValid()
{
	return m_byDataType != LCSH::EnumDataTypeEmpty;
}

void HiVariant::clear()
{
	switch (m_byDataType)
	{
	case LCSH::EnumDataTypeString:
		delete[] m_stringValue;
		m_stringValue = NULL;
		break;
	case LCSH::EnumDataTypeBoolSeq:
	case LCSH::EnumDataTypeByteSeq:
	case LCSH::EnumDataTypeShortSeq:
	case LCSH::EnumDataTypeIntSeq:
	case LCSH::EnumDataTypeLongSeq:
	case LCSH::EnumDataTypeFloatSeq:
	case LCSH::EnumDataTypeDoubleSeq:
		{
			delete[] m_binaryValue.m_pBinary;
			m_binaryValue.m_pBinary = NULL;
			m_binaryValue.m_nBinaryLength = 0;
			break;
		}
	default:
		break;
	}
	m_byDataType = LCSH::EnumDataTypeEmpty;
}

const char* HiVariant::typeName( const LCSH::EDataType& typ )
{
	if ( typ <= LCSH::EnumDataTypeEmpty || typ >= LCSH::EnumDataTypeDoubleSeq +1 )
		return 0;
	return type_map[typ];
}

const char* HiVariant::typeName()
{
	return typeName(type());
}

HiVariant::operator bool() const
{
	return toBool();
}

HiVariant::operator Byte() const 
{
	return toByte();
}

HiVariant::operator Short() const 
{
	return toShort();
}

HiVariant::operator Int() const 
{
	return toInt();
}

HiVariant::operator Float() const 
{
	return toFloat();
}

HiVariant::operator Long() const 
{
	return toLong();
}

HiVariant::operator Double() const 
{
	return toDouble();
}

HiVariant::operator char*() const 
{
	return toChar();
}

HiVariant::operator std::string() const 
{
	return toString();
}

HiVariant::operator LCSH::Time() const
{
	return toTime();
}

template<class T>
void HiVariant::writeSeq(const ::Ice::OutputStreamPtr& out,const HiBinary& v) const
{
	out->write(v.m_nBinaryLength);
	const T* pT = static_cast<const T*>(v.m_pBinary);
	out->write(pT,pT + v.m_nBinaryLength);
}

template<class T>
void HiVariant::readSeq(const ::Ice::InputStreamPtr& in,HiBinary& v,bool isByte) const
{
	IceUtil::ScopedArray<T> sa;
	std::pair<const T*, const T*> inParams;
	in->read(v.m_nBinaryLength);

	in->read( inParams ,sa);

	const T* pos = const_cast<T*>(inParams.first);
	v.m_pBinary = new T[v.m_nBinaryLength];
	memcpy(v.m_pBinary,pos,v.m_nBinaryLength * sizeof(T));
}

void HiVariant::readByteSeq(const ::Ice::InputStreamPtr& in,HiBinary& v) const
{
	std::pair<const Byte*, const Byte*> inParams;
	in->read(v.m_nBinaryLength);

	in->read( inParams);

	const Byte* pos = const_cast<Byte*>(inParams.first);
	v.m_pBinary = new Byte[v.m_nBinaryLength];
	memcpy(v.m_pBinary,pos,v.m_nBinaryLength * sizeof(Byte));
}

void HiVariant::ice_write(const ::Ice::OutputStreamPtr& out) const
{
	out->write(m_byDataType);
	switch( m_byDataType )
	{
	case LCSH::EnumDataTypeBool :		out->write(m_boolValue);		break;
	case LCSH::EnumDataTypeByte :		out->write(m_byteValue);		break; 
	case LCSH::EnumDataTypeShort :		out->write(m_shortValue);		break;
	case LCSH::EnumDataTypeInt :		out->write(m_intValue);			break;
	case LCSH::EnumDataTypeLong :		out->write(m_longValue);		break;
	case LCSH::EnumDataTypeFloat :		out->write(m_flatValue);		break;
	case LCSH::EnumDataTypeDouble :		out->write(m_doubleValue);		break;
	case LCSH::EnumDataTypeString :	
			{
				out->write(m_stringValue,true);
			}
		break;
	case LCSH::EnumDataTypeTime :	
			{
				out->write(m_timeValue.nSecond);
				out->write(m_timeValue.sMillisecond);
			}
		break;
	case LCSH::EnumDataTypeBoolSeq:											
	case LCSH::EnumDataTypeByteSeq:	writeSeq<Byte>(out,m_binaryValue);		break;
	case LCSH::EnumDataTypeShortSeq:writeSeq<Short>(out,m_binaryValue);		break;
	case LCSH::EnumDataTypeIntSeq:	writeSeq<Int>(out,m_binaryValue);		break;
	case LCSH::EnumDataTypeLongSeq:	writeSeq<Long>(out,m_binaryValue);		break;
	case LCSH::EnumDataTypeFloatSeq:writeSeq<Float>(out,m_binaryValue);		break;
	case LCSH::EnumDataTypeDoubleSeq:writeSeq<Double>(out,m_binaryValue);	break;
	default:
		break;
	}
}

void HiVariant::ice_read(const ::Ice::InputStreamPtr& in)
{
	in->read(m_byDataType);
	switch( m_byDataType )
	{
	case LCSH::EnumDataTypeBool :		in->read(m_boolValue);		break;
	case LCSH::EnumDataTypeByte :		in->read(m_byteValue);		break; 
	case LCSH::EnumDataTypeShort :		in->read(m_shortValue);		break;
	case LCSH::EnumDataTypeInt :		in->read(m_intValue);		break;
	case LCSH::EnumDataTypeLong :		in->read(m_longValue);		break;
	case LCSH::EnumDataTypeFloat :		in->read(m_flatValue);		break;
	case LCSH::EnumDataTypeDouble :		in->read(m_doubleValue);	break;
	case LCSH::EnumDataTypeString :	
		{
			std::string inParams;
			in->read(inParams);
			assign(m_stringValue,inParams.c_str());
		}
		break;
	case LCSH::EnumDataTypeTime :	
		{
			in->read(m_timeValue.nSecond);
			in->read(m_timeValue.sMillisecond);
		}
		break;
	case LCSH::EnumDataTypeBoolSeq:											
	case LCSH::EnumDataTypeByteSeq:	readByteSeq(in,m_binaryValue);			break;
	case LCSH::EnumDataTypeShortSeq: readSeq<Short>(in,m_binaryValue);		break;
	case LCSH::EnumDataTypeIntSeq:   readSeq<Int>(in,m_binaryValue);		break;
	case LCSH::EnumDataTypeLongSeq:	readSeq<Long>(in,m_binaryValue);		break;
	case LCSH::EnumDataTypeFloatSeq: readSeq<Float>(in,m_binaryValue);		break;
	case LCSH::EnumDataTypeDoubleSeq:readSeq<Double>(in,m_binaryValue);		break;
	default:
		break;
	}
}