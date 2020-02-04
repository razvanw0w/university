//
// Created by razvan on 30.03.2019.
//

#ifndef SDA3_DLLNODE_H
#define SDA3_DLLNODE_H

typedef int TElem;

class DLLNode {
private:
    TElem element;
    DLLNode* prev;
    DLLNode* next;

public:
    DLLNode(TElem element = 0, DLLNode *prev = nullptr, DLLNode *next = nullptr);
    TElem getElement() const;
    void setElement(TElem element);
    DLLNode *getPrev() const;
    void setPrev(DLLNode *prev);
    DLLNode *getNext() const;
    void setNext(DLLNode *next);
    bool operator==(const DLLNode &rhs) const;
    bool operator!=(const DLLNode &rhs) const;
};


#endif //SDA3_DLLNODE_H
