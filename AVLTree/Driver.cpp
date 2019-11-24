/*************************************************************
*
* Lab / Assignment: Lab4 - AVL Tree
*
* Overview:
*		This program is an implementation of an AVL Tree.
*		The user will either execute the program with an
*		argument of how many items they want to insert into
*		a large-scale test tree with random data, or if no
*		argument is sent then the program will prompt the user
*		to input the number of elements to the console instead.
*		After inserting, the amount of time the operation took
*		will be printed in milliseconds. Afterward, the
*		program will execute a series of tests and output
*		whether they were successful or failed.
*
* Input:
*		The program takes a command argument or otherwise
*		user input for the number of elements for the large-
*		scale timing test.
*
* Output:
*		The program will prompt the user for an amount of elements
*		to perform the large-scale timing test with if not
*		given with a command argument. The program will then
*		output how long the insertion operation took in milliseconds
*		and output the results of subsequent tests on preset data.
*
**************************************************************/

/*************************************************************
* Author: Dillon Wall
* Filename: Driver.cpp
* Date Created: 2/20/2019
* Modifications:
**************************************************************/
#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <crtdbg.h>
#include <conio.h>
#include <ctime>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "AVLTree.h"
#include "Exception.h"
#include "Random.h"

//globals
int g_int = 0;
bool g_testVal = false;
//int g_large_test_data[] = { 23051, 23001, 26015, 14910, 1837, 26646, 5933, 22953, 4959, 20841, 18870, 11710, 11852, 11360, 25049, 25989, 5292,
//							9571, 29351, 16086, 26566, 2094, 19004, 31598, 7731, 32133, 2210, 11331, 29156, 20770, 7666, 18197, 28519, 21491,
//							29628, 14918, 2661, 11906, 17833, 29419, 23408, 14261, 27999, 2339, 27387, 9143, 9637, 1704, 11690, 7990, 2248,
//							31651, 5581, 10959, 20029, 21957, 24103, 19142, 2951, 11667, 29171, 24315, 31836, 32257, 5673, 14105, 5635, 31299,
//							14333, 14097, 27136, 30176, 1192, 8135, 7155, 4872, 11884, 20490, 28350, 11047, 722, 4554, 11494, 9658, 13879, 18309,
//							28732, 12642, 2182, 3587, 3260, 4918, 10055, 9795, 8885, 94, 28889, 15285, 7210, 13790 };
int g_test_data[] = {8, 9, 10, 2, 1, 5, 3, 6, 4, 7, 11};//{ 20, 5, 12, 7, 36, 27, 94, 10, 44 };//{ 20, 12, 25, 11, 18, 22 };
int g_test_delete_order[] = {4, 5, 8, 9, 10, 2, 1, 3, 6, 7, 11};
int g_test_data_preorder[] = {5, 3, 2, 1, 4, 8, 6, 7, 10, 9, 11};//{ 20, 5, 12, 7, 10, 36, 27, 94, 44 };
int g_test_data_postorder[] = {1, 2, 4, 3, 7, 6, 9, 11, 10, 8, 5};//{ 10, 7, 12, 5, 27, 44, 94, 36, 20 };
int g_test_data_breadthfirst[] = {5, 3, 8, 2, 4, 6, 10, 1, 7, 9, 11};//{ 20, 5, 36, 12, 27, 94, 7, 44, 10 };
int g_num_elements = 11;
int g_height = 4;

//traverse functions
void PrintInt(int& i);
void CheckInOrder(int& i);
void CheckPreOrder(int& i);
void CheckPostOrder(int& i);
void CheckBreadthFirst(int& i);

// Test function declaration
bool test_default_ctor();
bool test_copy_ctor();
bool test_op_eql();

bool test_insert();
bool test_delete();
bool test_delete_empty();
bool test_purge();
bool test_height();
bool test_height_empty();

bool test_in_order();
bool test_in_order_empty();
bool test_pre_order();
bool test_pre_order_empty();
bool test_post_order();
bool test_post_order_empty();
bool test_breadth_first();
bool test_breadth_first_empty();


// Array of test functions
FunctionPointer test_functions[] = { test_default_ctor, test_copy_ctor, test_op_eql,
									test_insert, test_delete, test_delete_empty, test_purge, test_height, 
									test_height_empty, test_in_order, test_in_order_empty, test_pre_order,
									test_pre_order_empty, test_post_order, test_post_order_empty, 
									test_breadth_first, test_breadth_first_empty };

