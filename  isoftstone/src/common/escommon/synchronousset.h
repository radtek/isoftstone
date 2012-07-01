/************************************************************************/
/* 线程安全的set                                                        */
/************************************************************************/

#ifndef _SYNCHRONOUSSET_H
#define _SYNCHRONOUSSET_H

#include "escore.h"
#include "iestypedef.h"
#include <set>
#include <vector>
#include <IceUtil/RWRecMutex.h>
#include "IceUtil/Mutex.h"
#include <qglobal.h>
#include "predicateinterface.h"
#include "unaryprocinterface.h"

namespace escommon{

// 本类是线程安全的
// CFreeItem 模板参数参与 TYPE 对象的释放
template<class TYPE, class CFreeItem ,class ACE_LOCK>
class CSynchronousSet
{
public:
	typedef std::set<TYPE> CResourceSet;

	typedef TYPE value_type;
	// 判断式接口
	typedef escommon::CPredicateInterface<TYPE> CPredicateInterface;
	// 运算接口
	typedef escommon::CUnaryProcInterface<TYPE> CUnaryProcInterface;

	CSynchronousSet()
	{
	};

	~CSynchronousSet()
	{
		clear();
	};

	// 清空
	void clear()
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsSetMutex);

		CFreeItem clearitem;
		clearitem(m_resourceObjectsSet.begin(), m_resourceObjectsSet.end());

		m_resourceObjectsSet.clear();
	};

	// 判断对象object是否在set中保存,返回JTRUE存在,否则为不存在
	Jboolean exist(TYPE object)
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsSetMutex);

		typename CResourceSet::const_iterator ite = m_resourceObjectsSet.find(object);

		if (ite == m_resourceObjectsSet.end())
		{
			return JFALSE;
		}
		else
		{
			return JTRUE;
		}
	};

	// 增加对象,成功返回true
	Jboolean addObject(TYPE object)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsSetMutex);

		return m_resourceObjectsSet.insert(object).second;
	};

	// 删除对象,成功返回true
	Jboolean deleteObject(TYPE object)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsSetMutex);

		typename CResourceSet::iterator ite = m_resourceObjectsSet.find(object);

		if (ite == m_resourceObjectsSet.end())
		{
			return JFALSE;
		}
		else
		{
			typename CResourceSet::iterator afterIte = ite;
			++ afterIte;
			CFreeItem clearitem;
			clearitem(ite, afterIte);
			m_resourceObjectsSet.erase(ite);

			return JTRUE;
		}
	};

	void delObjects_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsSetMutex);

		typename CResourceSet::iterator ite;
		for (ite=m_resourceObjectsSet.begin(); ite!=m_resourceObjectsSet.end(); )
		{
			if (pred(*ite))
			{
				typename CResourceSet::iterator afterIte = ite;
				++ afterIte;
				CFreeItem clearitem;
				clearitem(ite, afterIte);
				m_resourceObjectsSet.erase(ite ++);
			}
			else
			{
				++ ite;
			}
		}
	};

	// 查找符合断言pred的对象,未找到返回false
	Jboolean findObject_if(const CPredicateInterface& pred, TYPE& object) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsSetMutex);

		Jboolean bRet = JFALSE;

		typename CResourceSet::const_iterator ite;
		for (ite = m_resourceObjectsSet.begin(); ite != m_resourceObjectsSet.end(); ++ite)
		{
			if (pred(*ite))
			{
				object = *ite;
				bRet = JTRUE;
				break;
			}
		}

		return bRet;
	};

	// 查找符合断言pred的对象
	TYPE findObject_if(const CPredicateInterface& pred) const
	{
		TYPE object;

		if (!findObject_if(pred, object))
		{
			object = TYPE();
		}

		return object;
	};

	// 获取所有对象
	void getObjects(std::vector<TYPE>& container) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsSetMutex);

		std::copy(m_resourceObjectsSet.begin(), m_resourceObjectsSet.end(), std::back_inserter(container));
	};

	// 获取所有符合断言pred的对象
	void getObjects_if(std::vector<TYPE>& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsSetMutex);

		typename CResourceSet::const_iterator ite;
		for (ite = m_resourceObjectsSet.begin(); ite != m_resourceObjectsSet.end(); ++ite)
		{
			if (pred(*ite))
			{
				container.push_back(*ite);
			}
		}
	};

	// 对所有对象应用函数op
	void for_each(CUnaryProcInterface& op) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsSetMutex);

		typename CResourceSet::const_iterator ite;
		for (ite = m_resourceObjectsSet.begin(); ite != m_resourceObjectsSet.end(); ++ite)
		{
			op(*ite);
		}
	};

	// 交换容器内容
	void swap(CSynchronousSet& right)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsSetMutex);
		IceUtil::WLockT<ACE_LOCK> guard_right(right.m_objectsSetMutex);

		m_resourceObjectsSet.swap(right.m_resourceObjectsSet);
	};

private:
	CResourceSet m_resourceObjectsSet;

	mutable ACE_LOCK m_objectsSetMutex;
};

}//namespace 

#endif//
