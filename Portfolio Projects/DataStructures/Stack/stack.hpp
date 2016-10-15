/*===================================================*/
/*         WELCOME TO THE FILE stack.hpp             */
/*             BY: Benjamin Cooper                   */
/*          CLASS: COP4350 - Data Structures         */
/*           DATE: 10/16/2015                        */
/*        UPDATED: 10/16/2015                        */
/*===================================================*/

// Purpose: This file contains the function definition
//          for the file stack.h to acompany this file
//
// Method:  The linked list standard library is used to
//          create wrapper functions in order to 
//          implement a functional stack for simplicity
//          of use.
// 
// Possible Improvements:
//          Additional functions and/or features.


using namespace cop4530;
//using namespace std;
template<typename T>
Stack<T>::Stack()
{

}
template<typename T>
Stack<T>::~Stack()
{
	
}
template<typename T>
Stack<T>::Stack(const Stack<T>& a)
{
	const std::list<T> d = a.Data;
	Data = d;
}
template<typename T>
Stack<T>::Stack(Stack<T>&& a)
{
	Data = a.Data;
	a.Data = NULL;
}
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& a)
{
	Stack n(a);
	Data = n.Data;
}
template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& a)
{
	Data = a.Data;
	a.Data = NULL;
}

template<typename T>
bool Stack<T>::empty() const
{
	return Data.empty();	
}

template<typename T>
void Stack<T>::clear()
{
	Data.clear();
}

template<typename T>
void Stack<T>::push(const T& x)
{
	T  t = x;
	Data.push_front(t);
}
template<typename T>
void Stack<T>::push(T&& x)
{
	Data.push_front(x);
}
template<typename T>
void Stack<T>::pop()
{
	Data.pop_front();
}
template<typename T>
T& Stack<T>::top()
{
	return Data.front();
}
template<typename T>
const T& Stack<T>::top() const
{
	return Data.front();
}

template<typename T>
int Stack<T>::size() const
{
	return Data.size();
}

template<typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
{
	auto itr = Data.rbegin();
	auto etr = Data.rend();
	while( itr != etr )
	{
		os << *itr << ofc;
		itr++;
	}
	//os << *itr;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a)
{
	a.print(os);
	return os;
}
template<typename T>
bool operator==(const Stack<T>& A, const Stack<T>& B)
{
	Stack<T> a=A;
	Stack<T> b=B;
	while(!a.empty() && !b.empty())
	{
	if(b.top() != a.top())
		return false;
	a.pop();
	b.pop();
	}
	return true;
}
template<typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b)
{
	return !(a==b);
}
template<typename T>
bool operator<(const Stack<T>& A, const Stack<T>& B)
{
	Stack<T> a=A;
	Stack<T> b=B;
	while(!a.empty())
	{
	if(b.top() <= a.top())
		return false;
	a.pop();
	b.pop();
	}
	return true;
}
