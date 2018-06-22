// tests for friends

#include <iostream>

#include "EuclideanVector.h"

int main() {
	evec::EuclideanVector ev (5);
	
	std::cout << ev << std::endl;
	
	// try the [] braces
	for (double d = 1.0; d < ev.getNumDimensions(); d += 1.0) {
		ev[static_cast<int>(d)] = d;
		std::cout << ev[static_cast<int>(d)] << std::endl;
	}
	
	auto evu = ev.createUnitVector();
	
	// try == and != 
	// note all of this should work as const
	std::cout << ev << std::endl;
	std::cout << ev.createUnitVector() << std::endl;
	std::cout << std::boolalpha << (ev != ev.createUnitVector()) << std::endl;
	std::cout << (ev == evu) << std::endl;
	std::cout << (ev == ev) << std::endl;
	
	// try +, -, *, / as friends
	// note all of this should work as const
	auto evf = evu + ev;
	std::cout << evf << std::endl;
	std::cout << evf - ev << std::endl;
	std::cout << ((evf - ev) == evu) << std::endl;
	std::cout << evf * ev << std::endl;
	std::cout << evf * 3.14 << std::endl;
	auto d = 3.14 * ev * evu;
	std::cout << d << std::endl;
	std::cout << ev / d << std::endl;
	
}