int main(int argc, char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	///-----------------------------LARGE-SCALE-TIMING-TEST-----------------------------///
	Random::Init();

	int n = 0;
	if (argc != 2)
	{
		cout << "Please enter an integer number of how many elements to add to the tree..." << endl;
		cin >> n;
	}
	else
	{
		n = atoi(argv[1]);
	}

	if (n <= 1)
	{
		cout << "Incorrect input (n was <= 1), terminating program" << endl;
		exit(1);
	}

	cout << "Inserting " << n << " elements..." << endl;

	AVLTree<int> tree;

	clock_t startTime;
	clock_t endTime;
	startTime = clock(); //set timer to current time
	//create and insert random data
	for (int i = 0; i < n; ++i)
	//for (int i = 0; i < 100; ++i)
	{
		int r = Random::GetRand();
		//cout << r << ", ";
		tree.Insert(r);

		//if (!tree.IsHeightBalanced())
		//	cout << "The tree is ***NOT*** balanced!" << endl;
	}
	endTime = clock(); //set timer to current time
	double milliSeconds = (endTime - startTime) / (CLOCKS_PER_SEC / 1000); //difference between now and before
	cout << "It took " << milliSeconds << "ms" << endl;

	//Check in order
	g_int = -1;
	g_testVal = true;
	tree.InOrder(CheckInOrder);

	if (!g_testVal)
		cout << "The tree is ***NOT*** in order!" << endl;
	else
		cout << "The tree is in order!" << endl;

	//Check balanced
	if (!tree.IsBalanced())
		cout << "The tree is ***NOT*** balanced!" << endl;
	else
		cout << "The tree is balanced!" << endl;
	///-------------------------------------------------------------------------------///

	///-------------------------------------TESTS-------------------------------------///
	bool tests_passed = true;

	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			cout << "passed\n";
		}
		else
		{
			cout << "***** failed *****\n";
			tests_passed = false;
		}
	}

	if (tests_passed) cout << "All tests passed";

	cout << "\nPress Any Key to Exit";

	cin.get();
}

//-----------------//
///Test functions ///
//-----------------//

void PrintInt(int & i)
{
	cout << i << " ";
}

void CheckInOrder(int & i)
{
	if (i < g_int)
		g_testVal = false;
}

void CheckPreOrder(int & i)
{
	if (g_test_data_preorder[g_int] != i)
		g_testVal = false;

	++g_int;
}

void CheckPostOrder(int & i)
{
	if (g_test_data_postorder[g_int] != i)
		g_testVal = false;

	++g_int;
}

void CheckBreadthFirst(int & i)
{
	if (g_test_data_breadthfirst[g_int] != i)
		g_testVal = false;

	++g_int;
}

bool test_default_ctor()
{
	bool pass = true;
	int default_size = 0;

	AVLTree<int> tree;

	if (!tree.IsEmpty())
		pass = false;

	cout << "Default ctor test ";

	return pass;
}

bool test_copy_ctor()
{
	bool pass = true;

	AVLTree<int> tree;

	for (int i = 0; i < g_num_elements; ++i)
	{
		tree.Insert(g_test_data[i]);
	}

	AVLTree<int> treeCpy(tree);

	for (int i = 0; i < g_num_elements && pass; ++i)
	{
		treeCpy.Delete(g_test_data[i]);

		g_int = -1;
		g_testVal = true;
		treeCpy.InOrder(CheckInOrder);

		if (!g_testVal)
			pass = false;
	}

	cout << "Copy ctor test ";

	return pass;
}

bool test_op_eql()
{
	bool pass = true;

	AVLTree<int> tree;

	for (int i = 0; i < g_num_elements; ++i)
	{
		tree.Insert(g_test_data[i]);
	}

	AVLTree<int> treeCpy;
	treeCpy = tree;

	for (int i = 0; i < g_num_elements && pass; ++i)
	{
		treeCpy.Delete(g_test_data[i]);

		g_int = -1;
		g_testVal = true;
		treeCpy.InOrder(CheckInOrder);

		if (!g_testVal)
			pass = false;
	}

	cout << "Op equals test ";

	return pass;
}

bool test_insert()
{
	bool pass = true;

	AVLTree<int> tree;

	for (int i = 0; i < g_num_elements && pass; ++i)
	{
		tree.Insert(g_test_data[i]);

		//Check in order
		g_int = -1;
		g_testVal = true;
		tree.InOrder(CheckInOrder);

		if (!g_testVal)
			pass = false;

		//Check balanced
		if (!tree.IsBalanced())
			pass = false;
	}

	cout << "Insert test ";

	return pass;
}

bool test_delete()
{
	bool pass = true;

	AVLTree<int> tree;

	for (int i = 0; i < g_num_elements; ++i)
	{
		tree.Insert(g_test_data[i]);
	}

	for (int i = 0; i < g_num_elements && pass; ++i)
	{
		tree.Delete(g_test_delete_order[i]);

		g_int = -1;
		g_testVal = true;
		tree.InOrder(CheckInOrder);

		if (!g_testVal)
			pass = false;
	}

	if (!tree.IsEmpty())
		pass = false;

	cout << "Delete test ";

	return pass;
}

