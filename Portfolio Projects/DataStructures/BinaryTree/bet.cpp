/*===================================================*/
/*           WELCOME TO THE FILE bet.cpp             */
/*             BY: Benjamin Cooper                   */
/*          CLASS: COP4350 - Data Structures         */
/*           DATE: 11/9/2015                         */
/*        UPDATED: 11/9/2015                         */
/*===================================================*/

// Purpose: This file contains the function definitions
//          for the class BET, or Binary Expression Tree
//          which is used in order to process binary expressions
//          by building a tree based on postfix notation
//          then being able to print out the tree
//          either infix or postfix

#include "bet.h"

BET::BET()
{
	root = NULL;
}

BET::BET(const string postfix)
{
	root = NULL;
	buildFromPostfix(postfix);
}

BET::BET(const BET& old)
{
	root = NULL;
	*this = old;
}

BET::~BET()
{
	makeEmpty(root);
}

//================================

bool BET::buildFromPostfix(const string postfix)
{
	istringstream iss(postfix);
	string read;
	stack<BET*> stk;
	BET * left;
	BET * right;
	BET * temp;

	while(iss >> read )
	{
		if(read == "+" || read == "-" || read == "*" || read == "/")
		{
			right = stk.top();
			stk.pop();
			left = stk.top();
			stk.pop();
			temp = new BET();
			temp->root = new BinaryNode(read, left->root, right->root);
			stk.push(temp);
		}
		else
		{
			temp = new BET();
			temp->root = new BinaryNode(read, NULL, NULL);
			stk.push(temp);
		}
		temp = NULL;
	}
	makeEmpty(root);
	if( stk.size() != 1 )
		return false;
	*this = *stk.top();
	return true;
}

const BET& BET::operator=(const BET & rhs)
{
	if( this != &rhs )
	{
		makeEmpty(root);
		root = clone( rhs.root );
	}
	return *this;
}

void BET::printInfixExpression()
{
	printInfixExpression(root);
	cout << endl;
}

void BET::printPostfixExpression()
{
	printPostfixExpression(root);
	cout << endl;
}

size_t BET::size()
{
	return size(root);
}

size_t BET::leaf_nodes()
{
	return leaf_nodes(root);
}

bool BET::empty()
{
	if( root == NULL )
	return true;
	else
	return false;
}


//================================

void BET::printInfixExpression(BinaryNode *n)
{	bool state=false;
	bool state2=false;
	if(n != NULL)
	{
		if(n->left != NULL && n->right != NULL)
		{
			if(n->element == "+" && n->right->element == "-")
				{state = true;}
			if(n->element == "-" && n->right->element == "+")
				{state = true;}
			if(n->element == "*" && n->right->element == "/")
				{state = true;}
			if(n->element == "/" && n->right->element == "*")
				{state = true;}
			if(n->element == n->right->element)
				{state = true;}
			if(n->element == "*" || n->element == "/")
				{
				if(n->right->element == "+" || n->right->element == "-")
					state = true;
				if(n->left->element == "+" || n->left->element == "-")
					state2 = true;
				}
			if(state2)
				cout << "(";
			printInfixExpression(n->left);
			if(state2)
				cout << ")";
			cout << " " <<  n->element << " ";
			if(state)
				cout << "(";
			printInfixExpression(n->right);
			if(state)
				cout << ")";
		}
		else
			cout << n->element;
	}	
}

void BET::makeEmpty(BinaryNode* &t)
{
	if(t != NULL)
	{
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}
	t = NULL;
}

BET::BinaryNode * BET::clone( BinaryNode *t ) const
{
	if(t == NULL)
		return NULL;
	
	return new BinaryNode( t->element, clone( t->left ), clone( t->right ) );
}

void BET::printPostfixExpression(BinaryNode *n)
{
	if(n != NULL)
	{
		if( n->left != NULL && n->right !=NULL)
		{
			printPostfixExpression(n->left);
			printPostfixExpression(n->right);
			cout << n->element << " ";
		}
		else
			cout << n->element << " "; 
	}
}

size_t BET::size(BinaryNode *t)
{
	if( t != NULL )
	{
		return( size(t->left) + size(t->right) + 1 );
	}
	return 0;
}

size_t BET::leaf_nodes(BinaryNode *t)
{
	if( t != NULL )

		if(t->left != NULL || t->right != NULL)
		{
			return( size(t->left) + size(t->right) );
		}
		else
		{
			return( size(t->left) + size(t->right) + 1);
		}
	
	return 0;
}

