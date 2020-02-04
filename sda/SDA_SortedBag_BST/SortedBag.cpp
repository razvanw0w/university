//
// Created by razvan on 23.05.2019.
//

#include "SortedBag.h"

SortedBag::SortedBag(Relation r): root{-1},
                                  numberOfElements{0},
                                  capacity{16},
                                  firstFree{0},
                                  r{r}
                                  {
                                      tree = new BSTNode[16];
                                  }

void SortedBag::add(TComp e) {
    if (mustBeResized()) { // daca trebuie sa redimensionam vectorul, o facem
        resize();
    }

    // nodul nou adaugat o sa fie pe pozitia firstFree, asa ca-l adaugam de pe acuma
    tree[firstFree].setValue(e);
    tree[firstFree].setLeftSon(-1);
    tree[firstFree].setRightSon(-1);

    // caut pozitia pe care trebuie sa adaug nodul
    // la final o sa fie "parent"
    int current = root, parent = -1;
    while (current != -1) {
        parent = current;
        if (r(e, tree[current].getValue())) // daca relatia dintre elementu pe care trebe sa-l bag si valoarea in arbore se satisface
                                            // atunci trebuie sa ma duc pe fiul stang
            current = tree[current].getLeftSon();
        else                                // altfel ma duc pe fiul drept
            current = tree[current].getRightSon();
    }


    if (root == -1) // caz particular - nu avem radacina => radacina este firstFree
        root = firstFree;
    else if (r(e, tree[parent].getValue())) // daca trebuie sa pun elementul pe fiul stang, il pun pe fiul stang
        tree[parent].setLeftSon(firstFree);
    else                                    // altfel, pe fiul drept
        tree[parent].setRightSon(firstFree);
    changeFirstFree(); // actualizam firstFree
    ++numberOfElements; // crestem nr. de elemente
}

void SortedBag::changeFirstFree() {
    ++firstFree;
    while (firstFree < capacity && !tree[firstFree].isNull())
        ++firstFree;
}

bool SortedBag::remove(TComp e) {
    bool removed = false; // daca l-am sters sau nu, o sa se actualizeze in functia removeRecursively
    root = removeRecursively(root, e, removed);
    if (removed)
        --numberOfElements;
    return removed;
}

bool SortedBag::search(TComp e) const {
    int currentNode = root;

    // ma duc pe fiul stang sau drept in functie de cum se stabileste relatia
    while (currentNode != -1) {
        if (tree[currentNode].getValue() == e)
            return true;
        if (r(e, tree[currentNode].getValue())) {
            currentNode = tree[currentNode].getLeftSon();
        }
        else {
            currentNode = tree[currentNode].getRightSon();
        }
    }
    return false;
}

int SortedBag::nrOccurrences(TComp e) const {
    int currentNode = root;
    int counter = 0;

    // la fel ca la search, nu e foarte greu de urmarit
    while (currentNode != -1) {
        if (tree[currentNode].getValue() == e)
            ++counter;
        if (r(e, tree[currentNode].getValue())) {
            currentNode = tree[currentNode].getLeftSon();
        }
        else {
            currentNode = tree[currentNode].getRightSon();
        }
    }
    return counter;
}

int SortedBag::size() const {
    return numberOfElements;
}

SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

bool SortedBag::isEmpty() const {
    return numberOfElements == 0;
}

SortedBag::~SortedBag() {
    delete[] tree;
}

bool SortedBag::mustBeResized() {
    return firstFree >= capacity;
}

void SortedBag::resize() {
    BSTNode *newTree = new BSTNode[capacity * 2];
    for (int i = 0; i < capacity; ++i) {
        newTree[i].setValue(tree[i].getValue());
        newTree[i].setLeftSon(tree[i].getLeftSon());
        newTree[i].setRightSon(tree[i].getRightSon());
    }
    delete[] tree;
    tree = newTree;
    firstFree = capacity;
    capacity *= 2;
}

TComp SortedBag::getMinimum(int startingRoot) {
    int currentNode = startingRoot, minNode = startingRoot;
    TComp minimum;

    // caut cel mai mic element din subarborele BSB cu radacina in startingRoot
    // asta inseamna cel mai din stanga nod, adica ma duc cat de tare pot in stanga
    // o sa se afle in minNode
    while (currentNode != -1) {
        minimum = tree[currentNode].getValue();
        minNode = currentNode;
        currentNode = tree[currentNode].getLeftSon();
    }
    return minNode;
}

TComp SortedBag::getMaximum(int startingRoot) {
    int currentNode = startingRoot, maxNode = startingRoot;
    TComp maximum;

    // caut cel mai mare element din subarborele BSB cu radacina in startingRoot
    // asta inseamna cel mai din dreapta nod, adica ma duc cat de tare pot in dreapta
    // o sa se afle in maxNode
    while (currentNode != -1) {
        maximum = tree[currentNode].getValue();
        maxNode = currentNode;
        currentNode = tree[currentNode].getRightSon();
    }
    return maxNode;
}

int SortedBag::removeRecursively(int node, TComp e, bool &removed) {
    if (node == -1)
        return node;

    if (e == tree[node].getValue()) {
        // am dat de elementul pe care-l caut, tre sa-l sterg
        removed = true;
        if (tree[node].getLeftSon() == -1) { // daca nu exista un fiu stang, inseamna ca mutam subarborele care incepe
                                             // in fiul drept peste subarborele determinat de "node"
            int rightSon = tree[node].getRightSon();
            tree[node] = BSTNode{NULL_TCOMP, -1, -1};
            return rightSon;
        }
        else if (tree[node].getRightSon() == -1) { // analog ca mai sus, doar ca pt fiul drept, mutam subarborele
                                                   // care incepe in fiul stang
            int leftSon = tree[node].getLeftSon();
            tree[node] = BSTNode{NULL_TCOMP, -1, -1};
            return leftSon;
        }

        // altfel daca are ambii fii, punem valoarea celui mai mare element din subarborele stang
        // cu valoarea din nodul si stergem o aparitie a celui mai mare element (ca sa nu apara de 2 ori, ca e ca si
        // cum l-am muta pe ala in nodul curent
        int maxNode = getMaximum(tree[node].getLeftSon());
        tree[node].setValue(tree[maxNode].getValue());
        tree[node].setLeftSon(removeRecursively(tree[node].getLeftSon(), tree[maxNode].getValue(), removed));
    }
    else if (r(e, tree[node].getValue())) {
        // daca nodul se afla in subarborele determinat de fiul stang, atunci
        // fiul stang va fi radacina subarborelui determinat de initialul fiu stang dupa ce elementul cautat
        // a fost sters
        tree[node].setLeftSon(removeRecursively(tree[node].getLeftSon(), e, removed));
    }
    else {
        // la fel, doar ca pt fiul drept
        tree[node].setRightSon(removeRecursively(tree[node].getRightSon(), e, removed));
    }
    return node;
}
