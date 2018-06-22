// copy construction

#include <iostream>
#include <list>
#include <vector>

#include "EuclideanVector.h"

int main() {
	
	// create a 3D eucldean vector
	std::vector<double> a1 {5,4,3.1,2,1.0};
	const evec::EuclideanVector ev{a1.begin() + 1,a1.begin() + 4};
	
	// type cast it
	std::list<double> l = ev;
	l.push_back(8.0);
	
	// make a second vector
	evec::EuclideanVector ev2{l.begin(), l.end()};
	
	// make a third vector
	evec::EuclideanVector *ev3 = new evec::EuclideanVector(4);
	
	std::cout << std::boolalpha << (ev2 == *ev3) << std::endl;
	std::cout << *ev3 << std::endl;
	std::cout << ev2 << std::endl;
	*ev3 = ev2 * 2;
	std::cout << *ev3 << std::endl;
	
	// make a 4th vector using a copy constructor
	evec::EuclideanVector *ev4 = new evec::EuclideanVector{ev2};
	std::cout << *ev4 << std::endl;
	
	// make a 5th vector using a copy constructor
	evec::EuclideanVector *ev5 = new evec::EuclideanVector{*ev3};
	std::cout << *ev5 << std::endl;
	
}
