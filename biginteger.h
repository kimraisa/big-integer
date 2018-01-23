//
//  main.cpp
//  task4_ProbA_BigInteger
//
//  Created by Raisa Kim on 05.12.2017.
//  Copyright © 2017 Raisa Kim. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BigInteger;

BigInteger operator + (const BigInteger& a, const BigInteger& b);
BigInteger operator - (const BigInteger& a, const BigInteger& b);
BigInteger operator * (const BigInteger & a, int b);
BigInteger operator * (const BigInteger & a, const BigInteger & b);
int FindDigit(const BigInteger & a, const BigInteger & b, size_t dif);
BigInteger operator / (const BigInteger & a, const BigInteger & b);
BigInteger operator % (const BigInteger & a, const BigInteger & b);

bool operator >= (const BigInteger & a, const BigInteger & b);
bool operator < (const BigInteger& a, const BigInteger& b);
bool operator <= (const BigInteger & a, const BigInteger & b);
bool operator > (const BigInteger & a, const BigInteger & b);
bool operator != (const BigInteger & a, const BigInteger & b);
bool operator == (const BigInteger & a, const BigInteger & b);


istream & operator >> (istream & c, BigInteger & a);
ostream & operator << (ostream & c, const BigInteger & a);

class BigInteger{
    int c = 10;
    vector <int> myint;
    bool s;
public:
    BigInteger(): s(true) {}
    
    BigInteger(const int& x){
        while(myint.size() != 0){
            myint.pop_back();
        }
        if(x == 0){
            myint.push_back(0);
            s = true;
        }
        int x_ = x;
        if(x > 0){
            s = true;
        }
        else{
            s = false;
            x_ = -x;
        }
        while(x_ != 0){
            myint.push_back((x_ % 10 + 10) % 10);
            x_ = x_ / 10;
        }
    }
    
    BigInteger (const BigInteger & a): myint(a.myint), s(a.s){}
    
    BigInteger(const string & str){
        while(myint.size() != 0){
            myint.pop_back();
        }
        if(str.size() == 0){
            return;
        }
        if(str[0] == '-'){
            s = false;
        }
        else{
            s = true;
        }
        for(size_t i = 0 ; i < str.size(); ++i){
            if(str[str.size() - 1 - i] != '-'){
                myint.push_back(str[str.size() - 1 - i] - '0');
            }
        }
    }
    
    BigInteger& operator = (const BigInteger & a){
        s = a.s;
        myint = a.myint;
        return *this;
    }
    
    const string toString() const {
        string str;
        if(myint.size() == 0){
            str.push_back('0');
        }
        if(!s && myint.size() > 0){
            str.push_back('-');
        }
        if(myint.size() == 1 && myint[0] == 0 && str.size() > 0){
            str.pop_back();
        }
        for(size_t i = 0; i < myint.size(); ++i){
            size_t j = myint.size() - 1 - i;
            str.push_back(myint[j] + '0');
        }
        return str;
    }
    
    explicit operator bool() const{
        if(myint.size() == 0){
            return false;
        }
        return myint[myint.size() - 1] ? true : false;
    }
    
    const BigInteger abs() const {
        BigInteger helper = *this;
        helper.s = true;
        return helper;
    }
    
    const BigInteger operator - () const{
        BigInteger helper;
        helper.myint = myint;
        if(myint.size() == 0){
            helper.myint.push_back(0);
            helper.s = true;
            return helper;
        }
        if(myint[myint.size() - 1] != 0){
            helper.s = !s;
        }
        return helper;
    }
    //prefix increase
    BigInteger& operator++(){
        *this += 1;
        return *this;
    }
    //postfix increase
    const BigInteger operator++(int){
        BigInteger old  = *this;
        ++(*this);
        return old;
    }
    //prefix decrease
    BigInteger& operator--(){
        *this -= 1;
        return *this;
    }
    //postfix decrease
    const BigInteger operator--(int){
        BigInteger old = *this;
        --(*this);
        return old;
    }
    
