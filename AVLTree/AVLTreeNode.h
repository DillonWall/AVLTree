/*************************************************************
* Author: Dillon Wall
* Filename: AVLTreeNode.h
* Date Created: 2/20/2019
* Modifications:
**************************************************************/

#pragma once

template <typename T>
class AVLTree;

/************************************************************************
* Class: AVLTreeNode
*
* Purpose: This class represents an AVLTreeNode used in an AVLTree
* Manager functions:
* AVLTreeNode();
* AVLTreeNode(T data);
* AVLTreeNode(const AVLTreeNode<T>& copy);
* AVLTreeNode<T>& operator=(const AVLTreeNode<T>& rhs);
* ~AVLTreeNode();
*
* Methods:
* const T& GetData() const;
*		Gets m_data
* void SetData(T data);
*		Sets m_data
* AVLTreeNode<T>* GetLeft() const;
*		Gets m_left
* void SetLeft(AVLTreeNode<T>* left);
*		Sets m_left
* AVLTreeNode<T>* GetRight() const;
*		Gets m_right
* void SetRight(AVLTreeNode<T>* right);
*		Sets m_right
* int GetBalance() const;
*		Gets m_balance
* void SetBalance(int balance);
*		Sets m_balance
*
*
*************************************************************************/
template <typename T>
class AVLTreeNode
{
	friend class AVLTree<T>;

public:

	enum BALANCE : int { LH = 1, EH = 0, RH = -1}; //LeftHeavy, EqualHeavy, RightHeavy

	const T& GetData() const;
	void SetData(T data);
	AVLTreeNode<T>* GetLeft() const;
	void SetLeft(AVLTreeNode<T>* left);
	AVLTreeNode<T>* GetRight() const;
	void SetRight(AVLTreeNode<T>* right);
	int GetBalance() const;
	void SetBalance(int balance);

private:
	AVLTreeNode();
	AVLTreeNode(T data);
	AVLTreeNode(const AVLTreeNode<T>& copy);
	AVLTreeNode<T>& operator=(const AVLTreeNode<T>& rhs);
	~AVLTreeNode();

	T m_data;
	int m_balance;
	AVLTreeNode<T>* m_left;
	AVLTreeNode<T>* m_right;
};


/// Function Code ///

template<typename T>
inline const T& AVLTreeNode<T>::GetData() const
{
	return m_data;
}

template<typename T>
inline void AVLTreeNode<T>::SetData(T data)
{
	m_data = data;
}

template<typename T>
inline AVLTreeNode<T> * AVLTreeNode<T>::GetLeft() const
{
	return m_left;
}

template<typename T>
inline void AVLTreeNode<T>::SetLeft(AVLTreeNode<T>* left)
{
	m_left = left;
}

template<typename T>
inline AVLTreeNode<T>* AVLTreeNode<T>::GetRight() const
{
	return m_right;
}

template<typename T>
inline void AVLTreeNode<T>::SetRight(AVLTreeNode<T>* right)
{
	m_right = right;
}

template<typename T>
inline int AVLTreeNode<T>::GetBalance() const
{
	return m_balance;
}

template<typename T>
inline void AVLTreeNode<T>::SetBalance(int balance)
{
	m_balance = balance;
}



template<typename T>
inline AVLTreeNode<T>::AVLTreeNode() : m_data(T()), m_balance(EH), m_left(nullptr), m_right(nullptr)
{
}

template<typename T>
inline AVLTreeNode<T>::AVLTreeNode(T data) : m_data(data), m_balance(EH), m_left(nullptr), m_right(nullptr)
{
}

template<typename T>
inline AVLTreeNode<T>::AVLTreeNode(const AVLTreeNode<T>& copy) : m_data(copy.m_data), m_balance(copy.m_balance), m_left(nullptr), m_right(nullptr)
{
}

template<typename T>
inline AVLTreeNode<T>& AVLTreeNode<T>::operator=(const AVLTreeNode<T>& rhs)
{
	if (this != &rhs)
	{
		//nothing to delete

		m_data = rhs.m_data;
		m_balance = rhs.m_balance;
		m_left = nullptr;
		m_right = nullptr;
	}

	return *this;
}

template<typename T>
inline AVLTreeNode<T>::~AVLTreeNode()
{
	//No deletes

	//Default values
	m_data = T();
	m_balance = EH;
	m_left = nullptr;
	m_right = nullptr;
}
