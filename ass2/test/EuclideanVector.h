#pragma once
#ifndef EUCLIDEANVECTOR_EUCLIDEANVECTOR_H
#define EUCLIDEANVECTOR_EUCLIDEANVECTOR_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <vector>
#include <list>

namespace evec {

class EuclideanVector
{
public:
	//Defualt Constructor
	EuclideanVector(): EuclideanVector(1U,0.0) {}

	//Constructor with size as @para
	EuclideanVector(const unsigned int& size): EuclideanVector(size,0.0) {}

	//Copy Constructor
	EuclideanVector(const EuclideanVector&);

	//Move Constructor 
	EuclideanVector(EuclideanVector&&);

	//Constructor with 2 @para
	EuclideanVector(const unsigned int& n, const double& m);
 	
 	//Iterator Constructor
	template<typename Iter>
	EuclideanVector(const Iter & first, const Iter & last,typename Iter::iterator_category* p = 0)
	{
		NumDimensions = static_cast<unsigned int>(std::distance(first,last));
		v = new double [NumDimensions];
		int i = 0;
		for(auto next = first; next != last; ++next){
			v[i++] = *next;
		}
	}

	//List constructor
	EuclideanVector(const std::initializer_list<double> &l);

	//List constructor
	EuclideanVector(const std::list<double> &l): EuclideanVector(l.cbegin(),l.cend()) {}

	//Vector constructor
	EuclideanVector(const std::vector<double> &vec): EuclideanVector(vec.cbegin(),vec.cend()) {}

	//vector operator
	operator std::vector<double>() const;

	//list operator
	operator std::list<double>() const;

	double& operator[](const int &index);

	double operator[](const int &index) const;

	//Destructor
	~EuclideanVector(){delete[] v;}

	//Set value by index
	void set(const unsigned int&, const double &);

	//Get value by index
	double get(const unsigned int & ) const;

	//Get Norm
	double getEuclideanNorm() const;

	//Get Dimensions
	inline const unsigned int& getNumDimensions() const {return NumDimensions;};

	//Operators override
    EuclideanVector& operator=(const EuclideanVector &obj);
    EuclideanVector& operator=(EuclideanVector &&obj);
	EuclideanVector& operator+=(const EuclideanVector &);
	EuclideanVector& operator-=(const EuclideanVector &);
	EuclideanVector& operator*=(const double &);
	EuclideanVector& operator/=(const double &);
	EuclideanVector& createUnitVector() const;
private:
	unsigned int NumDimensions;
	double* v;
};

//Non-member functions
std::ostream& operator<<(std::ostream &os, const EuclideanVector &v);
inline EuclideanVector& operator+(EuclideanVector lhs, const EuclideanVector& rhs){return lhs += rhs;};
inline EuclideanVector& operator-(EuclideanVector lhs, const EuclideanVector& rhs){return lhs -= rhs;};
inline EuclideanVector& operator*(EuclideanVector lhs, const double& rhs){return lhs *= rhs;};
inline EuclideanVector& operator*(const double& lhs, EuclideanVector rhs){return rhs *= lhs;};
inline EuclideanVector& operator/(EuclideanVector lhs, const double& rhs){return lhs /= rhs;};
inline EuclideanVector& operator/(const double& lhs, EuclideanVector rhs){return rhs /= lhs;};
bool operator==(const EuclideanVector&,const EuclideanVector&);
inline bool operator!=(const EuclideanVector& lhs,const EuclideanVector& rhs) {return !(lhs==rhs);};
double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs);
}

#endif