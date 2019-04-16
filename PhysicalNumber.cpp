//
//  PhysicalNumber.cpp
//  PhysicalNumber
//
//  Created by Jeme Jbareen on 4/2/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#include "PhysicalNumber.h"
#include "Unit.h"
#include <string>
#include <sstream>
#include<vector>
#include <map>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace ariel;
bool PhysicalNumber::checkType(const PhysicalNumber &a){
    if(_type>=0 && _type<=2 && a._type>=0 && a._type<=2) return true;
    else if(_type>=3 && _type<=5 && a._type>=3 && a._type<=5) return true;
    else if(_type>=6 && _type<=8 && a._type>=6 && a._type<=8) return true;
    return false;
}
int PhysicalNumber::get_num(){return _num;}
Unit PhysicalNumber::get_type(){return _type;}
double PhysicalNumber::Diff(const PhysicalNumber &a){
    if(checkType(a)){
        switch (_type) {
            case KM:
                if(a._type==KM) return 1;
                else if (a._type==M) return 0.001;
                else return 0.00001;
                break;
            case M:
                if(a._type==KM) return 1000;
                else if (a._type==M) return 1;
                else return 0.01;
                break;
            case CM:
                if(a._type==KM) return 1000*100;
                else if (a._type==M) return 100;
                else return 1;
                break;
            case HOUR:
                if(a._type==HOUR) return 1;
                else if (a._type==MIN) return 0.0166666667;
                else return 0.0002777778;
                break;
            case MIN:
                if(a._type==HOUR) return 60;
                else if (a._type==MIN) return 1;
                else return 0.0166666667;
                break;
            case SEC:
                if(a._type==HOUR) return 60*60;
                else if (a._type==MIN) return 60;
                else return 1;
                break;
            case TON:
                if(a._type==TON) return 1;
                else if (a._type==KG) return 0.001;
                else return 0.00001;
                break;
            case KG:
                if(a._type==TON) return 1000;
                else if (a._type==KG) return 1;
                else return 1000;
                break;
            case G:
                if(a._type==TON) return 1000*1000;
                else if (a._type==KG) return 1000;
                else return 1;
                break;
            default:
                break;
        }
    }
    return 0;
}

const PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& a) const{
    if(this->_group!=a._group)
        throw "you're trying to add two different types!";
    double res=a._num;
    switch (_type) {
        case KM:
            if(a._type==KM) res*=1;
            else if (a._type==M) res*=0.001;
            else  res*=0.00001;
            break;
        case M:
            if(a._type==KM) res*=1000;
            else if (a._type==M) res*=1;
            else res*=0.01;
            break;
        case CM:
            if(a._type==KM) res*=1000*100;
            else if (a._type==M) res*=100;
            else res*=1;
            break;
        case HOUR:
            if(a._type==HOUR) res*=1;
            else if (a._type==MIN) res*=0.0166666667;
            else res*=0.0002777778;
            break;
        case MIN:
            if(a._type==HOUR) res*=60;
            else if (a._type==MIN) res*=1;
            else res*=0.0166666667;
            break;
        case SEC:
            if(a._type==HOUR) res*=60*60;
            else if (a._type==MIN) res*=60;
            else res*=1;
            break;
        case TON:
            if(a._type==TON) res*=1;
            else if (a._type==KG) res*=0.001;
            else res*=0.00001;
            break;
        case KG:
            if(a._type==TON) res*=1000;
            else if (a._type==KG) res*=1;
            else res*=1000;
            break;
        case G:
            if(a._type==TON) res*=1000*1000;
            else if (a._type==KG) res*=1000;
            else res*=1;
            break;
        default:
            break;
    }
    return PhysicalNumber(_num+res,_type);
}
const PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& a) const{
    if(this->_group!=a._group)
        throw "you're trying to add two different types!";
    double res=a._num;
    switch (_type) {
        case KM:
            if(a._type==KM) res*=1;
            else if (a._type==M) res*=0.001;
            else  res*=0.00001;
            break;
        case M:
            if(a._type==KM) res*=1000;
            else if (a._type==M) res*=1;
            else res*=0.01;
            break;
        case CM:
            if(a._type==KM) res*=1000*100;
            else if (a._type==M) res*=100;
            else res*=1;
            break;
        case HOUR:
            if(a._type==HOUR) res*=1;
            else if (a._type==MIN) res*=0.0166666667;
            else res*=0.0002777778;
            break;
        case MIN:
            if(a._type==HOUR) res*=60;
            else if (a._type==MIN) res*=1;
            else res*=0.0166666667;
            break;
        case SEC:
            if(a._type==HOUR) res*=60*60;
            else if (a._type==MIN) res*=60;
            else res*=1;
            break;
        case TON:
            if(a._type==TON) res*=1;
            else if (a._type==KG) res*=0.001;
            else res*=0.00001;
            break;
        case KG:
            if(a._type==TON) res*=1000;
            else if (a._type==KG) res*=1;
            else res*=1000;
            break;
        case G:
            if(a._type==TON) res*=1000*1000;
            else if (a._type==KG) res*=1000;
            else res*=1;
            break;
        default:
            break;
    }
    return PhysicalNumber(_num-res,_type);
}

PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& a){
    if(!checkType(a))
        throw "you're trying to add two different types!";
    _num+=(Diff(a)*a._num);
    return *this;
}
PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& a){
    if(!checkType(a))
        throw "you're trying to add two different types!";
    _num-=(Diff(a)*a._num);
    return *this;
}
PhysicalNumber& PhysicalNumber::operator=(const PhysicalNumber& a){
    _num=a._num;
    _type=a._type;
    return *this;
}
const PhysicalNumber PhysicalNumber::operator+() const {
    return PhysicalNumber(_num,_type);
}
const PhysicalNumber PhysicalNumber::operator-() const {
    return PhysicalNumber(-_num,_type);
}
const bool PhysicalNumber::operator==(const PhysicalNumber& a){
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(_num==(Diff(a)*a._num))
        return true;
    return false;
}
const bool PhysicalNumber::operator<(const PhysicalNumber &a){
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(_num<(Diff(a)*a._num))
        return true;
    return false;
}
const bool PhysicalNumber::operator>( const PhysicalNumber &a){
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(_num>(Diff(a)*a._num))
        return true;
    return false;
}

const bool PhysicalNumber::operator<=(const PhysicalNumber &a){
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(_num<=(Diff(a)*a._num))
        return true;
    return false;
}
const bool PhysicalNumber::operator>=(const PhysicalNumber &a){
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(_num>=(Diff(a)*a._num))
        return true;
    return false;
}
const bool PhysicalNumber::operator!=(const PhysicalNumber &a){
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(_num!=(Diff(a)*a._num))
        return true;
    return false;
}
PhysicalNumber& PhysicalNumber::operator++(){
    _num++;
    return *this;
}
PhysicalNumber& PhysicalNumber::operator--(){
    _num--;
    return *this;
}

std::ostream& ariel::operator<<(std::ostream& os, const PhysicalNumber& a){
    switch (a._type) {
        case KM:
            os<<a._num<<"[km]";
            break;
        case M:
            os<<a._num<<"[m]";
            break;
        case CM:
            os<<a._num<<"[cm]";
            break;
        case HOUR:
            os<<a._num<<"[hour]";
            break;
        case MIN:
            os<<a._num<<"[min]";
            break;
        case SEC:
            os<<a._num<<"[sec]";
            break;
        case TON:
            os<<a._num<<"[ton]";
            break;
        case KG:
            os<<a._num<<"[kg]";
            break;
        default:
            os<<a._num<<"[g]";
            break;
    }
    return os;
}

Unit get_type(const std::string s){
    static std::map<std::string, Unit> string_type{
        {"CM", ariel::CM},
        {"M", ariel::M},
        {"KM", ariel::KM},
        {"SEC", ariel::SEC},
        {"MIN", ariel::MIN},
        {"HOUR", ariel::HOUR},
        {"G", ariel::G},
        {"KG", ariel::KG},
        {"TON", ariel::TON},
        
    };
    auto x = string_type.find(s);
    if (x != end(string_type)){
        return x->second;
    }
    throw std::invalid_argument(s);
}
istream &ariel::operator>>(istream &is, PhysicalNumber &a)
{
    std::string str;
    is >> str;
    if (str.find("]") == -1 || str.find("[") == -1 || str.find("[]")!=-1){
        return is;
    }
    str = str.substr(0, str.length() - 1);
    std::stringstream ss(str);
    std::vector<std::string> result;
    
    while (ss.good()){
        std::string substr;
        getline(ss, substr, '[');
        result.push_back(substr);
    }
    double val=0;
    try{
        val = stod(result[0]);
        std::transform(result[1].begin(), result[1].end(), result[1].begin(), ::toupper);
    }
    catch(...){
        return is;
    }
    Unit un =Unit::CM;
    const std::string type = result[1];
    try{
        un = get_type(type);
    }
    catch(...){
        return is;
    }
    a = PhysicalNumber(val, un);
    return is;
}


PhysicalNumber& PhysicalNumber::operator++ (int){
    ++(*this);
    return *this;
}
PhysicalNumber& PhysicalNumber::operator--(int){
    --(*this);
    return *this;
}
