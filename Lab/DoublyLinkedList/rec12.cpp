/*
  Rec12: Doubly Linked List Class
  Mayank Vanjani
  12/1/17
  CS2114
  NYU Tandon School of Engineering
*/

#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

class List {

  // Output Operator for List Class
  friend ostream& operator<<( ostream& os, const List& toPrint ) {
    Node* p = toPrint.hp;
    if ( !p ) { os << "EMPTY"; }
    else {
      while ( p ) {
	os << p->data << " ";
	p = p->next;
      }
    }
    return os;
  }
  
private:
  // Private Node Struct 
  struct Node {
    Node( int data, Node* next = nullptr, Node* prior = nullptr ) :
      data( data ), next( next ), prior( prior ) {}
    int data;
    Node* next;
    Node* prior;
  };

  // Other List Private Fields
  Node* hp;
  Node* tp;
  size_t len;

public:
  // Public Iterator Class
  class iterator {

    friend List;
    
    friend bool operator==( const iterator& lhs, const iterator& rhs ) {
      return ( lhs.ptr == rhs.ptr );
    }
    
  public:
    iterator( Node* ptr = nullptr ) : ptr( ptr ) {}
    
    iterator& operator++() {
      ptr = ptr->next;
      return *this;
    }
    
    iterator& operator--() {
      ptr = ptr->prior;
      return *this;
    }
    
    int operator*() {
      return ptr->data;
    }
    
  private:
    Node* ptr;
  }; // Close Iterator

  iterator begin() { return iterator( hp ); }
  iterator end() { return iterator( nullptr ); }
  iterator begin() const { return iterator( hp ); }
  iterator end() const { return iterator( nullptr ); }
  
  // Continue List Public Methods
  List() : hp(nullptr), tp(nullptr), len(0) {}


  Node* listCopy(Node* ptr) {
    if (ptr == nullptr) return nullptr;
    // Initialization code
    Node* result = new Node(ptr->data);
    Node* prev = result;
    Node* lastAdded = result;
    Node* p = ptr->next;

    while (p != nullptr) {
      lastAdded->next = new Node(p->data);
      lastAdded = lastAdded->next;
      lastAdded->prior = prev;
      p = p->next;
      prev = prev->next;
    }
    return result;
  }

  List( const List& rhs ) {
    cerr << "List(List)" << endl;
    hp = listCopy( rhs.hp );
    Node* tempTail = hp;
    while ( tempTail ) {
      tempTail = tempTail->next;
    }
    tp = tempTail;
    len = rhs.len;
  }
  
  void push_back( int data ) {
    Node* p = new Node( data );
    if ( !tp ) { hp = tp = p; }
    else {
      p->prior = tp;
      tp->next = p;
      tp = p;
    }
    ++len;
  }
  
  void pop_back() {
    if ( tp ) {
      if ( len == 1 ) {
	delete hp;
	hp = tp = nullptr;
      }
      else {
	Node* toRem = tp;
	tp = tp->prior;
	tp->next = nullptr;
	delete toRem;
      }
      --len;
    }
    else {
      cerr << "popping from empty list" << endl;
    }
  }

  int front() const {
    if ( !hp ) {
      return 0;
    }
    return hp->data;
  }

  int back() const {
    if ( !tp ) {
      return 0;
    }
    return tp->data;
  }

  size_t size() const {
    return len;
  }
  
  void push_front( int data ) {
    Node* p = new Node( data );
    if ( !hp ) { hp = tp = p; }
    else {
      p->next = hp;
      hp->prior = p;
      hp = p;
    }
    ++len;
  }
  
  void pop_front() {
    if ( hp ) {
      if ( len == 1 ) {
	delete hp;
	hp = tp = nullptr;
      }
      else {
	Node* toRem = hp;
	hp = hp->next;
	hp->prior = nullptr;
	delete toRem;
      }
      --len;
    }
    else {
      cerr << "popping from empty list" << endl;
    }
  }

  void clear() {
    while( hp ) { pop_front(); }
  }

  ~List() {
    cerr << "~List()" << endl;
    clear();
  }
  
  int operator[]( size_t index ) const {
    if ( index < len ) {
      Node* mover = hp;
      while( index != 0 ) {
	mover = mover->next;
	--index;
      }
      return mover->data;
    }
    else {
      cerr << "Index Out of Range" << endl;
      exit(1);
    }
  }
  
  int& operator[]( size_t index ) {
    if ( index < len ) {
      Node* mover = hp;
      while( index != 0 ) {
	mover = mover->next;
	--index;
      }
      return mover->data;
    }
    else {
      cerr << "Index Out of Range" << endl;
      exit(1);
    }
  }

