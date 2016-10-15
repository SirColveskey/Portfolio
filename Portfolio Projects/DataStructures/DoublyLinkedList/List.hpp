/*===================================================*/
/*       WELCOME TO THE LINKED LIST.hpp              */
/*             BY: Benjamin Cooper                   */
/*          CLASS: COP4350 - Data Structures         */
/*           DATE: 10/2/2015                         */
/*        UPDATED: 10/3/2015                         */
/*===================================================*/

// Purpose: This file is the .hpp implementation for a
// 	    provided file List.h by the course. Using
// 	    a textbook reference this file implements
// 	    the functions for a Doubly-Linked list with
// 	    dummy nodes Head and Tail using C++.
//
// Method:  Various functions are implemented in order
//          to fully implement the class. A collection
//          of non-standard functions are also
//          implemented including multiple constructors
//          and reverse().
// 
// Possible Improvements:
//          Cleaner implementation of Node, inclusion of
//          other relevant functions, such as Sort, etc.


#include "List.h"

using namespace std;

template<typename T>
List<T>::List()
{
  //default constructor. Call init() to initialize
  init();
};

template<typename T>
void List<T>::init()
{
  head = new Node;
  tail = new Node;
  theSize=0;
  head->next=tail;
  tail->prev=head;
  //initializes the member variables of the list
};

template<typename T>
List<T>::List(const List &rhs)
{
  init();
  *this = rhs;
};


template<typename T>
List<T>::List(List &&rhs)
{
   init();
   *this = rhs;
};

template<typename T>
List<T>::List(int num, const T& val /*= T{}*/) 
{
  init();
  for(int i=0; i<num; i++)
     push_front(val);
};

template<typename T>
List<T>::List(const_iterator start, const_iterator end)
{
  //makes a list with elements from another list including the element refered to by the start, exclude end
  //head->start->...->tail using a for loop checking itr != end; itr++;
  init();
  for(start; start!=end; start++)
  {
    const T val = start.current->data;
    push_back(val);
  };
};

template<typename T>
List<T>::~List()
{
  clear();
  delete head;
  delete tail;
};

template<typename T>
const List<T>& List<T>::operator=(const List & rhs)
{
  if(this == &rhs)
    return *this;
  clear();
  for(const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
    push_back(*itr);
  return *this;
};

template<typename T>
List<T>& List<T>::operator=(List && rhs)
{
  if(this == &rhs)
    return *this;
  clear();
  for(const_iterator itr = rhs.begin(); itr!= rhs.end(); ++itr)
    push_back(*itr);
  return *this;
};

template<typename T>
int List<T>::size() const
{
  return theSize; //return theSize
};

template<typename T>
bool List<T>::empty() const
{
  bool r;
  if(theSize==0) r=1;
  else r=0;
  return r; //return true if empty, else false
};

template<typename T>//TODO
void List<T>::clear()
{
  while(size()!= 0)
  {
    pop_front();
  };
//  if(head->next!=tail && tail->prev!=head) cout<<"ERROR!!!! Error in clear() ERROR!!!!"<<'\n';
};

template<typename T>//TODO
void List<T>::reverse()
{
  List<T>::iterator itr=end();
  itr--;
  for(int i=0; i<size(); i++)
  {
    push_back(*itr);
    itr=erase(itr);
    itr--;
  };
  //Loop through swapping values of prev and next
  //reverses the order of elements in the list. last-> first first-> last
};

template <typename T>//Use protected constructor: iterator(Node *p)
T& List<T>::front()
{
  iterator itr(head->next);
  return itr->value; //returns references to the first element
};

template<typename T>
const T& List<T>::front() const
{
  iterator itr(head->next);
  return itr->value;
};

template<typename T>
T& List<T>::back()
{ 
  iterator itr(tail->prev);
  return itr->value;
};

template<typename T>
const T& List<T>::back() const
{ 
  iterator itr(tail->prev);
  return itr->value;
};

template<typename T>
void List<T>::push_front(const T & val)
{
   //insert new object as first  
   insert(begin(),val);
};

template<typename T>
void List<T>::push_front(T && val)
{
  //WHAT DO I DO DIFFERENT HERE??
   insert(begin(),val);
};

template<typename T>
void List<T>::push_back(const T & val)
{
   insert(end(),val);
   //insert new object at back
//   insert(++end(), val);
};

template<typename T>
void List<T>::push_back(T && val)
{
   insert(end(),val);
  //same as above.
};

template<typename T>
void List<T>::pop_front()
{
    //pops off front
    erase(begin());
};

template<typename T>
void List<T>::pop_back()
{
    //pops off back
    erase(--end());
};

template<typename T>
void List<T>::remove(const T &val)//TODO
{
  List<T>::iterator itr=begin();
  while(itr != end())
  {
    if(*itr==val)
      itr=erase(itr);
    else
      itr++;
  };
  //deletes all nodes with val == val  
};

template<typename T>
void List<T>::print(std::ostream& os, char ofc /*= ' '*/) const
{
  auto itr=begin();
  for(int i=0; i<theSize; i++)
  {
    os << *itr << ofc;
    itr++;
  }
};

template<typename T>
typename List<T>::iterator List<T>::begin()//TODO
{
  return iterator(head->next); //return iterator to the first element of list
};

template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
  return const_iterator(head->next);
};

