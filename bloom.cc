// Caden Corontzos, Nov 2021. See License for terms of use
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

// two different hashing strats.
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

// produces a list of booleans corresponding to whether or not the element in to lookup list is in the set
vector<bool> bloomFilter( long totalSetSize,
                          int hashTableSize, 
                          int numElmsToBeAdded, 
                          vector<long> elmsToBeAdded,
                          int numLookups,
                          vector<long> elmsToLookUp){

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

// prints a report of a hash. used for hash testing
void print(vector <int> const &a, int numEntries) {
  cout << "START" << endl;
  long max = 0;
  long min = numEntries;
  for(int i=0; i < a.size(); i++){

    // output the entry
    cout << " (" << i << " : "<< a.at(i) << ")" << endl;

    // report min and max
    if( a.at(i) > max){
      max = a.at(i);
    }
    if( a.at(i) <= min){
      min = a.at(i);
    }

  }
  cout << "END" <<endl;
  // output a report on the data
  cout << "The max was " << max << " and the min was " << min << "."<< endl;
  cout << "The range was " << max-min << endl;
}

void generateBloomExample(bool counting, long totalSetSize, int hashTableSize, int numElmsToBeAdded){

  vector<long> toAdd(numElmsToBeAdded, 0);
  vector<long> toCheck(numElmsToBeAdded*2, 0);
  int temp = 0;
  srand(time(NULL));
  while(temp <numElmsToBeAdded){
    int rando = rand() % totalSetSize;
    toAdd.at(temp) = rando;
    toCheck.at(temp) = rando;
    temp++;
  }
  
  while(temp < numElmsToBeAdded*2){
    // find something not in set
    int notInSet = toCheck.at(temp-numElmsToBeAdded);
    while(std::find(toCheck.begin(), toCheck.end(), notInSet) != toCheck.end()){
      notInSet++;
    }

    toCheck.at(temp)=notInSet;
    temp++;
  }
  
 
  vector<bool> filter = bloomFilter(totalSetSize, hashTableSize, numElmsToBeAdded, toAdd, 2*numElmsToBeAdded, toCheck);


  

  for(int i=0 ;i < numElmsToBeAdded; i++){

    if(!filter.at(i)){
      cout << "False Negagive" << endl;
    }
  }
  
  int falsePositives = 0;
  for(int i=numElmsToBeAdded; i < filter.size(); i++){
    
    if(filter.at(i)){
      falsePositives++;
    }
  }

  float rate = falsePositives/static_cast<float>(numElmsToBeAdded*2) * 100;
  cout << "The false positive rate was %" << rate << ".";
 

}

int main() {
  long totalSetSize = 1000000000;
  int hashTableSize = 1000;
  int numElmsToBeAdded = 100;

  // generateBloomExample(false, totalSetSize,hashTableSize, numElmsToBeAdded);
 
  // int testLength = 2017;
  // int numTestEntries = 10000000;
  // vector<int> testone(testLength, 0);
  // vector<int> testtwo(testLength, 0);

  // hash1 one(testLength);
  // hash2 two(testLength);

  // srand(time(NULL));
  // int temp = numTestEntries;
  // while (temp > 0){
  //   int randomVal = rand();
  //   int indone = one.hash(randomVal);
  //   int indtwo = two.hash(randomVal);

  //   testone.at(indone) +=1;
  //   testtwo.at(indtwo) +=1;

  //   temp--;
  // }
  // print(testone, numTestEntries);
  // print(testtwo, numTestEntries);

  return 0;
}