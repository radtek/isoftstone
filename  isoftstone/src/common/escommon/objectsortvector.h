
#ifndef OBJECTSORTVECTOR_H_
#define OBJECTSORTVECTOR_H_

#include "escore.h"
#include "iestypedef.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <IceUtil/RWRecMutex.h>
#include "IceUtil/Mutex.h"
#include <qobject.h>
#include <qstring.h>
#include "predicateinterface.h"
#include "unaryprocinterface.h"
#include "freetemplate.h"


#pragma warning(disable: 4100)

namespace escommon
{

// 使用排序的 vector 实现的容器类
// 使用 TValue() 作为删除标记，所以不能 addObject(TValue()) 的值
// TFreeItem 模板参数参与 TValue 对象的释放
// ACE_LOCK 模板参数决定本类是否为线程安全的
template <class TKey, class TValue, class TDataCompare, class TFreeItem, class ACE_LOCK>
class CObjectSortVector
{
public:
	// 值类型
	typedef TValue value_type;
	// 判断式接口
	typedef escommon::CPredicateInterface<value_type> CPredicateInterface;
	// 运算接口
	typedef escommon::CUnaryProcInterface<value_type> CUnaryProcInterface;

	CObjectSortVector(void)
		: s_nullValue(TValue())
	{
		m_bAddDirty = JFALSE;
		m_uDelCount = 0;
	};

	~CObjectSortVector(void)
	{
		clear();
	};

	// 清空所保存对象
	void clear(void)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourceVector::iterator ite;
		for (ite = m_objects.begin(); ite != m_objects.end(); ++ite)
		{
			m_freeItem(*ite);
		}
		m_objects.clear();

		m_bAddDirty = JFALSE;
		m_uDelCount = 0;
	};

