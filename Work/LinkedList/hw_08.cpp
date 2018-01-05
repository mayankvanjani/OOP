/*
  Homework #8: Linked List
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

//class Node {
struct Node {
  Node(double data = 0, Node* next = nullptr) : data(data), next(next) {}
  double data;
  Node* next;
};

void listDisplay(Node* hp) {
  Node* p = hp;
  while (p != nullptr) {
    cout << p->data << ' ';
    p = p->next;
  }
  cout << endl;
  //  cout << "\t";
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



class Polynomial {

  friend ostream& operator<<( ostream& os, const Polynomial& poly ) {
    //    listDisplay( poly.headPtr );
    for( int i = poly.degree; i >= 0; --i) {
      
      int coeff = findData( poly.headPtr, i );
      if ( coeff != 0 ) {

	if ( (i == poly.degree && i == 0) || (i == 0) ) {
	  cout << coeff;
	}	
	else if ( i == 1) {
	  cout << coeff << "x + ";
	}
	else if ( coeff == 1 ) {
	  cout << "x^" << i  << " + ";
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

  friend bool operator==( const Polynomial& lhs, const Polynomial& rhs ) {
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

public:
  Polynomial() : headPtr(nullptr), degree(0) {
    listAddTail( headPtr, 0 );
  }

  void emptyClean() {
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

  explicit Polynomial( const vector<double>& toCreate ) : headPtr(nullptr) {
    if ( toCreate.size() == 0 ) {
      listAddTail( headPtr, 0 );
    }
    else {
      degree = toCreate.size() - 1;
    }

    for( size_t i = toCreate.size() - 1; i != -1; --i ) {
      listAddTail( headPtr, toCreate[i] );
    }
    
    for( int i = degree; i >= 0; --i) {
      int coeff = findData( headPtr, i );
      if ( coeff == 0 ) { --degree; }
      else { break; }
    }
	
    emptyClean();

    //    listDisplay( headPtr );
  }

  Polynomial( const Polynomial& rhs ) : headPtr(nullptr), degree(rhs.degree) {
    //    cerr << "In copy constructor\t";
    headPtr = listCopy( rhs.headPtr );
    //    listDisplay( headPtr );
    //    cerr << "Done" << endl;
  }

  ~Polynomial() {
    //    cerr << "In destructor" << endl;
    listClear( headPtr );
    degree = 0;
    //    cerr << "Done Destructor" << endl;
  }

  Polynomial& operator=( const Polynomial& rhs ) {
    //    cerr << "In assignment operator" << endl;
    listClear( headPtr );
    headPtr = listCopy( rhs.headPtr );
    degree = rhs.degree;
    //    cerr << "Done Assignment" << endl;
    return *this;
  }

  Polynomial& operator+=(const Polynomial& rhs) {
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

  double evaluate( double val ) const {
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

private:
  Node* headPtr;
  int degree;
  
}; // Close Polynomial

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs ) {
  Polynomial result(lhs);
  result += rhs;
  return result;
}

bool operator!=( const Polynomial& lhs, const Polynomial& rhs ) {
  return !( lhs == rhs );
}



void doNothing(Polynomial temp) {}

int main() {
  /*
  Polynomial px({0,0,1,0,0});
  cout << "px: " << px << endl;
  Polynomial py({4,0,1,7});
  cout << "py: " << py << endl;

  Polynomial p1({0});
  cout << "p1: " << p1 << endl;
  Polynomial p2({0, 0});
  cout << "p2: " << p2 << endl;
  Polynomial p3({0, 0, 0});
  cout << "p3: " << p3 << endl;
  */
  
  //test constructor
  Polynomial p1({17});
  Polynomial p2({1, 2});
  Polynomial p3({-1, 5});
  Polynomial p4({5, 4, 3, 2, 1});

  cout << "p1: " << p1 << endl;
  cout << "p2: " << p2 << endl;
  cout << "p3: " << p3 << endl;
  cout << "p4: " << p4 << endl;
  cout << endl;
  
  cout << "p2 + p3: " << (p2+p3) << endl;
  cout << "p2 + p4: " << (p2+p4) << endl;
  cout << "p4 + p2: " << (p4+p2) << endl;
  cout << endl;

  //test copy constructor - the statement below uses the copy constructor
  //to initialize poly3 with the same values as poly4
  Polynomial p5(p4);
  p5 += p3;
  cout << "Polynomial p5(p4);\n"
	 << "p5 += p3;\n";
  
  cout << "p4: " << p4 << endl;
  cout << "p5: " << p5 << endl;
  
  cout << "Calling doNothing(p5)\n";
  doNothing(p5);
  cout << "p5: " << p5 << endl;
  cout << endl;
  
  //tests the assignment operator
  Polynomial p6;
  cout << "p6: " << p6 << endl;
  cout << boolalpha;  // Causes bools true and false to be printed that way.
  cout << "(p4 == p6) is " << (p4 == p6) << endl;
  p6 = p4;
  cout << "p6: " << p6 << endl;
  cout << boolalpha;
  cout << "(p4 == p6) is " << (p4 == p6) << endl;
  cout << endl;
  
  //test the evaluaton
  int x = 5;
  cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
  cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
    
  Polynomial p7({3, 2, 1}); // 3x^2 + 2x + 1
  cout << "p7: " << p7 << endl;
  cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;
  cout << endl;
  
  cout << "(p1 == p2) is " << (p1 == p2) << endl;
  cout << "(p1 != p2) is " << (p1 != p2) << endl;

}

