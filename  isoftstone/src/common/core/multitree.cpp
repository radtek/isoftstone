
#include <list>
#include <string.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "multitree.h"
#include "general.h"
#include "treeiterator.h"
#include "container2stream.h"
#include "stringlist.h"
#include "properties.h"
#include "enumfile.h"



using namespace std;

int CRtMultiTree::m_static_id = 1;

CRtMultiTree::CRtMultiTree()
{
	m_RootNode = NULL;
	m_NodeContainer.clear();
	m_nodesize=0;
	init();

}

CRtMultiTree::~CRtMultiTree()
{
}
void CRtMultiTree::init()
{
}

void CRtMultiTree::listAllNode()
{
	QMutexLocker lock(&m_containerMutex);
	for (CRtMultiTree::NodeIterator iter = m_NodeContainer.begin();iter != m_NodeContainer.end();iter++)
	{
		HiNode* node = iter->second;
		node->print();
	}
}

void CRtMultiTree::createRootNode(HiNode* node)
{
	do
	{
		QMutexLocker lock(&m_nodeMutex);
		if (NULL == m_RootNode)
		{
			m_RootNode = node;
		}
		else
		{
			cout << "根结点已经创建！！" << std::endl;
		}
	}while(0);

	QMutexLocker lock(&m_containerMutex);
	m_NodeContainer.insert(std::make_pair(m_RootNode->nodeValue.id,m_RootNode));
}

void CRtMultiTree::addNode(int& parentid,HiNode* node)
{
	QMutexLocker lock(&m_containerMutex);
	CRtMultiTree::NodeIterator iter = m_NodeContainer.find(parentid);
	if (iter != m_NodeContainer.end())
	{
		HiNode* nodeptr = iter->second;
		HiNode* newnode = node;

		if (nodeptr->left == NULL)
		{
			nodeptr->left = newnode;
			newnode->parent = nodeptr;
			m_NodeContainer.insert(std::make_pair(newnode->nodeValue.id,newnode));
		}
		else
		{
			bool tag = true;
			nodeptr = nodeptr->left;
			while(nodeptr)
			{
				if (_stricmp(nodeptr->nodeValue.name.c_str(), newnode->nodeValue.name.c_str()) == 0)
				{
					cout << "结点重名" << endl;
					tag = false;
					break;
				}
				if (nodeptr->right)
				{
					nodeptr = nodeptr->right;
				}
				else
				{
					break;
				}
			}
			if (tag)
			{
				nodeptr->right = newnode;
				newnode->parent = nodeptr;
				m_NodeContainer.insert(std::make_pair(newnode->nodeValue.id,newnode));
			}
			else
			{
				delete newnode;
				newnode = NULL;
			}
		}
	}
	else
	{
		cout << "父节点不存在 ID: " << parentid << endl;
	}
}

void CRtMultiTree::deleteNode(int& id)
{
	QMutexLocker lock(&m_containerMutex);
	CRtMultiTree::NodeIterator iter = m_NodeContainer.find(id);

	if (iter != m_NodeContainer.end())
	{
		std::vector<HiNode*> retv;
		HiNode* node = iter->second;
		if(node->parent == NULL || node->parent->left == node ) // 第一个结点或者根结点
		{
			if (node->parent == NULL)
			{
				LevelDelete(node,retv);
				m_NodeContainer.clear();
				node = NULL;
				m_RootNode = NULL;
			}
			else
			{
				node->parent->left = node->right;	// 将下个结点作为第一个结点
				LevelDelete(node->left,retv);		//删除其下所有子结点,并将结点信息放到删除队列中存放
				retv.push_back(node); // 将本结点放到删除队列
				if (node->right)
				{
					node->right->parent = node->parent;	 // 要记住父指针
				}
			}
		}
		else if (node->right == NULL) // 最后一个结点
		{
			HiNode* parent = node->parent;
			parent->right = NULL;
			LevelDelete(node,retv);
		}
		else	// 中间结点
		{
			node->right->parent = node->parent;
			node->parent->right = node->right;
			LevelDelete(node->left,retv);
			retv.push_back(node);
		}
		for (std::vector<HiNode*>::iterator it = retv.begin();it != retv.end() ; it++)
		{
			HiNode* tnode = *it;
			m_NodeContainer.erase(tnode->nodeValue.id);
			delete tnode;
			tnode = NULL;
		}
	}
}

