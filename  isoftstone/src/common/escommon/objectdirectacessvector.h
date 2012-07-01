
#ifndef OBJECTDIRECTACESSVECTOR_H_
#define OBJECTDIRECTACESSVECTOR_H_

#include "escore.h"
#include "iestypedef.h"
#include <vector>
#include <iceutil/RWRecMutex.h>
#include "predicateinterface.h"
#include "unaryprocinterface.h"
#include "freetemplate.h"

namespace escommon {

template <class TKey>
class CCommonKey2Id
{
public:
	Juint32 operator()(const TKey& keyValue) const
	{
		return keyValue;
	};
};

// 键值作为下标 -> 对象的映射
// 使用下标进行查找，浪费内存，优化查找速度
// CKey2Id 转换键值到下标的仿函数
// CFreeItem 模板参数参与 TValue 对象的释放
// ACE_LOCK 模板参数决定本类是否为线程安全的
template <class TKey, class CKey2Id, class TValue, class CFreeItem, class ACE_LOCK>
class CObjectDirectAcessVector
{
public:
	// 值类型
	typedef TValue value_type;
	// 判断式接口
	typedef escommon::CPredicateInterface<value_type> CPredicateInterface;
	// 运算接口
	typedef escommon::CUnaryProcInterface<value_type> CUnaryProcInterface;

	CObjectDirectAcessVector(void)
	{
	};

	~CObjectDirectAcessVector(void)
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

		Jboolean bRet = JFALSE;

		if (checkKey(keyValue))
		{
			const value_type& record = getValue(keyValue);
			// 判断本记录是否有效
			if (checkValue(record))
			{
				objectValue = record;
				bRet = JTRUE;
			}
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
			objectValue = TValue();
		}
		return objectValue;
	};

	// 获取满足 pred 条件的对象
	Jboolean getObject_if(const CPredicateInterface& pred, TValue& objectValue) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			const value_type& record = *ite;
			if (checkValue(record) && pred(record))
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
			objectValue = TValue();
		}
		return objectValue;
	};

	// 获取全部对象
	void getObjects(std::vector<TValue>& container) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			const value_type& record = *ite;
			if (checkValue(record))
			{
				container.push_back(record);
			}
		}
	};

	// 获取满足 pred 条件的全部对象
	void getObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			// 通过判断式决定 ite 是否满足条件，是则追加到迭代器末尾
			const value_type& record = *ite;
			if (checkValue(record) && pred(record))
			{
				container.push_back(record);
			}
		}
	};

	// 遍历全部对象，对每个对象执行 op 操作
	void for_each(CUnaryProcInterface& op) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			const value_type& record = *ite;
			if (checkValue(record))
			{
				op(record);
			}
		}
	};

	// 加入对象
	// 返回值：JTRUE = 加入成功、JFALSE = 此键值已经存在于本容器中，加入失败
	Jboolean addObject(const TKey& keyValue, const TValue& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		// 如果键值超出容器大小，先扩展出
		expandSize(keyValue);

		value_type& record = getValue(keyValue);
		// 判断是否已经存在记录
		if (!checkValue(record))
		{
			record = objectValue;
			bRet = JTRUE;
		}
		return bRet;
	};

	// 删除对象
	// JTRUE = 删除成功、JFALSE = 此键值不存在于本容器中，删除失败
	Jboolean delObject(const TKey& keyValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		if (checkKey(keyValue))
		{
			value_type& record = getValue(keyValue);
			// 判断本记录是否有效
			if (checkValue(record))
			{
				m_freeItem(record);
				record = TValue();
				bRet = JTRUE;
			}
		}

		return bRet;
	};

	// 删除满足 pred 条件的全部对象
	void delObjects_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourceVector::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			value_type& record = *ite;
			if (checkValue(record) && pred(record))
			{
				m_freeItem(record);
				record = TValue();
			}
		}
	};

	// 取走对象，对象的生命周期由调用者负责
	// JTRUE = 取走成功、JFALSE = 此键值不存在于本容器中，取走失败
	Jboolean robObject(const TKey& keyValue, TValue& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		if (checkKey(keyValue))
		{
			value_type& record = getValue(keyValue);
			// 判断本记录是否有效
			if (checkValue(record))
			{
				objectValue = record;
				record = TValue();
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
			objectValue = TValue();
		}
		return objectValue;
	};

	// 取走满足 pred 条件的对象，对象的生命周期由调用者负责
	Jboolean robObject_if(const CPredicateInterface& pred, TValue& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourceVector::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			value_type& record = *ite;
			if (checkValue(record) && pred(record))
			{
				objectValue = record;
				record = TValue();
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
			objectValue = TValue();
		}
		return objectValue;
	};

	// 取走全部对象，对象的生命周期由调用者负责
	void robObjects(std::vector<TValue>& container)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		getObjects(container);
		m_objects.clear();
	};

	// 取走满足 pred 条件的全部对象，对象的生命周期由调用者负责
	void robObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourceVector::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			value_type& record = *ite;
			if (checkValue(record) && pred(record))
			{
				container.push_back(record);
				record = TValue();
			}
		}
	};

	// 内部存储已经保证有序，为了和 CObjectDirectAcessVector 接口一致，也声明此函数
	void resort(void)
	{
	}

	// 交换容器内容
	void swap(CObjectDirectAcessVector& right)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);
		IceUtil::WLockT<ACE_LOCK> guard_right(right.m_Mutex);
		m_objects.swap(right.m_objects);
	};

private:
	// 定义容器类型
	typedef std::vector<value_type> CResourceVector;

	// 键值作为下标获取只读对象
	const value_type& getValue(const TKey& keyValue) const
	{
		return m_objects[m_key2Id(keyValue)];
	};

	// 键值作为下标获取可读写对象
	value_type& getValue(const TKey& keyValue)
	{
		return m_objects[m_key2Id(keyValue)];
	};

	// 检测键值作为下标是否合法
	Jboolean checkKey(const TKey& keyValue) const
	{
		return (m_key2Id(keyValue) < m_objects.size());
	};

	Jboolean checkValue(const TValue& objectValue) const
	{
		return (objectValue != TValue());
	};

	// 扩展 vector 以容纳新的键值
	void expandSize(const TKey& keyValue)
	{
		if (m_key2Id(keyValue) >= m_objects.size())
		{
			m_objects.resize(m_key2Id(keyValue)+1);
		}
	};

	// 使用 vector 保存 键值下标 -> 对象的映射
	CResourceVector m_objects;

	// 同步对象
	mutable ACE_LOCK m_Mutex;

	CKey2Id m_key2Id;
	CFreeItem m_freeItem;

};

} // namespace escommon

#endif // OBJECTDIRECTACESSVECTOR_H_20070822
