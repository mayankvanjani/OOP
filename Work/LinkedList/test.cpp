#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Node {
  Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
  int data;
  Node* next;
};
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



int main() {
  Node z(3);
  Node y(2, &z);
  Node x(1, &y);
  Node z2(6);
  Node y2(5, &z2);
  Node x2(4, &y2);

  Node* headPtr = &x;
  Node* hp = headPtr;
  Node* rhsPtr = &x2;
  listDisplay( headPtr );
  listDisplay( rhsPtr );

  listAddTail( headPtr, 10 );
  hp = listFindTail( headPtr );
  hp = hp->next;
  listAddTail( headPtr, 11 );
  hp = listFindTail( headPtr );
  listDisplay( hp );
  listDisplay( headPtr );
  listDisplay( rhsPtr );
}
