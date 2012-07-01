

#ifndef OBJECTSET_H_20071023
#define OBJECTSET_H_20071023

#include "escore.h"
#include "iestypedef.h"
#include <set>
#include <functional>
#include <vector>
#include <IceUtil/RWRecMutex.h>
#include "IceUtil/Mutex.h"
#include "predicateinterface.h"
#include "unaryprocinterface.h"
#include "freetemplate.h"

namespace escommon {

// ʹ�� set ʵ�ֵ�������
// ֻ֧��ָ�����ͱ����� set ��
// TValueCompare ģ��������� TValue* ��������ıȽϴ�С
// TSubValue ģ�����Ҫ���� TValue ���ͣ������� TValue �������ͣ���ֱ���������󣬰��� TKey �������Ĺ��캯��
// TFreeItem ģ��������� TValue* ������ͷ�
// ACE_LOCK ģ��������������Ƿ�Ϊ�̰߳�ȫ��
template <class TKey, class TValue, class TSubValue, class TValueCompare, class TFreeItem, class ACE_LOCK>
class CObjectSet
{
public:
	// ֵ����
	typedef TValue* value_type;
	// �ж�ʽ�ӿ�
	typedef escommon::CPredicateInterface<value_type> CPredicateInterface;
	// ����ӿ�
	typedef escommon::CUnaryProcInterface<value_type> CUnaryProcInterface;

	CObjectSet(void)
	{
	};

	~CObjectSet(void)
	{
		clear();
	};

