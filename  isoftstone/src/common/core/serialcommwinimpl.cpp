// ====================串口通信包装类在Windows下的类实现============================
//
// 调用者并不直接使用此类，直接使用CSerialComm类，CSerialComm类根据操作系统平台
// 进行具体的实例化
//
////////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32)
#include "iestypedef.h"
#include "serialcommwinimpl.h"
#include "stdio.h"
#include <string>

using namespace HiRTDB;
// 构造函数
//##ModelId=3F136C17004D
CSerialCommWinImpl::CSerialCommWinImpl(const s_serial_param& param)
{
	m_comm_param = param;
	m_ComState = SERIAL_CLOSE;
	m_hCom = NULL;
}

// 拷贝构造函数
//##ModelId=3F136C170057
CSerialCommWinImpl::CSerialCommWinImpl(
    const CSerialCommWinImpl& right
)
{
	this->m_comm_param = right.m_comm_param;
}

// 析构函数
//##ModelId=3F136C170059
CSerialCommWinImpl::~CSerialCommWinImpl()
{
	if (m_hCom)
	{
		CloseHandle(m_hCom);
		m_hCom = NULL;
	}
}

// 打开串口，创建串口操作句柄
//##ModelId=3F136C170062
bool CSerialCommWinImpl::Open()
{
	bool bRet = true;
	if (m_hCom)
		return bRet;
#ifdef UNICODE
	Jwchar tmp[24];
	std::string qs(m_comm_param.strDevicename);
	memcpy(tmp, qs.data(), qs.length()*2);
	tmp[qs.length()] = 0;
	m_hCom = CreateFile(tmp,
		GENERIC_READ|GENERIC_WRITE,
		0,                    // exclusive access
		NULL,                 // no security attrs
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, // FILE_FLAG_OVERLAPPED
		NULL );
#else
	m_hCom = CreateFile(m_comm_param.strDevicename,
		GENERIC_READ|GENERIC_WRITE,
		0,                    // exclusive access
		NULL,                 // no security attrs
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, // FILE_FLAG_OVERLAPPED
		NULL );
#endif

	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		m_hCom = NULL;
		m_ComState = SERIAL_ERROR;
		bRet = false;
	}
	else
	{
		// 打开串口成功
		m_ComState = SERIAL_OPEN;
		// 设置参数
		bRet = SetCommParam();
	}

	return bRet;
}


// 关闭串口
//##ModelId=3F136C17006B
bool CSerialCommWinImpl::Close()
{
	if (m_hCom)
	{
		CloseHandle(m_hCom);
		m_hCom = NULL;
		m_ComState = SERIAL_CLOSE;
	}
	return true;
}

//##ModelId=3F136C17006D
//## 从串口中接收数据
int CSerialCommWinImpl::ReadData(
    void* data, 
    int count
)
{
	DWORD		dwErrorFlags;
	COMSTAT		ComStat ;
	DWORD		sReadByteCount = 0;
	BOOL		bReadState = FALSE;	
	if (!m_hCom)
		return -1;
	ClearCommError( m_hCom, &dwErrorFlags, &ComStat );
	if ( ComStat.cbInQue )
	{
		// 读缓冲区有数据
		if ((DWORD)count > ComStat.cbInQue)
			count = ComStat.cbInQue;
		
		bReadState = ReadFile(m_hCom, data, count, &sReadByteCount, NULL);
		
		if (!bReadState)
		{
			if(GetLastError() != ERROR_IO_PENDING)
			{
				sReadByteCount = -1;
			}
		}
	}

	return sReadByteCount;
}


//##ModelId=3F136C170076
//## 发送数据
int CSerialCommWinImpl::WriteData(
    void* data, 
    int count
)
{
	DWORD		dwErrorFlags;
	unsigned long sendCount = 0;
	COMSTAT		ComStat ;
	if (!m_hCom)
		return -1;
	ClearCommError( m_hCom, &dwErrorFlags, &ComStat );
	if (!ComStat.cbOutQue)
	{
		//发送缓冲区没有数据可以发送
		if (!WriteFile( m_hCom, data, count, &sendCount, NULL))
		{
			if(GetLastError() != ERROR_IO_PENDING)
			{
				sendCount = -1;
			}
		}
	}
	return sendCount;
}

// 进行通信参数设置
//##ModelId=3F136C17009E
bool CSerialCommWinImpl::SetCommParam()
{
	return this->SetCommParam(this->m_comm_param);
}
// 进行通信参数设置
//##ModelId=3F136C170089
bool CSerialCommWinImpl::SetCommParam(const s_serial_param& comm_param)
{
	COMMTIMEOUTS	CommTimeOuts ;
	DCB		comdcb;
	BOOL bComFlag;

	SetCommMask( m_hCom, EV_RXCHAR ) ;
	SetupComm( m_hCom, 4096, 4096 ) ;
	PurgeComm( m_hCom, PURGE_TXABORT | PURGE_RXABORT |
					PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

	// set up for overlapped I/O
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF ;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 1000*12/comm_param.wBPS ;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	// 异步读写的超时控制设置
	//SetCommTimeouts(m_hCom, &CommTimeOuts);

	GetCommState( m_hCom, &comdcb );
	//通信参数
	comdcb.BaudRate = comm_param.wBPS;			// 波特率
	
	switch (comm_param.chParity)
	{
		case 'N':
		case 'n':
			comdcb.Parity = NOPARITY;				// 无校验
			break;
		case 'E':
		case 'e':
			comdcb.Parity = EVENPARITY;				// 偶校验
			break;
		case 'O':
		case 'o':
			comdcb.Parity = ODDPARITY;				// 奇校验
			break;
		default:
			comdcb.Parity = NOPARITY;				// 无校验
			break;
	}

	switch (comm_param.chStopbit)
	{
		case 0:
		case '0':
			comdcb.StopBits = ONESTOPBIT;			// 1位停止位
			break;
		case 1:
		case '1':
			comdcb.StopBits = ONE5STOPBITS;			// 1.5 位停止位
			break;
		case 2:
		case '2':
			comdcb.StopBits = TWOSTOPBITS;			// 2位停止位
			break;
		default:
			comdcb.StopBits = ONESTOPBIT;			// 1位停止位
			break;

	}
	comdcb.ByteSize = comm_param.byDatabits;			// 数据位

	bComFlag = SetCommState(m_hCom,&comdcb);
	if(!bComFlag)
	{
		Close();
		return false;
	}
	return true;
}

// 重新设置波特率
//##ModelId=3F136C170093
bool CSerialCommWinImpl::SetBPS(Juint16 bps)
{
	DCB		comdcb;
	GetCommState( m_hCom, &comdcb );
	if (comdcb.BaudRate !=bps)
		comdcb.BaudRate = bps;
	if (SetCommState(m_hCom,&comdcb))
		return true;
	Close();
	return false;
}
// 设置RTS信号标志
void CSerialCommWinImpl::setRTS(bool bSet)
{
	if (bSet)
	{
		EscapeCommFunction(m_hCom,SETRTS);	
	}
	else
	{
		EscapeCommFunction(m_hCom,CLRRTS);
	}
}

// 设置DTR信号标志
void CSerialCommWinImpl::setDTR(bool bSet)
{
	if (bSet)
	{
		EscapeCommFunction(m_hCom,SETDTR);	
	}
	else
	{
		EscapeCommFunction(m_hCom,CLRDTR);
	}
}

#endif // _WIN32
