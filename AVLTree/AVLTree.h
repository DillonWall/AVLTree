/*************************************************************
* Author: Dillon Wall
* Filename: AVLTree.h
* Date Created: 2/20/2019
* Modifications:
**************************************************************/

#pragma once

#define DEBUG true

#include <iostream>
#include <algorithm>
using std::max;
using std::min;
#include "AVLTreeNode.h"
#include "Exception.h"
#include "Queue.h"

/************************************************************************
* Class: AVLTree
*
* Purpose: This class represents an AVLTree using AVLTreeNodes
*
* Manager functions:
* AVLTree();
* AVLTree(const AVLTree<T>& copy);
* ~AVLTree();
* AVLTree<T>& operator=(const AVLTree<T>& rhs);
*
* Methods:
* void Insert(const T& data); 
*		Inserts data into the tree
* void Delete(const T& data); 
*		Deletes the equivalent data from the tree. Returns if there was equivalent data or not
* void Purge(); 
*		calls Purge with m_root
* int Height() const; 
*		returns the height of the tree
*
* Testing:
* bool IsEmpty() const; 
*		Returns true if the tree is empty
* bool IsBalanced() const; 
*		Returns true if all balance factors are between -1 and 1
* //bool IsHeightBalanced() const;
*		Unused -- Checks the heights of the child nodes to determine if all nodes are actually balanced
* //bool BalanceMatchesHeights(AVLTreeNode<T>* root) const;
*		Unused -- Checks a node to see if its balance factor matches its actual calculated balance factor
*
* Traversals:
* void InOrder(void visit(T&));
*		Performs an InOrder traversal of the tree and calls visit with the node's data
* void PreOrder(void visit(T&));
*		Performs a PreOrder traversal of the tree and calls visit with the node's data
* void PostOrder(void visit(T&));
*		Performs a PostOrder traversal of the tree and calls visit with the node's data
* void BreadthFirst(void visit(T&));
*		Performs a BreadthFirst traversal of the tree and calls visit with the node's data
*
* --- HELPER FUNCTIONS ---
* Core helpers:
* void CopyTree(AVLTreeNode<T>*& root, const AVLTreeNode<T>* copyRoot);
*		Helps copy constructor by recursively copying data
* void Purge(AVLTreeNode<T>*& root); //Purge – remove all items from the list.
*		Helps Purge() function by recursively purging items
*
* Method helpers:
* void InsertNode(AVLTreeNode<T>*& root, const T& data, bool& taller);
*		Helps Insert function by recursively inserting and handling AVL logic
* void LLRotation(AVLTreeNode<T>*& root);
*		Performs an LL Rotation on "root"
* void RRRotation(AVLTreeNode<T>*& root);
*		Performs an RR Rotation on "root"
* AVLTreeNode<T>* FindNodeAndDelete(AVLTreeNode<T>*& root, const T& data);
*		Helps the Delete function by recursively finding a node, deleting it, and rebalancing the AVL tree
* int GetHeightOfNode(AVLTreeNode<T>* root) const;
*		Helps Height by recursively calculuating the height of a node "root"
* int Rebalance(AVLTreeNode<T>*& root);
*		Helps FindNodeAndDelete by recursively rebalancing the tree
*
* Testing helpers:
* bool IsBalancedNode(AVLTreeNode<T>* root) const;
*		Returns true if given node is balanced through recursion (Helps IsBalanced)
* //bool IsHeightBalancedNode(AVLTreeNode<T>* root) const;
*		Returns true if given node is truely balanced, based on heights, through recursion (Helps IsBalanced)
*
* Traversal helpers:
* void InOrderTraverse(AVLTreeNode<T>* root, void visit(T&));
*		Helps the InOrder function by recursively traversing and calling visit
* void PreOrderTraverse(AVLTreeNode<T>* root, void visit(T&));
*		Helps the PreOrder function by recursively traversing and calling visit
* void PostOrderTraverse(AVLTreeNode<T>* root, void visit(T&));
*		Helps the PostOrder function by recursively traversing and calling visit
*
*************************************************************************/
template <typename T>
class AVLTree
{
public:
	AVLTree();
	AVLTree(const AVLTree<T>& copy);
	~AVLTree();
	AVLTree<T>& operator=(const AVLTree<T>& rhs);