template<typename T>
typename List<T>::iterator List<T>::end()//TODO
{
  return iterator(tail);
};

template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
  return iterator(tail);
};

template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val)
{
  Node * block;
  block = itr.current;
  theSize++;
  return iterator(block->prev = block->prev->next = new Node(val,block->prev, block) );
  //insert value val ahead of node ref by itr
};

template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val)
{
  Node * block;
  block = itr.current;
  theSize++;
  return iterator(block->prev = block->prev->next = new Node(val, block-> prev, block) );
};

template<typename T>
typename List<T>::iterator List<T>::erase(iterator itr)
{//Model this after insert Don't forget to delete
  Node *p = itr.current;
  iterator retVal(p->next);
  p->prev->next = p->next;
  p->next->prev = p->prev;
  delete p;
  theSize--;
  return retVal;//delete node refered to by itr
};

template<typename T>
typename List<T>::iterator List<T>::erase(iterator start,iterator end)
{
  for(iterator itr=start;itr!=end;)
  {
    itr = erase(itr);
  };
  return end; //delete all nodes between start and end :: TO DO THIS ITERATE FROM START TILL ITR == END USING ERASE
};

template<typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs)
{
  //Quick check the size, then loop through two iterators comparing. While(rhs.Iterator != rhs.end || rhs.iterator != rhs.end)
  if(lhs.size()!=rhs.size())
    return 0;
  auto itrl=lhs.begin();
  auto itrr=rhs.begin();
  for(int i=0; i<rhs.size(); i++)
  {
    if(*itrl!=*itrr) return 0;
    itrl++;
    itrr++;
  }
  return 1; //checks if the two lists contain the same sequence of elements and the positions are equal
};

template<typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
  return !(lhs==rhs); //opposite ==
};

template<typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
  l.print(os);
  return os; //call List<T>::print() to print out everything in the list.
};

//List::iterator CLASS :: Confused as to where this differes from const_iterator

template <typename T>
List<T>::iterator::iterator()
{
  List<T>::iterator::current=NULL;
};

template <typename T>
T& List<T>::iterator::operator*()
{
  return this->retrieve();
};

template <typename T>
const T& List<T>::iterator::operator*() const
{
  return this->retrieve();
};

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
  this->current = this->current->next;
  return *this; //prefix increment
};

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
  auto r=*this;
  this->current = this->current -> next;
  return r; //postfix increment
};

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
  this->current = this->current->prev;
  return *this;//prefix decrement
};

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
  auto r=*this;
  this->current = this->current->prev;
  return r;
};

//List::const_iterator CLASS :: READY TO TEST
template <typename T>
T& List<T>::const_iterator::retrieve() const
{
  return current->data;
};

template <typename T>
List<T>::const_iterator::const_iterator()
{
  List<T>::const_iterator::current=NULL;
};

template <typename T>
const T& List<T>::const_iterator::operator*() const
{
  return retrieve();
};

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
  this->current = this->current->next;
  return *this;
};

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
  auto r=*this;
  this->current = this->current->next;
  return r;
};

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
    this->current = this->current->prev;
    return *this;
};

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
  auto r=*this;
  this->current = this->current->prev;
  return r;//postfix decrement
};

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
{
  bool r;
  if(current==rhs.current) r=1;
  else r=0;
  return r;//test if iterator points to same as other iterator
};

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
{
  return !(*this==rhs); 
};

/*template <typename T>
T& List<T>::const_iterator::retrieve() const 
{
  auto r;
  r=List<T>::const_iterator::current->value;
  return r;//return a reference to a corresponding element in a list
};
*/
template <typename T>
List<T>::iterator::iterator(Node *p)
{
  List<T>::iterator::current=p;
};
template <typename T>
List<T>::const_iterator::const_iterator(Node *p)
{
  List<T>::const_iterator::current=p;//one parameter constructor, set pointer current to teh given node pointer p
};

