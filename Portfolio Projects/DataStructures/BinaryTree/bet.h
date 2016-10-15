/*===================================================*/
/*           WELCOME TO THE FILE bet.h               */
/*             BY: Benjamin Cooper                   */
/*          CLASS: COP4350 - Data Structures         */
/*           DATE: 11/9/2015                         */
/*        UPDATED: 11/9/2015                         */
/*===================================================*/

// Purpose: This file contains the function declarations
// 	    for the class BET, or Binary Expression Tree
// 	    which is used in order to process binary expressions
// 	    by building a tree based on postfix notation
// 	    then being able to print out the tree in
// 	    either infix or postfix
// 
// Method:  The BET is constructed by having multiple public
// 	    member functions calling various private member
// 	    functions which are recursive in order to perform
// 	    its tasks. The build function uses an algorithm
// 	    described in the text in order to process input.
//  
// Possible Improvements:
//           Additional functions and/or features. Removal
//           of recursive functions for efficiency.
//
//

#include <iostream>
#include <stack>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

class BET
{
public:
	BET(); //default zero parameter constructor
	BET(const string postfix); //postfix is a postfix expr sep by " "
	BET(const BET&); //copy constructor
	~BET(); //destructor

	bool buildFromPostfix(const string postfix); //delete existing and make tree
	const BET & operator=(const BET &); //assignment operator
	void printInfixExpression(); //prints infix exp.
	void printPostfixExpression(); //postfix
	size_t size(); //returns number of nodes
	size_t leaf_nodes(); //returns number of leaf nodes
	bool empty(); //return true if empty
	
private:
	struct BinaryNode
	{
		string element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode(const string & theElement, BinaryNode *lt, BinaryNode *rt ) 
		  : element( theElement ), left( lt ), right( rt ){}
	};



	void printInfixExpression(BinaryNode *n); //print to stdo
	void makeEmpty(BinaryNode* &t); //delete all nodes in the subtree pointed to by t
	BinaryNode * clone(BinaryNode *t) const; //clone all nodes in t
	void printPostfixExpression(BinaryNode *n); //print to the stdo
	size_t size(BinaryNode *t); //returns number of nodes in subtree
	size_t leaf_nodes(BinaryNode *t); //returns the number of leaf nodes

	BinaryNode *root;

};
