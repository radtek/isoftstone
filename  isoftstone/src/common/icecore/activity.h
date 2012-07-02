
#ifndef ACTIVITYBASE_H_20070208
#define ACTIVITYBASE_H_20070208

#include "icecore.h"
#include "iestypedef.h"
#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>

namespace HiRTDB
{

class LIB_ICECORE_EXPORT CActivity
{
public:
	virtual ~CActivity(void);

	virtual void keepAlive(void) ;
	virtual void keepAlive(const IceUtil::Time& lastTime);

	virtual bool isAlive(void);
	virtual bool isAlive(const IceUtil::Time& lastTime);

	// ����ɾ����־�����ԭ������ɾ����������ʧ��
	virtual bool remove(void);
	// �жϱ������Ƿ���ɾ��״̬
	virtual bool isRemoved(void);

	// ��ȡ���������
	std::string getServiceName(void) const;

	// ����������ʱ�䣬���������ö���û���ٴε��� active������Ϊ�����ڿ���״̬
	// ��λ����
	void setMaxIdleTime(Juint32 nSeconds);
	// ��ȡ������ʱ������
	Juint32 getMaxIdleTime(void) const;

	void destroySession();

protected:
	CActivity(){};
	CActivity(const std::string& strServiceName);
	CActivity(const std::string& strServiceName, Juint32 nSeconds);

private:
	CActivity(const CActivity&);
	CActivity& operator=(const CActivity&);

	// �����������
	const std::string m_strServiceName;

	// ɾ����־��ʱ����Ϣ��
	mutable IceUtil::Mutex m_mutex;

	// ������ʱ��
	Juint32 m_maxIdleTime;
	// �ϴλʱ�䣬���� CPU �δ�ʱ��
	IceUtil::Time m_lastActiveTime;
	//ȱʡ�Ŀ���ʱ�䣬��λ����
	static Juint32 s_defaultIdleSeconds;

	// ��ɾ����־
	Jboolean m_removed;

};


} // namespace HiRTDB

#endif // ACTIVITYBASE_H_20070208
