//   copy onto itself

#include <iostream>

#include "EuclideanVector.h"

int main() {
	
	evec::EuclideanVector a {1, 2}; 

 	std::cout << a << std::endl;
        a  = a;
 	std::cout << a << std::endl;

 	auto &b = a;
 	std::cout << a << std::endl;
 	std::cout << b << std::endl;
        a = b;
 	std::cout << a << std::endl;
 	std::cout << b << std::endl;
}
