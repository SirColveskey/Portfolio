/*===================================================*/
/*   WELCOME TO THE INFIX TO POSTFIX CONVERTER       */
/*             BY: Benjamin Cooper                   */
/*          CLASS: COP4350 - Data Structures         */
/*           DATE: 10/16/2015                        */
/*        UPDATED: 10/16/2015                        */
/*===================================================*/

// Purpose: This file contains the example implementation
// 	    of the wrapper class Stack, where it is used
// 	    to evaluate infix notation expressions,
// 	    and convert them to postfix notation.
//
// Method:  Push and pop algorithms are used in order
// 	    to appropriately order an equation based
// 	    upon the order of occurance of three classes
// 	    of symbols. Operators, Operands, and Parends.
// 	    A second stack is then used in order to
// 	    recycle the expression, and allow for its
// 	    evaluation.
// 
// Possible Improvements:
//          Creation of the following functions to be
//          called by main: Postfix Conversion, and
//          Postfix Evaluation. These would pass by
//          reference stacks. A well organized switch
//          could also be implemented for readability.

#include "stack.h"
#include <string>
#include <iostream>
#include <cctype>

using namespace std;
using namespace cop4530;
int main()
{
	Stack<string> s1;
	Stack<string> s2;
	string error;
	string a;
	string read;
	//string flag;
	char next;
	char check;
	int parenthetical = 0;
	bool solve = 1;
	cout << "Input an infix equation (or type exit to quit): ";
	cin >> read;
	cout << endl;
	while(next != EOF  && cin && read != "exit")
	{
		        cout << "Postfix expression: ";
	while( next != EOF && next != '\n' )
	{
	/*	if(read == "QUIT" || read == "quit")
		{
			flag = "quit";
			break;
		}*/
		if( read == "(" || read == ")")
		{
			if( read == "(")
			{
				parenthetical++;
				s1.push(read);
			}
			else if( parenthetical == 0 && read == ")")
			{
				a = "outOfLine";
				break;
			}
			else
			{
				parenthetical--;
				if( s1.top() == "+" || s1.top() == "-" || s1.top() == "*" || s1.top() == "/" )
				{
					a = "outOfLine";
					break;
				}
				while( s1.top() != "(" )
				{
					cout << s1.top() << ' ';
					s2.push(s1.top());
					s1.pop();
				}
				s1.pop();
			}
		}
		else if( read == "+" || read == "-" ) //possible switch
		{
			while( !s1.empty() && s1.top() != "(" )
			{
				cout << s1.top() << ' ';
				s2.push(s1.top());
				s1.pop();
			}
			s1.push(read);
		}
				
		else if ( read == "*" || read == "/" ) //possible switch
		{
			while( !s1.empty() &&  s1.top() != "(" && s1.top() != "+" && s1.top() != "-")
			{
			//	cout<< "The values of s1 are as follows: ";
			//	s1.print(cout, '^');
			//	cout << endl;
				cout << s1.top() << ' ';
				s2.push(s1.top());
				s1.pop();
			}
			s1.push(read);
		}
		else //string contains an operand
		{
			check = read.front();
			if( isalpha(check) ) //turns off solver
				solve = 0;
			s1.push(read);
		};
		next = cin.peek();
	if(next != '\n' && next != EOF)
		cin >> read;
	};
	next = '0';
	if(s1.top() == "(" || s1.top() == "+" || s1.top() == "-" || s1.top() == "*" || s1.top() == "/" )
	{
		a = "badEnd";
		error = read;
	}
	int i=0;
	while( !s1.empty() )
	{
		if(s1.top() == "(")
		{
			a = "looseParen"; 
			break;
		};
		cout << s1.top() << ' ';
		s2.push(s1.top());
		s1.pop();
		i++;
	};	
	
	
	if( a == "outOfLine" )
	{
		cout << "ERROR: Out of line parenthetical. <element: )>" << endl;
		s1.clear();
	}
	if( a == "badEnd" )
	{
		cout << "ERROR: Unfulfilled operator at the close. <element: " 
		<< error << ">" << endl;
		s1.clear();
	}
	if( a == "looseParen" )
	{
		cout << "ERROR: Unclosed Parenthetical. <element: (>" << endl;
		s1.clear();
	}

	a = "0";
	parenthetical = 0;

	cout << endl;
	cout << "Postfix evaluation: ";
	s2.print(cout);
	while(!s2.empty())
	{
		s1.push(s2.top());
		s2.pop();
		
	}
	cout << " = ";
	if( solve == true )
	{
	while( s1.size() != 1 || s2.size() != 0 )
	{
	//cout << "Made it to evaluation loop!" << endl;
		if(s1.top() == "+" || s1.top() == "-" || s1.top() == "*" || s1.top() == "/" )
		{
			string i = s1.top();
			s1.pop();
			int a = atoi(s2.top().c_str());
			s2.pop();
			int b = atoi(s2.top().c_str());
			s2.pop();
			if(i == "+"){ s1.push(to_string(a+b)); }
			else if(i == "-"){ s1.push(to_string(b-a)); }
			else if(i == "*"){ s1.push(to_string(a*b)); }
			else if(i == "/"){ s1.push(to_string(a/b)); };
	//		cout << "\n evaluating an operator " << endl;
		}
		else
		{
			s2.push(s1.top());
			s1.pop();
	//		cout << "\n Flipping the operand. " << endl;
		}
	}
	cout << s1.top();
	}//closes true branch
	if( solve == false)
	{
		while( !s1.empty() )
		{
			cout << s1.top() << " ";
			s1.pop();
		}
	}//closes false branch

	cout << "\n" << "Input an infix equation (or type exit to Quit): ";
	cin >> read;
	cout << endl;
	char f = cin.peek();
	//if(f == 'Q'){flag = "quit";}
	s1.clear();
	s2.clear();
	}//closes larger while loop
	cout << "\n";	
	return 0;
}

