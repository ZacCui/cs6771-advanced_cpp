// Overloading and others

#include <iostream>
#include <list>
#include <vector>

#include "EuclideanVector.h"

int main() {
	
	// create a const euclidean vector
	std::vector<double> a1 {5,4,3.1,2,1.0};

	const evec::EuclideanVector ev{a1.begin(),a1.end()};
	
	// test << overload
	std::cout << ev << std::endl;

	
	// test get and [] overload
	for (unsigned int i = 0; i < ev.getNumDimensions(); ++i) {
		std::cout << ev.get(i) << " " << ev[i] << std::endl;
	}

	
	// test create unit vector
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
	std::cout << evf * 4 << std::endl;
	int d = 5 * ev * evu;
	std::cout << d << std::endl;
	std::cout << ev / d << std::endl;
	
	// try assignment to a non-const one and modify
	auto newEv = ev;
	newEv[0] = 0.532432;
	++newEv[1];
	std::cout << newEv << std::endl;
	
	// try type conversion. 
	std::list<double> evl = ev;
	std::cout << ev[0] << " " << evl.front() << std::endl;
	std::vector<double> evv{ev};
	std::cout << ev[2] << " " << ++evv[2] << std::endl;
}
