
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

//## ��ֵ -> �����ӳ�䣬�����ظ���ֵ
//## CFreeItem ģ��������� TValue ������ͷ�
//## ACE_LOCK ģ��������������Ƿ�Ϊ�̰߳�ȫ��
template <class TKey, class TValue, class CFreeItem, Jboolean bSingleValueOfSameKey, class ACE_LOCK>
class CObjectMultiMap
{
public:
	// ֵ����
	typedef TValue value_type;

	// �ж�ʽ�ӿ�
	typedef escommon::CPredicateInterface<value_type> CPredicateInterface;
	// ����ӿ�
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

	//## ������������
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

	// ȡ��¼����
	Juint32 size(void) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		return m_objects.size();
	};

	// �ж��Ƿ�Ϊ��
	Juint32 empty(void) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		return m_objects.empty();
	};

	// ��ȡ���ж���
	void getObjects(std::vector<TValue>& container) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMultiMap::const_iterator ite;
		for (ite = m_objects.begin(); ite != m_objects.end(); ++ite)
		{
			container.push_back(ite->second);
		}
	};

	// ����ԴID��ȡ����
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

	// ��ȡ���� pred ������ȫ������
	void getObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		typename CResourceMultiMap::const_iterator ite;
		for (ite = m_objects.begin(); ite != m_objects.end(); ++ite)
		{
			// ͨ���ж�ʽ���� ite �Ƿ���������������׷�ӵ�������ĩβ
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

	//## ����ԴID�������뵽������
	//## ����ֵ��JTRUE = ����ɹ�
	Jboolean addObject(const TKey& keyValue, const TValue& object)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JTRUE;
		if (m_bSingleValueOfSameKey)
		{
			// ���ֵ���ظ�
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

	//## ����ԴID�Ͷ���ɾ������
	//## ��Ϊ��ֵ�����ظ���ɾ��ʱ����Ҫ����ɾ���Ķ���
	//## JTRUE = ɾ���ɹ���JFALSE = ����ԴID�������ڱ������У�ɾ��ʧ��
	Jboolean delObject(const TKey& keyValue, const TValue& object)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		std::pair<typename CResourceMultiMap::iterator, typename CResourceMultiMap::iterator> itePair
			= m_objects.equal_range(keyValue);
		typename CResourceMultiMap::iterator ite1 = itePair.first;
		typename CResourceMultiMap::iterator ite2 = itePair.second;
		// ���������ɾ�����������ƻ�����������Ҫ���⴦��
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
					// ���ֵ�������ظ��������ټ�������ֵ
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

	// ɾ����ԴID��Ӧ�����ж���
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

	// ɾ������ pred ������ȫ������
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

	// ȡ��ȫ������ɾ�����м�¼��ɾ�����󣬶�������������ɵ����߸���
	void robObjects(std::vector<TValue>& container)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);

		getObjects(container);
		m_objects.clear();
	};

	// ȡ������ pred ������ȫ������ɾ����¼��ɾ�����󣬶�������������ɵ����߸���
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

	// ������������
	void swap(CObjectMultiMap& right)
	{
		IceUtil::WLockT<IceUtil::RWRecMutex> guard(m_Mutex);
		IceUtil::WLockT<IceUtil::RWRecMutex> guard_right(right.m_Mutex);

		m_objects.swap(right.m_objects);
	};

private:
	typedef std::multimap< TKey, TValue > CResourceMultiMap;

	//## ʹ�� map ���� ������ԴID -> ����
	CResourceMultiMap m_objects;

	//## ͬ������
	mutable IceUtil::RWRecMutex m_Mutex;

	//## multimap �������ظ��ļ������޶�ֵ���ظ���
	//## ������������ֵ���ظ�
	Jboolean m_bSingleValueOfSameKey;

};

} // namespace escommon

#endif // OBJECTMULTIMAP_H_20070823
