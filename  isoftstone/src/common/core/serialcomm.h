
// ====================串口通信包装类============================
// 
// 使用方式：
//	s_serial_param param;
// CSerialComm* commVar = CSerialComm::CreateInstance(param);
// commVar->Open();
// commVar->ReadData();
// commVar->WriteData();
// commVar->Close();
// commVar->Release();
////////////////////////////////////////////////////////////////////////////////////


#ifndef _CSERIALCOMM_H_
#define _CSERIALCOMM_H_

#include <memory.h>
#include "escore.h"

namespace HiRTDB 
{

// 串口状态
//##ModelId=40E4AA8B03DB
enum SERIAL_STATE
{
	SERIAL_OPEN = 0,	//串口打开
	SERIAL_CLOSE,		//串口关闭
	SERIAL_ERROR		//串口错误
};

// 串口通信参数定义
//##ModelId=40E4AA8B03E5
struct LIBCORE_EXPORT s_serial_param
{
	//##ModelId=40E4AA8D02CF
	s_serial_param()
	{
		wBPS = 1200;
		byDatabits = 8;
		chParity = 'N';
		chStopbit = 0;
		byFctrl = 0;
		memset(strDevicename, 0 ,sizeof(strDevicename)/sizeof(Jchar));
		nReserved = 0;
	}
	//##ModelId=40E4AA8D021C
	Juint16 wBPS;				// 波特率
	//##ModelId=40E4AA8D0230
	Juint8  byDatabits;			// 数据位数, 如:5, 6, 7, 8
	//##ModelId=40E4AA8D0244
	Jchar   chParity;			// 校验, 'N': 无, 'O': 奇校验, 'E': 偶校验
	//##ModelId=40E4AA8D0262
	Jchar   chStopbit;			// 停止位, 0 or '0':1位, 1 or '1':1.5位, 2 or '2':2位
	//##ModelId=40E4AA8D0276
	Jint8   byFctrl;			// 流控制, 0: 无, 1: 硬件, 2: 软件
	//##ModelId=40E4AA8D0294
	Jchar   strDevicename[12];	// 设备名, 如/dev/tty01,\\.\COM1等
	//##ModelId=40E4AA8D02B2
	Jint32  nReserved;			// 保留
};

//##ModelId=40E4AA8B0358
//## 串行通讯包装类，负责把数据从串行通道中接收并放到通道的原始数据区中。
//根据通道波特率、数据位、终止位、同步异步等进行接收和发送。
class LIBCORE_EXPORT CSerialComm
{
public:

    //##ModelId=40E4AA8C0300
    virtual ~CSerialComm() = 0;

    //##ModelId=40E4AA8C030B
    //## 打开串口，创建句柄
	virtual bool Open() = 0;

	// 串口是否打开
    //##ModelId=40E4AA8C030D
	virtual bool IsOpen() = 0;

	// 关闭串口
    //##ModelId=40E4AA8C0314
	virtual bool Close() = 0;

    //##ModelId=40E4AA8C0316
    //## 从串口中接收数据
    virtual int ReadData(
        void* data, 
        int count
    ) = 0;

    //##ModelId=40E4AA8C0328
    //## 发送数据
    virtual int WriteData(
        void* data, 
        int count
    ) = 0;

	// 进行通信参数设置
    //##ModelId=40E4AA8C0333
	virtual bool SetCommParam(const s_serial_param& comm_param) = 0;

    //##ModelId=40E4AA8C033C
    virtual bool SetBPS(Juint16 bps)=0;

	// 设置RTS信号标志
	virtual void setRTS(bool bSet)=0;
	// 设置DTR信号标志
	virtual void setDTR(bool bSet)=0;	

    //##ModelId=40E4AA8C0347
	//## 创建一个实例，根据操作系统平台创建子类的实例
	static CSerialComm*  CreateInstance(const s_serial_param& comm_param);

	// 释放对象资源
    //##ModelId=40E4AA8C0351
	void Release();

	// 得到串口设置参数
    //##ModelId=40E4AA8C0352
	s_serial_param GetCommParam();

protected:
	
	// 串口通信参数
    //##ModelId=40E4AA8C02ED
	s_serial_param m_comm_param;

};

}
#endif /* CSERIALCOMM_H_HEADER_INCLUDED_C2793608 */
