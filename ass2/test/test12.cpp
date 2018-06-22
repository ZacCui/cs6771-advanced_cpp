// list initialisation
#include <iostream>

#include "EuclideanVector.h"

int main() {
	
	evec::EuclideanVector a {1, 2, 3, 4}; 
 	std::cout << a  << std::endl;

	evec::EuclideanVector b {2}; 
 	std::cout << b  << std::endl;
	
	evec::EuclideanVector c (2); 
 	std::cout << c  << std::endl;
}
