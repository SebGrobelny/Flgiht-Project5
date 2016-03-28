//Authors: Sebastian Grobelny Nicki Padar
#include <iostream>
#include <cstdlib>

using namespace std;

template<typename data>
ListNode<data>::ListNode(const data c, ListNode<data> *node) 
                        : city(c), next(node)
{  
}  // ListNode<data>())

template<typename T>
List<T>::List() : head(NULL)
{
  count = 0;
} // List<T>()

template<typename T>
List<T>::List(const List<T>& orig)
{
  head = orig.head;
} //List<T>(const List&)

template<typename T>
List<T>::~List() 
{
  for (ListNode<T> *ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  }  // for each node
} // ~List<T>()

template<typename T>
int List<T>::getCount() const
{
  return count;
}  // getCount()

template<typename T>
List<T>&  List<T>::operator += (const T &rhs)
{
  ListNode<T> *ptr, *prev = NULL; 

  for (ptr = head; ptr && ptr-> city < rhs ; ptr = ptr->next)
  {
    prev = ptr;
  } //for

  if (prev)
    prev->next = new ListNode<T>(rhs, ptr);
  
  else // an empty list
    head = new ListNode<T>(rhs, head);
  
  count++;
  return *this;
}  // operator+=

template<typename T>
List<T>& List<T>::operator -= (const T &rhs)
{
  ListNode<T> *ptr, *prev = NULL;
  
  for (ptr = head; ptr && ! (ptr->city == rhs); ptr = ptr->next)
    prev = ptr;
  
  if (ptr)
  {
    count--;
    
    if (!prev)  // found at front of list
    {
      head = ptr->next;
      
      if (!head)  // head == NULL so now empty list
        prev = NULL;
    }  // if removing first node
    else // removing node after the first
    {
      prev->next = ptr->next;
    }  // else removing after the first node
    
    delete ptr;
  }  // if found 

  return *this;
}  // operator -=

template<typename T>
const T& List<T>::operator [] (int index) const
{
  int pos = 0;
  ListNode<T> *ptr;
  
  for (ptr = head; ptr && pos != index; ptr = ptr->next, pos++);
   
  if (!ptr)
  {
     cout << " in array indexing!\n";
     exit(1);
  }  // if index beyond end of list

  return ptr->city ; 
}  // const operator[]
 
 
template<typename T>
T& List<T>::operator [] (int index)
{
  int pos = 0;
  ListNode<T> *ptr;
   
  for (ptr = head; ptr && pos != index; ptr = ptr->next, pos++);
   
  if (!ptr)
  {
    cout << " in array indexing!\n";
    exit(1);
  } // if index beyond end of thec array.

  return ptr->city; 
}  // non-const operator[]

template<typename T>
ostream& operator << (ostream& os, const List<T>& list)
{
  ListNode<T> *ptr;

  for (ptr = list.head; ptr; ptr = ptr->next)
  {
    os << ptr->city;
  } //for
  
  return os ; 
}//return os;
