#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

class hash1 {    
  public:         
    int seed;
    hash1() { 
      srand(time(NULL));
      seed = rand();
    };
    int hash(int x){
      srand(x+seed);
      return rand();
    }
};


class hash2 {       
  public:          
    int a;
    int b;
    int modulus;
    hash2(int n){ 
      srand(time(NULL));
      a = rand() % n;
      b = rand() % n;
      modulus = n;
    };
    int hash(int x){
      return (a*x +b) % modulus;
    }
};



int main() {




}