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

vector<bool> bloomFilter( long TotalSetSize,
                          int hashTableSize, 
                          int numElmsToBeAdded, 
                          vector<int> elmsToBeAdded,
                          int numLookups,
                          vector<int> elmsToLookUp){

  // Set up our filter and our hash functions.
  vector<bool> theFilter(hashTableSize, false);
  int numHashes = 30;
  vector<hash1> hashes(numHashes, hash1(hashTableSize));

  // for every value, we run that value through the hash, then change the filter at the corresponding value
  // this is done for all (numHashes) hash functions.
  for(int i=0; i < elmsToBeAdded.size(); i++){
    for(int j=0; j< hashes.size(); j++){
      theFilter.at(hashes.at(j).hash(elmsToBeAdded.at(i))) = true;
    }
  }
  
  //Now we look up each value in the filter.
  vector<bool> valueAtIndexIsInSet(numLookups, true);
  for(int i=0; i < elmsToLookUp.size(); i++){
    for(int j=0; j< hashes.size(); j++){
      valueAtIndexIsInSet.at(i) = valueAtIndexIsInSet.at(i) && (theFilter.at(hashes.at(j).hash(elmsToLookUp.at(i))));
    }
  }

  return valueAtIndexIsInSet;
}

void print(vector <int> const &a, int numEntries) {
  cout << "START" << endl;
  long max = 0;
  long min = numEntries;
  for(int i=0; i < a.size(); i++){
    std::cout << " (" << i << " : "<< a.at(i) << ")" << endl;
    if( a.at(i) > max){
      max = a.at(i);
    }
    if( a.at(i) <= min){
      min = a.at(i);
      // cout << "Min at "<< i << " : " << a.at(i) << endl;
    }
  }
  cout << "END" <<endl;
  cout << "The max was " << max << " and the min was " << min << "."<< endl;
}

int main() {
  int testLength = 97;
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
  print(testone, numTestEntries);
  print(testtwo, numTestEntries);

}