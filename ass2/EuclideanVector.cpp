#include "EuclideanVector.h"

namespace evec {

EuclideanVector::EuclideanVector(const unsigned int& n, const double& m):NumDimensions{n}{
	v = new double [static_cast<unsigned int>(NumDimensions)];
	std::fill_n(v,NumDimensions,static_cast<double>(m)); 
}

EuclideanVector::EuclideanVector(const EuclideanVector& e){
	v = new double[e.getNumDimensions()];
    NumDimensions = e.getNumDimensions();
    for(unsigned int i = 0;i < NumDimensions;i++) {
        	v[i] = e.get(i);
    }
}

EuclideanVector::EuclideanVector(EuclideanVector&& e){
    NumDimensions= std::move(e.NumDimensions);
    v = new double [NumDimensions];
    for(unsigned int i = 0;i < NumDimensions;i++) {
       	v[i] = std::move(e.v[i]);
    }
    e.v= new double[NumDimensions];
    e.NumDimensions = 0;
}

EuclideanVector::EuclideanVector(const std::initializer_list<double> &l){
		NumDimensions = static_cast<unsigned int>(std::distance(l.begin(),l.end()));
		v = new double [NumDimensions];
		int i = 0;
		for(auto next = l.begin(); next != l.end(); ++next){
			v[i++] = *next;
		}
}

EuclideanVector& EuclideanVector::operator=(const EuclideanVector &rhs){
	if(&rhs != this){
		delete[] v;
		NumDimensions = rhs.NumDimensions;
		v = new double[NumDimensions];
		for(unsigned int i = 0; i < NumDimensions; ++i){
			v[i] = rhs.v[i];
		}
	}
	return *this;
}

EuclideanVector& EuclideanVector::operator=(EuclideanVector &&rhs){
	if(&rhs != this){
		delete[] v;
		NumDimensions = std::move(rhs.NumDimensions);
		v = new double[NumDimensions];
		for(unsigned int i = 0; i < NumDimensions; ++i){
			v[i] = std::move(rhs.v[i]);
		}
		rhs.v = nullptr;
	}
	return *this;
}

double & EuclideanVector::operator[](const int & index){
	try{
		return v[index];
	}catch (const std::exception &e) {
    	std::cerr << "Error: " << e.what() << '\n';
    	delete [] v;
    	exit(1);
  	}
}

double EuclideanVector::operator[](const int & index) const{
	try{
		return v[index];
	}catch (const std::exception &e) {
    	std::cerr << "Error: " << e.what() << '\n';
    	delete [] v;
    	exit(1);
  	}
}

EuclideanVector& EuclideanVector::createUnitVector() const {
		EuclideanVector *a = new EuclideanVector(*this);
		return *a/=getEuclideanNorm();
}

void EuclideanVector::set(const unsigned int& index, const double & num){
	try{
		v[index] = num;
	}catch (const std::exception &e) {
    	std::cerr << "Error: " << e.what() << '\n';
    	delete [] v;
    	exit(1);
  	}
}

double EuclideanVector::get(const unsigned int & index) const{
	try{
		return v[index];
	} catch (const std::exception &e) {
    	std::cerr << "Error: " << e.what() << '\n';
    	delete [] v;
    	exit(1);
  	}
}

double EuclideanVector::getEuclideanNorm() const{
	try{
		double square_sum = 0.0;
		double square = 0.0;
		for(unsigned int i = 0; i < NumDimensions; ++i){
			square = pow(get(i),2);
			square_sum += square;
		}
		return sqrt(square_sum);
	}catch (const std::exception &e) {
    	std::cerr << "Error: " << e.what() << '\n';
    	delete [] v;
    	exit(1);
  	}
}

double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs){
	double sum = 0.0;
	for(unsigned int i = 0; i < lhs.getNumDimensions(); ++i){
		sum += rhs.get(i)*lhs.get(i);
	}
	return sum;
}


EuclideanVector& EuclideanVector::operator+=(const EuclideanVector &rhs){
	if(getNumDimensions() == rhs.getNumDimensions()){;
		for(unsigned int i = 0; i < getNumDimensions(); ++i){
			set(i,get(i)+rhs.get(i));
		}
	}
	return *this;
}

EuclideanVector& EuclideanVector::operator-=(const EuclideanVector &rhs){
	if(getNumDimensions() == rhs.getNumDimensions()){;
		for(unsigned int i = 0; i < getNumDimensions(); ++i){
			set(i,get(i)-rhs.get(i));
		}
	}
	return *this;
}

EuclideanVector& EuclideanVector::operator*=(const double &rhs){
	for(unsigned int i = 0; i < getNumDimensions(); ++i){
		set(i,get(i)*rhs);
	}
	return *this;
}

EuclideanVector& EuclideanVector::operator/=(const double &rhs){
	if(rhs == 0){
		std::cerr << "Error: 0 Cannot be divided" << '\n';
		exit(1);
	}
	for(unsigned int i = 0; i < getNumDimensions(); ++i){
		set(i,get(i)/rhs);
	}
	return *this;
}

EuclideanVector::operator std::vector<double>() const{
	try{
		std::vector<double> vec;
		for(unsigned int i = 0; i < getNumDimensions(); ++i){
			vec.push_back(v[i]);
		}
		return vec;
	}catch (const std::exception &e) {
    	std::cerr << "Error: " << e.what() << '\n';
    	delete [] v;
    	exit(1);
  	}
}

EuclideanVector::operator std::list<double>() const{
	try{
		std::list<double> l;
		for(unsigned int i = 0; i < getNumDimensions(); ++i){
			l.push_back(v[i]);
		}
		return l;
	}catch (const std::exception &e) {
    	std::cerr << "Error: " << e.what() << '\n';
    	delete [] v;
    	exit(1);
  	}
}

bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs){
	if(&rhs == &lhs) return true;
	if(rhs.getNumDimensions() != lhs.getNumDimensions()) return false;
	for(unsigned int i = 0; i < lhs.getNumDimensions(); ++i){
		if(lhs.get(i) != rhs.get(i)) return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream &os, const EuclideanVector &v){
	if(!v.getNumDimensions()){
		os << "[]";
		return os;
	}
	os << "[";
	for(unsigned int i = 0; i < v.getNumDimensions(); ++i){
		if(i != v.getNumDimensions()-1){
			os << v.get(i) << " ";
		}else{
			os << v.get(i);
		}
	}
	os << "]";
	return os;
}
}


