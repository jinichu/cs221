#ifndef _DOUBLEHASHDICT_CPP
#define _DOUBLEHASHDICT_CPP

//DoubleHashDict.cpp
#include "DoubleHashDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of a dictionary ADT as hash table with double hashing
//

const int DoubleHashDict::primes[] = {53, 97, 193, 389, 769, 1543, 3079,
      6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869,
      3145739, 6291469, 12582917, 25165843, 50331653, 100663319,
      201326611, 402653189, 805306457, 1610612741, -1};
// List of good primes for hash table sizes from
// http://planetmath.org/goodhashtableprimes
// The -1 at the end is to guarantee an immediate crash if we run off
// the end of the array.

DoubleHashDict::DoubleHashDict() {
  size_index = 0;
  size = primes[size_index];
  table = new bucket[size](); // Parentheses force initialization to 0
  number = 0;

  // Initialize the array of counters for probe statistics
  probes_stats = new int[MAX_STATS]();
}

DoubleHashDict::~DoubleHashDict() {
  // Delete all table entries...
  for (int i=0; i<size; i++) {
    if (table[i].key!=NULL) {
      delete table[i].key;
      // Don't delete data here, to avoid double deletions.
    }
  }
  // Delete the table itself
  delete [] table;

  // It's not good style to put this into a destructor,
  // but it's convenient for this assignment...
  cout << "Probe Statistics for find():\n";
  for (int i=0; i<MAX_STATS; i++)
    cout << i << ": " << probes_stats[i] << endl;
  delete [] probes_stats;
}

int DoubleHashDict::hash1(string keyID) {
  int h=0;
  for (int i=keyID.length()-1; i>=0; i--) {
    h = (keyID[i] + 31*h) % size;
  }
// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "Hash 1:  " << keyID << " to " << h << std::endl;
#endif
// End of "DO NOT CHANGE" Block
  return h;
}

int DoubleHashDict::hash2(string keyID) {
  int h=0;
  for (int i=keyID.length()-1; i>=0; i--) {
    h = (keyID[i] + 63*h) % size;
  }
  // Make sure second hash is never 0 or size
  h = h/2 + 1;

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "Hash 2:  " << keyID << " to " << h << std::endl;
#endif
// End of "DO NOT CHANGE" Block
  return h;
}

void DoubleHashDict::rehash() {
// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// And leave this at the beginning of the rehash() function.
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "*** REHASHING " << size;
#endif
// End of "DO NOT CHANGE" Block

  std::cout << "Rehashing number = " << number << ", size = " << size << std::endl;


int old_size = size;
size_index++;
size = primes[size_index];
bucket *old_table = table;
table = new bucket[size]();
number = 0;

for(int k = 0; k < old_size; k++){
  if (old_table[k].key != NULL){
    add(old_table[k].key, old_table[k].data);
  }
}
delete[] old_table;


  // TODO:  Your code goes here...
std::cout << "Rehashing number = " << number << ", size = " << size << std::endl;

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// And leave this at the end of the rehash() function.
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << " to " << size << " ***\n";
#endif
// End of "DO NOT CHANGE" Block
}


bool DoubleHashDict::find(PuzzleState *key, PuzzleState *&pred) {
  // Returns true iff the key is found.
  // Returns the associated value in pred

  // Be sure not to keep calling getUniqId() over and over again!

  // TODO:  Your code goes here...
  //return find_helper(key->getUniqId(), pred, 0);
  string keyID = key->getUniqId();
  int hashKey = hash1(keyID);
  int hashKey2 = 0, probes = 0, position = 0;
  int target;

  while(position < size) {
    hashKey2 = hash2(keyID);
    target = (hashKey + position * hashKey2) % size;

    if(table[target].keyID == keyID) {
      if(probes < MAX_STATS) {
        probes_stats[probes]++;
        pred = table[target].data;
        }
        return true;
      } else {
        position++;
      }
      if(table[target].key == NULL) {
        if(probes < MAX_STATS) {
          probes_stats[probes]++;
        }
        return false;
      }
      probes++;
    }
    return false;
  }

  

// You may assume that no duplicate PuzzleState is ever added.
void DoubleHashDict::add(PuzzleState *key, PuzzleState *pred) {

  float lambda = (float) (number + 1)/ (float) size;
  if (lambda > 0.5)
    rehash();

  string keyID = key->getUniqId();
  int hashKey = hash1(keyID);
  int hashKey2 = 0, position = 0;
  int target;

  while(position < size) {
    hashKey2 = hash2(keyID);
    target = (hashKey + position * hashKey2) % size;

    if(table[target].key == NULL) {
        table[target].key = key;
        table[target].data = pred;
        table[target].keyID = keyID;
        number++;
        position++;
        return;
      } else {
        position++;
      }
    }
  }



#endif 

