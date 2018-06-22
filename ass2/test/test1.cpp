// simple constructors

#include <iostream>
#include <list>
#include <vector>

#include "EuclideanVector.h"

int main() {

	// delegating constructor test
	// give it an rvalue signed int
	evec::EuclideanVector a_rval(1);

	std::cout << a_rval.getNumDimensions() << " " << a_rval.get(0) << std::endl;

	// give it an unsigned int
	unsigned int ui = 2;
	evec::EuclideanVector a2(ui);

	std::cout << a2.getNumDimensions() << " " << a2.get(1) << std::endl;

	// give it a const int
	const int ci = 3;
	evec::EuclideanVector a3(ci);

	std::cout << a3.getNumDimensions() << " " << a3.get(2) << std::endl;

	// give it a const unsigned int
	const unsigned int cui = 4;
	evec::EuclideanVector a4(cui);

	std::cout << a4.getNumDimensions() << " " << a4.get(3) << std::endl;

	// give it a short
	short unsigned si = 5;
	evec::EuclideanVector a5(si);

	std::cout << a5.getNumDimensions() << " " << a5.get(4) << std::endl;

	// 0 dimensions test
	evec::EuclideanVector a6(0);

	std::cout << a6.getNumDimensions() << std::endl;

	// list constructor test
	// give it a iterator over some ints.
	std::list<double> l {1,2,4};
	evec::EuclideanVector b{l.begin(),l.end()};

	std::cout << b.getNumDimensions() << " " << b.get(ui) << std::endl;

	// vector constructor test
	std::vector<double> v2 {4,5,6,7};
	evec::EuclideanVector c{v2.begin(),v2.end()};

	std::cout << c.getNumDimensions() << " " << c.get(ci) << std::endl;

	// array constructor test
	std::vector<double> a1 {5,4,3.1,2,1.0};
	evec::EuclideanVector d{a1.begin(),a1.end()};

	std::cout << d.getNumDimensions() << " " << d.get(2) << std::endl;

	// test constructor that takes dimensions and magnitudes
	// unsigned rvalues
	evec::EuclideanVector e(1,4);

	std::cout << e.getNumDimensions() << " " << e.get(0) << std::endl;

	// give it some const values
	const int mag = 5;
	evec::EuclideanVector e2(ci,mag);

	std::cout << e2.getNumDimensions() << " " << e2.get(1) << std::endl;

	// try a double r-value
	evec::EuclideanVector e3(ui,4.9);

	std::cout << e3.getNumDimensions() << " " << e3.get(1) << std::endl;

	// try a double l-value
	double d1 = 3.14;
	evec::EuclideanVector e4(cui,d1);
	std::cout << e4.getNumDimensions() << " " << e4.get(ui) << std::endl;
}
