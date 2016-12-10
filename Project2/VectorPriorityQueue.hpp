//VectorPriorityQueue.hpp
#ifndef _VECTORPRIORITYQUEUE_HPP
#define _VECTORPRIORITYQUEUE_HPP

#include <vector>
#include "BagOfPuzzleStates.hpp"

// A naive implementation of a priority queue, using an unsorted array
// (inside a C++ STL vector) and searching for the min for each
// remove operation
//
class VectorPriorityQueue : public BagOfPuzzleStates
  {
  public:
    VectorPriorityQueue();
    PuzzleState *remove();
    void add(PuzzleState *element);
    PuzzleState *get_next();
    bool is_empty();
    ~VectorPriorityQueue();

  private:
    struct data {
      PuzzleState *state;
      int badness; // Faster to compute badness once and save it.
    };
    vector<data> array;
  };

#endif

