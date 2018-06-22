// copy control (copy + move semantics)

#include <iostream>
#include <vector>

#include "EuclideanVector.h"

int main() {
	
	std::vector<double> a1 {5,4,3.1,2,1.0};
	const evec::EuclideanVector ev{a1.begin(),a1.begin() + 4};
	
	std::cout << ev << std::endl;
	
	// try copy constructor with a const
	const auto ev2 = ev;
	std::cout << ev2 << std::endl;
	
	// copy constructor to a non-const
	evec::EuclideanVector ev3{ev2};
	std::cout << ev3 << std::endl;
	
	// modify the non-const and check both
	ev3[0] = 0;
	std::cout << ev2 << std::endl;
	std::cout << ev3 << std::endl;
	
	// normal copy constructors
	evec::EuclideanVector ev4{ev3};
	std::cout << ev4 << std::endl;
	
	// modify and check
	ev4[1]=8.89;
	std::cout << ev3 << std::endl;
	std::cout << ev4 << std::endl;
	
	// create a new ev
	evec::EuclideanVector ev5(4);
	std::cout << ev5 << std::endl;
	
	// copy assignment with overloading
	ev5 = ev4 * 2;
	std::cout << ev5 << std::endl;
	
	ev4 = ev5 - ev;
	std::cout << ev4 << std::endl;
	
	// move constructor with const. 
	auto ev6 = std::move(ev);
	std::cout << ev6 << std::endl;
	
	// because this is const we should still be able to use both ev and ev6
	ev6[2] = 34.6;
	std::cout << ev << std::endl;
	std::cout << ev6 << std::endl;
	
	// move constructor without const, note can't use auto here
	evec::EuclideanVector ev7 {std::move(ev5)};
	std::cout << ev7 << std::endl;
	// we shouldn't use ev5 beyond this point. 
	// but for testing purposes, we do:
	std::cout << ev5 << std::endl;
	
	// move assignment
	ev7 = std::move(ev6);
	std::cout << ev7 << std::endl;
	// we shouldn't use ev6 beyond this point. 
	// but for testing purposes, we do:
	std::cout << ev6 << std::endl;
}
