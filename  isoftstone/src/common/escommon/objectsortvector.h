
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

// ʹ������� vector ʵ�ֵ�������
// ʹ�� TValue() ��Ϊɾ����ǣ����Բ��� addObject(TValue()) ��ֵ
// TFreeItem ģ��������� TValue ������ͷ�
// ACE_LOCK ģ��������������Ƿ�Ϊ�̰߳�ȫ��
template <class TKey, class TValue, class TDataCompare, class TFreeItem, class ACE_LOCK>
class CObjectSortVector
{
public:
	// ֵ����
	typedef TValue value_type;
	// �ж�ʽ�ӿ�
	typedef escommon::CPredicateInterface<value_type> CPredicateInterface;
	// ����ӿ�
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

	// ������������
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
	Jboolean getObject(const TKey& keyValue, TValue& objectValue) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		// ����Ƿ��Ѿ�����
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

	// ��ȡ����
	// ���û�����ֵ��Ӧ�Ķ����򷵻�ȱʡֵ
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

	// ��ȡ���� pred �����Ķ���
	Jboolean getObject_if(const CPredicateInterface& pred, TValue& objectValue) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		// ����Ƿ��Ѿ�����
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

	// ��ȡ���� pred �����Ķ���
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

	// ��ȡȫ������
	void getObjects(std::vector<TValue>& container) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		// ����Ƿ��Ѿ�����
		checkDirty();

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			container.push_back(*ite);
		}
	};

	// ��ȡ���� pred ������ȫ������
	void getObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		// ����Ƿ��Ѿ�����
		checkDirty();

		typename CResourceVector::const_iterator ite;
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

		// ����Ƿ��Ѿ�����
		checkDirty();

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			op(*ite);
		}
	};

	// �������
	// ����ֵ��JTRUE = ����ɹ�
	Jboolean addObject(const TKey& keyValue, const TValue& objectValue)
	{
		Q_UNUSED(keyValue);

		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		// objectValue Ϊȱʡֵ���ܼ��뵽������
		if (s_nullValue != objectValue)
		{
			// ���ǵ�����ԭ��ÿ�μ���ʱ�����ж��Ƿ��Ѿ����ڼ�¼��Ҳ�Ͳ���������
			// �ȵ��� resort ���ٽ���һ������
			m_objects.push_back(objectValue);
			m_bAddDirty = JTRUE;
			bRet = JTRUE;
		}

		return bRet;
	};

	// ɾ������
	// JTRUE = ɾ���ɹ���JFALSE = �˼�ֵ�������ڱ������У�ɾ��ʧ��
	Jboolean delObject(const TKey& keyValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		// ��� m_bAddDirty ��־�������� m_uDelCount > 0
		checkAddDirty();

		Jboolean bRet = JFALSE;

		typename CResourceVector::iterator ite = std::lower_bound(m_objects.begin(), m_objects.end(), keyValue, m_dataCompare);
		if (ite != m_objects.end() && *ite == keyValue)
		{
			value_type& record = *ite;
			if (s_nullValue != record)
			{
				m_freeItem(record);

				// ������ɾ�� keyValue ��ָ�Ķ��󣬵ȵ��� resort ʱ������ɾ��
				record = s_nullValue;
				++m_uDelCount;
				bRet = JTRUE;
			}
		}

		return bRet;
	};

	// ɾ������ pred ������ȫ������
	void delObjects_if(const CPredicateInterface& pred)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		// ��� m_bAddDirty ��־�������� m_uDelCount > 0
		checkAddDirty();

		typename CResourceVector::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			value_type& record = *ite;
			if (s_nullValue != record && pred(record))
			{
				m_freeItem(record);
				// ������ɾ�� keyValue ��ָ�Ķ��󣬵ȵ��� resort ʱ������ɾ��
				record = s_nullValue;
				++m_uDelCount;
			}
		}
	};

	// ȡ�߶��󣬶�������������ɵ����߸���
	// JTRUE = ȡ�߳ɹ���JFALSE = �˼�ֵ�������ڱ������У�ȡ��ʧ��
	Jboolean robObject(const TKey& keyValue, TValue& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		// ��� m_bAddDirty ��־�������� m_uDelCount > 0
		checkAddDirty();

		Jboolean bRet = JFALSE;

		typename CResourceVector::iterator ite = std::lower_bound(m_objects.begin(), m_objects.end(), keyValue, m_dataCompare);
		if (ite != m_objects.end() && *ite == keyValue)
		{
			value_type& record = *ite;
			if (s_nullValue != record)
			{
				objectValue = record;
				// ������ɾ�� keyValue ��ָ�Ķ��󣬵ȵ��� resort ʱ������ɾ��
				record = s_nullValue;
				++m_uDelCount;
				bRet = JTRUE;
			}
		}

		return bRet;
	};

	// ȡ�߶��󣬶�������������ɵ����߸���
	// ���û�����ֵ��Ӧ�Ķ����򷵻�ȱʡֵ
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

	// ȡ������ pred �����Ķ��󣬶�������������ɵ����߸���
	Jboolean robObject_if(const CPredicateInterface& pred, TValue& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		// ��� m_bAddDirty ��־�������� m_uDelCount > 0
		checkAddDirty();

		Jboolean bRet = JFALSE;

		typename CResourceVector::iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			value_type& record = *ite;
			if (s_nullValue != record && pred(record))
			{
				objectValue = record;
				// ������ɾ�� keyValue ��ָ�Ķ��󣬵ȵ��� resort ʱ������ɾ��
				record = s_nullValue;
				++m_uDelCount;
				bRet = JTRUE;
				break;
			}
		}

		return bRet;
	};

	// ȡ������ pred �����Ķ��󣬶�������������ɵ����߸���
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

	// ȡ��ȫ�����󣬶�������������ɵ����߸���
	void robObjects(std::vector<TValue>& container)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		getObjects(container);

		m_objects.clear();
		m_bAddDirty = JFALSE;
		m_uDelCount = 0;
	};

	// ȡ������ pred ������ȫ�����󣬶�������������ɵ����߸���
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
				// ������ɾ�� keyValue ��ָ�Ķ��󣬵ȵ��� resort ʱ������ɾ��
				record = s_nullValue;
				++m_uDelCount;
			}
		}
	};

	// �޸����
	void resort(void)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		if (m_bAddDirty || m_uDelCount > 0)
		{
			// �����¶�����Ҫ��������
			std::stable_sort(m_objects.begin(), m_objects.end(), m_dataCompare);
			m_bAddDirty = JFALSE;

			if (m_uDelCount > 0)
			{
				// �� m_uDelCount ������ɾ�����������򣬶����е�����ĩβ
				m_objects.erase(m_objects.end()-m_uDelCount, m_objects.end());
				m_uDelCount = 0;
			}
		}
	}

	// ������������
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
		// �� get �Ȳ���ǰ��� m_bAddDirty��m_bDelDirty ��־
		if (m_bAddDirty || m_uDelCount > 0)
		{
			throw std::exception("CObjectSortVector ���ڶ�ȡ֮ǰ����������");
		}
	}

	void checkAddDirty(void) const
	{
		// �� del �Ȳ���ǰ��� m_bAddDirty ��־
		if (m_bAddDirty)
		{
			throw std::exception("CObjectSortVector ���ڶ�ȡ֮ǰ����������");
		}
	}

	// ������������
	typedef std::vector<value_type> CResourceVector;

	// ͬ������
	mutable ACE_LOCK m_Mutex;

	// ʹ�� vector ���� ��ֵ�±� -> �����ӳ��
	CResourceVector m_objects;

	// ���ж������ӣ�����Ϊ�����ݣ��� get �Ȳ���ǰ��Ҫ����
	Jboolean m_bAddDirty;

	// ���ж���ɾ����m_uDelCount+1���� get �Ȳ���ǰ��Ҫ���򣬲����
	Juint32 m_uDelCount;

	TFreeItem m_freeItem;
	TDataCompare m_dataCompare;

	// ��ֵ
	const TValue s_nullValue;

};

} // namespace 

#endif // OBJECTSORTVECTOR_H_