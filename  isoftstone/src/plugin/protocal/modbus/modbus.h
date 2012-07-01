
#ifndef PROTOCAL_MODBUS_H
#define PROTOCAL_MODBUS_H

#include <qglobal.h>
#include <QByteArray>

typedef unsigned char byte;

class CModbus
{
public:
	// 6 + 1 + 1 + 2 + 2 + 2
	// 00 E1 00 00 00 06 01 03 00 00 0A

	struct RTU
	{
		byte* Counter;
		byte Address;
		byte Fun;
		short Register;
		ushort Count;
		ushort CRC;
	};

	struct RTU_INT
	{
		byte  Address;
		ushort Offset; 
		short* Int_Values;
	};

	struct RTU_FLOAT
	{
		byte Address;
		ushort Offset;
		float* Float_Values;
	};

	struct RTU_RET
	{
		byte* Counter;
		byte Address;
		byte Fun;
		byte Count;
		byte* Data;
		ushort CRC;
	};

	struct ASK
	{
		byte Fun;
		byte ErrorCode;
	};

	static const byte s_ReadCoil = 0x01;
	static const byte s_ReadInputStatus = 0x02;
	static const byte s_ReadRegister = 0x03;
	static const byte s_WriterCoil = 0x05;
	static const byte s_PreWriteSignalRegister = 0x06;
	static const byte s_ReturnCheck = 0x08;
	static const byte s_ForceWriteMultiCoil = 0x0f;
	static const byte s_PreWriteMulRegister = 0x10;

	static const bool bModbusTCP = false;
	static const byte byDataType = 1; // 1 short 2 int 3 float

	static const int CRC_LEN = 2;


public:

	static ushort CRC16(byte* buffer, int Count);

	static byte* TCP_Package(RTU info);

	static float* getFloatValues(RTU_RET ret,int offset,int count);

	static void setFloatValues(RTU_RET& ret,float* values);

};

#endif