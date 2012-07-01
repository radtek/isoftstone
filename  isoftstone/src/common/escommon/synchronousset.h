/************************************************************************/
/* �̰߳�ȫ��set                                                        */
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

// �������̰߳�ȫ��
// CFreeItem ģ��������� TYPE ������ͷ�
template<class TYPE, class CFreeItem ,class ACE_LOCK>
class CSynchronousSet
{
public:
	typedef std::set<TYPE> CResourceSet;

	typedef TYPE value_type;
	// �ж�ʽ�ӿ�
	typedef escommon::CPredicateInterface<TYPE> CPredicateInterface;
	// ����ӿ�
	typedef escommon::CUnaryProcInterface<TYPE> CUnaryProcInterface;

	CSynchronousSet()
	{
	};

	~CSynchronousSet()
	{
		clear();
	};

	// ���
	void clear()
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsSetMutex);

		CFreeItem clearitem;
		clearitem(m_resourceObjectsSet.begin(), m_resourceObjectsSet.end());

		m_resourceObjectsSet.clear();
	};

	// �ж϶���object�Ƿ���set�б���,����JTRUE����,����Ϊ������
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

	// ���Ӷ���,�ɹ�����true
	Jboolean addObject(TYPE object)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsSetMutex);

		return m_resourceObjectsSet.insert(object).second;
	};

	// ɾ������,�ɹ�����true
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

	// ���ҷ��϶���pred�Ķ���,δ�ҵ�����false
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

	// ���ҷ��϶���pred�Ķ���
	TYPE findObject_if(const CPredicateInterface& pred) const
	{
		TYPE object;

		if (!findObject_if(pred, object))
		{
			object = TYPE();
		}

		return object;
	};

	// ��ȡ���ж���
	void getObjects(std::vector<TYPE>& container) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsSetMutex);

		std::copy(m_resourceObjectsSet.begin(), m_resourceObjectsSet.end(), std::back_inserter(container));
	};

	// ��ȡ���з��϶���pred�Ķ���
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

	// �����ж���Ӧ�ú���op
	void for_each(CUnaryProcInterface& op) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsSetMutex);

		typename CResourceSet::const_iterator ite;
		for (ite = m_resourceObjectsSet.begin(); ite != m_resourceObjectsSet.end(); ++ite)
		{
			op(*ite);
		}
	};

	// ������������
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
