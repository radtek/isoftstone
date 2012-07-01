
// ====================����ͨ�Ű�װ����Unix�µ���ʵ��============================
//
// �����߲���ֱ��ʹ�ô��ֱ࣬��ʹ��CSerialComm�࣬CSerialComm����ݲ���ϵͳƽ̨
// ���о����ʵ����
//
////////////////////////////////////////////////////////////////////////////////////
#if !defined(_WIN32)
#include "iestypedef.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#if defined(HPUX)
#include <sys/modem.h>
#endif//HPUX

#if (defined(LINUX) || defined(AIX))
#include <sys/ioctl.h>
#endif//LINUX || AIX

#include <fcntl.h>
#include "serialcommuniximpl.h"

using namespace escore;

//���캯��
CSerialCommUnixImpl::CSerialCommUnixImpl(const s_serial_param& param)
{
	m_comm_param = param;			//���ڲ���
	m_fd = -1;						//��ʾ�豸���ڹر�״̬
	m_nDevStaus = SERIAL_CLOSE;		//�豸״̬λ�ر�
}

//��������
CSerialCommUnixImpl::~CSerialCommUnixImpl()
{
	if(m_fd > 0)
		Close();
}

//�򿪴����豸
bool CSerialCommUnixImpl::Open()
{
	bool bRet = false;
	if (m_fd > 0)
		return true;

	m_fd = open(m_comm_param.strDevicename, O_RDWR | O_NOCTTY | O_NDELAY);//
	if (m_fd < 0)
		m_nDevStaus = SERIAL_ERROR;
	else {
		m_nDevStaus = SERIAL_OPEN;

		tcgetattr(m_fd, &m_termio_old);
		bRet = SetCommParam(m_comm_param);
		tcgetattr(m_fd, &m_termio_new);
	}

	return bRet;
}

// ����ͨ�Ų�������
bool CSerialCommUnixImpl::SetCommParam(const s_serial_param& devparam)
{
	SetBaudrate(devparam.wBPS);
	SetDataBit(devparam.byDatabits);
	SetParityCheck(devparam.chParity);
	SetStopBit(devparam.chStopbit);
	SetOtherOption();

	return true;
}


int CSerialCommUnixImpl::BAUDRATE(int baudrate)
{
	switch (baudrate) {
		case 0:
			return (B0);
		case 50:
			return (B50);
		case 75:
			return (B75);
		case 110:
			return (B110);
		case 134:
			return (B134);
		case 150:
			return (B150);
		case 200:
			return (B200);
		case 300:
			return (B300);
		case 600:
			return (B600);
		case 1200:
			return (B1200);
		case 2400:
			return (B2400);
		case 4800:
			return (B4800);
		case 9600:
			return (B9600);
		case 19200:
			return (B19200);
		case 38400:
			return (B38400);
// ����������������aix��û�ж���,������sun��solaris�ж���.
		case 57600:
//			return (B57600);
		case 115200:
//			return (B115200);
		default:
			return (B9600);
	}
}

//���ò�����
void CSerialCommUnixImpl::SetBaudrate(int baudrate)
{
	struct termios options;

	tcgetattr(m_fd, &options);
	
	cfsetispeed(&options, BAUDRATE(baudrate));
	cfsetospeed(&options, BAUDRATE(baudrate));
	options.c_cflag |= (CLOCAL | CREAD);

	tcsetattr(m_fd, TCSANOW, &options);
}

//����������
void CSerialCommUnixImpl::SetFlowControl(int)
{
/*
	switch(fctrl) {
		case 0:
			m_termio_new.c_cflag &= ~CRTSCTS;
			break;
		case 1:
		default:
			m_termio_new.c_cflag |= CRTSCTS;
			break;
		case 2:
		break;
	}
*/
}

//��������λ
void CSerialCommUnixImpl::SetDataBit(int databit)
{
	struct termios options;

	tcgetattr(m_fd, &options);

	options.c_cflag &= ~CSIZE;
	switch (databit) {
		case 5:
			options.c_cflag |= CS5;
			break;
		case 6:
			options.c_cflag |= CS6;
			break;
		case 7:
			options.c_cflag |= CS7;
			break;
		case 8:
		default:
			options.c_cflag |= CS8;
			break;
	}

	tcsetattr(m_fd, TCSANOW, &options);
}

