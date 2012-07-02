
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

	// 设置删除标志，如果原先是已删除，则设置失败
	virtual bool remove(void);
	// 判断本对象是否处于删除状态
	virtual bool isRemoved(void);

	// 获取服务的名字
	std::string getServiceName(void) const;

	// 设置最大空闲时间，超过此设置对象没有再次调用 active，则认为对象处于空闲状态
	// 单位：秒
	void setMaxIdleTime(Juint32 nSeconds);
	// 获取最大空闲时间设置
	Juint32 getMaxIdleTime(void) const;

	void destroySession();

protected:
	CActivity(){};
	CActivity(const std::string& strServiceName);
	CActivity(const std::string& strServiceName, Juint32 nSeconds);

private:
	CActivity(const CActivity&);
	CActivity& operator=(const CActivity&);

	// 本服务的名字
	const std::string m_strServiceName;

	// 删除标志、时间信息锁
	mutable IceUtil::Mutex m_mutex;

	// 最大空闲时间
	Juint32 m_maxIdleTime;
	// 上次活动时间，保存 CPU 滴答时间
	IceUtil::Time m_lastActiveTime;
	//缺省的空闲时间，单位：秒
	static Juint32 s_defaultIdleSeconds;

	// 已删除标志
	Jboolean m_removed;

};


} // namespace HiRTDB

#endif // ACTIVITYBASE_H_20070208
