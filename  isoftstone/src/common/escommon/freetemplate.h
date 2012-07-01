#ifndef FREETEMPLATE_H_
#define FREETEMPLATE_H_

#include "escore.h"
#include "iestypedef.h"
#include <vector>
#include <list>
#include <deque>
#include <qglobal.h>

namespace escommon {

// ָ������ִ��ɾ������
template <class TValue>
struct CPtrFree
{
	// ���������������ɾ��
	void operator()(typename std::vector<TValue>::const_iterator ite1,
		typename std::vector<TValue>::const_iterator ite2)
	{
		for ( ; ite1!=ite2; ++ite1 )
		{
			delete *ite1;
		}
	};
	void operator()(typename std::list<TValue>::const_iterator ite1,
		typename std::list<TValue>::const_iterator ite2)
	{
		for ( ; ite1!=ite2; ++ite1 )
		{
			delete *ite1;
		}
	};
	void operator()(typename std::deque<TValue>::const_iterator ite1,
		typename std::deque<TValue>::const_iterator ite2)
	{
		for ( ; ite1!=ite2; ++ite1 )
		{
			delete *ite1;
		}
	};
	// ���������ɾ��
	void operator()(TValue value)
	{
		delete value;
	}
};

// �ղ���
template <class TValue>
struct CNullFree
{
	// ���������������ɾ��
	void operator()(typename std::vector<TValue>::const_iterator ite1,
		typename std::vector<TValue>::const_iterator ite2)
	{
		Q_UNUSED(ite1);
		Q_UNUSED(ite2);
	};
	void operator()(typename std::list<TValue>::const_iterator ite1,
		typename std::list<TValue>::const_iterator ite2)
	{
		Q_UNUSED(ite1);
		Q_UNUSED(ite2);
	};
	void operator()(typename std::deque<TValue>::const_iterator ite1,
		typename std::deque<TValue>::const_iterator ite2)
	{
		Q_UNUSED(ite1);
		Q_UNUSED(ite2);
	};
	void operator()(TValue value)
	{
		Q_UNUSED(value);
	}
};

} // namespace 

#endif // FREETEMPLATE_H_
