#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "escore.h"


template <typename Node = HiNode,
template <typename N = HiNode,typename F = SUnUsedFacor>class Strategy = SPreOrder,
typename Factor = SUnUsedFacor>
class LIBCORE_EXPORT CTreeIterator
{
public:

	CTreeIterator(Node* b)
	{
		m_node = b;
		m_nindex = -1;
		m_vecNode.clear();

		Strategy<Node,Factor> strate;
		strate(b,Factor());
		m_vecNode.swap(strate.retv);
	}

	virtual ~CTreeIterator()
	{
		m_vecNode.clear();
	}

	Node* begin()
	{
		m_nindex = 0;
		if (m_nindex < m_vecNode.size())
		{
			return m_vecNode[m_vecNode];
		}
		return NULL;
	}

	Node* rbegin()
	{
		m_nindex = m_vecNode.size() - 1;
		if (m_nindex > -1)
		{
			return m_vecNode[m_vecNode];
		}
		return NULL;
	}

	Node* next()
	{
		m_nindex++;
		return m_vecNode[m_nindex];
	}

	Node* previous()
	{
		m_nindex--;
		return m_vecNode[m_nindex];
	}

	bool end()
	{
		return m_nindex + 1 == m_vecNode.size();
	}

	bool rend()
	{
		return m_nindex  == 0;
	}

private:

	Node* m_node;

	std::vector<Node*> m_vecNode;

	int m_nindex;

};
