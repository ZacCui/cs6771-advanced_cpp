// tests for compound assignments

#include <iostream>

#include "EuclideanVector.h"

int main() {
	evec::EuclideanVector ev {5};

	std::cout << ev << std::endl;

	// try the [] braces
	for (double d = 1.0; d < ev.getNumDimensions(); d += 1.0) {
		ev[static_cast<int>(d)] = d;
		std::cout << ev[static_cast<int>(d)] << std::endl;
	}

	auto evu = ev.createUnitVector();

	// try assignment
	ev += evu;
	std::cout << ev << std::endl;
	ev -= evu;
	std::cout << ev << std::endl;
	ev *= 5.6;
	std::cout << ev << std::endl;
	ev /= 5.6;
	std::cout << ev << std::endl;
}
