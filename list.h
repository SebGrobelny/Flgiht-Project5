//Authors: Sebastian Grobelny Nicki Padar
#ifndef LIST_H
  #define	LIST_H

#include <fstream>
#include <iostream>

using namespace std;

template<typename data>
class List;

template<typename data>
ostream& operator << (ostream& os, const List<data>& list);

template<typename data>
class ListNode
{
  data city;
  ListNode<data> *next;
  ListNode(const data city, ListNode<data> *next);
public:
  friend class List<data>;
  friend ostream& operator << <data>(ostream& os, const List<data>& list);
};  // class ListNode

template<typename data>
class List 
{
  ListNode<data> *head;
  int count;
public:
  List();
  List(const List<data>& orig);
  ~List();
  int getCount() const;
  List<data>& operator += (const data &rhs);
  List<data>& operator -= (const data &rhs);
  const data& operator [] (int index) const;
  data& operator [] (int index);
  friend ostream& operator << <data>(ostream& os, const List<data>& list);

}; // class List 

#include "list.cpp"
#endif	// LIST_H 

