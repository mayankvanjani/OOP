/*
  Rec14: Recursion
  Mayank Vanjani
  12/15/17
  CS2114
  NYU Tandon School of Engineering
*/

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct Node {
  Node( int data = 0, Node* next = nullptr ) : data(data), next(next) {}
  int data;
  Node* next;
};

// Node FUnctions
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
  //while (p != nullptr && p->next != nullptr) {
  while (p->next != nullptr) {
    p = p->next;
  }
  return p;
}


void listAddTail(Node*& hp, int data) {
  //Node* nodeToAdd = new Node(data);
  Node* tail = listFindTail(hp);
  if (tail == nullptr) {
    hp = new Node(data);
  } else {
    tail->next = new Node(data);
  }
}

void listAddHead(Node*& hp, int data) {
  hp = new Node( data, hp );
}

// Tree Struct
struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};



// ========================= //

// Task One
bool evenBinaryOnes( int n ) {
  if ( n == 0 ) { return true; }
  else { return ( n & 1 ) ^ evenBinaryOnes( n >> 1 ); }
}

// Task Two
Node* sumList( Node* first, Node* second ) {
  if ( !first || !second ) { return nullptr; }
  else {
    Node* result = sumList( first->next, second->next );
    listAddHead( result, first->data + second->data );
    return result;
  }
}

// Task Three
int treeMax( TNode* root ) {
  if ( !root ) { return INT_MIN; }
  else {
    return max( max( treeMax( root->left ), treeMax( root->right ) ), root->data );
  }
}

// Task Four
bool palindrome( char* s, int length ) {
  //  cout << s << endl;
  if ( length < 2 ) { return true; }
  else {
    return ( *s == *(s+length-1) && palindrome( s+1, length-2 ) );
  }
}

// Task Five
int towers( int n, char start, char helper, char target ) {
  if ( n == 0 ) return 0;
  int moveOff = towers(n-1, start, target, helper);
  //  cout << "Moving disk " << n << " from spindle " << start << " to " << target << endl;
  int moveOn = towers(n-1, helper, start, target);
  return moveOff + 1 + moveOn;
}

// Task Six
void mystery( int n ) {
  if (n > 1) {
    cout << 'a';
    mystery(n/2);
    cout << 'b';
    mystery(n/2);
  }
  cout << 'c';
}


// ========================= //

int main() {
  // Task ONE
  cout << "Task One" << endl;
  for ( int i = 0; i < 10; ++i ) {
    cout << "Even Num Binary Ones?: " << i << ": \t"
	 << boolalpha << evenBinaryOnes( i ) << endl;
  }
  cout << endl;

  // Task TWO
  cout << "Task Two" << endl;
  Node* first = nullptr;
  Node* second = nullptr;
  for ( int i = 0; i < 5; ++i ) {
    listAddTail( first, i );
    listAddTail( second, i*2 );
  }
  
  cout << "First:   \t";
  listDisplay( first );
  cout << "Second: \t";
  listDisplay( second );
  cout << "sumList: \t";
  listDisplay( sumList( first, second ) );
  cout << endl;
  
  // Task THREE
  cout << "Task Three" << endl;
  TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
  cout << "Max of Given Tree: " << treeMax(&f) << endl;
  cout << endl;

  // Task FOUR
  cout << "Task Four" << endl;
  char s[] = "racecar";
  cout << "Palindrome " << s << "? \t" << boolalpha << palindrome( s, 7 ) << endl;
  char t[] = "noon";
  cout << "Palindrome " << t << "? \t" << boolalpha << palindrome( t, 4 ) << endl;
  char u[] = "racer";
  cout << "Palindrome " << u << "? \t" << boolalpha << palindrome( u, 5 ) << endl;
  cout << endl;

  // Task FIVE
  cout << "Task Five" << endl;
  for ( int i = 1; i <= 10; ++i ) {
    cout << "towers(" << i <<  ", 'a', 'b', 'c'):\t" << towers( i, 'a', 'b', 'c') << endl;
  }
  cout << endl;

  // Task SIX
  cout << "Task Six" << endl;
  for ( int i = 1; i <= 10; ++i ) {
    cout << "mystery(" << i << "):\t";
    mystery( i );
    cout << endl;
  }
  cout << endl;

}

  
  
