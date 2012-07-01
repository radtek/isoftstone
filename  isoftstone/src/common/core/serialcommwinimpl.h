
// ====================串口通信包装类在Windows下的类定义============================
//
// 调用者并不直接使用此类，直接使用CSerialComm类，CSerialComm类根据操作系统平台
// 进行具体的实例化
//
////////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32)
#ifndef _CSERIALCOMM_WINIMPL_H_
#define _CSERIALCOMM_WINIMPL_H_
#include "serialcomm.h"
#include "windows.h"
#include "escore.h"

namespace HiRTDB 
{

//##ModelId=40E4AA8B0377
//## 串口通讯在Windows下的实现，用异步方式实现
class LIBCORE_EXPORT CSerialCommWinImpl : public CSerialComm
{
public:
    //##ModelId=40E4AA8D001C
    CSerialCommWinImpl(const s_serial_param& param);

    //##ModelId=40E4AA8D0026
    CSerialCommWinImpl(
        const CSerialCommWinImpl& right
    );

    //##ModelId=40E4AA8D0030
    virtual ~CSerialCommWinImpl();

// 接口实现
public:
    //##ModelId=40E4AA8D0032
    //## 打开串口
	virtual bool Open();

	// 串口是否打开
    //##ModelId=40E4AA8D0034
	virtual bool IsOpen()
	{
		return (m_ComState == SERIAL_OPEN)?true:false;
	}

	// 关闭串口
    //##ModelId=40E4AA8D003B
	virtual bool Close();

    //##ModelId=40E4AA8D003D
    //## 从串口中接收数据
    virtual int ReadData(
        void* data, 
        int count
    );

  
    //##ModelId=40E4AA8D004F
    //## 发送数据
    virtual int WriteData(
        void* data, 
        int count
    );

	// 进行通信参数设置
    //##ModelId=40E4AA8D0059
	virtual bool SetCommParam(const s_serial_param& comm_param);
	// 设置波特率
    //##ModelId=40E4AA8D0064
	virtual bool SetBPS(Juint16 bps);
	// 设置RTS信号标志
	virtual void setRTS(bool bSet);
	// 设置DTR信号标志
	virtual void setDTR(bool bSet);	

// 私有成员方法
private:
	// 进行通信参数设置
    //##ModelId=40E4AA8D006E
	bool SetCommParam();

private:
    // 句柄
    //##ModelId=3F136C17001C
	HANDLE m_hCom;

    // 串口状态
    //##ModelId=40E4AA8D0009
	SERIAL_STATE m_ComState;

};

}

#endif /* CSERIALCOMM_WINIMPL_H_HEADER_INCLUDED_C27832EA */

#endif // _WIN32
