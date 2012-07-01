
#include "iestypedef.h"
#include "serialcomm.h"
#if defined(_WIN32)
#include "serialcommwinimpl.h"
#else
#include "serialcommuniximpl.h"
#endif

using namespace HiRTDB;

//##ModelId=3F136C160351
//## ����һ��ʵ�������ݲ���ϵͳƽ̨���������ʵ��
CSerialComm* CSerialComm::CreateInstance(const s_serial_param& comm_param)
{
#if defined(_WIN32)
		CSerialComm* comm = new CSerialCommWinImpl(comm_param);
		return comm;
#else
		CSerialComm* comm = new CSerialCommUnixImpl(comm_param);
		return comm;
#endif
}

CSerialComm::~CSerialComm()
{
}

s_serial_param CSerialComm::GetCommParam()
{
	return this->m_comm_param;
}

// �ͷŶ�����Դ
//##ModelId=3F136C16035A
void CSerialComm::Release()
{
	delete this;
}


