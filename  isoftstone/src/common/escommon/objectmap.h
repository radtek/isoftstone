
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

// ʹ�� map ʵ�ֵ�������
// TFreeItem ģ��������� TValue ������ͷ�
// ACE_LOCK ģ��������������Ƿ�Ϊ�̰߳�ȫ��
template <class TKey, class TValue, class TFreeItem, class ACE_LOCK>
class CObjectMap
{
public:
	// ֵ����
	typedef TValue value_type;
	// �ж�ʽ�ӿ�
	typedef escommon::CPredicateInterface<value_type> CPredicateInterface;
	// ����ӿ�
	typedef escommon::CUnaryProcInterface<value_type> CUnaryProcInterface;

	CObjectMap(void)
	{
	};

	~CObjectMap(void)
	{
		clear();
	};

	//## ������������
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

	// ȡ��¼����
	Juint32 size(void) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		return m_objects.size();
	};

	// �ж��Ƿ�Ϊ��
	Jboolean empty(void) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		return m_objects.empty();
	};

	// ��ȡ����
	// ����ֵָʾ�Ƿ���ڴ˶���
	Jboolean getObject(const TKey& keyValue, TValue& objectValue) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourceMap::const_iterator ite = m_objects.find(keyValue);
		// ���û���ҵ��˼�ֵ��������ָ��������ĩβ
		if (ite != m_objects.end())
		{
			objectValue = ite->second;
			bRet = JTRUE;
		}

		return bRet;
	};

	// ��ȡ����
	// ���û�����ֵ��Ӧ�Ķ����򷵻�ȱʡֵ
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

	// ��ȡ���� pred �����Ķ���
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

	// ��ȡ���� pred �����Ķ���
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

	// ��ȡȫ������
	void getObjects(std::vector<TValue>& container) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMap::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			container.push_back(ite->second);
		}
	};

	// ��ȡ���� pred ������ȫ������
	void getObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMap::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			// ͨ���ж�ʽ���� ite �Ƿ���������������׷�ӵ�������ĩβ
			const value_type& record = ite->second;
			if (pred(record))
			{
				container.push_back(record);
			}
		}
	};

	// ����ȫ�����󣬶�ÿ������ִ�� op ����
	void for_each(CUnaryProcInterface& op) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMap::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			op(ite->second);
		}
	};

	// �������
	// ����ֵ��JTRUE = ����ɹ���JFALSE = �˼�ֵ�Ѿ������ڱ������У�����ʧ��
	Jboolean addObject(const TKey& keyValue, const TValue& objectValue)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		// ���԰Ѷ�����뵽���������سɹ�ʧ�ܱ�־
		return m_objects.insert(typename CResourceMap::value_type(keyValue, objectValue)).second;
	};

	// ɾ������
	// JTRUE = ɾ���ɹ���JFALSE = �˼�ֵ�������ڱ������У�ɾ��ʧ��
	Jboolean delObject(const TKey& keyValue)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourceMap::iterator ite = m_objects.find(keyValue);
		// ���û���ҵ��˼�ֵ��������ָ��������ĩβ
		if (ite != m_objects.end())
		{
			m_freeItem(ite->second);
			m_objects.erase(ite);
			bRet = JTRUE;
		}

		return bRet;
	};

	// ɾ������ pred ������ȫ������
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

	// ȡ�߶��󣬶�������������ɵ����߸���
	// JTRUE = ȡ�߳ɹ���JFALSE = �˼�ֵ�������ڱ������У�ȡ��ʧ��
	Jboolean robObject(const TKey& keyValue, TValue& objectValue)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		typename CResourceMap::iterator ite = m_objects.find(keyValue);
		// ���û���ҵ��˼�ֵ��������ָ��������ĩβ
		if (ite != m_objects.end())
		{
			objectValue = ite->second;
			m_objects.erase(ite);
			bRet = JTRUE;
		}

		return bRet;
	};

	// ȡ�߶��󣬶�������������ɵ����߸���
	// ���û�����ֵ��Ӧ�Ķ����򷵻�ȱʡֵ
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

	// ȡ������ pred �����Ķ��󣬶�������������ɵ����߸���
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

	// ȡ������ pred �����Ķ��󣬶�������������ɵ����߸���
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

	// ȡ��ȫ�����󣬶�������������ɵ����߸���
	void robObjects(std::vector<TValue>& container)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		getObjects(container);
		m_objects.clear();
	};

	// ȡ������ pred ������ȫ�����󣬶�������������ɵ����߸���
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

	// �ڲ��洢�Ѿ���֤����Ϊ�˺� CObjectSortVector �ӿ�һ�£�Ҳ�����˺���
	void resort(void)
	{
	}

	// ������������
	void swap(CObjectMap& right)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);
		IceUtil::WLockT<IceUtil::RWRecMutex> guard_right(right.m_Mutex);
		m_objects.swap(right.m_objects);
	};

private:
	typedef std::map<TKey, TValue> CResourceMap;

	//## ʹ�� map ���� ������ԴID -> �����ӳ��
	CResourceMap m_objects;

	// ͬ������
	mutable IceUtil::RWRecMutex m_Mutex;

	TFreeItem m_freeItem;

};

} // namespace 

#endif // 
