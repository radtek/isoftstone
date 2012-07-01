
#ifndef OBJECTMAP_H_
#define OBJECTMAP_H_

#include "escore.h"
#include "iestypedef.h"
#include <map>
#include <vector>
#include <IceUtil/RWRecMutex.h>
#include "IceUtil/Mutex.h"
#include "predicateinterface.h"
#include "unaryprocinterface.h"
#include "freetemplate.h"

namespace escommon {

// 使用 map 实现的容器类
// TFreeItem 模板参数参与 TValue 对象的释放
// ACE_LOCK 模板参数决定本类是否为线程安全的
template <class TKey, class TValue, class TFreeItem, class ACE_LOCK>
class CObjectMap
{
public:
	// 值类型
	typedef TValue value_type;
	// 判断式接口
	typedef escommon::CPredicateInterface<value_type> CPredicateInterface;
	// 运算接口
	typedef escommon::CUnaryProcInterface<value_type> CUnaryProcInterface;

	CObjectMap(void)
	{
	};

	~CObjectMap(void)
	{
		clear();
	};

	//## 清空所保存对象
	void clear(void)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMap::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			m_freeItem(ite->second);
		}
		m_objects.clear();
	};

	// 取记录个数
	Juint32 size(void) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		return m_objects.size();
	};

	// 判断是否为空
	Jboolean empty(void) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		return m_objects.empty();
	};

	// 获取对象
	// 返回值指示是否存在此对象
	Jboolean getObject(const TKey& keyValue, TValue& objectValue) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourceMap::const_iterator ite = m_objects.find(keyValue);
		// 如果没有找到此键值，迭代器指向容器的末尾
		if (ite != m_objects.end())
		{
			objectValue = ite->second;
			bRet = JTRUE;
		}

		return bRet;
	};

	// 获取对象
	// 如果没有与键值对应的对象则返回缺省值
	TValue getObject(const TKey& keyValue) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

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
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourceMap::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			const value_type& record = ite->second;
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
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

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
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMap::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			container.push_back(ite->second);
		}
	};

	// 获取满足 pred 条件的全部对象
	void getObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMap::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			// 通过判断式决定 ite 是否满足条件，是则追加到迭代器末尾
			const value_type& record = ite->second;
			if (pred(record))
			{
				container.push_back(record);
			}
		}
	};

	// 遍历全部对象，对每个对象执行 op 操作
	void for_each(CUnaryProcInterface& op) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMap::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			op(ite->second);
		}
	};

	// 加入对象
	// 返回值：JTRUE = 加入成功、JFALSE = 此键值已经存在于本容器中，加入失败
	Jboolean addObject(const TKey& keyValue, const TValue& objectValue)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		// 尝试把对象加入到容器，返回成功失败标志
		return m_objects.insert(typename CResourceMap::value_type(keyValue, objectValue)).second;
	};

	// 删除对象
	// JTRUE = 删除成功、JFALSE = 此键值不存在于本容器中，删除失败
	Jboolean delObject(const TKey& keyValue)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourceMap::iterator ite = m_objects.find(keyValue);
		// 如果没有找到此键值，迭代器指向容器的末尾
		if (ite != m_objects.end())
		{
			m_freeItem(ite->second);
			m_objects.erase(ite);
			bRet = JTRUE;
		}

		return bRet;
	};

	// 删除满足 pred 条件的全部对象
	void delObjects_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMap::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); )
		{
			if (pred(ite->second))
			{
				m_freeItem(ite->second);
				m_objects.erase(ite ++);
			}
			else
			{
				++ ite;
			}
		}
	};

	// 取走对象，对象的生命周期由调用者负责
	// JTRUE = 取走成功、JFALSE = 此键值不存在于本容器中，取走失败
	Jboolean robObject(const TKey& keyValue, TValue& objectValue)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourceMap::iterator ite = m_objects.find(keyValue);
		// 如果没有找到此键值，迭代器指向容器的末尾
		if (ite != m_objects.end())
		{
			objectValue = ite->second;
			m_objects.erase(ite);
			bRet = JTRUE;
		}

		return bRet;
	};

	// 取走对象，对象的生命周期由调用者负责
	// 如果没有与键值对应的对象则返回缺省值
	TValue robObject(const TKey& keyValue)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

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
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourceMap::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			const value_type& record = ite->second;
			if (pred(record))
			{
				objectValue = record;
				m_objects.erase(ite);
				bRet = JTRUE;
				break;
			}
		}

		return bRet;
	};

	// 取走满足 pred 条件的对象，对象的生命周期由调用者负责
	TValue robObject_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

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
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		getObjects(container);
		m_objects.clear();
	};

	// 取走满足 pred 条件的全部对象，对象的生命周期由调用者负责
	void robObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMap::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); )
		{
			const value_type& record = ite->second;
			if (pred(record))
			{
				container.push_back(record);
				m_objects.erase(ite ++);
			}
			else
			{
				++ ite;
			}
		}
	};

	// 内部存储已经保证有序，为了和 CObjectSortVector 接口一致，也声明此函数
	void resort(void)
	{
	}

	// 交换容器内容
	void swap(CObjectMap& right)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);
		IceUtil::WLockT<IceUtil::RWRecMutex> guard_right(right.m_Mutex);
		m_objects.swap(right.m_objects);
	};

private:
	typedef std::map<TKey, TValue> CResourceMap;

	//## 使用 map 保存 对象资源ID -> 对象的映射
	CResourceMap m_objects;

	// 同步对象
	mutable IceUtil::RWRecMutex m_Mutex;

	TFreeItem m_freeItem;

};

} // namespace 

#endif // 
