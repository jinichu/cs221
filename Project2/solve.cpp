/*
  solve.cpp: contains 'main' function.

*/

#include <iostream>

#include <cstring>
#include <cstdlib>
#include <unistd.h>

// 221 STUDENTS: You'll need to include any .hpp files of classes that
// you create and use here
#include "PuzzleState.hpp"
//#include "WolfGoatCabbage.hpp"
#include "SliderPuzzle.hpp"
//#include "Sudoku.hpp"
//#include "MazeRunner.hpp"

//#include "ArrayStack.hpp"
//#include "LinkedListStack.hpp"
#include "VectorPriorityQueue.hpp"
//#include "LinkedListQueue.hpp"
//#include "ArrayQueue.hpp"
//#include "HeapPriorityQueue.hpp"

#include "LinkedListDict.hpp"
#include "AVLDict.hpp"
#include "LinearHashDict.hpp"
#include "DoubleHashDict.hpp"

using namespace std;


// This function does the actual solving.
void solvePuzzle(PuzzleState *start, BagOfPuzzleStates &active, PredDict &seen, vector<PuzzleState*> &solution) {

  PuzzleState *state;
  PuzzleState *temp;

  active.add(start); // Must explore the successors of the start state.
  seen.add(start,NULL); // We've seen this state.  It has no predecessor.

  while (!active.is_empty()) {
    // Loop Invariants:
    // 'seen' contains the set of puzzle states that we know how to reach.
    // 'active' contains the set of puzzle states that we know how to reach,
    //    and whose successors we might not have explored yet.

    state = active.remove();
    // Note:  Do not delete this, as this PuzzleState is also in 'seen'

    // The following two lines are handy for debugging, or seeing what
    // the algorithm is doing.
    // 221 STUDENTS:  Comment these out when you want the program to
    // run at full speed!
    //cout << "Exploring State: \n";
    //state->print(cout);
    //usleep(1000000);	// Pause for some microseconds, to let human read output

    if (state->isSolution()) {
      // Found a solution!
      cout << "Found solution! \n";
      state->print(cout);

      // Follow predecessors to construct path to solution.
      temp = state;
      while (temp!=NULL) {
	solution.push_back(temp);
	// Guaranteed to succeed, because these states must have been
	// added to dictionary already.
        seen.find(temp,temp);
      }
      return;
    }

    vector<PuzzleState*> nextMoves = state->getSuccessors();
    for (unsigned int i=0; i < nextMoves.size(); i++) {
      if (!seen.find(nextMoves[i], temp)) {
        // Never seen this state before.  Add it to 'seen' and 'active'
        active.add(nextMoves[i]);
        seen.add(nextMoves[i], state);
      } else {
	delete nextMoves[i];
      }
    }
  }

  // Ran out of states to explore.  No solution!
  solution.clear();
  return;
}

int main ()
{
  PuzzleState *startState;

  // 221 STUDENTS: Initialize startState with an object of the type
  // of puzzle you want solved.
  // For some kinds of puzzles, you will want to pass in a parameter
  // to specify the starting position (e.g., for the 8- or 15-puzzles.)

  // This is for the WolfGoatCabbage problem.
  //startState = new WolfGoatCabbage();

  // This is an empty Sudoku grid:
  //startState = new Sudoku("000000000000000000000000000000000000000000000000000000000000000000000000000000000");

  // This is a medium difficulty problem:
  //startState = new Sudoku("167000000050600047000300009641057000800060005000980716700008000490006050000000671");

  // And this next one is a really easy Sudoku...
  //startState = new Sudoku("927430008060000097008000402000308005400060003800201000602000300790000080500089271");

  //startState = new MazeRunner(11,30,"    X                 X    X  XX XXXXXXXX  XXXXXX   X   XX   X X    X$    X  X   XXX  X    X X XXXXXXX  X      X    X  X X X          X  XXXXXX  XX XX   X          X  X       X  X    XXXXXXXXXXXX  X  XXXXXX  X      X      X   XXX  X  X   X X    X  X   X        X  X   X X    X  X   X   X    X  X   X X       X       X             ",0,0);

// This is what the maze looks like...
//    X                 X    X  
//XX XXXXXXXX  XXXXXX   X   XX  
// X X    X$    X  X   XXX  X   
// X X XXXXXXX  X      X    X  X
// X X          X  XXXXXX  XX XX
//   X          X  X       X  X 
//   XXXXXXXXXXXX  X  XXXXXX  X 
//     X      X   XXX  X  X   X 
//X    X  X   X        X  X   X 
//X    X  X   X   X    X  X   X 
//X       X       X             

  //startState = new SliderPuzzle(3,3,"8 7 6 5 4 3 2 1 0");
  //startState = new SliderPuzzle(3,4,"11 10 9 8 7 6 5 4 3 1 2 0");
  //startState = new SliderPuzzle(4,4,"15 14 13 12 11 10 9 8 7 6 5 4 3 1 2 0");
  //startState = new SliderPuzzle(5,5,"24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0");
  startState = new SliderPuzzle(6,6,"35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 1 2 0");


  // 221 STUDENTS:  For this assignment, stick with VectorPriorityQueue.
  // The other declarations are left here in case you want to play with them.
  //ArrayStack activeStates;
  //LinkedListStack activeStates;
  VectorPriorityQueue activeStates;
  //ArrayQueue activeStates;
  //LinkedListQueue activeStates;
  //HeapPriorityQueue activeStates;

  // 221 STUDENTS:  When you're ready, uncomment one of these to be your
  // dictionary implementation.
  // I've provided you an optimized version of LinkedListDict from Project 1.
  //LinkedListDict seenStates;
  AVLDict seenStates;
  //LinearHashDict seenStates;
  //DoubleHashDict seenStates;

  vector<PuzzleState*> solution;

  solvePuzzle(startState, activeStates, seenStates, solution);

  // Print out solution
  for (int i=(int)solution.size()-1; i >= 0; i--) {
    cout << "STEP " << solution.size()-i << ":\n";
    solution[i]->print(cout);
    cout << endl;
  }
  
  // Don't delete any states, as every state gets entered into the
  // seenStates dictionary, and each will get deleted exactly once
  // when seenStates destructor is called.
  //delete startState;

  return 0;
}