void CRtMultiTree::modifyNode(int& id,string& name,double& value)
{
	QMutexLocker lock(&m_containerMutex);
	CRtMultiTree::NodeIterator iter = m_NodeContainer.find(id);
	if (iter != m_NodeContainer.end())
	{
		HiNode* nodeptr = iter->second;
		HiNode* currentnode = nodeptr;
		if (nodeptr->parent != NULL)
		{
			// 定位到第一个结点
			while(nodeptr->parent->left != nodeptr)
			{
				if (nodeptr->parent)
				{
					nodeptr = nodeptr->parent; 
				}
			}
		}
		while(nodeptr)
		{
			if (_stricmp(nodeptr->nodeValue.name.c_str(), name.c_str()) == 0)
			{
				cout << "与其他子结点有重名,ID为" << nodeptr->nodeValue.id << endl;
				return;
			}
			else
			{
				nodeptr = nodeptr->right; // 下一个子结点
			}
		}
		// 需要确保唯一性，需要检查与其他兄弟结点是否有重名

		CNodeInfo& nodevalue = currentnode->nodeValue;
		nodevalue.name = name;
		nodevalue.value = value;
	}
	else
	{
		cout << "所选择得结点不存在 ID:" << id << endl;
	}
}

void CRtMultiTree::getNode(int& id)
{
	QMutexLocker lock(&m_containerMutex);
	CRtMultiTree::NodeIterator iter = m_NodeContainer.find(id);
	if (iter != m_NodeContainer.end())
	{
		cout << "ID		名称		值" << endl;
		HiNode* node = iter->second;
		node->print();
	}
	else
	{
		cout << "所选择得结点不存在ID: " << id << endl;
	}
}

int CRtMultiTree::getRoot()
{
	return m_RootNode->nodeValue.id;

	CTreeIterator<HiNode> iter(m_RootNode);
	while(!iter.end())
	{
		HiNode* p = iter.next();
		p->print();
	}
}

void CRtMultiTree::getAllChild(int& id,std::vector<HiNode*>& retv)
{
	QMutexLocker lock(&m_containerMutex);
	CRtMultiTree::NodeIterator iter = m_NodeContainer.find(id);
	if (iter != m_NodeContainer.end())
	{
		cout << "ID		NAME		VALUE" << endl;
		HiNode* node = iter->second;
		if (node->left)
		{
			node = node->left;
			retv.clear();
			LevelOrder(node,SPrintFacor(),retv);
		}
		else
		{
			cout << "当前结点没有子结点 ID：  " << id << endl;
		}
	}
	else
	{
		cout << "所选结点不存在" << id << endl;
	}
}

std::string CRtMultiTree::getPath(const int& id,const int& root)
{
	QMutexLocker lock(&m_containerMutex);
	CRtMultiTree::NodeIterator iter = m_NodeContainer.find(id);
	CRtMultiTree::NodeIterator iter_root = m_NodeContainer.find(root);
	ostringstream ostr;

	if (iter != m_NodeContainer.end() && iter_root != m_NodeContainer.end())
	{
		HiNode* node = iter->second;
		HiNode* node_root = iter_root->second;
		return node->getPath(node_root);
	}
	else
	{
		cout << "所选结点不存在ID " << id << endl;
	}
	return "";
}

