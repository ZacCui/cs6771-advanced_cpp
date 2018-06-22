//   move onto itself

#include <iostream>

#include "EuclideanVector.h"

int main() {
	
	evec::EuclideanVector a {1, 2}; 

 	std::cout << a << std::endl;
        a = std::move(a);

}
