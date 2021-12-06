# bloomfilter
A bloom filter in C++. Note that this implementation is meant for learning/instructive purposes only. 

## Background 
A bloom filter uses a series of hash functions to test membership in a set. It does this by running a collection of hash functions on an input and setting the resultant flag in the filter to true for each has function. Thus, it is not possible to get false negatives but it is possible to get false positives. The essential funtion of the filter is that it gives us a way of testing set membership without having to store the entire set. It has a number of useful applications, including but not limited to
* Google Chrome uses bloom filters to flag suspisious URLs
* Ethereum uses it for quick lookup of blockchain logs
* Many database engines use them for lookup of non-existent rows/columns

For more information on bloom filters, visit the [wikipedia page.](https://courses.cs.duke.edu/spring03/cps296.5/papers/ziv_lempel_1977_universal_algorithm.pdf)

## Usage

In a traditional Bloom Filter, one cannot remove elements from the filter without deleting the filter and starting over (since each element of the filter is a single bit, flipping that bit may affect other elements which hash to that value). A solution to this is to use a counting filter, in which each element is a counter rather than a single bit. This can be 

## Possible Extensions
Here are some directions that this could be taken but weren't due to time constraints
* The program could be modified to take in a dataset on the command line and produce a filter for it
* 
* 