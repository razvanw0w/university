#include "ShortTest.h"
#include <assert.h>
#include <iostream>
#include "Set.h"
#include "SetIterator.h"

void print_debug(const std::string& s) {
    std::cout << s << '\n';
    std::cout.flush();
}

void testAll() { 
	Set s;
	assert(s.isEmpty() == true);
    print_debug("Passed short empty");
	assert(s.size() == 0);
    print_debug("Passed short empty size");
	assert(s.add(5)==true);
	assert(s.add(1)==true);
	assert(s.add(10)==true);
	assert(s.add(7)==true);
	assert(s.add(1)==false);
	assert(s.add(10)==false);
	assert(s.add(-3)==true);
    print_debug("Passed short add");
	assert(s.size() == 5);
    print_debug("Passed short size");
	assert(s.search(10) == true);
	assert(s.search(16) == false);
    print_debug("Passed short search");
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
    print_debug("Passed short remove");
	assert(s.size() == 4);
    print_debug("Passed short remove size");

    print_debug("Began short iterator");
	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 19);
    print_debug("Passed short iterator");

    testUnion();
    print_debug("Passed in-lab union");
    print_debug("Passed SHORT TESTS!");
}

void testUnion() {
    Set s1, s2;
    s1.add(1);
    s1.add(2);
    s1.add(3);
    s1.add(4);
    s1.add(5);
    s1.add(6);
    s2.add(3);
    s2.add(4);
    s2.add(5);
    s2.add(6);
    s2.add(7);
    s2.add(8);

    s1.setUnion(s2);
    assert(s1.size() == 8);
    for (int i = 1; i <= 8; ++i)
        assert(s1.search(i));
}

