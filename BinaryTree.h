#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <string>

class TreeNode
{
public:
	char m_cValue;
	TreeNode* m_pLeft;
	TreeNode* m_pRight;
};

class BinaryTree
{
public:
	BinaryTree();
	BinaryTree(const std::string&);
	virtual ~BinaryTree();
	void PreOrder(std::string&) const;
	void InOrder(std::string&) const;
	void PostOrder(std::string&) const;
	void LevelOrder(std::string&) const;
	void SLevelOrder(std::string&) const;
private:
	TreeNode* m_pTree;
};

#endif //#ifndef
