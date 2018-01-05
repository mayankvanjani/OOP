/*
  Rec11: Linked Lists
  Mayank Vanjani
  11/17/17
  CS2114
  NYU Tandon School of Engineering
*/

#include <string>
#include <iostream>
using namespace std;

struct Node {
    Node(int data=0, Node* next=nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void listInsertHead(Node*& headPtr, int data) {
    headPtr = new Node(data, headPtr);
}

void display( Node* hp ) {
  if ( !hp ) { cout << "Empty"; }
  Node* p = hp;
  while ( p ) {
    cout << p->data << "  ";
    p = p->next;
  }
  cout << endl;
}

//Part One Splice
void spliceInto( Node* insertAfter, Node* splice ) {
  if ( !insertAfter->next ) { insertAfter->next = splice; }
  else if ( splice ) {
    Node* rightAfter = insertAfter->next;
    while ( splice->next ) {
      insertAfter->next = splice;
      insertAfter = insertAfter->next;
      splice = splice->next;
    }
    splice->next = rightAfter;
  }
  
}

//Part Two Sublist
Node* sublist( Node* hp, Node* check ) {
  Node* answer = hp;
  Node* answerMover = answer;
  Node* checkMover = check;
  
  while ( answerMover && checkMover ) {

    if ( answerMover->data == checkMover->data ) {
      if (!checkMover->next) {
	return answer;
      }
      if (!answerMover->next) {
	cout << "Failed to Match" << endl;
	return nullptr;
      }
      answerMover = answerMover->next;
      checkMover = checkMover->next;
    }
    
    else {
      answer = answer->next;
      answerMover = answer;
      checkMover = check;
    }

  }

  cout << "Failed to Match" << endl;
  return nullptr;

}





int main() {
  cout << "Part One:" << endl << endl;
  Node* L1 = new Node(5);
  L1->next = new Node(7);
  L1->next->next = new Node(9);
  L1->next->next->next = new Node(1);
  cout << "L1: ";
  display(L1);

  Node* L2 = new Node(6);
  L2->next = new Node(3);
  L2->next->next = new Node(2);
  cout << "L2: ";
  display(L2);

  Node* target = L1->next;
  cout << "Target: ";
  display(target);

  cout << "Splicing L2 into target 7 in L1" << endl;
  spliceInto( target, L2 );
  cout << "L1: ";
  display(L1);
  cout << "L2: ";
  display(L2);
  cout << endl;
  /*
  Node* edge = new Node(0);
  Node* oneTarget = new Node(1);
  display( edge );
  display( oneTarget );
  spliceInto( edge, oneTarget );
  cout << "Splicing" << endl;
  display( edge );
  display( oneTarget );

  Node* noSplice = nullptr;  
  cout << "Splicing" << endl;
  spliceInto( edge, noSplice );
  cout << "Splicing" << endl;
  display( edge );
  display( noSplice );
  */
  cout << "==========" << endl << endl;


  
  cout << "Part 2:" << endl;
  Node* target2 = new Node(1);
  target2->next = new Node(2);
  target2->next->next = new Node(3);
  target2->next->next->next = new Node(2);
  target2->next->next->next->next = new Node(3);
  target2->next->next->next->next->next = new Node(2);
  target2->next->next->next->next->next->next = new Node(4);
  target2->next->next->next->next->next->next->next = new Node(5);
  target2->next->next->next->next->next->next->next->next = new Node(6);

  cout << endl << "Target: ";
  display( target2 );
  cout << endl;

  Node* match1 = new Node(1);

  Node* match2 = new Node(3);
  match2->next = new Node(9);

  Node* match3 = new Node(2);
  match3->next = new Node(3);

  Node* match4 = new Node(2);
  match4->next = new Node(4);
  match4->next->next = new Node(5);
  match4->next->next->next = new Node(6);

  Node* match5 = new Node(2);
  match5->next = new Node(3);
  match5->next->next = new Node(2);
  match5->next->next->next = new Node(4);

  Node* match6 = new Node(5);
  match6->next = new Node(6);
  match6->next->next = new Node(7);
  
  cout << "Attempt match: ";
  display(match1);
  display( sublist( target2, match1 ) );
  cout << endl;
  
  cout << "Attempt match: ";
  display(match2);
  display( sublist( target2, match2 ) );
  cout << endl;
  
  cout << "Attempt match: ";
  display(match3);
  display( sublist( target2, match3 ) );
  cout << endl;
  
  cout << "Attempt match: ";
  display(match4);
  display( sublist( target2, match4 ) );
  cout << endl;
  
  cout << "Attempt match: ";
  display(match5);
  display( sublist( target2, match5 ) );
  cout << endl;
    
  cout << "Attempt match: ";
  display(match6);
  display( sublist( target2, match6 ) );
  cout << endl;

  // nullptr match
  cout << "Attempt match: ";
  display( nullptr );
  display( sublist( target2, nullptr ) );
  cout << endl;

  // nullptr match and target
  cout << "Attempt match: ";
  display( nullptr );
  display( sublist( nullptr, nullptr ) );
  cout << endl;
}
