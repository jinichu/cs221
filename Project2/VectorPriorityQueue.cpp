#ifndef _VECTORPRIORITYQUEUE_CPP
#define _VECTORPRIORITYQUEUE_CPP

//VectorPriorityQueue.cpp
#include "VectorPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// A naive implementation of a priority queue, using
// a vector and searching for the max for each remove operation.
//
// Priority is based on the each PuzzleState's getBadness() method.

VectorPriorityQueue::VectorPriorityQueue() {
  // empty, nothing to do
}

VectorPriorityQueue::~VectorPriorityQueue() {
  // no clean-up to do, since array is not dynamically allocated
}

void VectorPriorityQueue::add(PuzzleState *elem) {
  data temp;
  temp.state = elem;
  temp.badness = elem->getBadness();
  array.push_back(temp);
}

PuzzleState *VectorPriorityQueue::remove() {
  if (array.size() < 1)
    return (PuzzleState *)NULL;

  int min_index = 0;
  for (int i = 0; i < (int)array.size(); i++) {
    if (array[i].badness < array[min_index].badness)
      min_index = i;
  }

  PuzzleState *ret = array[min_index].state;
  // remove array[min_index].  Since array is unsorted, this is O(1)
  array[min_index] = array[array.size()-1];
  array.pop_back();
  return ret;
}


PuzzleState *VectorPriorityQueue::get_next() {
  if (array.size() < 1)
    return (PuzzleState *)NULL;

  int min_index = 0;
  for (int i = 0; i < (int)array.size(); i++) {
    if (array[i].badness < array[min_index].badness)
      min_index = i;
  }

  return array[min_index].state;
}

bool VectorPriorityQueue::is_empty() {
  return (array.size() == 0);
}

#endif 
