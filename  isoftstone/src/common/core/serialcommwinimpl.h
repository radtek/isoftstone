
// ====================����ͨ�Ű�װ����Windows�µ��ඨ��============================
//
// �����߲���ֱ��ʹ�ô��ֱ࣬��ʹ��CSerialComm�࣬CSerialComm����ݲ���ϵͳƽ̨
// ���о����ʵ����
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
//## ����ͨѶ��Windows�µ�ʵ�֣����첽��ʽʵ��
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

// �ӿ�ʵ��
public:
    //##ModelId=40E4AA8D0032
    //## �򿪴���
	virtual bool Open();

	// �����Ƿ��
    //##ModelId=40E4AA8D0034
	virtual bool IsOpen()
	{
		return (m_ComState == SERIAL_OPEN)?true:false;
	}

	// �رմ���
    //##ModelId=40E4AA8D003B
	virtual bool Close();

    //##ModelId=40E4AA8D003D
    //## �Ӵ����н�������
    virtual int ReadData(
        void* data, 
        int count
    );

  
    //##ModelId=40E4AA8D004F
    //## ��������
    virtual int WriteData(
        void* data, 
        int count
    );

	// ����ͨ�Ų�������
    //##ModelId=40E4AA8D0059
	virtual bool SetCommParam(const s_serial_param& comm_param);
	// ���ò�����
    //##ModelId=40E4AA8D0064
	virtual bool SetBPS(Juint16 bps);
	// ����RTS�źű�־
	virtual void setRTS(bool bSet);
	// ����DTR�źű�־
	virtual void setDTR(bool bSet);	

// ˽�г�Ա����
private:
	// ����ͨ�Ų�������
    //##ModelId=40E4AA8D006E
	bool SetCommParam();

private:
    // ���
    //##ModelId=3F136C17001C
	HANDLE m_hCom;

    // ����״̬
    //##ModelId=40E4AA8D0009
	SERIAL_STATE m_ComState;

};

}

#endif /* CSERIALCOMM_WINIMPL_H_HEADER_INCLUDED_C27832EA */

#endif // _WIN32
