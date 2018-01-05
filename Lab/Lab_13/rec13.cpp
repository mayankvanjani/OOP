/*
  Rec13: STL
  Mayank Vanjani
  12/1/17
  CS2114
  NYU Tandon School of Engineering
*/

#include <iostream>w
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <set>         // task 20
#include <map>         // task 22
using namespace std;

void printList( const list<int>& ls ) {
  for ( list<int>::const_iterator iter = ls.begin(); iter != ls.end(); ++iter) {
    cout << *iter << "  ";
  }
  cout << endl;
}

void printRangedList( const list<int>& ls ) {
  for ( int x : ls ) {
    cout << x << "  ";
  }
  cout << endl;
}

void printListAuto( const list<int>& ls ) {
  for ( auto iter = ls.begin(); iter != ls.end(); ++iter ) {
    cout << *iter << "  ";
  }
  cout << endl;
}


list<int>::const_iterator my_find_long( const list<int>& ls, int check ) {
  for( list<int>::const_iterator iter = ls.begin(); iter != ls.end(); ++iter ) {
    if ( *iter == check ) {
      cout << "FOUND: ";
      return iter;
    }
  }
  cout << "NOT FOUND: ";
  return ls.end();
}

auto my_find( const list<int>& ls, int check ) {
  for( auto iter = ls.begin(); iter != ls.end(); ++iter ) {
    if ( *iter == check ) {
      cout << "FOUND: ";
      return iter;
    }
  }
  cout << "NOT FOUND: ";
  return ls.end();
}

bool isEven( int n ) { return n % 2 == 0; }

class Even {
public:
  bool operator() (int n) { return (n & 1) == 0; }
};

/*
auto ourFind( const list<int>& ls, int check ) {
  cout << "ourFind: Looking for " << check << " in ";
  printListAuto( ls );
  
  for( auto iter = ls.begin(); iter != ls.end(); ++iter ) {
    if ( *iter == check ) {
      cout << "FOUND: ";
      return iter;
    }
  }
  cout << "NOT FOUND: ";
  return ls.end();
}


template <typename T>
auto ourFind( const list<T>& ls, T check ) {
  cout << "ourFind Template: Looking for " << check << " in ";
  printListAuto( ls );
  
  for( auto iter = ls.begin(); iter != ls.end(); ++iter ) {
    if ( *iter == check ) {
      cout << "FOUND: ";
      return iter;
    }
  }
  cout << "NOT FOUND: ";
  return ls.end();
}


template <typename T>
bool ourFind( const vector<T>& ls, T check ) {
  for ( size_t i = 0; i < ls.size(); ++i ) {
    if ( ls[i] == check) { return true; }
  }
  return false;
}
*/

template <typename T, typename U>
T ourFind( T start, T stop, U check ) {
  cout << "ourFind Template: Looking for " << check << " in ";
  //  printListAuto( ls );
  
  for( T iter = start; iter != stop; ++iter ) {
    if ( *iter == check ) {
      //      cout << "FOUND: ";
      return iter;
    }
  }
  //  cout << "NOT FOUND: ";
  return stop;
}

bool checkFind( vector<string> book, string word ) {
  for ( size_t i = 0; i < book.size(); ++i ) {
    if ( book[i] == word ) { return true; }
  }
  return false;
}


