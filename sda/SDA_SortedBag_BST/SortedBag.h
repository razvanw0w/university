#pragma once
#include "SortedBagIterator.h"
#include "BSTNode.h"

typedef int TComp;
typedef bool(*Relation)(TComp, TComp);

class SortedBagIterator;

class SortedBag {
    friend class SortedBagIterator;

private:
    BSTNode *tree;
    int root;
    int numberOfElements;
    int capacity;
    int firstFree;
    Relation r;

    void changeFirstFree();
    bool mustBeResized();
    void resize();
    TComp getMinimum(int startingRoot);
    TComp getMaximum(int startingRoot);
    int removeRecursively(int node, TComp e, bool &removed);

public:
    //constructor
    SortedBag(Relation r);

    //adds an element to the sorted bag
    //Complexitate: O(n) daca arborele e degenerat (arata ca un lant)
    //              O(log2 n) pe caz mediu
    void add(TComp e);

    //removes one occurence of an element from a sorted bag
    //returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
    //Complexitate: O(n) - arbore degenerat
    //              O(log2 n) - caz general
    bool remove(TComp e);

    //checks if an element appearch is the sorted bag
    //Complexitate: O(n) - arbore degenerat
    //              O(log2 n) - caz general
    bool search(TComp e) const;

    //returns the number of occurrences for an element in the sorted bag
    //Complexitate: O(n) - arbore degenerat
    //              O(log2 n) - caz general
    int nrOccurrences(TComp e) const;

    //returns the number of elements from the sorted bag
    //Complexitate: Theta(1)
    int size() const;

    //returns an iterator for this sorted bag
    //complexitate: Theta(1)
    SortedBagIterator iterator() const;

    //checks if the sorted bag is empty
    //Complexitate: Theta(1)
    bool isEmpty() const;

    //destructor
    ~SortedBag();
};