	//Methods
	void Insert(const T& data); //Inserts data into the tree
	void Delete(const T& data); //Deletes the equivalent data from the tree. Returns if there was equivalent data or not
	void Purge(); //calls Purge with m_root
	int Height() const; //returns the height of the tree

	//Testing
	bool IsEmpty() const; //Returns true if the tree is empty
	bool IsBalanced() const; //Returns true if all balance factors are between -1 and 1
	//bool IsHeightBalanced() const;
	//bool BalanceMatchesHeights(AVLTreeNode<T>* root) const;

	//Traversals
	void InOrder(void visit(T&));
	void PreOrder(void visit(T&));
	void PostOrder(void visit(T&));
	void BreadthFirst(void visit(T&));

private:
	//Core helpers
	void CopyTree(AVLTreeNode<T>*& root, const AVLTreeNode<T>* copyRoot);
	void Purge(AVLTreeNode<T>*& root); //Purge – remove all items from the list.

	//Method helpers
	void InsertNode(AVLTreeNode<T>*& root, const T& data, bool& taller);
	void LLRotation(AVLTreeNode<T>*& root);
	void RRRotation(AVLTreeNode<T>*& root);
	AVLTreeNode<T>* FindNodeAndDelete(AVLTreeNode<T>*& root, const T& data);
	int GetHeightOfNode(AVLTreeNode<T>* root) const;
	int Rebalance(AVLTreeNode<T>*& root);

	//Testing helpers
	bool IsBalancedNode(AVLTreeNode<T>* root) const;
	//bool IsHeightBalancedNode(AVLTreeNode<T>* root) const;
	
	//Traversal helpers
	void InOrderTraverse(AVLTreeNode<T>* root, void visit(T&));
	void PreOrderTraverse(AVLTreeNode<T>* root, void visit(T&));
	void PostOrderTraverse(AVLTreeNode<T>* root, void visit(T&));

	AVLTreeNode<T>* m_root;
};

template<typename T>
inline AVLTree<T>::AVLTree() : m_root(nullptr)
{
}

template<typename T>
inline AVLTree<T>::AVLTree(const AVLTree<T> & copy) : m_root(nullptr)
{
	if (!copy.IsEmpty())
	{
		CopyTree(m_root, copy.m_root);
	}
}

template<typename T>
inline AVLTree<T>::~AVLTree()
{
	Purge(m_root);

	//Default values
	m_root = nullptr;
}

template<typename T>
inline AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T> & rhs)
{
	if (this != &rhs)
	{
		Purge(m_root);
		m_root = nullptr;

		//copy
		if (!rhs.IsEmpty())
		{
			CopyTree(m_root, rhs.m_root);
		}
	}

	return *this;
}

template<typename T>
inline void AVLTree<T>::Insert(const T & data)
{
	bool taller = false;
	InsertNode(m_root, data, taller);
}

template<typename T>
inline void AVLTree<T>::Delete(const T & data)
{
	if (IsEmpty())
		throw Exception("Tried to delete from empty tree");

	m_root = FindNodeAndDelete(m_root, data);
}

template<typename T>
inline void AVLTree<T>::Purge()
{
	Purge(m_root);
	m_root = nullptr;
}

template<typename T>
inline void AVLTree<T>::Purge(AVLTreeNode<T>*& root)
{
	if (root != nullptr)
	{
		Purge(root->m_left);
		Purge(root->m_right);
		delete root;
	}
}

template<typename T>
inline int AVLTree<T>::Height() const
{
	if (IsEmpty())
		throw Exception("Tried to get height of empty tree");

	return GetHeightOfNode(m_root);
}

template<typename T>
inline void AVLTree<T>::InOrder(void visit(T&))
{
	InOrderTraverse(m_root, visit);
}

template<typename T>
inline void AVLTree<T>::PreOrder(void visit(T&))
{
	PreOrderTraverse(m_root, visit);
}

template<typename T>
inline void AVLTree<T>::PostOrder(void visit(T&))
{
	PostOrderTraverse(m_root, visit);
}

template<typename T>
inline void AVLTree<T>::BreadthFirst(void visit(T&))
{
	if (!IsEmpty())
	{
		Queue<AVLTreeNode<T>*> nodes;

		nodes.Enqueue(m_root);

		while (!nodes.isEmpty())
		{
			AVLTreeNode<T>* current = nodes.Dequeue();

			if (current->m_left != nullptr)
				nodes.Enqueue(current->m_left);
			if (current->m_right != nullptr)
				nodes.Enqueue(current->m_right);
		}
	}
}

