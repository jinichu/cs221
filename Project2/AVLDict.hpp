//AVLDict.hpp
#ifndef _AVLDICT_HPP
#define _AVLDICT_HPP

#include "PredDict.hpp"

// An implementation of a dictionary ADT as an AVL tree.
//
class AVLDict : public PredDict
  {
  public:
    AVLDict();
    ~AVLDict();
    bool find(PuzzleState *key, PuzzleState *&pred);
    void add(PuzzleState *key, PuzzleState *pred);

  private:
    struct node {
      PuzzleState *key;
      string keyID; // Avoid recomputation of key's getUniqId()
      PuzzleState *data;
      int height; // Avoid recomputation of subtree height.
      node *left;
      node *right;
    };

    node *root;

    // The next two variables are just to collect statistics on the
    // number of probes required for each call to find().
    int *depth_stats; // probe_stats[i] should be how often i probes needed
    const static int MAX_STATS = 30; // How big to make the array.

    void destructor_helper(node * x);
    bool find_helper(node *r, string keyID, PuzzleState *&pred, int depth);
    // These are helper functions just like in your lab...
    inline int height(node *x) { return (x==NULL) ? -1 : x->height; }
    bool update_height(node *x);
    void rotate_left(node *&a);
    void rotate_right(node *&b);

    void doubleRotate_left(node *&a);
    void doubleRotate_right(node *&b);

    void insert(node *&temp, node *&root);

    void balance(node * &x);
    int get_balance(node * x);

    // You may add additional helper functions and member variables...
  };

#endif

