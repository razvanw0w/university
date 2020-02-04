#include "Set.h"
#include <assert.h>
#include "ExtendedTest.h"
#include "SetIterator.h"
#include <iostream>
#include <sstream>

using namespace std;

void printDebug(const std::string& s) {
    std::cout << s << '\n';
    std::cout.flush();
}

void printM(Set& s){
	SetIterator it = s.iterator();
	while (it.valid()){
		std::cout << it.getCurrent() << " ";
		it.next();
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void testCreate() {
	Set s;
	assert(s.size() == 0);
	assert(s.isEmpty() == true);

    printDebug("Passed extended create");

	for (int i = -10; i < 10; i++) { //search in an empty set
		assert(s.search(i) == false);
	}
    printDebug("Passed extended create search in empty set");

    for (int i = -10; i < 10; i++) { //delete from an empty set
		assert(s.remove(i) == false);
	}
    printDebug("Passed extended create remove in empty set");

	SetIterator it = s.iterator(); //iterator on the empty set should be invalid from the start
	assert(it.valid() == false);
    printDebug("Passed extended create search in empty set");
    printDebug("Passed extended CREATE!");
}


void testAdd() {
	Set s; //adaugam elemente [0, 10)
    bool ok;
	for (int i = 0; i < 10; i++) {
		ok = s.add(i);
		assert(ok == true);
	}
	//printM(m);
	assert(s.isEmpty() == false);
	assert(s.size() == 10);
    printDebug("Passed extended add [0, 10]");
	for (int i = -10; i < 20; i++) { //add more elements [-10, 20)
		ok = s.add(i);
		if (i >= 0 && i < 10) {
		    assert(ok == false);
		}
		else {
		    assert(ok == true);
		}
	}
	//printM(m);
	assert(s.isEmpty() == false);
	assert(s.size() == 30);
    printDebug("Passed extended add [-10, 20]");
	for (int i = -100; i < 100; i++) { //add more elements [-100, 100)
		ok = s.add(i);
		if (i >= -10 && i < 20) {
		    assert(ok == false);
		}
		else {
		    assert(ok == true);
		}
	}
	//printM(m);
	assert(s.isEmpty() == false);
	assert(s.size() == 200);
    printDebug("Passed extended add [-100, 100]");
	for (int i = -200; i < 200; i++) {
	    std::stringstream stream;
		if (i < -100) {
			assert(s.search(i) == false);
		}
		else if (i < 0) {
			assert(s.search(i) == true);
		}
		else if (i < 100) {
			assert(s.search(i) == true);
		}
		else {
			assert(s.search(i) == false);
		}
	}
    printDebug("Passed extended add search");
    printDebug("Began extended add large values");
	for (int i = 10000; i > -10000; i--) { //add larger values first
		s.add(i);
	}
	assert(s.size()==20000);
    printDebug("Passed extended add large values");
    printDebug("Passed extended ADD!");
}


void testRemove() {
	Set m;
	for (int i = -100; i < 100; i++) { //delete from the emtpy set
		assert(m.remove(i) == false);
	}
	assert(m.size() == 0);
    printDebug("Passed extended remove from empty set");
	//printM(m);
	for (int i = -100; i < 100; i = i + 2) { 
		m.add(i);
	}
    printDebug("Passed extended remove add even [-100, 100]");
	for (int i = -100; i < 100; i++) { //delete everything (including inexistent elements)
		if (i % 2 == 0) {
			assert(m.remove(i) == true);
		}
		else {
			assert(m.remove(i) == false);
		}
	}
	assert(m.size() == 0);
    printDebug("Passed extended remove even [-100, 100]");
	//printM(m);

	for (int i = -100; i <= 100; i = i + 2) { 
		m.add(i);
	}
	//printM(m);
	for (int i = 100; i > -100; i--) { //delete in descending order (reverse order compared to the adding)
		if (i % 2 == 0) {
			assert(m.remove(i) == true);
		}
		else {
			assert(m.remove(i) == false);
		}
	}
	assert(m.size() == 1);
    printDebug("Passed extended remove even [-100, 100] descending");
	//printM(m);

	m.remove(-100);
	assert(m.size() == 0);

	for (int i = -100; i < 100; i++) { //add each element five times
		m.add(i);
		m.add(i);
		m.add(i);
		m.add(i);
		m.add(i);
	}
	//printM(m);
	assert(m.size() == 200);
	for (int i = -200; i < 200; i++) { //delete existing and inexistent elements
		if (i < -100 || i >= 100) {
			assert(m.remove(i) == false);
		}
		else {
			assert(m.remove(i) == true);
			assert(m.remove(i) == false);
		}
	}
	assert(m.size() == 0);
    printDebug("Passed extended remove [-100, 100] multiply added");
    printDebug("Passed extended REMOVE!");
 }


void testIterator() {
	Set s;
	SetIterator it = s.iterator(); //iterator on an empty set
	assert(it.valid() == false);
    printDebug("Passed extended iterator empty");

	for (int i = 0; i < 100; i++) {  
		s.add(33);
	}
	//printM(m);
	SetIterator it2 = s.iterator(); 
	assert(it2.valid() == true);
	TElem elem = it2.getCurrent();
	assert(elem == 33);
	it2.next();
	assert(it2.valid() == false);

	it2.first(); 
	assert(it2.valid() == true);

    printDebug("Passed extended iterator one value");
	Set s2;
	for (int i = -100; i < 100; i++) { 
		s2.add(i);
		s2.add(i);
		s2.add(i);
	}
	//printM(m2);
	SetIterator it3 = s2.iterator();
	assert(it3.valid() == true);
	for (int i = 0; i < 200; i++) {
		//TElem e1 = im3.element();
		it3.next();
	}
	assert(it3.valid() == false);
	it3.first();
	assert(it3.valid() == true);
    printDebug("Passed extended iterator [-100, 100]");

	Set s3;
	for (int i = 0; i < 200; i= i + 4) { 
		s3.add(i);
	}
	//printM(m3);

	SetIterator it4 = s3.iterator();
	assert(it4.valid() == true);
	int count = 0;
	while (it4.valid()) { 
		TElem e = it4.getCurrent();
		assert(e % 4 == 0);
		it4.next();
		count++;
	}
	assert(count == 50);
    printDebug("Passed extended iterator [0, 200)");
    printDebug("Passed extended ITERATOR!");
}



void testQuantity() {//add lots of elements
	Set s;
    printDebug("Began extended quantity add");
	for (int i = 10; i >= 1; i--) {
		for (int j = -30000; j < 30000; j = j + i) {
			s.add(j);
		}
	}
	assert(s.size() == 60000);
    printDebug("Passed extended quantity add");
	SetIterator it = s.iterator();

    printDebug("Began extended quantity iterator");
	assert(it.valid() == true);
	for (int i = 0; i < s.size(); i++) {
		it.next();
	}
	it.first();
	while (it.valid()) { 
		TElem e = it.getCurrent();
		assert(s.search(e) == true);
		it.next();
	}
	assert(it.valid() == false);
    printDebug("Passed extended quantity iterator");

    printDebug("Began extended quantity remove");
	for (int i = 0; i < 10; i++) { //delete existing and inexistent elements
		for (int j = 40000; j >= -40000; j--) {
			s.remove(j);
		}
	}
	assert(s.size() == 0);
    printDebug("Passed extended quantity remove");
    printDebug("Passed extended QUANTITY!");
}


// we don't know how the set is represented and in which order the elements are stored or printed, we can only test general thing
void testAllExtended() {
	testCreate();
	testAdd();
	testRemove();
	testIterator();
	testQuantity();
    printDebug("Passed EXTENDED TESTS!");
}