template<typename T>
inline bool AVLTree<T>::IsEmpty() const
{
	return m_root == nullptr;
}

template<typename T>
inline bool AVLTree<T>::IsBalanced() const
{
	return IsBalancedNode(m_root);
}

//template<typename T>
//inline bool AVLTree<T>::IsHeightBalanced() const
//{
//	return IsHeightBalancedNode(m_root);
//}

//template<typename T>
//inline bool AVLTree<T>::BalanceMatchesHeights(AVLTreeNode<T>* root) const
//{
//	int LH = GetHeightOfNode(root->m_left);
//	int RH = GetHeightOfNode(root->m_right);
//	return (LH - RH == root->m_balance);
//}

template<typename T>
inline void AVLTree<T>::CopyTree(AVLTreeNode<T>*& root, const AVLTreeNode<T>* copyRoot)
{
	if (copyRoot != nullptr)
	{
		root = new AVLTreeNode<T>(*copyRoot);
		CopyTree(root->m_left, copyRoot->m_left);
		CopyTree(root->m_right, copyRoot->m_right);
	}
}

template<typename T>
inline void AVLTree<T>::InsertNode(AVLTreeNode<T>*& root, const T & data, bool& taller)
{
	if (root == nullptr)
	{
		root = new AVLTreeNode<T>(data);
		taller = true;
	}
	else if (data < root->m_data)
	{
		InsertNode(root->m_left, data, taller);
		if (taller)
		{
			switch (root->m_balance)
			{
			case AVLTreeNode<T>::BALANCE::LH:
				if (data >= root->m_left->m_data) //Checks LR
				{
					++(root->m_left->m_balance);
					RRRotation(root->m_left);	
				}
				//else
				LLRotation(root);
				taller = false;

				break;
			case AVLTreeNode<T>::BALANCE::EH:
				root->m_balance = AVLTreeNode<T>::BALANCE::LH;

				break;
			case AVLTreeNode<T>::BALANCE::RH:
				root->m_balance = AVLTreeNode<T>::BALANCE::EH;
				taller = false;

				break;
			}
		}
	}
	else
	{
		InsertNode(root->m_right, data, taller);
		if (taller)
		{
			switch (root->m_balance)
			{
			case AVLTreeNode<T>::BALANCE::LH:
				root->m_balance = AVLTreeNode<T>::BALANCE::EH;
				taller = false;

				break;
			case AVLTreeNode<T>::BALANCE::EH:
				root->m_balance = AVLTreeNode<T>::BALANCE::RH;

				break;
			case AVLTreeNode<T>::BALANCE::RH:
				if (data < root->m_right->m_data) //Checks RL
				{
					--(root->m_right->m_balance);
					LLRotation(root->m_right);
				}
				//else
				RRRotation(root);
				taller = false;

				break;
			}
		}
	}
}

template<typename T>
inline void AVLTree<T>::LLRotation(AVLTreeNode<T>*& root)
{
	AVLTreeNode<T>* left = root->m_left;
	AVLTreeNode<T>* leftRight = left->m_right;

	++(root->m_balance);
	root->m_balance = root->m_balance - 1 - max(left->m_balance, 0);
	left->m_balance = left->m_balance - 1 + min(root->m_balance, 0);

	left->m_right = root;
	root->m_left = leftRight;

	root = left;
}

