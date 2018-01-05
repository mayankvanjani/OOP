#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

int main() {
  string s = "bat";
  cout << s << endl;
  cout << s[0] << endl;
  s[0] = 'c';
  cout << s[0] << endl;
  cout << s << endl;
}
