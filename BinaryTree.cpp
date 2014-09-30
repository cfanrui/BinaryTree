
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
	output.clear();
	if (!m_pTree) return;
	bool isOdd = true;
	size_t levelNodeCnt = 1;
	std::queue<TreeNode*> que;
	que.push(m_pTree);
	while (!que.empty())
	{
		size_t nextLevelCnt = 0;
		if (isOdd)
		{
			std::stack<TreeNode*> s;
			while (levelNodeCnt--)
			{
				TreeNode* p = que.front();
				que.pop();
				s.push(p);
				if (p->m_pLeft)
				{
					nextLevelCnt++;
					que.push(p->m_pLeft);
				}
				if (p->m_pRight)
				{
					nextLevelCnt++;
					que.push(p->m_pRight);
				}
			}
			while (!s.empty())
			{
				output.push_back(s.top()->m_cValue);
				s.pop();
			}
		}
		else
		{
			while (levelNodeCnt--)
			{
				TreeNode* p = que.front();
				que.pop();
				output.push_back(p->m_cValue);
				if (p->m_pLeft)
				{
					nextLevelCnt++;
					que.push(p->m_pLeft);
				}
				if (p->m_pRight)
				{
					nextLevelCnt++;
					que.push(p->m_pRight);
				}
			}
		}
		levelNodeCnt = nextLevelCnt;
		isOdd = !isOdd;
	}
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
size_t Height(TreeNode* T)
{
	if (!T) return 0;
	size_t left = Height(T->m_pLeft);
	size_t right = Height(T->m_pRight);
	if (left > right)
		return left + 1;
	else return right + 1;
}
size_t BinaryTree::Height() const
{
	return ::Height(m_pTree);
}
size_t BinaryTree::Width() const
{
	std::string levels;
	size_t height = Height();
	size_t maxWidth = 0;
	if (m_pTree)
	{
		for (size_t level = 1; level <= height; level++)
		{
			levels.clear();
			this->LevelAt(level, levels);
			if (maxWidth < levels.size()) maxWidth = levels.size();
		}
	}
	return maxWidth;
}
//calculate the longest path length
void LongestPath(TreeNode* T, size_t& max)
{
	static size_t pathLen = 0;
	if (T)
	{
		pathLen++;
		if (T->m_pLeft == NULL && T->m_pRight == NULL && 
			pathLen > max) max = pathLen;
		LongestPath(T->m_pLeft, max);
		LongestPath(T->m_pRight, max);
		pathLen--;
	}
}
void LongestPath(TreeNode* T, const size_t& max, std::vector<std::string>& output)
{
	static size_t pathLen = 0;
	static std::string outStr;
	if (T)
	{
		pathLen++;
		outStr.push_back(T->m_cValue);
		if (T->m_pLeft == NULL && T->m_pRight == NULL &&
			pathLen == max)
		{
			output.push_back(outStr);
		}
		LongestPath(T->m_pLeft, max, output);
		LongestPath(T->m_pRight, max, output);
		pathLen--;
		outStr.pop_back();
	}
}
size_t BinaryTree::LongestPath(std::vector<std::string>& output) const
{
	output.clear();
	size_t longest = 0;
	::LongestPath(m_pTree, longest);
	::LongestPath(m_pTree, longest, output);
	return longest;
}
size_t BinaryTree::NumberOfNodes() const
{
	return m_nNodeCount;
}
