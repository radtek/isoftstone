
#include "transform.h"


using namespace std;

Composite* CTreeTransfer::m_multiTree = NULL;

HiNode* CTreeTransfer::m_binaryTree = NULL;

HiNode* CTreeTransfer::transfrom2BinaryTree(Composite* multi,HiNode* binary)
{
	if(!multi)
		return m_binaryTree;

	Component* com = multi;
	HiNode* node = binary;
	if (!com->m_isleaf) // 如果为容器
	{
		if(binary == NULL) // 根结点
		{
			m_binaryTree = com->m_des;
			node = m_binaryTree;
		}
		for (Composite::ComIter iter = multi->m_container.begin() ; iter != multi->m_container.end() ;iter++)
		{
			Component* tmp = iter->second;
			if (iter == multi->m_container.begin()) // 第一个结点
			{
				node->left = tmp->m_des;
				node = node->left;
			}
			else
			{
				node->right = tmp->m_des;
				node = node->right;
			}
			transfrom2BinaryTree(dynamic_cast<Composite*>(tmp),node);
		}
	}

	return m_binaryTree;
}

// 二叉树转为多叉树
Composite* CTreeTransfer::transform2MultiTree(Composite* multi,HiNode* binary)
{
	if (!binary)
	{
		return multi;
	}

	HiNode* node = binary;
	bool lefttag = true;
	if (node->left) // 如果左不为空，说明有子结点，则为容器
	{
		Composite* com = new Composite(multi,node,false);
		if (multi == NULL)
		{
			m_multiTree = com;
		}
		else
		{
			multi->add(com);
		}
		while(node)
		{
			if (lefttag)
			{
				node = node->left;
				lefttag = false;
			}
			else
			{
				node = node->right;
			}
			transform2MultiTree(com,node);
		}

	}
	else // 叶子结点
	{
		multi->add(new Leaf(multi,node,true));
	}

	return m_multiTree;
}
