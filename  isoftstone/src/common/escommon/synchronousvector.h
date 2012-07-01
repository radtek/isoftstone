/************************************************************************/
/* �̰߳�ȫ��vector                                                     */
/************************************************************************/

#ifndef _SYNCHRONOUSVECTOR_H
#define _SYNCHRONOUSVECTOR_H

#include "escore.h"
#include "iestypedef.h"
#include <vector>
#include <IceUtil/RWRecMutex.h>
#include "IceUtil/Mutex.h"
#include <qglobal.h>
#include "predicateinterface.h"
#include "unaryprocinterface.h"

namespace escommon{

// �������̰߳�ȫ��
// CFreeItem ģ��������� TYPE ������ͷ�
template<class TYPE, class CFreeItem,class ACE_LOCK>
class CSynchronousVector
{
public:
	typedef std::vector<TYPE> CResourceVector;
	typedef TYPE value_type;
	// �ж�ʽ�ӿ�
	typedef escommon::CPredicateInterface<TYPE> CPredicateInterface;
	// ����ӿ�
	typedef escommon::CUnaryProcInterface<TYPE> CUnaryProcInterface;

	CSynchronousVector()
	{
	};

	CSynchronousVector(Jint32 size)
		: m_resourceObjectsVector(size)
	{
	};

	~CSynchronousVector()
	{
		clear();
	};

	// ���
	void clear()
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsVectorMutex);

		CFreeItem clearitem;
		clearitem(m_resourceObjectsVector.begin(), m_resourceObjectsVector.end());

		m_resourceObjectsVector.clear();
	};

	// �ж϶���object�Ƿ���vector�б���,����JTRUE����,����Ϊ������
	Jboolean exist(TYPE object)
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsVectorMutex);

		typename CResourceVector::const_iterator ite = std::find(m_resourceObjectsVector.begin(), m_resourceObjectsVector.end(), object);

		if (ite == m_resourceObjectsVector.end())
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
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsVectorMutex);

		typename CResourceVector::iterator ite = std::find(m_resourceObjectsVector.begin(), m_resourceObjectsVector.end(), object);

		if (ite == m_resourceObjectsVector.end())
		{				
			m_resourceObjectsVector.push_back(object);
			return JTRUE;
		}
		else
		{
			return JFALSE;
		}
	};

	// ɾ������,�ɹ�����true
	Jboolean deleteObject(TYPE object)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsVectorMutex);

		typename CResourceVector::iterator ite = std::find(m_resourceObjectsVector.begin(), m_resourceObjectsVector.end(), object);

		if (ite == m_resourceObjectsVector.end())
		{
			return JFALSE;
		}
		else
		{
			typename CResourceVector::iterator afterIte = ite;
			++ afterIte;
			CFreeItem clearitem;
			clearitem(ite, afterIte);
			m_resourceObjectsVector.erase(ite);

			return JTRUE;
		}
	};

	void delObjects_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsVectorMutex);

		typename CResourceVector::iterator ite;
		for (ite = m_resourceObjectsVector.begin(); ite != m_resourceObjectsVector.end(); )
		{
			if (pred(*ite))
			{
				typename CResourceVector::iterator afterIte = ite;
				++ afterIte;
				CFreeItem clearitem;
				clearitem(ite, afterIte);
				ite = m_resourceObjectsVector.erase(ite);
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
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsVectorMutex);

		Jboolean bRet = JFALSE;

		typename CResourceVector::const_iterator ite;
		for (ite = m_resourceObjectsVector.begin(); ite != m_resourceObjectsVector.end(); ++ite)
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
	void getObjects(CResourceVector& container) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsVectorMutex);

		container = m_resourceObjectsVector;
	};

	// ��ȡ���з��϶���pred�Ķ���
	void getObjects_if(CResourceVector& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsVectorMutex);

		typename CResourceVector::const_iterator ite;
		for (ite = m_resourceObjectsVector.begin(); ite != m_resourceObjectsVector.end(); ++ite)
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
		IceUtil::RLockT<ACE_LOCK> guard(m_objectsVectorMutex);

		typename CResourceVector::const_iterator ite;
		for (ite = m_resourceObjectsVector.begin(); ite != m_resourceObjectsVector.end(); ++ite)
		{
			op(*ite);
		}
	};

	// ������������
	void swap(CSynchronousVector& right)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_objectsVectorMutex);
		IceUtil::WLockT<ACE_LOCK> guard_right(right.m_objectsVectorMutex);

		m_resourceObjectsVector.swap(right.m_resourceObjectsVector);
	};

private:
	CResourceVector m_resourceObjectsVector;

	mutable ACE_LOCK m_objectsVectorMutex;
};

}//namespace 

#endif//
