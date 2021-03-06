/*
  Homework #8: Linked List
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "polynomial.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

//class Node {
Node::Node(double data, Node* next = nullptr) : data(data), next(next) {}

void listDisplay(Node* hp) {
  Node* p = hp;
  while (p != nullptr) {
    cout << p->data << ' ';
    p = p->next;
  }
  cout << endl;
}

Node* listFindTail(Node* hp) {
  if (hp == nullptr) return nullptr;
  Node* p = hp;
  while (p->next != nullptr) {
    p = p->next;
  }
  return p;
}

void listAddTail(Node*& hp, double data) {
  Node* tail = listFindTail(hp);
  if (tail == nullptr) {
    hp = new Node(data);
  } else {
    tail->next = new Node(data);
  }
}

void listAddHead(Node*& hp, double data) {
  hp = new Node(data, hp);
}

void listInsertAfter(Node* prior, double data) {
  prior->next = new Node(data, prior->next);
}

void listRemoveAfter(Node* prior) {
  Node* target = prior->next;
  prior->next = prior->next->next;
  delete target;
}

Node* listCopy(Node* hp) {
  if (hp == nullptr) return nullptr;
  Node* result = new Node(hp->data);
  Node* lastAdded = result;
  Node* p = hp->next;

  while (p != nullptr) {
    lastAdded->next = new Node(p->data);
    lastAdded = lastAdded->next;
    p = p->next;
  }
  return result;
}

void listClear(Node*& hp) {
  if (hp == nullptr) return;
  while (hp->next != nullptr) {
    listRemoveAfter(hp);
  }
  delete hp;
  hp = nullptr;
}

double findData( Node* hp, int pos) {
  Node* p = hp;
  while ( pos > 0 ) {
    p = p->next;
    --pos;
  }
  return p->data;
}



ostream& operator<<( ostream& os, const Polynomial& poly ) {
  //listDisplay( poly.headPtr );
  for( int i = poly.degree; i >= 0; --i) {
    
    int coeff = findData( poly.headPtr, i );
    if ( coeff != 0 ) {
      
      if ( (i == poly.degree && i == 0) || (i == 0) ) {
	cout << coeff;
      }	
      else if ( (i==1) && (coeff==1) ) {
	cout << "x + ";
      }
      else if ( i == 1 ) {
	cout << coeff << "x + ";
      }
      else if ( coeff == 1 ) {
	cout << "x^" << i << " + ";
      }
      else {
	cout << coeff << "x^" << i  << " + ";
      }
      
    }
  }
  if (poly.degree == 0 && poly.headPtr->data == 0) { cout << "0"; }
  //    cerr << "\tDegree: " << poly.degree;
  return os;
}

bool operator==( const Polynomial& lhs, const Polynomial& rhs ) {
  Node* lhsPtr = lhs.headPtr;
  Node* rhsPtr = rhs.headPtr;
  while ( lhsPtr || rhsPtr ) {
    if ( (lhsPtr && !rhsPtr) || (rhsPtr && !lhsPtr) ) {
      return false;
    }
    if ( lhsPtr->data != rhsPtr->data ) {
      return false;
    }
    
    lhsPtr = lhsPtr->next;
    rhsPtr = rhsPtr->next;
  }
  return true;
}

Polynomial::Polynomial() : headPtr(nullptr), degree(0) {
  listAddTail( headPtr, 0 );
}

Polynomial::Polynomial( const vector<double>& toCreate ) : headPtr(nullptr) {
  if ( toCreate.size() == 0 ) {
    listAddTail( headPtr, 0 );
  }
  else {
    degree = toCreate.size() - 1;
  }
  
  for( size_t i = toCreate.size() - 1; i != -1; --i ) {
    listAddTail( headPtr, toCreate[i] );
  }

  emptyClean();
  
  //    listDisplay( headPtr );
}

Polynomial::Polynomial( const Polynomial& rhs ) : headPtr(nullptr), degree(rhs.degree) {
  //    cerr << "In copy constructor\t";
  headPtr = listCopy( rhs.headPtr );
  //    listDisplay( headPtr );
  //    cerr << "Done" << endl;
}

Polynomial::~Polynomial() {
  //    cerr << "In destructor" << endl;
  listClear( headPtr );
  degree = 0;
  //    cerr << "Done Destructor" << endl;
}

Polynomial& Polynomial::operator=( const Polynomial& rhs ) {
  //    cerr << "In assignment operator" << endl;
  listClear( headPtr );
  headPtr = listCopy( rhs.headPtr );
  degree = rhs.degree;
  //    cerr << "Done Assignment" << endl;
  return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
  Node* hp = headPtr;
  Node* rhsPtr = rhs.headPtr;
  while ( rhsPtr ) {
    
    if ( hp ) {
      hp->data += rhsPtr->data;
      hp = hp->next;
    }
    else {
      listAddTail( headPtr, rhsPtr->data );
      ++degree;
    }
    
    rhsPtr = rhsPtr->next;
  }

  emptyClean();
  //    listDisplay( headPtr );
  //    cerr << "this: " << *this << endl;
  return *this;
}

double Polynomial::evaluate( double val ) const {
  double ans = 0;
  int power = 0;
  Node* hp = headPtr;
  
  while ( hp ) {
    ans += hp->data * ( pow( val, power ) );
    ++power;
    hp = hp->next;
  }
  return ans;
}

void Polynomial::emptyClean() {
  bool allZero = true;
  for( int i = degree; i >= 0; --i) {
    if ( findData( headPtr, i ) != 0 ) {
      allZero = false;
      break;
    }
  }
  if (allZero) {
    listClear( headPtr->next );
    degree = 0;
  }
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs ) {
  Polynomial result(lhs);
  result += rhs;
  return result;
}

bool operator!=( const Polynomial& lhs, const Polynomial& rhs ) {
  return !( lhs == rhs );
}