    BigInteger& operator +=(const BigInteger & a){
        //   cerr << *this << " " << a;
        if( s == a.s ){
            int x = 0;
            for(size_t i = 0; i < a.myint.size(); ++i){
                if(i < myint.size()){
                    x = x + a.myint[i] + myint[i];
                    myint[i] = (x % 10 + 10) % 10;
                    x = x / 10;
                }
                else{
                    x = x + a.myint[i];
                    myint.push_back( (x % 10 + 10) % 10);
                    x = x / 10;
                }
            }
            size_t j = a.myint.size();
            while(x != 0){
                if(j < myint.size()){
                    x = x + myint[j];
                    myint[j] = (x % 10 + 10) % 10;
                    x = x / 10;
                    j++;
                }
                else{
                    myint.push_back((x % 10 + 10) % 10);
                    x = x / 10;
                    j++;
                }
            }
            return *this;
        }
        else{
            s = !s;
            *this -= a;
            s = !s;
        }
        return *this;
    }
    
    BigInteger& operator -=(const BigInteger & a){
        if( s == a.s ){
            if(abs() == a.abs()){
                s = true;
                while(myint.size() != 0){
                    myint.pop_back();
                }
                myint.push_back(0);
                return *this;
            }
            if( abs() > a.abs() ){
                for(size_t i = 0; i < a.myint.size(); ++i){
                    myint[i] = myint[i] - a.myint[i];
                }
            }
            else{
                s = !s;
                for(size_t i = 0; i < myint.size(); ++i){
                    myint[i] = a.myint[i] - myint[i];
                }
                for(size_t i = myint.size(); i < a.myint.size(); ++i){
                    myint.push_back(a.myint[i]);
                }
            }
            
            for(size_t i = 0; i < (myint.size() - 1); ++i){
                if(myint[i] < 0){
                    myint[i] = 10 + myint[i];
                    myint[i + 1]--;
                }
            }
            
            if(myint.size() == 0){
                return *this;
            }
            
            while(myint[myint.size() - 1] == 0 && myint.size() > 1){
                myint.pop_back();
            }
            
        }
        else{
            s = !s;
            *this += a;
            s = !s;
        }
        return *this;
    }
    
    BigInteger multiplyDigit(int digit, size_t shift) const{
        BigInteger result;
        result.s = true;
        int x = 0;
        for(size_t i = 0; i < shift; ++i){
            result.myint.push_back(0);
        }
        for(size_t i  = 0; i < myint.size(); ++i){
            x = x + digit * myint[i];
            result.myint.push_back((x % 10 + 10) % 10);
            x = x / 10;
        }
        while(x != 0){
            result.myint.push_back((x % 10 + 10) % 10);
            x = x / 10;
        }
        return result;
    }
    
    BigInteger& operator *= (const BigInteger & a){
        if(*this == 0){
            return *this;
        }
        if(a == 0){
            *this = 0;
            return *this;
        }
        BigInteger result(0);
        int digit = 0;
        size_t shift = 0;
        for(size_t i = 0; i < a.myint.size(); ++i){
            digit = a.myint[i];
            shift = i;
            result += multiplyDigit(digit, shift);
        }
        if(s == a.s){
            result.s = true;
        }
        else{
            result.s = false;
        }
        *this = result;
        return *this;
    }
    
