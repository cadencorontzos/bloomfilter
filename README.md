# bloomfilter
A bloom filter in C++. Note that this implementation is meant for learning/instructive purposes only. 

## Background 
A bloom filter uses a series of hash functions to test membership in a set. It does this by running a collection of hash functions on an input and setting the resultant flag in the filter to true for each has function. Thus, it is not possible to get false negatives but it is possible to get false positives. The essential funtion of the filter is that it gives us a way of testing set membership without having to store the entire set. It has a number of useful applications, including but not limited to
* Google Chrome uses bloom filters to flag suspisious URLs
* Ethereum uses it for quick lookup of blockchain logs
* Many database engines use them for lookup of non-existent rows/columns

For more information on bloom filters, visit the [wikipedia page.](https://courses.cs.duke.edu/spring03/cps296.5/papers/ziv_lempel_1977_universal_algorithm.pdf)

## Usage

To complile the program, run
```
    make
```
This will make an executable called bloom. To execute the program, run
```
    ./bloom
```
To clear the directory of executables, you can run
```
    make clean
```
In a traditional Bloom Filter, one cannot remove elements from the filter without deleting the filter and starting over (since each element of the filter is a single bit, flipping that bit may affect other elements which hash to that value). A solution to this is to use a counting filter, in which each element is a counter rather than a single bit. This can be 


## Hash Function Exploration

I explored two options for the hash method used in the bloom filter. They both used the std random library, which in practice may not be the best move depending on the randomness desired in your hash. 
Hashes 1 and 2 work as follows
1. For each of the k hash functions, pick a seed si. Using a random number generator seeded with x, then
we have the hash function hi(x) = r(si + x). Meaning, the random number generator seeded at si + x.
2. For each of the k hash functions, pick two random numbers ai, bi such that ai is uniform in {1, 2, ..., n−1} and bi is uniform in {0, 1, ..., n − 1}. Then the hash function hi(x) = ai ∗ x + bimodn with n being prime.

To see which might work better for my purposes, I generated random values and hashed them. I varied the number of values added to the hash and the size of the hash, and I tracked the hits in each bucket using the `print()` function. I found that the spread (the diffrenece between the bucket with the most hits and the one with the least hits) was consistently smalller in hash2, leading me to think that it would serve better for the purpose of the hash filter. A better spread means less overlap, and less overlap leads to less false negatives. Here is an example test

```cpp
  int testLength = 2017;
  int numTestEntries = 10000000;
  vector<int> testone(testLength, 0);
  vector<int> testtwo(testLength, 0);

  hash1 one(testLength);
  hash2 two(testLength);

  srand(time(NULL));
  int temp = numTestEntries;
  while (temp > 0){
    int randomVal = rand();
    int indone = one.hash(randomVal);
    int indtwo = two.hash(randomVal);

    testone.at(indone) +=1;
    testtwo.at(indtwo) +=1;

    temp--;
  }
  print(testone, numTestEntries);
  print(testtwo, numTestEntries);

```

## Possible Extensions
Here are some directions that this could be taken but weren't due to time constraints
* The program could be modified to take in a dataset on the command line and produce a filter for it
* The counters in the counting bloom filter could be limited in size to save on space
* Study the hash functions more in depth and find if using the std random library could possible lead to problems in large datasets