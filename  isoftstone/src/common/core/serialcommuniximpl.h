
// ====================����ͨ�Ű�װ����Unix�µ��ඨ��============================
//
// �����߲���ֱ��ʹ�ô��ֱ࣬��ʹ��CSerialComm�࣬CSerialComm����ݲ���ϵͳƽ̨
// ���о����ʵ����
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

//## ����ͨѶ��Unix�µ�ʵ��
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
    //## �򿪴��ڣ��������
	//##ModelId=40E4AA8C0386
	virtual bool Open();

	// �����Ƿ��
	//##ModelId=40E4AA8C038C
	virtual bool IsOpen()
	{
		return (m_nDevStaus == SERIAL_OPEN)?true:false;
	}

	// �رմ���
	//##ModelId=40E4AA8C038E
	virtual bool Close();

    //## �Ӵ����н�������
    //##ModelId=40E4AA8C0396
	virtual int ReadData(
        void* data, 
        int count
    );

    //## ��������
    //##ModelId=40E4AA8C039A
	virtual int WriteData(
        void* data, 
        int count
    );

	// ����ͨ�Ų�������
	//##ModelId=40E4AA8C03A3
	virtual bool SetCommParam(const s_serial_param& comm_param);
	// ���ò�����
	//##ModelId=40E4AA8C03AB
	virtual bool SetBPS(Juint16 bps);
	// ����RTS�źű�־
	virtual void setRTS(bool bSet);
	// ����DTR�źű�־
	virtual void setDTR(bool bSet);	

private:
	//##ModelId=40E4AA8C03AE
	int BAUDRATE(int rate);

	//##ModelId=40E4AA8C03B5
	int SetPortAttr(s_serial_param devparam);		//�����豸����
	//##ModelId=40E4AA8C03BF
	void SetBaudrate(int baudrate);				//���ò�����
	//##ModelId=40E4AA8C03C1
	void SetFlowControl(int fctrl);				//����������
	//##ModelId=40E4AA8C03C9
	void SetDataBit(int databit);				//��������λ
	//##ModelId=40E4AA8C03CB
	void SetStopBit(char stopbit);				//����ֹͣλ
	//##ModelId=40E4AA8C03D3
	void SetParityCheck(char parity);			//����У��
	//##ModelId=40E4AA8C03DC
	void SetOtherOption();					// ���ô��ڵ�����ѡ��
	
	//##ModelId=40E4AA8C03DD
	int GetBaudrate();							//��ȡ�豸�Ĳ�����
	
private:
	int m_nDevStaus;							//�豸״̬
	struct termios m_termio_new;				//�豸����
	struct termios m_termio_old;				//�豸����
	int m_fd;									//�ļ�������

};

}

#endif // _CSERIALCOMM_UNIXIMPL_H_

#endif // _WIN32
