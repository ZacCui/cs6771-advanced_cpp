#include <iostream>
#include <vector>
#include <list>

#include "EuclideanVector.h"

int main() {
	
	evec::EuclideanVector a(2);	
	
	std::list<double> l {1,2,3};
	evec::EuclideanVector b{l.begin(),l.end()};
	
	std::vector<double> v2 {4,5,6,7};
	evec::EuclideanVector c{v2.begin(),v2.end()};
	
	std::vector<double> a1 {5,4,3,2,1};
	evec::EuclideanVector d{a1.begin(),a1.end()};
	
	std::list<double> a2 {9,0,8,6,7};
	evec::EuclideanVector e{a2.begin(),a2.end()};
	
	// use the copy constructor
	evec::EuclideanVector f{e};	

	std::cout << a.getNumDimensions() << ": " << a << std::endl;
	std::cout << "D1:" << b.get(1) << " " << b << std::endl;
	std::cout << c << " Euclidean Norm = " << c.getEuclideanNorm() << std::endl;
	std::cout << d << " Unit Vector: " << d.createUnitVector() << " L = " << d.createUnitVector().getEuclideanNorm() << std::endl;
	std::cout << e << std::endl;
	std::cout << f << std::endl;
	
	// test the move constructor
	evec::EuclideanVector g = std::move(f);
	std::cout << g << std::endl;
	std::cout << f << std::endl;
	
	// try operator overloading
	e += d;
	std::cout << e << std::endl;
	
	evec::EuclideanVector h = e - g;
	std::cout << h << std::endl;
	
	// test scalar multiplication
	h *= 2;
	std::cout << h << std::endl;
	
	evec::EuclideanVector j = b / 2;
	std::cout << j << std::endl;
	
	std::cout << "dot product = " << j * b << std::endl;
	
	if (g == (e - d)) std::cout << "true" << std::endl;
	if (j != b ) std::cout << "false" << std::endl;
	
	j[0] = 1;
	std::cout << j << std::endl;
	
	// type cast from EuclideanVector to a std::vector
	std::vector<double> vj = j;
	
	// type cast from EuclideanVector to a std::vector
	std::list<double> lj = j;
	
	for (auto d : lj) {
		std::cout << d << std::endl;
	}

	// list initialisation
        evec::EuclideanVector k {1, 2, 3};
        std::cout << k << std::endl;
}
