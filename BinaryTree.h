
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <string>

//structure of a tree node
class TreeNode
{
public:
	//value of node
	char m_cValue;
	//points to the left child node
	TreeNode* m_pLeft;
	//points to the right child node
	TreeNode* m_pRight;
};

class BinaryTree
{
public:
	BinaryTree();
	//Create a tree through a string
	//such as "abdg@@@eh@@@c@f@@"
	BinaryTree(const std::string&);
	//delete the tree
	virtual ~BinaryTree();
	//traverse in preorder way
	void PreOrder(std::string&) const;
	//traverse in inorder way
	void InOrder(std::string&) const;
	//traverse in postorder way
	void PostOrder(std::string&) const;
	//traverse one level by one level
	void LevelOrder(std::string&) const;
	//traverse one level by one level
	//and node sequence reverses at each odd level
	void SLevelOrder(std::string&) const;
	//extract nodes of a certain level
	//level number starts with 1
	void LevelAt(size_t, std::string&) const;
	//return the height of the tree
	size_t Height() const;
	//return the width of the tree
	//width is defined as:
	//the node number of a level that has the most node number
	size_t Width() const;
	//return one of the longest paths from root to a leaf node
	//and save the node values of the path
	size_t LongestPath(std::string&) const;
	size_t NumberOfNodes() const;
private:
	//root pointer
	TreeNode* m_pTree;
	//amount of the tree nodes
	size_t m_nNodeCount;
};

#endif //#ifndef
