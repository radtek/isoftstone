
#ifndef __NODE_LCSH_H
#define __NODE_LCSH_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "macro2.h"
#include "escore.h"

#define  MaxSize 256

using namespace std;

using std::operator <<;


class LIBCORE_EXPORT CNodeInterface
{
	virtual void print() = 0;
};

template <typename T>   
struct CBaseNode  : public CNodeInterface 
{  
public:

	CBaseNode()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	
	virtual ~CBaseNode()
	{

	}

	CBaseNode(const T& item, CBaseNode<T> *lptr = NULL, CBaseNode<T> *rptr = NULL, CBaseNode<T> *pptr = NULL) 
	{
		nodeValue = item;
		left = lptr;
		right = rptr;
		parent = pptr;   
	}
	
	CBaseNode(CBaseNode* pnode,CBaseNode* rnode)
	{
		left = NULL;
		right = NULL;
		parent = pnode;
		nodeValue = rnode->nodeValue;
	}

	// 如果为true则只克隆自己，否则克隆子树
	CBaseNode* clone(bool self = false)
	{
		if (self)
		{
			return new CBaseNode(NULL,this);
		}
		else
		{
			// 子树拷贝信息
			CBaseNode* nnode = NULL;
			cloneNode(this->left,nnode);
			CBaseNode* rnode = new CBaseNode(NULL,this);
			rnode->left = nnode;
			return rnode;
		}
	}

	void setValue(CBaseNode* node)
	{
		nodeValue = node->nodeValue;
	}

	// 返回当前结点相对根结点的路径
	std::string getPath(const CBaseNode* root = NULL)
	{
		ostringstream ostr;
		HiNode* node = this;
		const HiNode* node_root = root;
		HiNode* current = NULL;
		std::list<HiNode*> pathlist;
		pathlist.push_back(node);
		while (node->parent != node_root)
		{
			current = node;
			if (node->parent->left == current) // 如果为第一个结点
			{
				pathlist.push_back(node->parent);
			}
			node = node->parent;
		}
		ostr << std::string("/") ;
		while (!pathlist.empty())
		{
			ostr << pathlist.back()->nodeValue.name ;
			if (pathlist.size() != 1)
			{
				ostr << pathlist.back()->nodeValue.name << std::string("/") ;
			}

			pathlist.pop_back();
		}
		return ostr.str();
	}

	virtual void print()
	{
		nodeValue.print();
	}

	T   nodeValue;   
	CBaseNode<T>	*left;
	CBaseNode<T>   *right;
	CBaseNode<T>   *parent;   
};   

struct CNodeInfo :public CNodeInterface
{
public:

	CNodeInfo()
	{
		id = 0;
		name = "";
		value = 0.0;
	}
	
	virtual ~CNodeInfo()
	{

	}

	CNodeInfo(int id, std::string name ,double value)
	{
			this->id = id;
			this->name = name;
			this->value = value;
	}
	
	CNodeInfo(CNodeInfo& right)
	{
		this->operator()(right);
	}

	void operator()(CNodeInfo& right)
	{
		id = right.id;
		name = right.name;
		value = right.value;
	}

	virtual void print()
	{
		printf("%d		",id);
		printf("%s		",name.c_str());
		printf("%f	\n",value);
	}

	int id;
	std::string name;
	double value;
};

typedef CBaseNode<CNodeInfo> HiNode;

struct SPrintFacor : std::unary_function<HiNode,void>
{
	void operator()(const HiNode* p)
	{
		printf("%d		",p->nodeValue.id);
		printf("%s		",p->nodeValue.name.c_str());
		printf("%f	\n",p->nodeValue.value);
	}
};

struct SDeleteFacor : std::unary_function<HiNode,void>
{
	void operator()(HiNode*& p)
	{
		delete p;
		p = NULL;
	}
};

struct SUnUsedFacor : std::unary_function<HiNode,void>
{
	void operator()(HiNode*& p)
	{
		Hi_UNUSED(p);
	}
};


typedef void (*FLevelFactor)(HiNode*);

inline ofstream& operator<<(ofstream& os,const CNodeInfo& info)
{
	os << info.id << ' ';
	os << info.name << ' ';
	os << info.value << ' ';
	return os;
}

inline ifstream& operator>>(ifstream& is,CNodeInfo& info)
{
	is >> info.id;
	is >> info.name;
	is >> info.value;
	return is;
}


template <class Node, class _Fun>
struct SBinaryOrder
{
	void operator()(Node* b,_Fun _func)
	{

	}

	std::vector<Node*> retv;
};

template <class Node, class _Fun>
struct SPreOrder : public SBinaryOrder<Node,_Fun>
{
	SPreOrder()
	{
		retv.clear();
	}

	void operator()(Node* b,_Fun _func)
	{
		PreOrder(b,_func,retv);
	}
	
};

// 前序遍历递归算法
template <class Node, class _Fun>
struct SPreOrder_Rec : public SBinaryOrder<Node,_Fun>
{
	SPreOrder_Rec()
	{
		retv.clear();
	}

	void operator()(Node* b,_Fun _func)
	{
		PreOrder_Rec(b,_func);
	}

};


template <class Node, class _Fun>
inline void PreOrder_Rec(Node* b,_Fun _func)
{
	if (b)
	{
		PreOrder_Rec(b->left);
		_func(b);
		PreOrder_Rec(b->right);
	}
}

// 前序遍历算法
template <class Node, class _Fun>
inline void PreOrder(Node* b,_Fun _func,std::vector<Node*>& retv)
{ 
	if (b == NULL)
	{
		return;
	}
	Node* stack[MaxSize];
	Node* p = b;
	int top = -1; 

	while (p != NULL || top != -1)
	{ 
		while (p != NULL)
		{ 
			_func(p);
			retv.push_back(p);
			stack[++top] = p;
			p = p->left;
		}
		p = stack[top--];
		p = p->right;
	}
} 