int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vec = {5,4,3,2,1};
    for ( int x : vec ) { cout << x << "  "; }
    cout << endl;    
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> lc( vec.begin(), vec.end() );
    for ( int x : lc ) { cout << x << "  "; }
    cout << endl;    
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort( vec.begin(), vec.end() );
    for ( int x : vec ) { cout << x << "  "; }
    cout << endl;
    for ( int x : lc ) { cout << x << "  "; }
    cout << endl;    
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for( size_t i = 0; i < vec.size(); ++i ) {
      if ( i % 2 == 0 ) {
	cout << vec[i] << "  ";
      }
    }
    cout << endl;    
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    /*
    for( size_t i = 0; i < lc.size(); ++i ) {
      if ( i % 2 == 0 ) {
	cout << lc[i] << "  ";
      }
    }
    cout << endl;    
    */
    cout << "No [] for list because inefficient" << endl;
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    //    for ( int x : vec ) { cout << x << "  "; }
    for ( vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter ) {
      if ( iter == vec.end() ) { break; }
      if ( iter != vec.begin() && ++iter == vec.end() ) {
	break;
      }
      else {
	cout << *iter << "  ";
      }
    }
    cout << endl;
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    //    for ( int x : lc ) { cout << x << "  "; }
    for ( list<int>::iterator iter = lc.begin(); iter != lc.end(); ++iter ) {
      if ( iter == lc.end() ) { break; }
      if ( iter != lc.begin() && ++iter == lc.end() ) {
	break;
      }
      else {
	cout << *iter << "  ";
      }
    }
    cout << endl;
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    cout << "Before: ";
    for ( int x : lc ) { cout << x << "  "; }
    cout << endl;
    lc.sort();
    cout << "After: ";
    for ( int x : lc ) { cout << x << "  "; }
    cout << endl;
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    cout << "Using Normal printList: ";
    printList( lc );
    cout << endl;
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    cout << "Using Ranged for printRangedList: ";
    printRangedList( lc );
    cout << endl;
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    cout << "Using auto printListAuto: ";
    printListAuto( lc );
    cout << endl;
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << "In ";
    printListAuto( lc );
    cout << "looking for 3\t\t";
    cout << *( my_find_long( lc, 3) ) << endl;
    cout << endl;
    
    cout << "In ";
    printListAuto( lc );
    cout << "looking for 10\t\t";
    cout << *( my_find_long( lc, 10) ) << endl;
    cout << endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << "In ";
    printListAuto( lc );
    cout << "looking for 3\t\t";
    cout << *( my_find( lc, 3) ) << endl;
    cout << endl;
    
    cout << "In ";
    printListAuto( lc );
    cout << "looking for 10\t\t";
    cout << *( my_find( lc, 10) ) << endl;
    cout << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << "In ";
    printListAuto( lc );
    cout << "looking for 3\t\t";
    cout << *( find( lc.begin(), lc.end(), 3 ) ) << endl;
    cout << endl;
    
    cout << "In ";
    printListAuto( lc );
    cout << "looking for 10\t\t";
    cout << *( find( lc.begin(), lc.end(), 10 ) ) << endl;
    cout << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    cout << "find_if: ";
    cout << *( find_if( vec.begin(), vec.end(), isEven) ) << endl;
    cout << endl;
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    cout << "functor: ";
    cout << *( find_if( vec.begin(), vec.end(), Even() ) ) << endl;
    cout << endl;
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    cout << "lambda: ";
    cout << *( find_if( vec.begin(), vec.end(), [] (int n) { return n % 2 == 0; } ) ) << endl;
    cout << endl;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int arr[5];
    copy( vec.begin(), vec.end(), arr );
    for ( int i : arr ) { cout << i << "  "; }
    cout << endl;
    cout << "Finding 3: ";
    cout << *( find( arr, arr+5, 3 ) ) << endl;
    /*
    cout << "Finding 10: ";
    cout << *( find( arr, arr+5, 10 ) ) << endl;
    */
    cout << endl;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    auto val = ourFind( lc.begin(), lc.end(), 3 );
    cout << *val << endl;
    cout << endl;
    
    val = ourFind( lc.begin(), lc.end(), 10 );
    cout << *val << endl;
    cout << endl;
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    val = ourFind( lc.begin(), lc.end(), 3 );
    cout << *val << endl;
    cout << endl;
    
    val = ourFind( lc.begin(), lc.end(), 10 );
    cout << *val << endl;
    cout << endl;
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing 
    cout << "Task 21:\n";
    vector<string> book;
    string word;

    ifstream somefileStream("pooh-nopunc.txt");
    if (!somefileStream) {
      cerr << "failed to open\n";
      exit(1);
    }

    while( somefileStream >> word ) {
      //      cout << *( find_if( vec.begin(), vec.end(), isEven) ) << endl;
      //     if ( *ourFind( book.begin(), book.end(), word ) != word ) { book.push_back( word ); }
      if ( !checkFind( book, word ) ) { book.push_back( word ); }
    }

    somefileStream.close();
    
    cout << "Words: " << book.size() << endl;
    //    for ( string s : book ) { cout << s << " "; }
    cout << endl;
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> novel;
    string elem;

    somefileStream = ifstream("pooh-nopunc.txt");
    if (!somefileStream) {
      cerr << "failed to open\n";
      exit(1);
    }

    while( somefileStream >> elem ) {
      novel.insert( elem );
    }

    somefileStream.close();
    
    cout << "Words: " << novel.size() << endl;
    for ( string s : novel ) { cout << s << " "; }
    cout << endl;
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    string thing;
    
    somefileStream = ifstream("pooh-nopunc.txt");
    if (!somefileStream) {
      cerr << "failed to open\n";
      exit(1);
    }

    int pos = 0;
    while( somefileStream >> thing ) {
      wordMap[thing].push_back( pos );
      ++pos;
    }

    somefileStream.close();
    
    cout << "Words: " << wordMap.size() << endl;

    /*
    for( const auto& pair : wordMap ) {
      cout << pair.first << " POS: ";
      for ( int place: pair.second ) {
	cout << place << ' ';
      }
      cout << endl;
    }
    */			      
    cout << "=======\n";

}
