#ifndef OOP5_DYNAMICARRAY_H
#define OOP5_DYNAMICARRAY_H

#include <stdexcept>

template <typename TElem>
class DynamicArray {

    /**
     * This function resizes the list when it is needed
     * @tparam TElem
     */
    void resizeList();

    /**
     * This function tells if the vector needs a resize or not
     * @tparam TElem
     * @return: true if the vector needs a resize
     *          false otherwise
     */
    bool needsResize() {
        return size == capacity;
    }

public:
    /**
     * Constructor based on capacity
     * @tparam TElem: a generic data type
     * @param capacity: int - the given capacity
     */
    DynamicArray(int capacity = 1): capacity {capacity}, size {0}, list {new TElem[capacity]}{}

    /**
     * Copy constructor
     * @tparam TElem: a generic data type
     * @param other: const DynamicArray& - another dynamic array
     */
    DynamicArray(const DynamicArray& other): capacity {other.capacity}, size {other.size}, list {new TElem[other.capacity]} {
        for (int i = 0; i < size; ++i) {
            list[i] = other.list[i];
        }
    }


    /**
     * Copy assignment operator
     * @tparam TElem
     * @param other
     * @return: the newly copied object (*this)
     */
     DynamicArray &operator=(const DynamicArray &other) {
        if (this != &other) {
            if (capacity < other.size) {
                delete[] list;
                list = new TElem[other.capacity];
            }
            size = other.size;
            capacity = other.capacity;
            for (int i = 0; i < size; ++i)
                list[i] = other.list[i];
        }
        return *this;
     }

    /**
     * Destructor of the dynamic array
     * @tparam TElem
     */
    virtual ~DynamicArray() {
        delete[] list;
    }

    /**
     * This function appends an element to the list
     * @tparam TElem
     * @param element: TElem - an element which must be added to a list
     */
    void append(TElem element) {
        if (needsResize())
            resizeList();
        list[size++] = element;
    }

    /**
     * This function removes an element from the list
     * @tparam TElem
     * @param element: TElem - the desired element
     * if the element is not present in the list, the list will not be affected
     */
    void remove(const TElem &element) {
        int position = search(element);
        if (position != -1) {
            for (int i = position; i < size - 1; ++i) {
                list[i] = list[i + 1];
            }
            --size;
        }
    }

    /**
     * This function searched an element in a list and returns its position
     * @tparam TElem
     * @param element: TElem - the element to be searched
     * @return: int - the position of the element if it is present in the list
     *          -1 otherwise
     */
    int search(const TElem &element) {
        for (int i = 0; i < size; ++i) {
            if (list[i] == element)
                return i;
        }
        return -1;
    }

    /**
     * This function updates an element
     * @tparam TElem
     * @param elementToUpdate: TElem - the object of updation
     * @param updatedElement: TElem - the updated element
     * if the element to update is nowhere to be found, then the list won't be affected
     */
    void update(const TElem &elementToUpdate, const TElem &updatedElement) {
        int position = search(elementToUpdate);
        if (position != -1) {
            list[position] = updatedElement;
        }
    }

    /**
     * Indexing operator for the dynamic array
     * @tparam TElem
     * @param index: int - the index of need
     * @preconditions: 0 <= index < size
     * @return: list[index]: TElem - the desired element
     * @except: can throw std::runtime_error if the index is out of bounds
     */
    TElem& operator[](int index) {
        if (index < 0 || index >= size)
            throw std::runtime_error("invalid index");
        return list[index];
    }

    /**
     * This function returns the length of the dynamic array
     * @tparam TElem
     * @return length: int - the length of the dynamic array
     */
    int length() {
        return size;
    }

    DynamicArray operator+(const TElem& element) {
        DynamicArray dynamicArray {*this};
        dynamicArray.append(element);
        return dynamicArray;
    }

    friend DynamicArray operator+ (const TElem& element, const DynamicArray& dynamicArray) {
        DynamicArray otherDynamicArray {dynamicArray};
        otherDynamicArray.append(element);
        return otherDynamicArray;
    }

private:
    TElem *list;
    int size;
    int capacity;
};

/**
     * This function resizes the list when it is needed
     * @tparam TElem
     */
template <typename TElem>
void DynamicArray<TElem>::resizeList() {
    TElem *newList = new TElem[capacity * 2];
    for (int i = 0; i < size; ++i)
        newList[i] = list[i];
    capacity *= 2;
    delete[] list;
    list = newList;
}

#endif //OOP5_DYNAMICARRAY_H