template <class Node, class _Fun>
struct SMiddleOrder : public SBinaryOrder<Node,_Fun>
{
	SMiddleOrder()
	{
		retv.clear();
	}

	void operator()(Node* b,_Fun _func)
	{
		MiddleOrder(b,_func,retv);
	}

};

template <class Node, class _Fun>
struct SMiddleOrder_Rec : public SBinaryOrder<Node,_Fun>
{
	SMiddleOrder_Rec()
	{
		retv.clear();
	}

	void operator()(Node* b,_Fun _func)
	{
		MiddleOrder_Rec(b,_func);
	}

};
// 中序遍历递归算法
template <class Node, class _Fun>
inline void MiddleOrder_Rec(Node* b,_Fun _func)
{
	if (b)
	{
		_func(b);
		MiddleOrder_Rec(b->left);
		MiddleOrder_Rec(b->right);
	}
}

// 中序遍历算法
template <class Node, class _Fun>
inline void MiddleOrder(Node* b,_Fun _func,std::vector<Node*>& retv)
{ 
	if (b == NULL)
	{
		return;
	}
	Node* stack[MaxSize];
	Node* p = b;
	int top = -1; 

	while (p != NULL || top != -1)
	{ 
		while (p != NULL)
		{ 
			stack[++top] = p;
			p = p->left;
		}
		p = stack[top--];
		retv.push_back(p);
		_func(p);
		p = p->right;
	}
} 

template <class Node, class _Fun>
struct SPostOrder : public SBinaryOrder<Node,_Fun>
{
	SPostOrder()
	{
		retv.clear();
	}

	void operator()(Node* b,_Fun _func)
	{
		PostOrder(b,_func,retv);
	}

};

template <class Node, class _Fun>
struct SPostOrder_Rec : public SBinaryOrder<Node,_Fun>
{
	SPostOrder_Rec()
	{
		retv.clear();
	}

	void operator()(Node* b,_Fun _func)
	{
		PostOrder_Rec(b,_func);
	}

};
// 后序遍历递归算法
template <class Node, class _Fun>
inline void PostOrder_Rec(Node* b,_Fun _func)
{
	if (b)
	{
		PostOrder_Rec(b->left);
		PostOrder_Rec(b->right);
		_func(b);
	}
}

// 后序遍历算法
template <class Node, class _Fun>
inline void PostOrder(Node* b,_Fun _func,std::vector<Node*>& retv)
{ 
	if (b == NULL)
	{
		return;
	}
	Node* stack1[MaxSize];
	Node* p = b;
	int stack2[MaxSize];
	int flag = -1;
	int top = -1; 

	while (p != NULL || top != -1)
	{ 
		while (p != NULL) 
		{
			stack1[++top] = p;
			stack2[top] = 0;
			p = p->left;
		}
		p = stack1[top];
		flag = stack2[top--];
		if (flag == 0) 
		{
			stack1[++top] = p;
			stack2[top] = 1;
			p = p->right;

		}
		else 
		{
			retv.push_back(p);
			_func(p);
			p = NULL;
		}
	}
} 

template <class Node, class _Fun>
struct SLevelOrder : public SBinaryOrder<Node,_Fun>
{
	SLevelOrder()
	{
		retv.clear();
	}

	void operator()(Node* b,_Fun _func)
	{
		LevelOrder(b,_func,retv);
	}

};

// 层次遍历算法
template <class Node, class _Fun>
inline void LevelOrder(Node* b,_Fun _func,std::vector<Node*>& retv)
{
	HiNode *p;
	HiNode *qu[MaxSize];
	int front,rear;
	front=rear=-1;
	if (b)
	{
		rear++;
		qu[rear]=b;
	}
	while(front!=rear)
	{
		front=(front+1)%MaxSize;
		p=qu[front];
		
		if(p->left!=NULL)
		{
			rear=(rear+1)%MaxSize;
			qu[rear]=p->left;
		}   
		if(p->right!=NULL)
		{
			rear=(rear+1)%MaxSize;
			qu[rear]=p->right;
		}     
		retv.push_back(p);
		_func(p);
	}    
}


inline void LevelOrder_s(HiNode*& b,FLevelFactor *factor,std::vector<HiNode*>& retv)
{
	return LevelOrder(b,*factor,retv);
}

inline void LevelDelete(HiNode*& b,std::vector<HiNode*>& retv)
{
	return LevelOrder(b,SUnUsedFacor(),retv);
}

// 层次遍历进行节点拷贝工作
template <class Node>
inline void cloneNode(Node* b,Node*& outp)
{
	HiNode *p;
	HiNode *np = NULL;
	HiNode *qu[MaxSize];
	HiNode *cu[MaxSize];
	int front,rear;
	front=rear=-1;
	if (b)
	{
		rear++;
		qu[rear] = b;
		np = new Node();
		np->setValue(b);
		cu[rear] = np;
		outp = np;
	}
	while(front!=rear)
	{
		front = (front+1)%MaxSize;
		p = qu[front];
		np = cu[front];

		if(p->left!=NULL)
		{
			rear=(rear+1)%MaxSize;
			qu[rear]=p->left;
			np->left = new Node(np,(p->left));
			cu[rear] = np->left;
		}   
		if(p->right!=NULL)
		{
			rear=(rear+1)%MaxSize;
			qu[rear]=p->right;
			np->right = new Node(np,(p->right));
			cu[rear] = np->right;
		}     
	}    
}

#endif