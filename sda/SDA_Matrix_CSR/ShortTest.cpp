#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == 0);

	Matrix m2(3, 3);
	m2.modify(0, 0, 1);
	m2.modify(0, 2, 2);
	m2.modify(1, 0, 3);
	m2.modify(2, 2, 4);
	MatrixIterator it = m2.iterator();
	TElem elements[] = {1, 2, 3, 4};
	int curr = 0;
	while (it.valid()) {
	    assert(it.getCurrent() == elements[curr]);
	    ++curr;
	    it.next();
	}
	assert(curr == 4);
}