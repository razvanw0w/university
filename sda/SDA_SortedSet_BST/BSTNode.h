//
// Created by razvan on 27.05.2019.
//

#ifndef SDA7_BSTNODE_H
#define SDA7_BSTNODE_H

typedef int TComp;

class BSTNode {
private:
    TComp value;
    BSTNode *leftSon;
    BSTNode *rightSon;

public:
    BSTNode(int value = 0, BSTNode *leftSon = nullptr, BSTNode *rightSon = nullptr);
    TComp getValue() const;
    void setValue(TComp value);
    BSTNode *getLeftSon() const;
    void setLeftSon(BSTNode *leftSon);
    BSTNode *getRightSon() const;
    void setRightSon(BSTNode *rightSon);
    bool isLeaf(); // returneaza daca e frunza sau nu (adica nu are deloc fii)
};


#endif //SDA7_BSTNODE_H
