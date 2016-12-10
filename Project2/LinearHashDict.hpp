//LinearHashDict.hpp
#ifndef _LINEARHASHDICT_HPP
#define _LINEARHASHDICT_HPP

#include "PredDict.hpp"

// An implementation of a dictionary as a hash table with linear probing.
//
class LinearHashDict : public PredDict
  {
  public:
    LinearHashDict();
    ~LinearHashDict();
    bool find(PuzzleState *key, PuzzleState *&pred);
    void add(PuzzleState *key, PuzzleState *pred);

  private:
    struct bucket {
      PuzzleState *key; // NULL indicates empty bucket.
      // No need for tombstones, as we never delete.
      string keyID; // Avoid recomputation of key's getUniqId()
      PuzzleState *data;
    };

    // A pointer to the underlying hash table array, with elements
    // of type bucket.  We use an explicit pointer, instead of
    // declaring "bucket array[size]" so you can resize the table.
    // This is just like ArrayStack and ArrayQueue in your first project.
    bucket *table;
    int size; // current size of the hash table array
    const static int primes[]; // table of good primes for table size
    int size_index; // index of the current table size in the primes[] array
                    // Invariant:  size == primes[size_index]
    int number; // how many items are currently in hash table

    // The next two variables are just to collect statistics on the
    // number of probes required for each call to find().
    int *probes_stats; // probe_stats[i] should be how often i probes needed
    const static int MAX_STATS = 20; // How big to make the array.

    int hash(string keyID); // The hash function
    void rehash(); // Resizes to next bigger table and rehashes everything
    //bool find_helper(string keyID, PuzzleState *&pred, int position);
  };

#endif