    BigInteger & operator /= (const BigInteger & other){
        if(*this == 0){
            return *this;
        }
        if(other == 0){
            *this = 0;
            return *this;
        }
        if( abs() < other.abs() ){
            *this = 0;
            s = true;
            return *this;
        }
        bool sRight;
        if(s == other.s){
            sRight = true;
        }
        else{
            sRight = false;
        }
        s = true;
        vector<int> result;
        BigInteger helper = other;
        helper.s = true;
        //size_t dif = myint.size() - other.myint.size();
        for(size_t i = 0; i < (myint.size() - other.myint.size()); ++i){
            helper *= 10;
        }
        for(size_t i = 0; i < 100 * myint.size(); ++i){
            if(helper.myint.size() < other.myint.size()){
                break;
            }
            //cout << "la";
            result.push_back(0);
            while(*this >= helper){
                result.back()++;
                *this -= helper;
            }
            for(size_t j = 0; j < (helper.myint.size() - 1); ++j){
                helper.myint[j] = helper.myint[j + 1];
            }
            helper.myint.pop_back();
        }
        while(myint.size() != 0){
            myint.pop_back();
        }
        for(size_t i = 0; i < result.size(); ++i){
            size_t j = result.size() - 1 - i;
            myint.push_back(result[j]);
        }
        
        if(myint.size() == 0){
            s = true;
            return *this;
        }
        
        while(myint[myint.size() - 1] == 0 && myint.size() > 1){
            myint.pop_back();
        }
        s = sRight;
        return *this;
    }
    
    BigInteger & operator %= (const BigInteger & a){
        *this -= (*this / a) * a;
        return *this;
    }
    
    int compareAbs(const BigInteger & other) const {
        //1 если наше число больше, 0 если равны, -1 если наше число меньше
        if(myint.size() != other.myint.size()){
            return myint.size() > other.myint.size() ? 1 : -1;
        }
        for(size_t i = 0; i < myint.size(); ++i){
            size_t j = myint.size() - 1 - i;
            if(myint[j] != other.myint[j]){
                return myint[j] > other.myint[j] ? 1 : -1;
            }
        }
        return 0;
    }
    
    int compare(const BigInteger & other) const {
        if(compareAbs(other) == 0){
            if(myint.size() == 0){
                return 0;
            }
            if(myint.back() == 0){
                return 0;
            }
        }
        if(s != other.s){
            return (s > other.s) ? 1 : -1;
        }
        return (s) ? compareAbs(other) : compareAbs(other)*(-1);
    }
};


bool operator >= (const BigInteger & a, const BigInteger & b){
    //done
    return a.compare(b) >= 0 ? true : false;
}

bool operator < (const BigInteger& a, const BigInteger& b){
    return a.compare(b) < 0 ? true : false;
}

bool operator <= (const BigInteger & a, const BigInteger & b){
    return a.compare(b) <= 0 ? true : false;
}

bool operator > (const BigInteger & a, const BigInteger & b){
    return a.compare(b) > 0 ? true : false;
}

bool operator != (const BigInteger & a, const BigInteger & b){
    return a.compare(b) != 0 ? true : false;
}

bool operator == (const BigInteger & a, const BigInteger & b){
    return a.compare(b) == 0 ? true : false;
}


BigInteger operator + (const BigInteger& a, const BigInteger& b){
    BigInteger result = a;
    result += b;
    return result;
}
BigInteger operator - (const BigInteger& a, const BigInteger& b){
    BigInteger result = a;
    result -= b;
    return result;
}

BigInteger operator * (const BigInteger & a, const BigInteger & b){
    BigInteger result = a;
    result *= b;
    return result;
}

BigInteger operator / (const BigInteger & a, const BigInteger & b){
    BigInteger result = a;
    result /= b;
    return result;
}

BigInteger operator % (const BigInteger & a, const BigInteger & b){
    BigInteger result = a;
    result %= b;
    return result;
}

istream & operator >> (istream & c, BigInteger & a){
    string str;
    c >> str;
    a = BigInteger(str);
    return c;
}

ostream & operator << (ostream & c, const BigInteger & a){
    c << a.toString();
    return c;
}

/*int main(int argc, const char * argv[]) {
 // insert code here...
string s1, s2;
cin >> s1;
 cin >> s2;
 BigInteger a(s1);
 BigInteger b(s2);
    cout << a % b;
 return 0;
 }
*/

