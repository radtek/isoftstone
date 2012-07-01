
#ifndef LIMITPOOL_H_HEADER_INCLUDED_
#define LIMITPOOL_H_HEADER_INCLUDED_

#include "escore.h"
#include "iestypedef.h"
#include <deque>
#include <iceutil/Mutex.h>

namespace escore {

// ������
template <class CItem>
struct CNoDiscardStrategy
{
	typedef typename std::deque<CItem> CItemDeque;
	Juint32 operator()(CItemDeque&) const
	{
		return 0;
	}
};

// ��̭��ɵ�����
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

// ��̭ǰ�벿�֣��ȽϺ� :)
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

// ���޳�ģ����
// �ر������̰߳�ȫ
// CItem ������Ҫ������࣬CDiscardStrategy ��������
// �ع�����ԣ������δ���������з����ݳɹ��������������ʹ��ĳ�ֶ�������
// �ӳ���ȡ���ݣ��Ƚ��ȳ�
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

	// ��ճ�����
	void clear(void)
	{
		IceUtil::Mutex::Lock guard(m_mutex);

		m_limitPool.clear();
	}

	// ��������
	void initLimitSize(Juint32 uLimitSize)
	{
		IceUtil::Mutex::Lock guard(m_mutex);

		m_uLimitSize = (uLimitSize == 0) ? s_defaultLimitSize : uLimitSize;
		if (m_limitPool.size() > m_uLimitSize)
		{
			// �������ƣ�ֱ�Ӷ�����������
			m_limitPool.resize(m_uLimitSize);
		}
	}

	// �����з��¶���
	// ����ֵ JTRUE = �����ݳɹ���������ñ��������ݣ����������ݲ��ԣ��򷵻� JFALSE
	// nDiscardCount ���ض�������
	Jboolean push(const CItem& item, Juint32& nDiscardCount)
	{
		IceUtil::Mutex::Lock guard(m_mutex);

		Jboolean bRet = JTRUE;
		nDiscardCount = 0;

		if (m_limitPool.size() >= m_uLimitSize)
		{
			CDiscardStrategy discardStrategy;
			// ���ض�������
			nDiscardCount = discardStrategy(m_limitPool);
			bRet = (nDiscardCount > 0);
		}
		if (bRet)
		{
			m_limitPool.push_back(item);
		}
		return bRet;
	}

	// ������ȡ����
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

	// �ط��ʻ������
	mutable IceUtil::Mutex m_mutex;

	// �ش�С
	Juint32 m_uLimitSize;
	// ȱʡ�ش�С
	static const Juint32 s_defaultLimitSize = 128;

	typedef typename CDiscardStrategy::CItemDeque CItemDeque;

	// ��������
	CItemDeque m_limitPool;

};

} // namespace 



#endif /* LIMITPOOL_H_HEADER_INCLUDED_BF0B68F7 */
