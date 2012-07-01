

#ifndef SBYTEORDER_H_HEADER_
#define SBYTEORDER_H_HEADER_

#include "escore.h"
#include "iestypedef.h"
#include <qdatastream.h>
#include <qapplication.h>

namespace core {

//## ���ֽ�˳��
struct LIBCORE_EXPORT SByteOrder
{
	SByteOrder()
	{
		m_byteOrder = getByteOrder();
	};

	static Juint8 getByteOrder()
	{
		if (!s_bInit)
		{
			int wordSize;
			bool bigEndian;
			qSysInfo(&wordSize, &bigEndian);
			s_byteOrder = bigEndian ? QDataStream::BigEndian : QDataStream::LittleEndian;
			s_bInit = JTRUE;
		}
		return s_byteOrder;
	};

	//## ��ͨ�Ű��ֽ�˳�򣨴�ˡ�С�ˣ�
	//## ȡֵ QDataStream::BigEndian QDataStream::LittleEndian
	Juint8 m_byteOrder;

private:
	//## ���汾�����ֽ���
	static Juint8 s_byteOrder;

	//## �Ƿ��ʼ�� s_byteOrder
	static Jboolean s_bInit;
};

inline QDataStream& operator<<(QDataStream& dataStream, const SByteOrder& data)
{
	dataStream << data.m_byteOrder;
	return dataStream;
};

inline QDataStream& operator>>(QDataStream& dataStream, SByteOrder& data)
{
	dataStream >> data.m_byteOrder;
	return dataStream;
};

} // namespace core

#endif /* SBYTEORDER_H_HEADER_INCLUDED_C1062D11 */
