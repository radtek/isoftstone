
#ifndef __LCSHVARIANT_ICE
#define __LCSHVARIANT_ICE

module LCSH
{
    // 定义联合体变量类型常量

    sequence < byte > ByteSeq;
    sequence < int > IntSeq;
    sequence < long > LongSeq;
    sequence < bool > BoolSeq;
    sequence < short > ShortSeq;
    sequence < float > FloatSeq;
    sequence < double > DoubleSeq;
    sequence < string > StringSeq;


    enum VariantConst
    {
        ConstByte,
        ConstBool,
        ConstShort,
        ConstInt,
        ConstLong,
        ConstFloat,
        ConstDouble,
        ConstString,
	ConstByteSeq,
        ConstBoolSeq,
        ConstShortSeq,
        ConstIntSeq,
        ConstLongSeq,
        ConstFloatSeq,
        ConstDoubleSeq,
        ConstStringSeq
    };

    struct SimipleValue
    {
	VariantConst datatype;
	byte byteValue;
	int intValue;
	bool boolValue;
	short shortValue;
	long longValue;
	float floatValue;
	double doubleValue;
	string stringValue;
	ByteSeq byteSeqs;
	IntSeq intSeqs;
	LongSeq longSeqs;
	BoolSeq boolSeqs;
	ShortSeq shortSeqs;
	FloatSeq floatSeqs;
	DoubleSeq doubleSeqs;
	StringSeq stringSeqs;
    };

};

#endif
