
#ifndef LIMITPOOL_H_HEADER_INCLUDED_
#define LIMITPOOL_H_HEADER_INCLUDED_

#include "escore.h"
#include "iestypedef.h"
#include <deque>
#include <iceutil/Mutex.h>

namespace escore {

// 不丢弃
template <class CItem>
struct CNoDiscardStrategy
{
	typedef typename std::deque<CItem> CItemDeque;
	Juint32 operator()(CItemDeque&) const
	{
		return 0;
	}
};

// 淘汰最旧的数据
template <class CItem>
struct CDiscardOldestStrategy
{
	typedef typename std::deque<CItem> CItemDeque;
	Juint32 operator()(CItemDeque& itemDeque) const
	{
		itemDeque.pop_front();
		return 1;
	}
};

// 淘汰前半部分，比较恨 :)
template <class CItem>
struct CDiscardHalfStrategy
{
	typedef typename std::deque<CItem> CItemDeque;
	Juint32 operator()(CItemDeque& itemDeque) const
	{
		Juint32 nDiscardCount = itemDeque.size()/2;
		itemDeque.erase(itemDeque.begin(), itemDeque.begin()+nDiscardCount);
		return nDiscardCount;
	}
};

// 受限池模板类
// 池本身是线程安全
// CItem 传入需要保存的类，CDiscardStrategy 丢弃策略
// 池管理策略：如果池未满，往池中放数据成功，如果池满，则使用某种丢弃策略
// 从池中取数据，先进先出
template <class CItem, class CDiscardStrategy = CDiscardOldestStrategy<CItem> >
class CLimitPool
{
public:
	CLimitPool(Juint32 uLimitSize=s_defaultLimitSize)
	{
		m_uLimitSize = (uLimitSize == 0) ? s_defaultLimitSize : uLimitSize;
	}

	~CLimitPool(void)
	{
	}

	// 清空池数据
	void clear(void)
	{
		IceUtil::Mutex::Lock guard(m_mutex);

		m_limitPool.clear();
	}

	// 调整限制
	void initLimitSize(Juint32 uLimitSize)
	{
		IceUtil::Mutex::Lock guard(m_mutex);

		m_uLimitSize = (uLimitSize == 0) ? s_defaultLimitSize : uLimitSize;
		if (m_limitPool.size() > m_uLimitSize)
		{
			// 调整限制，直接丢弃超出部分
			m_limitPool.resize(m_uLimitSize);
		}
	}

	// 往池中放新对象
	// 返回值 JTRUE = 放数据成功，如果采用保留老数据，丢弃新数据策略，则返回 JFALSE
	// nDiscardCount 返回丢弃个数
	Jboolean push(const CItem& item, Juint32& nDiscardCount)
	{
		IceUtil::Mutex::Lock guard(m_mutex);

		Jboolean bRet = JTRUE;
		nDiscardCount = 0;

		if (m_limitPool.size() >= m_uLimitSize)
		{
			CDiscardStrategy discardStrategy;
			// 返回丢弃个数
			nDiscardCount = discardStrategy(m_limitPool);
			bRet = (nDiscardCount > 0);
		}
		if (bRet)
		{
			m_limitPool.push_back(item);
		}
		return bRet;
	}

	// 往池中取对象
	Jboolean pop(CItem& item)
	{
		IceUtil::Mutex::Lock guard(m_mutex);

		Jboolean bRet = (!m_limitPool.empty());
		if (bRet)
		{
			item = m_limitPool.front();
			m_limitPool.pop_front();
		}
		return bRet;
	}

	Juint32 size(void) const
	{
		IceUtil::Mutex::Lock guard(m_mutex);

		return m_limitPool.size();
	}

	Jboolean empty(void) const
	{
		IceUtil::Mutex::Lock guard(m_mutex);

		return m_limitPool.empty();
	}

private:
	CLimitPool(const CLimitPool& right);
	CLimitPool& operator=(const CLimitPool& right);

	// 池访问互斥对象
	mutable IceUtil::Mutex m_mutex;

	// 池大小
	Juint32 m_uLimitSize;
	// 缺省池大小
	static const Juint32 s_defaultLimitSize = 128;

	typedef typename CDiscardStrategy::CItemDeque CItemDeque;

	// 空闲项缓存池
	CItemDeque m_limitPool;

};

} // namespace 



#endif /* LIMITPOOL_H_HEADER_INCLUDED_BF0B68F7 */
