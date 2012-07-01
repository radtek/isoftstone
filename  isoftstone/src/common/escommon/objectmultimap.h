
#ifndef OBJECTMULTIMAP_H_20070823
#define OBJECTMULTIMAP_H_20070823

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

//## 键值 -> 对象的映射，允许重复键值
//## CFreeItem 模板参数参与 TValue 对象的释放
//## ACE_LOCK 模板参数决定本类是否为线程安全的
template <class TKey, class TValue, class CFreeItem, Jboolean bSingleValueOfSameKey, class ACE_LOCK>
class CObjectMultiMap
{
public:
	// 值类型
	typedef TValue value_type;

	// 判断式接口
	typedef escommon::CPredicateInterface<value_type> CPredicateInterface;
	// 运算接口
	typedef escommon::CUnaryProcInterface<value_type> CUnaryProcInterface;

	//##ModelId=3EF108A00310
	CObjectMultiMap(void)
	{
		m_bSingleValueOfSameKey = bSingleValueOfSameKey;
	};

	~CObjectMultiMap(void)
	{
		clear();
	};

	//## 清空所保存对象
	void clear(void)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		CFreeItem freeItem;
		typename CResourceMultiMap::iterator ite;
		for (ite = m_objects.begin(); ite != m_objects.end(); ++ite)
		{
			freeItem(ite->second);
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
	Juint32 empty(void) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		return m_objects.empty();
	};

	// 获取所有对象
	void getObjects(std::vector<TValue>& container) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMultiMap::const_iterator ite;
		for (ite = m_objects.begin(); ite != m_objects.end(); ++ite)
		{
			container.push_back(ite->second);
		}
	};

	// 以资源ID获取对象
	void getObjects(const TKey& keyValue, std::vector<TValue>& container) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		std::pair<typename CResourceMultiMap::const_iterator, typename CResourceMultiMap::const_iterator> itePair
			= m_objects.equal_range(keyValue);
		typename CResourceMultiMap::const_iterator ite1 = itePair.first;
		typename CResourceMultiMap::const_iterator ite2 = itePair.second;
		for (; ite1!=ite2; ++ite1)
		{
			container.push_back(ite1->second);
		}
	};

	// 获取满足 pred 条件的全部对象
	void getObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMultiMap::const_iterator ite;
		for (ite = m_objects.begin(); ite != m_objects.end(); ++ite)
		{
			// 通过判断式决定 ite 是否满足条件，是则追加到迭代器末尾
			if (pred(ite->second))
			{
				container.push_back(ite->second);
			}
		}
	};

	void for_each(CUnaryProcInterface& op) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMultiMap::const_iterator ite;
		for (ite = m_objects.begin(); ite != m_objects.end(); ++ite)
		{
			op(ite->second);
		}
	};

	//## 把资源ID与对象加入到容器中
	//## 返回值：JTRUE = 加入成功
	Jboolean addObject(const TKey& keyValue, const TValue& object)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JTRUE;
		if (m_bSingleValueOfSameKey)
		{
			// 检查值的重复
			std::pair<typename CResourceMultiMap::const_iterator, typename CResourceMultiMap::const_iterator> itePair
				= m_objects.equal_range(keyValue);
			typename CResourceMultiMap::const_iterator ite1 = itePair.first;
			typename CResourceMultiMap::const_iterator ite2 = itePair.second;
			for (; ite1!=ite2; ++ite1)
			{
				if (ite1->second == object)
				{
					bRet = JFALSE;
					break;
				}
			}
		}
		if (bRet)
		{
			m_objects.insert(typename CResourceMultiMap::value_type(keyValue, object));
		}
		return bRet;
	};

	//## 以资源ID和对象，删除对象
	//## 因为键值可以重复，删除时还需要传入删除的对象
	//## JTRUE = 删除成功、JFALSE = 此资源ID不存在于本容器中，删除失败
	Jboolean delObject(const TKey& keyValue, const TValue& object)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		std::pair<typename CResourceMultiMap::iterator, typename CResourceMultiMap::iterator> itePair
			= m_objects.equal_range(keyValue);
		typename CResourceMultiMap::iterator ite1 = itePair.first;
		typename CResourceMultiMap::iterator ite2 = itePair.second;
		// 以下语句有删除操作，会破坏迭代器，需要特殊处理
		for (; ite1!=ite2; )
		{
			if (ite1->second == object)
			{
				bRet = JTRUE;

				CFreeItem freeItem;
				freeItem(ite1->second);
				m_objects.erase(ite1 ++);

				if (m_bSingleValueOfSameKey)
				{
					// 如果值不允许重复，不必再检查后续的值
					break;
				}
			}
			else
			{
				++ ite1;
			}
		}

		return bRet;
	};

	// 删除资源ID对应的所有对象
	void delObjects(const TKey& keyValue)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		std::pair<typename CResourceMultiMap::const_iterator, typename CResourceMultiMap::const_iterator> itePair
			= m_objects.equal_range(keyValue);
		typename CResourceMultiMap::const_iterator ite1 = itePair.first;
		typename CResourceMultiMap::const_iterator ite2 = itePair.second;
		CFreeItem freeItem;
		for (; ite1!=ite2; ++ite1)
		{
			freeItem(ite1->second);
		}
		m_objects.erase(keyValue);
	};

	// 删除满足 pred 条件的全部对象
	void delObjects_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMultiMap::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); )
		{
			if (pred(ite->second))
			{
				CFreeItem freeItem;
				freeItem(ite->second);
				m_objects.erase(ite ++);
			}
			else
			{
				++ ite;
			}
		}
	};

	// 取走全部对象，删除所有记录不删除对象，对象的生命周期由调用者负责
	void robObjects(std::vector<TValue>& container)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		getObjects(container);
		m_objects.clear();
	};

	// 取走满足 pred 条件的全部对象，删除记录不删除对象，对象的生命周期由调用者负责
	void robObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMultiMap::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); )
		{
			if (pred(ite->second))
			{
				container.push_back(ite->second);
				m_objects.erase(ite ++);
			}
			else
			{
				++ ite;
			}
		}
	};

	// 交换容器内容
	void swap(CObjectMultiMap& right)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);
		IceUtil::WLockT<IceUtil::RWRecMutex> guard_right(right.m_Mutex);

		m_objects.swap(right.m_objects);
	};

private:
	typedef std::multimap< TKey, TValue > CResourceMultiMap;

	//## 使用 map 保存 对象资源ID -> 对象
	CResourceMultiMap m_objects;

	//## 同步对象
	mutable IceUtil::RWRecMutex m_Mutex;

	//## multimap 允许有重复的键，不限定值的重复性
	//## 本参数可限制值的重复
	Jboolean m_bSingleValueOfSameKey;

};

} // namespace escommon

#endif // OBJECTMULTIMAP_H_20070823
