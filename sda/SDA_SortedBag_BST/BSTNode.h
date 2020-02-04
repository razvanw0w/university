#pragma once

typedef int TComp;
const int NULL_TCOMP = -99999999; // valoare care semnaleaza ca nodul este nul (nu e nimic in el)

// clasa care simbolizeaza un nod al arborelui binar de cautare (BSB)
class BSTNode {
private:
    TComp value;  // valoarea asociata
    int leftSon;  // pozitia in vector a fiului stang
    int rightSon; // -/////////////////- fiului drept

public:
    BSTNode(TComp value = NULL_TCOMP, int leftSon = -1, int rightSon = -1);
    TComp getValue() const;
    void setValue(TComp value);
    int getLeftSon() const;
    void setLeftSon(int leftSon);
    int getRightSon() const;
    void setRightSon(int rightSon);
    bool isNull(); // returneaza true sau false daca e nul
    bool isLeaf(); // returneaza daca e frunza sau nu (adica nu are deloc fii)
};