int CRtMultiTree::getNodeID(string& pathname)
{
	std::vector<string> sname ;
	HiStringList::split("/",pathname).toVector(sname);

	QMutexLocker lock(&m_nodeMutex);
	HiNode* nodeptr = m_RootNode;
	std::vector<string>::iterator iter = sname.begin();
	bool find = false;
	while(nodeptr && iter != sname.end())
	{
		if (nodeptr->nodeValue.name == *iter)
		{
			iter++;
			if (iter == sname.end())
			{
				find = true;
				break;
			}
			nodeptr = nodeptr->left;
		}
		else
		{
			nodeptr = nodeptr->right;
		}
	}
	if (find)
	{
		return nodeptr->nodeValue.id ;
		
	}
	else
	{
		return -1;
	}
}

std::vector<HiNode*> CRtMultiTree::getFilterNode(string& filter)
{
	QMutexLocker lock(&m_containerMutex);
	std::vector<HiNode*> ret;
	for (CRtMultiTree::NodeIterator iter = m_NodeContainer.begin();iter != m_NodeContainer.end();iter++)
	{
		HiNode* node = iter->second;
		CNodeInfo& info = node->nodeValue;
		if (CGeneralFunction::kmp_matcher(info.name.c_str(), filter.c_str()) > 0)
			//if (info.name.find(filter) != -1)
		{
			node->print();
			ret.push_back(node);
		}
	}
	return ret;
}

void CRtMultiTree::copyNode(int& id,int& pid)
{
	QMutexLocker lock(&m_containerMutex);
	CRtMultiTree::NodeIterator it = m_NodeContainer.find(id);
	if (it == m_NodeContainer.end())
	{
		return;
	}
	HiNode* node = it->second;
	HiNode* newnode = node->clone();
	CTreeIterator<HiNode> iter(newnode);
	while(!iter.end())
	{
		HiNode* tnode = iter.next();
		tnode->nodeValue.id = m_static_id++;
		m_NodeContainer.insert(std::make_pair(tnode->nodeValue.id,tnode));
	}
	it = m_NodeContainer.find(pid);
	if (it != m_NodeContainer.end())
	{
		addChild(it->second,newnode);
	}
}

void CRtMultiTree::moveNode(int& id,int& pid)
{
	QMutexLocker lock(&m_containerMutex);
	CRtMultiTree::NodeIterator it = m_NodeContainer.find(id);
	if (it == m_NodeContainer.end())
	{
		return;
	}
	HiNode* node = it->second;

	it = m_NodeContainer.find(pid);
	if (it == m_NodeContainer.end())
	{
		return;
	}

	if (isAncestor(node,it->second))
	{
		cout << "祖先结点不能移到子结点下面" << endl;
		return;
	}

	if(node->parent == NULL || node->parent->left == node ) // 第一个结点或者根结点
	{
		if (node->parent == NULL)
		{
			cout << "根节点不能移动" << endl;
		}
		else
		{
			node->parent->left = node->right;	// 将下个结点作为第一个结点
			if (node->right)
			{
				node->right->parent = node->parent;	 // 要记住父指针
			}
		}
	}
	else if (node->right == NULL) // 最后一个结点
	{
		HiNode* parent = node->parent;
		parent->right = NULL;
	}
	else	// 中间结点
	{
		node->right->parent = node->parent;
		node->parent->right = node->right;
	}

	// 增加到新的父结点下面

	addChild(it->second,node);
}


HiNode* CRtMultiTree::getParent(HiNode* node)
{
	while(node && node->parent && node->parent->left != node)
	{
		node = node->parent;
	}
	return node->parent;
}

bool CRtMultiTree::isAncestor(HiNode* pnode,HiNode* node)
{
	int i = 0;
	while((node = getParent(node)) != pnode && node != NULL)
	{
		i++;
	}
	return node == NULL ? false: true;
}

bool CRtMultiTree::isParent(HiNode* pnode,HiNode* node)
{
	if (getParent(node) == pnode)
	{
		return true;
	}
	return false;
}

// 如果返回NULL说明没有子结点，否则返回最后一个子结点
HiNode* CRtMultiTree::getLastChild(HiNode* node)
{
	HiNode* retnode = NULL;
	if (node)
	{
		if (node->left)
		{
			retnode = node->left;
			while(retnode->right)
			{
				retnode = retnode->right;
			}
		}
	}
	return retnode;
}

