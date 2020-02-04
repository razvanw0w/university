#ifndef SDA3_LISTITERATOR_H
#define SDA3_LISTITERATOR_H

#include "IteratedList.h"

class IteratedList;

class ListIterator {
    friend class IteratedList;
private:
    const IteratedList& list;
    DLLNode* currentNode;
    ListIterator(const IteratedList &list);

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
    bool operator==(const ListIterator &rhs) const;
    bool operator!=(const ListIterator &rhs) const;
};

#endif //SDA3_LISTITERATOR_H
