#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::stod;
using std::vector;
using std::stoi;
using std::string;
using std::to_string;
using std::stack;
using std::stringstream;
using std::setprecision;
using std::fixed;


template <typename A>
inline A add(A const& a,A const& b){
    return a + b;
}
template <typename S>
inline S sub(S const& a,S const& b){
    return a - b;
}
template <typename M>
inline M mult(M const& a,M const& b){
    return a * b;
}
template <typename D>
inline D div(D const& a,D const& b){
    return a / b;
}

// helper functions declearation
void do_calculate(std::vector<string> & s, string const&str);
void readInput(vector<string> & vec, vector<string> const& data);
bool isDouble(string const& a);
bool isDouble(string const& a, string const& b);
void do_reverse(std::vector<string> &v);
void vec_print(std::vector<string> const & v);
bool hasRepeat(std::vector<string> const &v);
void repeat(std::vector<string> &v);
void repeat_vec(vector<string> &v,int const& num);
void do_sqrt(std::vector<string> & vec, string const& str);
void do_format(string &s);

int main(int argc, char* argv[]) {

    // setup the print out format for the precision required.
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);

    // open the file for reading
    std::ifstream in;
    in.open(argv[1]);

    // string to be read into
    std::string s;

    // read the file while we have input.
    std::vector<string> vec;
    std::vector<string> data;

    //store and format the input data
    while(in >> s){
        if(isdigit(s[0]) && isDouble(s)) do_format(s);
        data.push_back(s);
    }
    
    // Process the data and expand the repeat
    while(hasRepeat(data)) {
        repeat(data);
    }
    //vec_print(data);
    // process the input
    readInput(vec,data);

    in.close();
    return 0;
}

void readInput(vector<string> & vec, vector<string> const& data){
    for(const auto & s : data) {
        if (!s.compare("add") || !s.compare("mult") 
                || !s.compare("div") || !s.compare("sub")){
            do_calculate(vec,s);
        }else if(!s.compare("sqrt")){
            do_sqrt(vec,s);
        }else if(!s.compare("pop")){
            vec.pop_back();  
        }else if(!s.compare("reverse")){
            do_reverse(vec);
        }else if(isdigit(s[0])){
            vec.push_back(s);
        }else{
            //ignore the invalid input
            //should I just ignore the invalid input
            //Or print error message and exit the program?
        }
    }
}

void do_calculate(std::vector<string> & vec, string const& str){
    // pop_back twice and get the data reference
    //vec_print(vec);
    const auto a = vec.back();
    vec.pop_back();
    const double A = stod(a);
    const auto b = vec.back();
    const double B = stod(b);
    // case : "sqrt" only requires pop_back once
    if(str != "sqrt") vec.pop_back();
    // get the sign and result
    string sign;
    double result;
    //double check the format
    stringstream stream;
    if (!str.compare("sub")){
        sign = " - ";
        result = sub(A,B);
    }else if(!str.compare("add")){
        sign = " + ";
        result = add(A,B);
    }else if(!str.compare("mult")){
        sign = " * ";
        result = mult(A,B);
    }else{
        sign = " / ";
        result = div(A,B);
    }
    if(isDouble(a,b)){
        cout << a <<  sign << b << " = "<< result << '\n';
        stream << fixed << setprecision(3) << result;
        vec.push_back(stream.str());
    }else{
        cout << a << sign << b << " = "<<(int)result << '\n';
        vec.push_back(to_string((int)result));
    }

}

void do_sqrt(std::vector<string> & vec, string const& str){
    const auto a = vec.back();
    vec.pop_back();
    const double A = stod(a);
    stringstream stream;
    if(isDouble(a)){
        cout << "sqrt " << a << " = "<< sqrt(A) << '\n';
        stream << fixed << setprecision(3) << sqrt(A);
        vec.push_back(stream.str());
    }else{
        cout << "sqrt " << a << " = "<< (int)sqrt(A) << '\n';
        vec.push_back(to_string((int)sqrt(A)));
    }
}

bool isDouble(string const& a){
    return (a.find('.') != std::string::npos) ? true : false;
}

bool isDouble(string const& a, string const& b){
    if(a.find('.') != std::string::npos
            || b.find('.') != std::string::npos){
        return true;
    }
    return false;
}

void do_reverse(std::vector<string> &v){
    if(stoi(v.back()) < 0){
        std::cerr << "Error Invalid Input: The Reverse Offset Cannot be Negative" << '\n';
        exit(1);
    }
    const decltype(v.size()) offset = stoi(v.back());
    v.pop_back();
    if(offset <= v.size()){
        std::reverse(v.end()-offset, v.end());
    }
}


void vec_print(std::vector<string> const & v){
    for(const auto & s : v){
        cout<< s << '\n';
    }
}

void repeat(std::vector<string> &v){
    stack<string> st;
    std::vector<string> temp;
    bool start = false;
    int num = 0;
    int pos = 0;
    int end_pos = 0;
    int i = 0;
    for(auto &s : v){
        if(!s.compare("repeat")){
            if(st.empty()){
                num = stoi(v.at(i-1));
                pos = i;
                start = true;
            }
            st.push("repeat");
        }
        if(!s.compare("endrepeat")){
            st.pop();
            if(st.empty()){
                end_pos = i;
                break;
            }
        }
        if(start){
            temp.push_back(s);
        }
        i++; 
    }
    if(!end_pos){
        std::cerr<< "Error Invalid Input: Repeat Not Nested" << '\n';
        exit(1);
    }
    v.erase(v.begin()+pos-1,v.begin()+end_pos+1);
    repeat_vec(temp,num);
    v.insert(v.begin()+pos-1,temp.begin(),temp.end());
}

void repeat_vec(vector<string> &v,int const& num){
    v.erase(v.begin());
    std::vector<string> temp;
    std::copy(v.begin(), v.end(), std::inserter(temp, temp.end()));
    for(int i = 1; i < num; ++i){
        v.insert(v.end(),temp.begin(),temp.end());
    }
}

bool hasRepeat(std::vector<string> const &v){
    for(const auto &s : v){
        if(!s.compare("repeat")) return true;
    }
    return false;
}

void do_format(string &s){
    stringstream stream;
    stream << fixed << setprecision(3) << stod(s);
    s = stream.str();
}








