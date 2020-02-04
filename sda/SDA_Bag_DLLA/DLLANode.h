//
// Created by razvan on 01.04.2019.
//

#ifndef SDA4_DLLANODE_H
#define SDA4_DLLANODE_H

typedef int TElem;

class DLLANode {
private:
    TElem element;
    int frequency;
    int prev;
    int next;

public:
    DLLANode(TElem element = 0, int frequency = 1, int prev = -1, int next = -1);
    TElem getElement() const;
    void setElement(TElem element);
    int getPrev() const;
    void setPrev(int prev);
    int getNext() const;
    void setNext(int next);
    int getFrequency() const;
    void setFrequency(int frequency);
};


#endif //SDA4_DLLANODE_H
