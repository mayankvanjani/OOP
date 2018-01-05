/*
  Conway's Game of Life Lab
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void print_board(const vector<string>& board) {
  for (size_t index = 0; index < board.size(); index++){
    cout << board[index] << endl;
  }
}

vector<string> make_board(const string& filename) {
  ifstream somefileStream(filename);
  if (!somefileStream) {
    cerr << "failed to open\n";
    exit(1);
  }
  
  vector<string> board;
  string bord = "";
  string line;
  bool test = true;

  while(getline(somefileStream, line)) {
    if (test) {
      for (size_t index = 0; index < line.size()+2; ++index) {
	bord += '_';
      }
      board.push_back(bord);
    }
    test = false;
    for (size_t index = 0; index < line.size(); ++index) {
      if (line[index] == '-') {
	line[index] = ' ';
      }
    }
    board.push_back('|' + line + '|');
  }
  board.push_back(bord);
  //print_board(board);
  return board;
}



int main() {
  string filename = "life.txt";
  vector<string> successor;
  vector<string> board = make_board(filename);
  
  cout << endl << "INITIAL WORLD" << endl;
  print_board(board);
  cout << endl;

  //int gen = 0;
  //while (gen < 10) {
  
  for (int gen = 0; gen < 10; gen++) {
    
    successor = board;
    
    for (size_t row = 1; row < board.size() - 1; row++) {
      for (size_t col = 1; col < board[row].size() - 1; col++) {
	
	int neighbors = 0;
	
	if (board[row][col-1] == '*') 
	  neighbors++;
	if (board[row][col+1] == '*') 
	  neighbors++;
	if (board[row-1][col-1] == '*') 
	  neighbors++;
	if (board[row-1][col] == '*') 
	  neighbors++;
	if (board[row-1][col+1] == '*') 
	  neighbors++;
	if (board[row+1][col-1] == '*') 
	  neighbors++;
	if (board[row+1][col] == '*') 
	  neighbors++;       
	if (board[row+1][col+1] == '*') 
	  neighbors++;

	if (board[row][col] == '*') {
	  if (neighbors < 2 || neighbors > 3) 
	    successor[row][col] = ' ';
	}
	  
	else {
	  if (neighbors == 3) 
	    successor[row][col] = '*';	    
	}
	
      }
    } // closes both FOR loops

    cout << "GENERATION: " << gen+1 << endl;
    print_board(successor);
    cout << endl;
    
    board = successor;
      
  }
}

