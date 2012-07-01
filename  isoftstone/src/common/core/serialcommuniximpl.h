
// ====================串口通信包装类在Unix下的类定义============================
//
// 调用者并不直接使用此类，直接使用CSerialComm类，CSerialComm类根据操作系统平台
// 进行具体的实例化
//
////////////////////////////////////////////////////////////////////////////////////
#if !defined(_WIN32)

#ifndef _CSERIALCOMM_UNIXIMPL_H_
#define _CSERIALCOMM_UNIXIMPL_H_
#include "serialcomm.h"
#include <termios.h>
#include "escore.h.h"

namespace HiRTDB 
{

//## 串口通讯在Unix下的实现
//##ModelId=40E4AA8B036D
class LIBCORE_EXPORT CSerialCommUnixImpl : public CSerialComm
{
public:
	//##ModelId=40E4AA8C0379
    CSerialCommUnixImpl(const s_serial_param& param);

	//##ModelId=40E4AA8C0382
    CSerialCommUnixImpl(
        const CSerialCommUnixImpl& right
    );

	//##ModelId=40E4AA8C0384
    virtual ~CSerialCommUnixImpl();

public:
    //## 打开串口，创建句柄
	//##ModelId=40E4AA8C0386
	virtual bool Open();

	// 串口是否打开
	//##ModelId=40E4AA8C038C
	virtual bool IsOpen()
	{
		return (m_nDevStaus == SERIAL_OPEN)?true:false;
	}

	// 关闭串口
	//##ModelId=40E4AA8C038E
	virtual bool Close();

    //## 从串口中接收数据
    //##ModelId=40E4AA8C0396
	virtual int ReadData(
        void* data, 
        int count
    );

    //## 发送数据
    //##ModelId=40E4AA8C039A
	virtual int WriteData(
        void* data, 
        int count
    );

	// 进行通信参数设置
	//##ModelId=40E4AA8C03A3
	virtual bool SetCommParam(const s_serial_param& comm_param);
	// 设置波特率
	//##ModelId=40E4AA8C03AB
	virtual bool SetBPS(Juint16 bps);
	// 设置RTS信号标志
	virtual void setRTS(bool bSet);
	// 设置DTR信号标志
	virtual void setDTR(bool bSet);	

private:
	//##ModelId=40E4AA8C03AE
	int BAUDRATE(int rate);

	//##ModelId=40E4AA8C03B5
	int SetPortAttr(s_serial_param devparam);		//设置设备属性
	//##ModelId=40E4AA8C03BF
	void SetBaudrate(int baudrate);				//设置波特率
	//##ModelId=40E4AA8C03C1
	void SetFlowControl(int fctrl);				//设置流控制
	//##ModelId=40E4AA8C03C9
	void SetDataBit(int databit);				//设置数据位
	//##ModelId=40E4AA8C03CB
	void SetStopBit(char stopbit);				//设置停止位
	//##ModelId=40E4AA8C03D3
	void SetParityCheck(char parity);			//设置校验
	//##ModelId=40E4AA8C03DC
	void SetOtherOption();					// 设置串口的其他选项
	
	//##ModelId=40E4AA8C03DD
	int GetBaudrate();							//获取设备的波特率
	
private:
	int m_nDevStaus;							//设备状态
	struct termios m_termio_new;				//设备参数
	struct termios m_termio_old;				//设备描述
	int m_fd;									//文件描述符

};

}

#endif // _CSERIALCOMM_UNIXIMPL_H_

#endif // _WIN32
