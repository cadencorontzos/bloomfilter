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
vector<bool> bloomFilter( bool counting,
                          long totalSetSize,
                          int hashTableSize, 
                          int numElmsToBeAdded, 
                          vector<long> elmsToBeAdded,
                          int numLookups,
                          vector<long> elmsToLookUp,
                          int numHashes){

  // Set up our filter and our hash functions.
  vector<bool> theFilter(hashTableSize, false);
  vector<int> theCountingFilter(hashTableSize, 0);
  vector<hash1> hashes;
  srand(time(NULL));
  for(int i=0; i < numHashes; i++){
    hashes.push_back(hash1(hashTableSize));
  }


  // for every value, we run that value through the hash, then change the filter at the corresponding value
  // this is done for all (numHashes) hash functions.
  for(int i=0; i < elmsToBeAdded.size(); i++){
    for(int j=0; j< hashes.size(); j++){
      if(counting){
        theCountingFilter.at(hashes.at(j).hash(elmsToBeAdded.at(i)))+=1;
      }else{
        theFilter.at(hashes.at(j).hash(elmsToBeAdded.at(i))) = true;
      }
    }
  }

  
  //Now we look up each value in the filter.
  vector<bool> valueAtIndexIsInSet(numLookups, true);
  for(int i=0; i < elmsToLookUp.size(); i++){
    for(int j=0; j< hashes.size(); j++){
      if(!counting){
        valueAtIndexIsInSet.at(i) = (valueAtIndexIsInSet.at(i)>=1) && ((theFilter.at(hashes.at(j).hash(elmsToLookUp.at(i))))>=1);
      }
      else{
         valueAtIndexIsInSet.at(i) = (valueAtIndexIsInSet.at(i)>=1) && ((theCountingFilter.at(hashes.at(j).hash(elmsToLookUp.at(i))))>=1);
      }
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

// creates filter, adds elements, checks elements, and outputs false positive rate.
void generateBloomExample(bool counting, long totalSetSize, int hashTableSize, int numElmsToBeAdded, int numHashes){
  string border = "---------------------------------------------------------------------------------------";
  cout << border << endl;
  vector<long> toAdd(numElmsToBeAdded, 0);
  vector<long> toCheck(numElmsToBeAdded*2, 0);
  int temp = 0;
  srand(time(NULL));

  // chose some random elements to be added to the filter
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

  // output a report on the filter
  if(counting){
    cout << "A counting bloom filter was generated with the following properties" << endl;
  }else{
    cout << "A bloom filter was generated with the following properties" << endl ;
  }
  cout << "Range of Elements : Integers from 0 to " << totalSetSize << endl;
  cout << "Hash Table Size   : Integers from 0 to " << hashTableSize << endl;
  cout << "Elements Added    : There were " << numElmsToBeAdded << " elements added to the filter from the chosen range" << endl;
  
  vector<bool> filter = bloomFilter(counting, totalSetSize, hashTableSize, numElmsToBeAdded, toAdd, 2*numElmsToBeAdded, toCheck, numHashes);
  
  for(int i=0 ;i < numElmsToBeAdded; i++){

    // this should not be possible. If it happens, the filter is not working correctly
    if(filter.at(i) == 0){
      cout << "False Negative" << endl;
    }
  }
  
  // Check for false positives and output rate
  int falsePositives = 0;
  for(int i=numElmsToBeAdded; i < filter.size(); i++){
    
    if(filter.at(i)>=1){
      falsePositives++;
    }
  }
  float rate = falsePositives/static_cast<float>(numElmsToBeAdded*2) * 100;
  cout << "False positive rt : %" << rate << endl;
  cout << border << endl;
}

int main() {

  // an example input. Modifying these variables will change the false output rate
  long totalSetSize = 1000000000;
  int hashTableSize = 1000;
  int numElmsToBeAdded = 100;
  int numHashes = 30;
  generateBloomExample(false, totalSetSize, hashTableSize, numElmsToBeAdded, numHashes);
  return 0;
}