//����ֹͣλ
void CSerialCommUnixImpl::SetStopBit(char stopbit)
{
	struct termios options;

	tcgetattr(m_fd, &options);

	switch (stopbit) {
		case 2:
		case '2':
			options.c_cflag |= CSTOPB;
			break;
		case 0:
		case '0':
		case 1:
		case '1':
		default:
			options.c_cflag &= ~CSTOPB;
			break;
	}

	tcsetattr(m_fd, TCSANOW, &options);
}

//����У����
void CSerialCommUnixImpl::SetParityCheck(char parity)
{
	struct termios options;

	tcgetattr(m_fd, &options);

	switch (parity) {
		case 'E':
		case 'e':
			options.c_cflag |= PARENB;
			options.c_cflag &= ~PARODD;
			break;
		case 'O':
		case 'o':
			options.c_cflag |= PARENB;
			options.c_cflag |= PARODD;
			break;
		case 'N':
		case 'n':
		default:
			options.c_cflag &= ~PARENB;
			break;
	}

	tcsetattr(m_fd, TCSANOW, &options);
}

// ���ú���
void CSerialCommUnixImpl::SetOtherOption()
{
	struct termios options;

	tcgetattr(m_fd, &options);

	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
//	options.c_iflag |= (INPCK | ISTRIP);
	options.c_iflag &= ~(IXON | IXOFF | IXANY);

	tcsetattr(m_fd, TCSANOW, &options);
}

//�رմ����豸
bool CSerialCommUnixImpl::Close()
{
	tcsetattr(m_fd, TCSADRAIN, &m_termio_old);
	if (m_fd > -1)
		close(m_fd);
	m_fd = -1;
	m_nDevStaus = SERIAL_CLOSE;
	return true;
}

//д���豸����
int CSerialCommUnixImpl::WriteData(void* buf, int length)
{
	if (m_nDevStaus != SERIAL_OPEN)
        	return -1;

	int write_count = -1;
/*	timeval tv_timeout;
	fd_set fs_write;

	FD_ZERO(&fs_write);
	FD_SET(m_fd, &fs_write);

	tv_timeout.tv_sec = 0;
	tv_timeout.tv_usec = 100000;

	int retval = select(m_fd + 1, NULL, &fs_write, NULL, &tv_timeout);
	if (retval) */
		write_count = write(m_fd, buf, length);

	return write_count;
}

//��ȡ�豸����
int CSerialCommUnixImpl::ReadData(void* data, int length)
{
	if (m_nDevStaus != SERIAL_OPEN)
		return -1;

//	int retval = 0;
//	fd_set fs_read;
//
//	FD_ZERO(&fs_read);
//	FD_SET(m_fd, &fs_read);
//
//	timeval tv_timeout;
//	tv_timeout.tv_sec = 0;
//	tv_timeout.tv_usec = 100000;
//
//	if (select(m_fd + 1, &fs_read, NULL, NULL, &tv_timeout))
        	return read(m_fd, data, length);
//	else
//        	return -1;
}

//��ȡ�豸�Ĳ�����
int CSerialCommUnixImpl::GetBaudrate()
{
    return (BAUDRATE(cfgetospeed(&m_termio_new)));
}

//�������ò�����
bool CSerialCommUnixImpl::SetBPS(Juint16 bps)
{
	SetBaudrate(bps);
	tcgetattr(m_fd, &m_termio_new);
	return true;
}
// ����RTS�źű�־
void CSerialCommUnixImpl::setRTS(bool bSet)
{
	int status;

	ioctl(m_fd, TIOCMGET, &status);
	if (bSet)
		status |= TIOCM_RTS;
	else
		status &= ~TIOCM_RTS;
	ioctl(m_fd, TIOCMSET, &status);
}

// ����DTR�źű�־
void CSerialCommUnixImpl::setDTR(bool bSet)
{
	int status;

	ioctl(m_fd, TIOCMGET, &status);
	if (bSet)
		status |= TIOCM_DTR;
	else
		status &= ~TIOCM_DTR;
	ioctl(m_fd, TIOCMSET, &status);
}

#endif // _WIN32