void CRtMultiTree::addChild(HiNode* node,HiNode* newnode)
{
	if (!node)
	{
		return;
	}
	HiNode* lnode = getLastChild(node);
	if (lnode)
	{
		lnode->right = newnode;
		newnode->parent = lnode;
	}
	else
	{
		node->left = newnode;
		newnode->parent = node;
	}
}

bool CRtMultiTree::load(string filename,ETreeSaveStyle style )
{
	ios::open_mode mode = ios::out;
	if (style == eSaveAsBin)
	{
		mode = ios::binary;
	}
	ifstream fin(filename.c_str(),mode);
	int n;
	HiNode *p;
	int i,j;
	int count;
	clear();
	if (fin.fail()) return false;
	if (style == eSaveAsBin)
	{
		read(fin,n);
	}
	else
	{
		if (!(fin >> n)) 
			return false;
	}
	
	count = 0;
	m_nodesize = n;
	for (i=0;i<n;i++)
	{
		int id;
		CNodeInfo data;
		bool isok = true;
		if (style == eSaveAsBin)
		{
			read(fin,id);
			read(fin,data.id);
			read(fin,data.name);
			read(fin,data.value);
		}
		else
		{
			if (!(fin >> id && fin >> data) || id<=0)
				isok = false;
		}
		if (!isok)
		{
			clear();
			fin.close();
			return false;
		}
		if (m_RootNode == NULL)
		{
			m_RootNode = new HiNode;
			count++;
		}
		p = m_RootNode;
		for (j = 30;j >= 0;j--)
		{
			if (id & (1 << j))
				break;
		}
		while (j--)
		{
			if (!(id & (1 << j)))
			{
				if (p->left == 0)
				{
					p->left = new HiNode;
					p->left->parent = p;
					count++;
				}
				p = p->left;
			}
			else
			{
				if (p->right == 0)
				{
					p->right = new HiNode;
					p->right->parent = p;
					count++;
				}
				p = p->right;
			}
		}
		p->nodeValue = data;
		m_NodeContainer.insert(std::make_pair(p->nodeValue.id,p));
		p = NULL;
	}
	if (!m_NodeContainer.empty())
	{
		m_static_id = m_NodeContainer.rbegin()->first + 1;
	}
	fin.close();
	if (count>n)
	{
		clear();
		return false;
	}
	return true;
}

bool CRtMultiTree::save(string filename,ETreeSaveStyle style )
{
	ios::open_mode mode = ios::out;
	if (style == eSaveAsBin)
	{
		mode = ios::binary|ios::trunc;
	}
	ofstream fout(filename.c_str(),mode);
	if (fout.fail())
		return false;
	m_nodesize = m_NodeContainer.size();
	if (style == eSaveAsBin)
	{
		write(fout,m_nodesize);
	}
	else
	{
		fout << m_nodesize << endl;
	}
	if (m_RootNode) 
		save(m_RootNode,1,fout,style);
	fout.close();
	return true;
}

void CRtMultiTree::save(HiNode *p,int id,ofstream &fout,ETreeSaveStyle style )
{
	CNodeInfo& info = p->nodeValue;
	if (style == eSaveAsBin)
	{
		write(fout,id);
		write(fout,info.id);
		write(fout,info.name);
		write(fout,info.value);
	}
	else
	{
		fout << id << ' ' ;
		fout<< info << endl;
	}
	
	if (p->left) save(p->left,id*2,fout,style);
	if (p->right) save(p->right,id*2+1,fout,style);
}

void CRtMultiTree::clear()
{
	if (m_RootNode != NULL) 
		clear(m_RootNode);
	m_RootNode = NULL;
	m_nodesize = 0;
}

void CRtMultiTree::clear(HiNode *p)
{
	if (p)
	{
		if (p->left) clear(p->left);
		if (p->right) clear(p->right);
		m_NodeContainer.erase(p->nodeValue.id);
		delete p;
	}
}