	// 取记录个数
	Juint32 size(void) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		return m_objects.size();
	};

	// 判断是否为空
	Jboolean empty(void) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		return m_objects.empty();
	};

	// 获取对象
	// 返回值指示是否存在此对象
	Jboolean getObject(const TKey& keyValue, TValue& objectValue) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		// 检测是否已经排序
		checkDirty();

		Jboolean bRet = JFALSE;

		typename CResourceVector::const_iterator ite = std::lower_bound(m_objects.begin(), m_objects.end(), keyValue, m_dataCompare);
		if (ite != m_objects.end() && *ite == keyValue)
		{
			objectValue = *ite;
			bRet = JTRUE;
		}

		return bRet;
	};

	// 获取对象
	// 如果没有与键值对应的对象则返回缺省值
	TValue getObject(const TKey& keyValue) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		TValue objectValue;
		if (!getObject(keyValue, objectValue))
		{
			objectValue = s_nullValue;
		}
		return objectValue;
	};

	// 获取满足 pred 条件的对象
	Jboolean getObject_if(const CPredicateInterface& pred, TValue& objectValue) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		// 检测是否已经排序
		checkDirty();

		Jboolean bRet = JFALSE;

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			const value_type& record = *ite;
			if (pred(record))
			{
				objectValue = record;
				bRet = JTRUE;
				break;
			}
		}

		return bRet;
	};

	// 获取满足 pred 条件的对象
	TValue getObject_if(const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		TValue objectValue;
		if (!getObject_if(pred, objectValue))
		{
			objectValue = s_nullValue;
		}
		return objectValue;
	};

	// 获取全部对象
	void getObjects(std::vector<TValue>& container) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		// 检测是否已经排序
		checkDirty();

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			container.push_back(*ite);
		}
	};

	// 获取满足 pred 条件的全部对象
	void getObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		// 检测是否已经排序
		checkDirty();

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			// 通过判断式决定 ite 是否满足条件，是则追加到迭代器末尾
			const value_type& record = *ite;
			if (pred(record))
			{
				container.push_back(record);
			}
		}
	};

	// 遍历全部对象，对每个对象执行 op 操作
	void for_each(CUnaryProcInterface& op) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		// 检测是否已经排序
		checkDirty();

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			op(*ite);
		}
	};

	// 加入对象
	// 返回值：JTRUE = 加入成功
	Jboolean addObject(const TKey& keyValue, const TValue& objectValue)
	{
		Q_UNUSED(keyValue);

		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		// objectValue 为缺省值不能加入到本容器
		if (s_nullValue != objectValue)
		{
			// 考虑到性能原因，每次加入时并不判断是否已经存在记录，也就不进行排序
			// 等调用 resort 后再进行一次排序
			m_objects.push_back(objectValue);
			m_bAddDirty = JTRUE;
			bRet = JTRUE;
		}

		return bRet;
	};

	// 删除对象
	// JTRUE = 删除成功、JFALSE = 此键值不存在于本容器中，删除失败
	Jboolean delObject(const TKey& keyValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		// 检测 m_bAddDirty 标志，允许有 m_uDelCount > 0
		checkAddDirty();

		Jboolean bRet = JFALSE;

		typename CResourceVector::iterator ite = std::lower_bound(m_objects.begin(), m_objects.end(), keyValue, m_dataCompare);
		if (ite != m_objects.end() && *ite == keyValue)
		{
			value_type& record = *ite;
			if (s_nullValue != record)
			{
				m_freeItem(record);

				// 不立即删除 keyValue 所指的对象，等调用 resort 时再真正删除
				record = s_nullValue;
				++m_uDelCount;
				bRet = JTRUE;
			}
		}

		return bRet;
	};

	// 删除满足 pred 条件的全部对象
	void delObjects_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		// 检测 m_bAddDirty 标志，允许有 m_uDelCount > 0
		checkAddDirty();

		typename CResourceVector::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			value_type& record = *ite;
			if (s_nullValue != record && pred(record))
			{
				m_freeItem(record);
				// 不立即删除 keyValue 所指的对象，等调用 resort 时再真正删除
				record = s_nullValue;
				++m_uDelCount;
			}
		}
	};

	// 取走对象，对象的生命周期由调用者负责
	// JTRUE = 取走成功、JFALSE = 此键值不存在于本容器中，取走失败
	Jboolean robObject(const TKey& keyValue, TValue& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		// 检测 m_bAddDirty 标志，允许有 m_uDelCount > 0
		checkAddDirty();

		Jboolean bRet = JFALSE;

		typename CResourceVector::iterator ite = std::lower_bound(m_objects.begin(), m_objects.end(), keyValue, m_dataCompare);
		if (ite != m_objects.end() && *ite == keyValue)
		{
			value_type& record = *ite;
			if (s_nullValue != record)
			{
				objectValue = record;
				// 不立即删除 keyValue 所指的对象，等调用 resort 时再真正删除
				record = s_nullValue;
				++m_uDelCount;
				bRet = JTRUE;
			}
		}

		return bRet;
	};

	// 取走对象，对象的生命周期由调用者负责
	// 如果没有与键值对应的对象则返回缺省值
	TValue robObject(const TKey& keyValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		TValue objectValue;
		if (!robObject(keyValue, objectValue))
		{
			objectValue = s_nullValue;
		}
		return objectValue;
	};

	// 取走满足 pred 条件的对象，对象的生命周期由调用者负责
	Jboolean robObject_if(const CPredicateInterface& pred, TValue& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		// 检测 m_bAddDirty 标志，允许有 m_uDelCount > 0
		checkAddDirty();

		Jboolean bRet = JFALSE;

		typename CResourceVector::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			value_type& record = *ite;
			if (s_nullValue != record && pred(record))
			{
				objectValue = record;
				// 不立即删除 keyValue 所指的对象，等调用 resort 时再真正删除
				record = s_nullValue;
				++m_uDelCount;
				bRet = JTRUE;
				break;
			}
		}

		return bRet;
	};

	// 取走满足 pred 条件的对象，对象的生命周期由调用者负责
	TValue robObject_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		TValue objectValue;
		if (!robObject_if(pred, objectValue))
		{
			objectValue = s_nullValue;
		}
		return objectValue;
	};

	// 取走全部对象，对象的生命周期由调用者负责
	void robObjects(std::vector<TValue>& container)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		getObjects(container);

		m_objects.clear();
		m_bAddDirty = JFALSE;
		m_uDelCount = 0;
	};

	// 取走满足 pred 条件的全部对象，对象的生命周期由调用者负责
	void robObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourceVector::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			value_type& record = *ite;
			if (s_nullValue != record && pred(record))
			{
				container.push_back(record);
				// 不立即删除 keyValue 所指的对象，等调用 resort 时再真正删除
				record = s_nullValue;
				++m_uDelCount;
			}
		}
	};

	// 修改完成
	void resort(void)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		if (m_bAddDirty || m_uDelCount > 0)
		{
			// 增加新对象，需要重新排序
			std::stable_sort(m_objects.begin(), m_objects.end(), m_dataCompare);
			m_bAddDirty = JFALSE;

			if (m_uDelCount > 0)
			{
				// 有 m_uDelCount 个对象被删除，经过排序，都集中到容器末尾
				m_objects.erase(m_objects.end()-m_uDelCount, m_objects.end());
				m_uDelCount = 0;
			}
		}
	}

	// 交换容器内容
	void swap(CObjectSortVector& right)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);
		IceUtil::WLockT<ACE_LOCK> guard_right(right.m_Mutex);

		m_objects.swap(right.m_objects);
		std::swap(m_bAddDirty, right.m_bAddDirty);
		std::swap(m_uDelCount, right.m_uDelCount);
	};

private:
	void checkDirty(void) const
	{
		// 在 get 等操作前检测 m_bAddDirty、m_bDelDirty 标志
		if (m_bAddDirty || m_uDelCount > 0)
		{
			throw std::exception("CObjectSortVector 类在读取之前必须先排序");
		}
	}

	void checkAddDirty(void) const
	{
		// 在 del 等操作前检测 m_bAddDirty 标志
		if (m_bAddDirty)
		{
			throw std::exception("CObjectSortVector 类在读取之前必须先排序");
		}
	}

	// 定义容器类型
	typedef std::vector<value_type> CResourceVector;

	// 同步对象
	mutable ACE_LOCK m_Mutex;

	// 使用 vector 保存 键值下标 -> 对象的映射
	CResourceVector m_objects;

	// 当有对象增加，设置为脏数据，在 get 等操作前需要排序
	Jboolean m_bAddDirty;

	// 当有对象删除，m_uDelCount+1，在 get 等操作前需要排序，并清除
	Juint32 m_uDelCount;

	TFreeItem m_freeItem;
	TDataCompare m_dataCompare;

	// 零值
	const TValue s_nullValue;

};

} // namespace 

#endif // OBJECTSORTVECTOR_H_