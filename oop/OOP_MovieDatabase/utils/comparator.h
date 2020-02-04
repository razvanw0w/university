//
// Created by razvan on 17.04.2019.
//

#ifndef OOP5_COMPARATOR_H
#define OOP5_COMPARATOR_H

template <typename TElem>
class Comparator {
public:
    virtual bool compare(const TElem& t1, const TElem& t2) const = 0;
};


#endif //OOP5_COMPARATOR_H