template<typename T>
inline void AVLTree<T>::RRRotation(AVLTreeNode<T>*& root)
{
	AVLTreeNode<T>* right = root->m_right;
	AVLTreeNode<T>* rightLeft = right->m_left;
	
	--(root->m_balance);
	root->m_balance = root->m_balance + 1 - min(right->m_balance, 0);
	right->m_balance = right->m_balance + 1 + max(root->m_balance, 0);

	right->m_left = root;
	root->m_right = rightLeft;

	root = right;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::FindNodeAndDelete(AVLTreeNode<T>*& root, const T & data)
{
	if (root == nullptr)
		throw Exception("Could not find item to delete from tree");

	if (data < root->m_data)
	{
		//data smaller, go left and set m_left to whatever the next node will be
		FindNodeAndDelete(root->m_left, data);
		return root;
	}
	else if (data > root->m_data)
	{
		FindNodeAndDelete(root->m_right, data);
		return root;
	}
	else
	{
		//this is the node to delete, delete -> fix -> return this node to fix reference
		//For AVL, delete node, then rebalance
		if (root->m_left == nullptr && root->m_right == nullptr) //empty
		{
			delete root;
			root = nullptr;

			//Node is deleted, rebalance
			Rebalance(m_root);

			return root;
		}
		else if (root->m_left == nullptr) //right only
		{
			AVLTreeNode<T>* temp = root->m_right;
			delete root;
			root = temp;

			//Node is deleted, rebalance
			Rebalance(m_root);

			return temp;
		}
		else if (root->m_right == nullptr) //left only
		{
			AVLTreeNode<T>* temp = root->m_left;
			delete root;
			root = temp;

			//Node is deleted, rebalance
			Rebalance(m_root);

			return temp;
		}
		else //both
		{
			AVLTreeNode<T>* current = root->m_left;
			AVLTreeNode<T>* previous = nullptr;

			while (current->m_right != nullptr)
			{
				previous = current;
				current = current->m_right;
			}

			root->m_data = current->m_data;

			if (previous == nullptr)
				root->m_left = current->m_left;
			else
				previous->m_right = current->m_left;

			delete current;

			//Node is deleted, rebalance
			Rebalance(m_root);

			return root;
		}
		
	}
}

template<typename T>
inline int AVLTree<T>::GetHeightOfNode(AVLTreeNode<T>* root) const
{
	if (root == nullptr)
		return 0;

	int leftHeight = GetHeightOfNode(root->m_left);
	int rightHeight = GetHeightOfNode(root->m_right);
	if (leftHeight > rightHeight)
		return leftHeight + 1;
	//else
	return rightHeight + 1;
}

template<typename T>
inline int AVLTree<T>::Rebalance(AVLTreeNode<T>*& root)
{
	if (root != nullptr)
	{
		int LH = Rebalance(root->m_left);
		int RH = Rebalance(root->m_right);
		root->m_balance = LH - RH;

		//Rotate if balance is more than LH or less than RH
		if (root->m_balance > AVLTreeNode<T>::BALANCE::LH) //LL or LR
		{
			LLRotation(root);
			Rebalance(m_root);
		}
		else if (root->m_balance < AVLTreeNode<T>::BALANCE::RH) //RR or RL
		{
			RRRotation(root);
			Rebalance(m_root);
		}

		return (1 + max(LH, RH));
	}

	return 0;
}

template<typename T>
inline bool AVLTree<T>::IsBalancedNode(AVLTreeNode<T>* root) const
{
	if (root != nullptr)
	{
		return (IsBalancedNode(root->m_left) &&
			root->m_balance >= -1 && root->m_balance <= 1 &&
			IsBalancedNode(root->m_right));
	}
	return true;
}

//template<typename T>
//inline bool AVLTree<T>::IsHeightBalancedNode(AVLTreeNode<T>* root) const
//{
//	if (root != nullptr)
//	{
//		int leftHeight = GetHeightOfNode(root->m_left);
//		int rightHeight = GetHeightOfNode(root->m_right);
//		return (IsHeightBalancedNode(root->m_left) &&
//			leftHeight - rightHeight >= -1 && leftHeight - rightHeight <= 1 &&
//			IsHeightBalancedNode(root->m_right));
//	}
//	return true;
//}

template<typename T>
inline void AVLTree<T>::InOrderTraverse(AVLTreeNode<T>* root, void visit(T&))
{
	if (root != nullptr)
	{
		InOrderTraverse(root->m_left, visit);
		visit(root->m_data);
		InOrderTraverse(root->m_right, visit);
	}
}

template<typename T>
inline void AVLTree<T>::PreOrderTraverse(AVLTreeNode<T>* root, void visit(T&))
{
	if (root != nullptr)
	{
		visit(root->m_data);
		PreOrderTraverse(root->m_left, visit);
		PreOrderTraverse(root->m_right, visit);
	}
}

template<typename T>
inline void AVLTree<T>::PostOrderTraverse(AVLTreeNode<T>* root, void visit(T&))
{
	if (root != nullptr)
	{
		PostOrderTraverse(root->m_left, visit);
		PostOrderTraverse(root->m_right, visit);
		visit(root->m_data);
	}
}
