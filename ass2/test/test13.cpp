//   move construction

#include <iostream>

#include "EuclideanVector.h"

int main() {
	
	evec::EuclideanVector a {1, 2}; 
	evec::EuclideanVector b (2, 4); 
 	std::cout << a << std::endl;
 	std::cout << b << std::endl;

        a  = a + b; 
 	std::cout << a << std::endl;
 	std::cout << b << std::endl;

	evec::EuclideanVector c {std::move(b)};
 	std::cout << c << std::endl;
        // b is empty according to the spec
	std::cout << b << std::endl;
	
}
