

#ifndef MULTITREE_LCSH_H
#define MULTITREE_LCSH_H

#include <Ice/Ice.h>
#include <list>
#include <string>
#include <map>
#include "node.h"
#include <iostream>
#include <fstream>
#include "enumfile.h"
#include "escore.h"

class CPrintTreeCommand;

class LIBCORE_EXPORT CRtMultiTree 
{
public:

	CRtMultiTree();

	~CRtMultiTree();

	HiNode* getLastChild(HiNode* node);

	void addChild(HiNode* node,HiNode* newnode);

	HiNode* getParent(HiNode* node);

	bool isAncestor(HiNode* pnode,HiNode* node);

	bool isParent(HiNode* pnode,HiNode* node);

	void listAllNode();

	void createRootNode(HiNode* node);

	void addNode(int& parentid,HiNode* node);

	void deleteNode(int& id);

	void modifyNode(int& id,string& name,double& value);

	void getNode(int& id);

	int getRoot();

	void getAllChild(int& id,std::vector<HiNode*>& retv);

	std::string getPath(const int& id,const int& root);

	int getNodeID(string& pathname);

	std::vector<HiNode*> getFilterNode(string& filter);

	void copyNode(int& id,int& pid);

	void moveNode(int& id,int& pid);

	void save(HiNode*,int,std::ofstream&,ETreeSaveStyle style = eSaveAsTxt);

	bool load(string,ETreeSaveStyle style = eSaveAsTxt);//��ָ���ļ��ж�ȡ������ 

	bool save(string ,ETreeSaveStyle style = eSaveAsTxt);//��������������ָ���ļ�

	void clear(HiNode*);

	void clear();//���ԭ�ȶ���������Ϣ 

	static int m_static_id;

private:

	IceUtil::Mutex m_nodeMutex; // ��д�����Ƚ�С

	HiNode* m_RootNode;

	IceUtil::Mutex m_containerMutex; // �������Ƚϴ�

	std::map<int,HiNode*> m_NodeContainer;

	int m_nodesize;

	typedef std::map<int,HiNode*>::iterator NodeIterator;

	void init();


public:

	friend class CPrintTreeCommand;

};

#endif