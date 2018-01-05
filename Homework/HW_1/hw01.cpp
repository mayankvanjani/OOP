/*
  Homework #1: Ceaser Cypher Decryption Program
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;



// Given an encrypted char c and an offset of steps
// Returns decrypted char
char decrypt_char(char c, int steps) {
  if (c <= 'z' && c >= 'a') { // If Lowercase
    if (c <= ('a'+ steps - 1)) { // First few characters need to wrap-around
      c += 26;
    }
    c -= steps; // Step modification
  }
  return c;
}

// Given encrypted string line and an offset of steps
// Modifies line by decrypting it character by character
void decrypt_line(string& line, int steps) {
  for (size_t index = 0; index < line.size(); ++index) { //loop char in line
    line[index] = decrypt_char(line[index], steps); // replace with decrypted char
  }
}


int main() {

  /*
    //Testing decrypt_char
  char c = decrypt_char('e', 5);
  cout << c << endl;
  
    //Testing decrypt_line
  string s = "abcde";
  cout << s << endl;
  decrypt_line(s, 5);
  cout << s << endl;
  */

  ifstream somefileStream("encrypted.txt");
  if (!somefileStream) {
    cerr << "failed to open\n";
    exit(1);
  }

  //Initial File Printing
  cout << "ENCRYPTED CODE" << endl;
  string line;
  while(getline(somefileStream, line)) {
    cout << line << endl;
  }
  cout << endl << endl;
  somefileStream.close();

  //Re-Open File and Decrypt
  somefileStream.open("encrypted.txt");

  int offset;
  somefileStream >> offset; // reads in first int (offset value)

  getline(somefileStream, line); // pass the rest of the first line

  cout << "DECRYPTED CODE" << endl;
  cout << "Offset = " << offset << endl;

  string answer = ""; //Used to print lines in reverse
  while(getline(somefileStream, line)) { //Loops lines and decrypts
    decrypt_line(line, offset);
    answer = line + "\n" + answer;
  }

  cout << answer << endl;
  somefileStream.close();

}




