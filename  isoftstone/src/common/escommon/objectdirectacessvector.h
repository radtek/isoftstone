
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

// ��ֵ��Ϊ�±� -> �����ӳ��
// ʹ���±���в��ң��˷��ڴ棬�Ż������ٶ�
// CKey2Id ת����ֵ���±�ķº���
// CFreeItem ģ��������� TValue ������ͷ�
// ACE_LOCK ģ��������������Ƿ�Ϊ�̰߳�ȫ��
template <class TKey, class CKey2Id, class TValue, class CFreeItem, class ACE_LOCK>
class CObjectDirectAcessVector
{
public:
	// ֵ����
	typedef TValue value_type;
	// �ж�ʽ�ӿ�
	typedef escommon::CPredicateInterface<value_type> CPredicateInterface;
	// ����ӿ�
	typedef escommon::CUnaryProcInterface<value_type> CUnaryProcInterface;

	CObjectDirectAcessVector(void)
	{
	};

	~CObjectDirectAcessVector(void)
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

		Jboolean bRet = JFALSE;

		if (checkKey(keyValue))
		{
			const value_type& record = getValue(keyValue);
			// �жϱ���¼�Ƿ���Ч
			if (checkValue(record))
			{
				objectValue = record;
				bRet = JTRUE;
			}
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
			objectValue = TValue();
		}
		return objectValue;
	};

	// ��ȡ���� pred �����Ķ���
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

	// ��ȡ���� pred �����Ķ���
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

	// ��ȡȫ������
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

	// ��ȡ���� pred ������ȫ������
	void getObjects_if(std::vector<TValue>& container, const CPredicateInterface& pred) const
	{
		IceUtil::RLockT<ACE_LOCK> guard(m_Mutex);

		typename CResourceVector::const_iterator ite;
		for (ite=m_objects.begin(); ite!=m_objects.end(); ++ite)
		{
			// ͨ���ж�ʽ���� ite �Ƿ���������������׷�ӵ�������ĩβ
			const value_type& record = *ite;
			if (checkValue(record) && pred(record))
			{
				container.push_back(record);
			}
		}
	};

	// ����ȫ�����󣬶�ÿ������ִ�� op ����
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

	// �������
	// ����ֵ��JTRUE = ����ɹ���JFALSE = �˼�ֵ�Ѿ������ڱ������У�����ʧ��
	Jboolean addObject(const TKey& keyValue, const TValue& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		// �����ֵ����������С������չ��
		expandSize(keyValue);

		value_type& record = getValue(keyValue);
		// �ж��Ƿ��Ѿ����ڼ�¼
		if (!checkValue(record))
		{
			record = objectValue;
			bRet = JTRUE;
		}
		return bRet;
	};

	// ɾ������
	// JTRUE = ɾ���ɹ���JFALSE = �˼�ֵ�������ڱ������У�ɾ��ʧ��
	Jboolean delObject(const TKey& keyValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		if (checkKey(keyValue))
		{
			value_type& record = getValue(keyValue);
			// �жϱ���¼�Ƿ���Ч
			if (checkValue(record))
			{
				m_freeItem(record);
				record = TValue();
				bRet = JTRUE;
			}
		}

		return bRet;
	};

	// ɾ������ pred ������ȫ������
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

	// ȡ�߶��󣬶�������������ɵ����߸���
	// JTRUE = ȡ�߳ɹ���JFALSE = �˼�ֵ�������ڱ������У�ȡ��ʧ��
	Jboolean robObject(const TKey& keyValue, TValue& objectValue)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		Jboolean bRet = JFALSE;

		if (checkKey(keyValue))
		{
			value_type& record = getValue(keyValue);
			// �жϱ���¼�Ƿ���Ч
			if (checkValue(record))
			{
				objectValue = record;
				record = TValue();
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
			objectValue = TValue();
		}
		return objectValue;
	};

	// ȡ������ pred �����Ķ��󣬶�������������ɵ����߸���
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

	// ȡ������ pred �����Ķ��󣬶�������������ɵ����߸���
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

	// ȡ��ȫ�����󣬶�������������ɵ����߸���
	void robObjects(std::vector<TValue>& container)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);

		getObjects(container);
		m_objects.clear();
	};

	// ȡ������ pred ������ȫ�����󣬶�������������ɵ����߸���
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

	// �ڲ��洢�Ѿ���֤����Ϊ�˺� CObjectDirectAcessVector �ӿ�һ�£�Ҳ�����˺���
	void resort(void)
	{
	}

	// ������������
	void swap(CObjectDirectAcessVector& right)
	{
		IceUtil::WLockT<ACE_LOCK> guard(m_Mutex);
		IceUtil::WLockT<ACE_LOCK> guard_right(right.m_Mutex);
		m_objects.swap(right.m_objects);
	};

private:
	// ������������
	typedef std::vector<value_type> CResourceVector;

	// ��ֵ��Ϊ�±��ȡֻ������
	const value_type& getValue(const TKey& keyValue) const
	{
		return m_objects[m_key2Id(keyValue)];
	};

	// ��ֵ��Ϊ�±��ȡ�ɶ�д����
	value_type& getValue(const TKey& keyValue)
	{
		return m_objects[m_key2Id(keyValue)];
	};

	// ����ֵ��Ϊ�±��Ƿ�Ϸ�
	Jboolean checkKey(const TKey& keyValue) const
	{
		return (m_key2Id(keyValue) < m_objects.size());
	};

	Jboolean checkValue(const TValue& objectValue) const
	{
		return (objectValue != TValue());
	};

	// ��չ vector �������µļ�ֵ
	void expandSize(const TKey& keyValue)
	{
		if (m_key2Id(keyValue) >= m_objects.size())
		{
			m_objects.resize(m_key2Id(keyValue)+1);
		}
	};

	// ʹ�� vector ���� ��ֵ�±� -> �����ӳ��
	CResourceVector m_objects;

	// ͬ������
	mutable ACE_LOCK m_Mutex;

	CKey2Id m_key2Id;
	CFreeItem m_freeItem;

};

} // namespace escommon

#endif // OBJECTDIRECTACESSVECTOR_H_20070822
