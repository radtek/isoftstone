#ifndef COMPONENT_LCSH_H
#define COMPONENT_LCSH_H

#include <map>
#include <vector>
#include "node.h"
#include "escore.h"

class FlyWight
{
public:
	virtual void print() = 0;
	virtual ~FlyWight(){};
};
class Composite;
class Component:public FlyWight
{
public:
	Component(Composite* parent,HiNode* desc,bool isleaf)
	{
		m_parent = parent;
		m_des = desc;
		m_isleaf = isleaf;
	}
	virtual ~Component(){};
	virtual Composite* getParent()
	{
		return m_parent;
	};
	virtual void print()
	{
		// cout << m_des->nodeValue.id << "	" << m_des->nodeValue.name << "		" << m_des->nodeValue.value << endl;
		HiNode*& p = m_des;
		printf("%d		",p->nodeValue.id);
		printf("%s		",p->nodeValue.name.c_str());
		printf("%f	\n",p->nodeValue.value);
	}
	HiNode* m_des; // ��¼��ǰ�ڵ���Ϣ
	Composite* m_parent; // ��¼���ڵ���Ϣ
	bool m_isleaf;
};

// �����������ӽڵ�
class Composite:public Component
{
	friend class CTreeTransfer;
	friend class CPrintTreeCommand;

public:
	Composite(Composite* parent,HiNode* desc,bool isleaf):Component(parent,desc,isleaf){};
	virtual ~Composite(){};
	void add(Component* com)
	{
		m_container.insert(std::make_pair(com->m_des->nodeValue.id,com));
	};
	void erase(Component* com)
	{
		m_container.erase(com->m_des->nodeValue.id);
	};
	Component* find(int resid)
	{
		m_iter = m_container.find(resid);
		return m_iter == m_container.end() ? NULL:m_iter->second;
	}
	virtual void print()
	{
		Component::print();
		// ����߰����˵ݹ����
		for (m_iter = m_container.begin();m_iter != m_container.end() ;m_iter++)
		{
			Component*& com = m_iter->second;
			com->print();
		}
	}

private:
	typedef std::map<int,Component*,std::less<int> > ComponentContainer;
	typedef ComponentContainer::iterator ComIter;
	ComponentContainer m_container; // �����ӽڵ�
	ComIter m_iter;

};
// Ҷ�ӽڵ�
class Leaf:public Component
{
public:
	Leaf(Composite* parent,HiNode* desc,bool isleaf):Component(parent,desc,isleaf){};
	virtual ~Leaf(){};
};


#endif