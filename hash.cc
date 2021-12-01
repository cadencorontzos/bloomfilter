// Caden Corontzos, Nov 2021. See License for terms of use
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

class hash1 {    
  public:         
    long seed;
    int modulus;
    hash1(int n) { 
      srand(time(NULL));
      seed = rand();
      modulus = n;
    };
    int hash(long x){
      srand(x+seed);
      return rand() % modulus;
    }
};


class hash2 {       
  public:          
    long a;
    long b;
    int modulus;
    hash2(long n){ 
      srand(time(NULL));
      a = rand() % n;
      b = rand() % n;
      modulus = n;
    };
    int hash(long x){
      return (a*x +b) % modulus;
    }
};

void bloomFilter(long TotalSetSize,
                 int hashTableSize, 
                 int numElmsToBeAdded, 
                 vector<int> elmsToBeAdded,
                 int numLookups,
                 vector<int> elmsToLookUp){
    
    cout << "pass" ;

}

void print(std::vector <int> const &a, int numEntries) {
  std::cout << "START" << endl;
  long max = 0;
  long min = 0;
  for(int i=1; i < a.size(); i++){
    // std::cout << " (" << i << " : "<< a.at(i) << ")" << endl;
    if( a.at(i) > max){
      max = a.at(i);
    }
    if( a.at(i) <= min){
      min = a.at(i);
      cout << "Min at "<< i << " : " << a.at(i) << endl;
    }
  }
  cout << "END" <<endl;
  cout << "The max was " << max << " and the min was " << min << "."<< endl;
}

int main() {
  int testLength = 2963;
  int numTestEntries = 10000000;
  vector<int> testone(testLength, 0);
  vector<int> testtwo(testLength, 0);

  hash1 one(testLength);
  hash2 two(testLength);

  srand(time(NULL));
  while (numTestEntries > 0){
    int randomVal = rand();
    int indone = one.hash(randomVal);
    int indtwo = two.hash(randomVal);

    testone.at(indone) +=1;
    testtwo.at(indtwo) +=1;

    numTestEntries--;
  }
  print(testone, testLength);
  print(testtwo, testLength);

}