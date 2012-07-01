
// ====================����ͨ�Ű�װ��============================
// 
// ʹ�÷�ʽ��
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

// ����״̬
//##ModelId=40E4AA8B03DB
enum SERIAL_STATE
{
	SERIAL_OPEN = 0,	//���ڴ�
	SERIAL_CLOSE,		//���ڹر�
	SERIAL_ERROR		//���ڴ���
};

// ����ͨ�Ų�������
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
	Juint16 wBPS;				// ������
	//##ModelId=40E4AA8D0230
	Juint8  byDatabits;			// ����λ��, ��:5, 6, 7, 8
	//##ModelId=40E4AA8D0244
	Jchar   chParity;			// У��, 'N': ��, 'O': ��У��, 'E': żУ��
	//##ModelId=40E4AA8D0262
	Jchar   chStopbit;			// ֹͣλ, 0 or '0':1λ, 1 or '1':1.5λ, 2 or '2':2λ
	//##ModelId=40E4AA8D0276
	Jint8   byFctrl;			// ������, 0: ��, 1: Ӳ��, 2: ���
	//##ModelId=40E4AA8D0294
	Jchar   strDevicename[12];	// �豸��, ��/dev/tty01,\\.\COM1��
	//##ModelId=40E4AA8D02B2
	Jint32  nReserved;			// ����
};

//##ModelId=40E4AA8B0358
//## ����ͨѶ��װ�࣬��������ݴӴ���ͨ���н��ղ��ŵ�ͨ����ԭʼ�������С�
//����ͨ�������ʡ�����λ����ֹλ��ͬ���첽�Ƚ��н��պͷ��͡�
class LIBCORE_EXPORT CSerialComm
{
public:

    //##ModelId=40E4AA8C0300
    virtual ~CSerialComm() = 0;

    //##ModelId=40E4AA8C030B
    //## �򿪴��ڣ��������
	virtual bool Open() = 0;

	// �����Ƿ��
    //##ModelId=40E4AA8C030D
	virtual bool IsOpen() = 0;

	// �رմ���
    //##ModelId=40E4AA8C0314
	virtual bool Close() = 0;

    //##ModelId=40E4AA8C0316
    //## �Ӵ����н�������
    virtual int ReadData(
        void* data, 
        int count
    ) = 0;

    //##ModelId=40E4AA8C0328
    //## ��������
    virtual int WriteData(
        void* data, 
        int count
    ) = 0;

	// ����ͨ�Ų�������
    //##ModelId=40E4AA8C0333
	virtual bool SetCommParam(const s_serial_param& comm_param) = 0;

    //##ModelId=40E4AA8C033C
    virtual bool SetBPS(Juint16 bps)=0;

	// ����RTS�źű�־
	virtual void setRTS(bool bSet)=0;
	// ����DTR�źű�־
	virtual void setDTR(bool bSet)=0;	

    //##ModelId=40E4AA8C0347
	//## ����һ��ʵ�������ݲ���ϵͳƽ̨���������ʵ��
	static CSerialComm*  CreateInstance(const s_serial_param& comm_param);

	// �ͷŶ�����Դ
    //##ModelId=40E4AA8C0351
	void Release();

	// �õ��������ò���
    //##ModelId=40E4AA8C0352
	s_serial_param GetCommParam();

protected:
	
	// ����ͨ�Ų���
    //##ModelId=40E4AA8C02ED
	s_serial_param m_comm_param;

};

}
#endif /* CSERIALCOMM_H_HEADER_INCLUDED_C2793608 */
