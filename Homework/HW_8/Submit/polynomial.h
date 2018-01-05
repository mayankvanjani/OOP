/*
  Homework #8: Linked List
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

#include <vector>

//class Node {
struct Node {
  Node( double, Node* );
  double data;
  Node* next;
};

// Linked List Functions
void listDisplay(Node* hp);

Node* listFindTail(Node* hp);

void listAddTail(Node*& hp, double data);

void listAddHead(Node*& hp, double data);

void listInsertAfter(Node* prior, double data);

void listRemoveAfter(Node* prior);

Node* listCopy(Node* hp);

void listClear(Node*& hp);

double findData( Node* hp, int pos);


// Polynomial Class supports:
//     vector paramater constructor, +=, +, copy control, ==, !=, <<, evaluation
class Polynomial {

  friend std::ostream& operator<<( std::ostream& os, const Polynomial& poly );
  
  friend bool operator==( const Polynomial& lhs, const Polynomial& rhs );
  
public:
  Polynomial();

  Polynomial( const std::vector<double>& toCreate );

  Polynomial( const Polynomial& rhs );

  ~Polynomial();
 
  Polynomial& operator=( const Polynomial& rhs );
 
  Polynomial& operator+=(const Polynomial& rhs);
 
  double evaluate( double val ) const;

  void emptyClean();
 
private:
  Node* headPtr;
  int degree;
 
}; // Close Polynomial

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs );

bool operator!=( const Polynomial& lhs, const Polynomial& rhs );

void doNothing(Polynomial temp);

#endif