  void insert( const iterator& iter, int data ) {
    Node* toAdd = new Node( data );
    Node* p = iter.ptr;
    if ( p == end() ) {
      push_back( data );
    }
    else if ( p == begin() ) {
      push_front( data );
    }
    else if ( p->prior ) {
      Node* prev = p->prior;
      prev->next = toAdd;
      toAdd->prior = prev;
      toAdd->next = p;
      p->prior = toAdd;
    }
    else {
      toAdd->next = p;
      p->prior = toAdd;
    }
  }
  
  iterator erase( const iterator& iter ) {
    Node* p = iter.ptr;
    Node* after = nullptr;
    if ( p ) {
      if ( p == begin() ) {
	pop_front();
	after = hp;
      }
      else if ( p->prior ) {
	Node* prev = p->prior;
	after = p->next;
	prev->next = after;
	after->prior = prev;
	delete iter.ptr;
      }
    }
    return iterator( after );
  }

  List& operator=( const List& rhs ) {
    cerr << "List::op=(List)" << endl;
    clear();
    hp = listCopy( rhs.hp );
    Node* tempTail = hp;
    while ( tempTail ) {
      tempTail = tempTail->next;
    }
    tp = tempTail;
    len = rhs.len;
    return *this;
  }
  
}; // Close List Class

// != method for Iterators
bool operator!=( const List::iterator& lhs, const List::iterator& rhs ) {
  return !( lhs == rhs );
}



void printListInfo(const List& myList) {
  cout << "size: " << myList.size()
       << ", front: " << myList.front()
       << ", back(): " << myList.back()
       << ", list: " << myList << endl;
}

// Task 8
void doNothing(const List aList) {
  cout << "In doNothing\n";
  printListInfo(aList);
  cout << endl;
  cout << "Leaving doNothing\n";
}

int main() {

  // Task 1
  cout << "\n------Task One------\n";
  List myList;
  cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
  for (int i = 0; i < 10; ++i) {
    cout << "myList.push_back(" << i*i << ");\n";
    myList.push_back(i*i);
    printListInfo(myList);
  }
  cout << "===================\n";
  cout << "Remove the items with pop_back\n";
  while (myList.size()) {
    printListInfo(myList);
    myList.pop_back();
  }
  cout << "===================\n";

  // Task2
  cout << "\n------Task Two------\n";
  cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
  for (int i = 0; i < 10; ++i) {
    cout << "myList2.push_front(" << i*i << ");\n";
    myList.push_front(i*i);
    printListInfo(myList);
  }
  cout << "===================\n";
  cout << "Remove the items with pop_front\n";
  while (myList.size()) {
    printListInfo(myList);
    myList.pop_front();
  }
  cout << "===================\n";

  // Task3
  cout << "\n------Task Three------\n";
  cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
  for (int i = 0; i < 10; ++i) {
    myList.push_back(i*i);
  }
  printListInfo(myList);
  cout << "Now clear\n";
  myList.clear();
  cout << "Size: " << myList.size() << ", list: " << myList << endl;
  cout << "===================\n";

  // Task4
  cout << "\n------Task Four------\n";
  cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
  for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
  cout << "Display elements with op[]\n";
  for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
  cout << endl;
  cout << "Add one to each element with op[]\n";
  for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
  cout << "And print it out again with op[]\n";
  for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
  cout << endl;

  // Task 5
  cout << "\n------Task Five------\n";
  cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
  myList.clear();
  for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
  printListInfo(myList);
  cout << "Now display the elements in a ranged for\n";
  for (int x : myList) cout << x << ' ';
  cout << endl;
  cout << "And again using the iterator type directly:\n";
  for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    cout << *iter << ' ';
  }
  cout << endl;
  cout << "WOW!!! (I thought it was cool.)\n";

  // Task 6
  cout << "\n------Task Six------\n";
  cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
  myList.clear();
  for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
  printListInfo(myList);
  cout << "Filling an empty list with insert at begin(): "
       << "i*i for i from 0 to 9\n";
  myList.clear();
  for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
  printListInfo(myList);
  // ***Need test for insert other than begin/end***
  cout << "===================\n";

  // Task 7
  cout << "\n------Task Seven------\n";
  cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
  myList.clear();
  for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
  cout << "Erasing the elements in the list, starting from the beginning\n";
  while (myList.size()) {
    printListInfo(myList);
    myList.erase(myList.begin());
  }
  // ***Need test for erase other than begin/end***
  cout << "===================\n";

  // Task 8
  cout << "\n------Task Eight------\n";
  cout << "Copy control\n";
  cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
  myList.clear();
  for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
  printListInfo(myList);
  cout << "Calling doNothing(myList)\n";
  doNothing(myList);
  cout << "Back from doNothing(myList)\n";
  printListInfo(myList);

  cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
  List listTwo;
  for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
  printListInfo(listTwo);
  cout << "listTwo = myList\n";
  listTwo = myList;
  cout << "myList: ";
  printListInfo(myList);
  cout << "listTwo: ";
  printListInfo(listTwo);
  cout << "===================\n";

}