	// ������������
	void clear(void)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourcePairSet::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			m_freeItem(*ite);
		}
		m_objects.clear();
	};

	// ȡ��¼����
	Juint32 size(void) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		return m_objects.size();
	};

	// �ж��Ƿ�Ϊ��
	Jboolean empty(void) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		return m_objects.empty();
	};

	// ��ȡ����
	// ����ֵָʾ�Ƿ���ڴ˶���
	Jboolean getObject(const TKey& keyValue, TValue*& objectValue) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		TSubValue keyResource(keyValue);
		value_type resourcePair(&keyResource);

		typename CResourcePairSet::const_iterator ite = m_objects.find(resourcePair);
		// ���û���ҵ��˼�ֵ��������ָ��������ĩβ
		if (ite != m_objects.end())
		{
			objectValue = *ite;
			bRet = JTRUE;
		}

		return bRet;
	};

	// ��ȡ����
	// ���û�����ֵ��Ӧ�Ķ����򷵻�ȱʡֵ
	TValue* getObject(const TKey& keyValue) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		TValue* objectValue;
		if (!getObject(keyValue, objectValue))
		{
			objectValue = NULL;
		}
		return objectValue;
	};

	// ��ȡ���� pred �����Ķ���
	Jboolean getObject_if(const CPredicateInterface& pred, TValue*& objectValue) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourcePairSet::const_iterator ite;
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

	// ��ȡ���� pred �����Ķ���
	TValue* getObject_if(const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		TValue* objectValue;
		if (!getObject_if(pred, objectValue))
		{
			objectValue = NULL;
		}
		return objectValue;
	};

	// ��ȡȫ������
	void getObjects(std::vector<TValue*>& container) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourcePairSet::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			container.push_back(*ite);
		}
	};

	// ��ȡ���� pred ������ȫ������
	void getObjects_if(std::vector<TValue*>& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourcePairSet::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			// ͨ���ж�ʽ���� ite �Ƿ���������������׷�ӵ�������ĩβ
			const value_type& record = *ite;
			if (pred(record))
			{
				container.push_back(record);
			}
		}
	};

	// ����ȫ�����󣬶�ÿ������ִ�� op ����
	void for_each(CUnaryProcInterface& op) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourcePairSet::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			op(*ite);
		}
	};

	// �������
	// ����ֵ��JTRUE = ����ɹ���JFALSE = �˼�ֵ�Ѿ������ڱ������У�����ʧ��
	Jboolean addObject(const TKey& keyValue, TValue* objectValue)
	{
		Q_UNUSED(keyValue);

		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		// ���԰Ѷ�����뵽���������سɹ�ʧ�ܱ�־
		Jboolean bRet = JFALSE;
		if (NULL != objectValue)
		{
			bRet = m_objects.insert(objectValue).second;
		}
		return bRet;
	};

	// ɾ������
	// JTRUE = ɾ���ɹ���JFALSE = �˼�ֵ�������ڱ������У�ɾ��ʧ��
	Jboolean delObject(const TKey& keyValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		TSubValue keyResource(keyValue);
		value_type resourcePair(&keyResource);

		typename CResourcePairSet::iterator ite = m_objects.find(resourcePair);
		// ���û���ҵ��˼�ֵ��������ָ��������ĩβ
		if (ite != m_objects.end())
		{
			m_freeItem(*ite);
			m_objects.erase(ite);
			bRet = JTRUE;
		}

		return bRet;
	};

	// ɾ������ pred ������ȫ������
	void delObjects_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourcePairSet::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); )
		{
			if (pred(*ite))
			{
				m_freeItem(*ite);
				m_objects.erase(ite ++);
			}
			else
			{
				++ ite;
			}
		}
	};

	// ȡ�߶��󣬶�������������ɵ����߸���
	// JTRUE = ȡ�߳ɹ���JFALSE = �˼�ֵ�������ڱ������У�ȡ��ʧ��
	Jboolean robObject(const TKey& keyValue, TValue*& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		TSubValue keyResource(keyValue);
		value_type resourcePair(&keyResource);

		typename CResourcePairSet::iterator ite = m_objects.find(resourcePair);
		// ���û���ҵ��˼�ֵ��������ָ��������ĩβ
		if (ite != m_objects.end())
		{
			objectValue = *ite;
			m_objects.erase(ite);
			bRet = JTRUE;
		}

		return bRet;
	};

	// ȡ�߶��󣬶�������������ɵ����߸���
	// ���û�����ֵ��Ӧ�Ķ����򷵻�ȱʡֵ
	TValue* robObject(const TKey& keyValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		TValue* objectValue;
		if (!robObject(keyValue, objectValue))
		{
			objectValue = NULL;
		}
		return objectValue;
	};

	// ȡ������ pred �����Ķ��󣬶�������������ɵ����߸���
	Jboolean robObject_if(const CPredicateInterface& pred, TValue*& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourcePairSet::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			const value_type& record = *ite;
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

	// ȡ������ pred �����Ķ��󣬶�������������ɵ����߸���
	TValue* robObject_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		TValue* objectValue;
		if (!robObject_if(pred, objectValue))
		{
			objectValue = NULL;
		}
		return objectValue;
	};

	// ȡ��ȫ�����󣬶�������������ɵ����߸���
	void robObjects(std::vector<TValue*>& container)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		getObjects(container);
		m_objects.clear();
	};

	// ȡ������ pred ������ȫ�����󣬶�������������ɵ����߸���
	void robObjects_if(std::vector<TValue*>& container, const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourcePairSet::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); )
		{
			const value_type& record = *ite;
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

	// �ڲ��洢�Ѿ���֤����Ϊ�˺� CObjectSortVector �ӿ�һ�£�Ҳ�����˺���
	void resort(void)
	{
	}

	// ������������
	void swap(CObjectSet& right)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);
		IceUtil::WLockT<ACE_LOCK> guard_right(right.m_Mutex);
		m_objects.swap(right.m_objects);
	};

private:
	typedef std::set<value_type, TValueCompare> CResourcePairSet;

	// ʹ�� set ���� ������ԴID -> �����ӳ��
	CResourcePairSet m_objects;

	// ͬ������
	mutable ACE_LOCK m_Mutex;

	TFreeItem m_freeItem;

};

} // namespace escommon

#endif // OBJECTSET_H_20071023
