
#include "BinaryTree.h"
#include <stack>
#include <queue>

BinaryTree::BinaryTree() : m_pTree(NULL){}

void CreateTree(TreeNode** T, const std::string& values)
{
	static unsigned sp = 0;
	if (values[sp] == '@')
	{
		*T = NULL;
		sp++;
	}
	else
	{
		*T = new TreeNode;
		(*T)->m_cValue = values[sp++];
		CreateTree(&((*T)->m_pLeft), values);
		CreateTree(&((*T)->m_pRight), values);
	}
}
BinaryTree::BinaryTree(const std::string& values)
{
	if (values.empty()){ m_pTree = NULL; return; }
	CreateTree(&m_pTree, values);
}

void DeleteTree(TreeNode* T)
{
	if (T)
	{
		DeleteTree(T->m_pLeft);
		DeleteTree(T->m_pRight);
		delete T;
	}
}
BinaryTree::~BinaryTree()
{
	DeleteTree(m_pTree);
	m_pTree = NULL;
}
void BinaryTree::PreOrder(std::string& output) const
{
	output.clear();
	TreeNode* p = m_pTree; //p指向当前正访问的节点
	std::stack<TreeNode*> s;
	while (p || !s.empty())
	{
		while (p)
		{
			output.push_back(p->m_cValue);
			s.push(p);
			p = p->m_pLeft;
		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->m_pRight;
		}
	}
}
void BinaryTree::InOrder(std::string& output) const
{
	output.clear();
	TreeNode* p = m_pTree;
	std::stack<TreeNode*> s;
	while (p || !s.empty())
	{
		while (p)
		{
			s.push(p);
			p = p->m_pLeft;
		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			output.push_back(p->m_cValue);
			p = p->m_pRight;
		}
	}
}
void BinaryTree::PostOrder(std::string& output) const
{

}
void BinaryTree::LevelOrder(std::string& output) const
{

}
void BinaryTree::SLevelOrder(std::string& output) const
{

}
