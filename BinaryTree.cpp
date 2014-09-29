
#include "BinaryTree.h"
#include <stack>
#include <queue>
#include <cmath>

BinaryTree::BinaryTree() : m_pTree(NULL), m_nNodeCount(0){}

size_t CreateTree(TreeNode** T, const std::string& values)
{
	static unsigned sp = 0;
	static size_t cnt = 0; //count of the nodes
	if (values[sp] == '@')
	{
		*T = NULL;
		sp++;
	}
	else
	{
		*T = new TreeNode;
		cnt++;
		(*T)->m_cValue = values[sp++];
		CreateTree(&((*T)->m_pLeft), values);
		CreateTree(&((*T)->m_pRight), values);
	}
	return cnt;
}
BinaryTree::BinaryTree(const std::string& values)
{
	if (values.empty())
	{
		m_pTree = NULL;
		m_nNodeCount = 0;
		return;
	}
	m_nNodeCount = CreateTree(&m_pTree, values);
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
	//p points to the current visited node
	TreeNode* p = m_pTree;
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
	output.clear();
	std::stack<TreeNode*> s;
	if (m_pTree) s.push(m_pTree);
	TreeNode* p, *pre = m_pTree;
	while (!s.empty())
	{
		p = s.top();
		if (pre == p->m_pLeft || pre == p->m_pRight ||
			p->m_pLeft == NULL && p->m_pRight == NULL)
		{
			s.pop();
			output.push_back(p->m_cValue);
			pre = p;
		}
		else
		{
			if (p->m_pRight) s.push(p->m_pRight);
			if (p->m_pLeft) s.push(p->m_pLeft);
		}
	}
}
void BinaryTree::LevelOrder(std::string& output) const
{
	output.clear();
	std::queue<TreeNode*> q;
	TreeNode* p;
	if (m_pTree) q.push(m_pTree);
	while (!q.empty())
	{
		p = q.front();
		output.push_back(p->m_cValue);
		q.pop();
		if (p->m_pLeft) q.push(p->m_pLeft);
		if (p->m_pRight) q.push(p->m_pRight);
	}
}
void BinaryTree::SLevelOrder(std::string& output) const
{

}

void LevelAt(TreeNode* T, size_t level, std::string& output)
{
	if (NULL != T)
	{
		if (1 == level)
		{
			output.push_back(T->m_cValue);
		}
		else
		{
			LevelAt(T->m_pLeft, level - 1, output);
			LevelAt(T->m_pRight, level - 1, output);
		}
	}
}
void BinaryTree::LevelAt(size_t level, std::string& output) const
{
	output.clear();
	if (level<1 || level>Height() || NULL==m_pTree) return;
	::LevelAt(m_pTree, level, output);
}
size_t BinaryTree::Height() const
{
	if (m_nNodeCount > 0)
		return (size_t)(log10(double(m_nNodeCount))
			/ log10(double(2))) + 1;
	else return 0;
}
size_t BinaryTree::Width() const
{
	return 0;
}
size_t BinaryTree::LongestPath(std::string&) const
{
	return 0;
}
size_t BinaryTree::NumberOfNodes() const
{
	return m_nNodeCount;
}
