/*
  Chemical Formulae Lab
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering
  9/15/17
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Formula {
  vector<string> names;
  int num_c = 0;
  int num_h = 0;
};

size_t findFormula(int next_c, int next_h, const vector<Formula>& formulas);
void printFormulas(const vector<Formula>& formulas);



int main() {
  vector<Formula> formulas;

  ifstream formulaStream("example.txt");
  if (!formulaStream) {
    cerr << "Failed to open example";
    exit(1);
  }

  string line;
  cout << endl << "GIVEN FILE" << endl;
  while(getline(formulaStream, line)) {
    cout << line << endl;
  }
  cout << endl;
  formulaStream.close();

  cout << "ORGANIZED FILE" << endl;
  formulaStream.open("example.txt");
  if (!formulaStream) {
    cerr << "Failed to open example";
    exit(1);
  }
  
  string next_name;
  char extra;
  int next_c;
  int next_h;
  
  while (formulaStream >> next_name) {
    formulaStream >> extra
		  >> next_c
		  >> extra
		  >> next_h;
    
    size_t where = findFormula(next_c, next_h, formulas);
    if (where == formulas.size() ) {
      Formula toAdd;
      toAdd.num_c = next_c;
      toAdd.num_h = next_h;
      toAdd.names.push_back(next_name);
      formulas.push_back(toAdd);
    }
    else {
      formulas[where].names.push_back(next_name);
    }
    
  }
  
  printFormulas(formulas);
  
}


//METHODS

// Given next formula's C and H, returns pos of existing formula or max size if not found
size_t findFormula(int next_c, int next_h, const vector<Formula>& formulas) {
  for (size_t index = 0; index < formulas.size(); ++index) {
    if (next_c == formulas[index].num_c && next_h == formulas[index].num_h) {
      return index;
    }
  }
  return formulas.size();
}


// Given the formulas collection, prints the "sorted" formlulas
void printFormulas(const vector<Formula>& formulas) {
  int min_c = formulas[0].num_c;
  int max_c = formulas[0].num_c;
  for (const Formula& item : formulas) { // Find min/max Carbons
    if (item.num_c < min_c) {
      min_c = item.num_c;
    }
    if (item.num_c > max_c) {
      max_c = item.num_c;
    }
  }

  
  for (int c_range = min_c; c_range <= max_c; ++c_range) { // Loop from min-max Carbons and print formula
    for (const Formula& item : formulas) {
      if (item.num_c == c_range) {
	cout << "C" << item.num_c << "H" << item.num_h << "\t";
	for (const string& naming : item.names) {
	  cout << " " << naming;
	}
	cout << endl;
      }
    }
  }
  cout << endl;
}