bool test_delete_empty()
{
	bool pass = false;
	bool pass2 = false;

	AVLTree<int> tree;

	try
	{
		tree.Delete(42);
	}
	catch (Exception c)
	{
		pass = true;
	}

	for (int i = 0; i < g_num_elements; ++i)
	{
		tree.Insert(g_test_data[i]);
	}

	try
	{
		for (int i = 0; i < g_num_elements + 1 && pass; ++i) //one extra
		{
			tree.Delete(g_test_data[i]);
		}
	}
	catch (Exception c)
	{
		pass2 = true;
	}

	cout << "Delete empty test ";

	return pass && pass2;
}

bool test_purge()
{
	bool pass = true;

	AVLTree<int> tree;

	for (int i = 0; i < g_num_elements && pass; ++i)
	{
		tree.Insert(g_test_data[i]);
	}

	tree.Purge();

	pass = tree.IsEmpty();

	cout << "Purge test ";

	return pass;
}

bool test_height()
{
	bool pass = true;

	AVLTree<int> tree;

	for (int i = 0; i < g_num_elements && pass; ++i)
	{
		tree.Insert(g_test_data[i]);
	}

	pass = tree.Height() == g_height;

	cout << "Height test ";

	return pass;
}

bool test_height_empty()
{
	bool pass = false;

	AVLTree<int> tree;

	try
	{
		tree.Height();
	}
	catch (Exception e)
	{
		pass = true;
	}

	cout << "Height empty test ";

	return pass;
}

bool test_in_order()
{
	bool pass = true;

	AVLTree<int> tree;

	for (int i = 0; i < g_num_elements && pass; ++i)
	{
		tree.Insert(g_test_data[i]);

		g_int = -1;
		g_testVal = true;
		tree.InOrder(CheckInOrder);

		if (!g_testVal)
			pass = false;
	}

	cout << "In order test ";

	return pass;
}

bool test_in_order_empty()
{
	bool pass = true;

	AVLTree<int> tree;

	g_int = -1;
	g_testVal = true;
	tree.InOrder(CheckInOrder);

	if (!g_testVal)
		pass = false;

	cout << "In order empty test ";

	return pass;
}

bool test_pre_order()
{
	bool pass = true;

	AVLTree<int> tree;

	for (int i = 0; i < g_num_elements && pass; ++i)
	{
		tree.Insert(g_test_data[i]);
	}

	g_int = 0;
	g_testVal = true;
	//tree.PreOrder(PrintInt);
	tree.PreOrder(CheckPreOrder);

	if (!g_testVal)
		pass = false;

	cout << "Pre-order test ";

	return pass;
}

bool test_pre_order_empty()
{
	bool pass = true;

	AVLTree<int> tree;

	g_int = 0;
	g_testVal = true;
	tree.PreOrder(CheckPreOrder);

	if (!g_testVal)
		pass = false;

	cout << "Pre-order empty test ";

	return pass;
}

bool test_post_order()
{
	bool pass = true;

	AVLTree<int> tree;

	for (int i = 0; i < g_num_elements && pass; ++i)
	{
		tree.Insert(g_test_data[i]);
	}

	g_int = 0;
	g_testVal = true;
	//tree.PostOrder(PrintInt);
	tree.PostOrder(CheckPostOrder);

	if (!g_testVal)
		pass = false;

	cout << "Post-order test ";

	return pass;
}

bool test_post_order_empty()
{
	bool pass = true;

	AVLTree<int> tree;

	g_int = 0;
	g_testVal = true;
	tree.PostOrder(CheckPostOrder);

	if (!g_testVal)
		pass = false;

	cout << "Post-order empty test ";

	return pass;
}

bool test_breadth_first()
{
	bool pass = true;

	AVLTree<int> tree;

	for (int i = 0; i < g_num_elements && pass; ++i)
	{
		tree.Insert(g_test_data[i]);
	}

	g_int = 0;
	g_testVal = true;
	tree.BreadthFirst(CheckBreadthFirst);

	if (!g_testVal)
		pass = false;

	cout << "Breadth-first test ";

	return pass;
}

bool test_breadth_first_empty()
{
	bool pass = true;

	AVLTree<int> tree;

	g_int = 0;
	g_testVal = true;
	tree.BreadthFirst(CheckBreadthFirst);

	if (!g_testVal)
		pass = false;

	cout << "Breadth-first empty test ";

	return pass;
}
