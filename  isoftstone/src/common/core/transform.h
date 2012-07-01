#ifndef TRANSFORM_LCSH_H
#define TRANSFORM_LCSH_H

#include <map>
#include <vector>
#include "node.h"
#include "component.h"
#include "escore.h"



// 二叉树与多叉树得转换接口
class LIBCORE_EXPORT CTreeTransfer
{
public:

	CTreeTransfer()
	{
		m_multiTree = NULL;
		m_binaryTree = NULL;
	}

	~CTreeTransfer(){};

	static HiNode* transfrom2BinaryTree(Composite* multi,HiNode* binary);

	static Composite* transform2MultiTree(Composite* multi,HiNode* binary);

	static Composite* m_multiTree;

	static HiNode* m_binaryTree;
};


#endif