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

// Given an encrypted char c, returns decrypted char using offset steps
char decrypt_char(char c, int steps) {
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  char decrypted = c;
  if (c <= alphabet.back() && c >= alphabet[0]) { // In-Bounds
    for (size_t index = 0; index < alphabet.size(); ++index) { // 
      if (alphabet[index] == c) {
	if (index < 5) {
	  index += 26;
	}
	decrypted = alphabet[ (index - steps) % alphabet.size() ];
      }
    }
  }
  return decrypted;
}

// Given encrypted string line, modifies line by decrypting it with offset steps
void decrypt_line(string& line, int steps) {
  for (size_t index = 0; index < line.size(); ++index) {
    line[index] = decrypt_char(line[index], steps);
  }
}


int main() {
  /*

    //Testing decrypt_char
  char c = decrypt_char('y', 3);
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

  string offset;
  string line;
  
  while(getline(somefileStream, line)) {
    cout << line << endl;
  }
  cout << endl << endl;
  somefileStream.close();
  somefileStream.open("encrypted.txt");
  
  getline(somefileStream, offset);
  cout << "DECRYPTED CODE" << endl;
  cout << "Offset = " << offset << endl;

  string answer = "";
  while(getline(somefileStream, line)) {
    //cout << line << endl;
    decrypt_line(line, stoi(offset));
    answer = line + "\n" + answer;
  }

  cout << answer << endl;
  somefileStream.close();
  
}
