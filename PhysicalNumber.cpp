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

bool PhysicalNumber::checkType(const PhysicalNumber &a) const{
    if(this->_type>=0 && this->_type<=2 && a._type>=0 && a._type<=2) return true;
    else if(this->_type>=3 && this->_type<=5 && a._type>=3 && a._type<=5) return true;
    else if(this->_type>=6 && this->_type<=8 && a._type>=6 && a._type<=8) return true;
    return false;
}
double PhysicalNumber::get_num() const{return _num;}
Unit PhysicalNumber::get_type() const{return _type;}
double PhysicalNumber::Diff(const PhysicalNumber &a) const{
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
                else if (a._type==MIN) return 0.016666666666667;
                else return 0.000277777777778;
                break;
            case MIN:
                if(a._type==HOUR) return 60;
                else if (a._type==MIN) return 1;
                else return 0.016666666666667;
                break;
            case SEC:
                if(a._type==HOUR) return 60*60;
                else if (a._type==MIN) return 60;
                else return 1;
                break;
            case TON:
                if(a._type==TON) return 1;
                else if (a._type==KG) return 0.001;
                else return 0.000001;
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
double Diff(const PhysicalNumber &a){
    switch (a.get_type()) {
        case KM:
            return 100000;
            break;
        case M:
            return 100;
            break;
        case CM:
            break;
        case HOUR:
            return 3600;
            break;
        case MIN:
            return 60;
            break;
        case SEC:
            break;
        case TON:
            return 1000000;
            break;
        case KG:
            return 1000;
            break;
        case G:
            break;
        default:
            return 1;
            break;
    }
    return 1;
}
const PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& a) const{
    if(!checkType(a))
        throw "you're trying to add two different types!";
    double val=::Diff(a)*a._num + ::Diff(*(this))*_num;
    val/=::Diff(*(this));
    return PhysicalNumber(val,_type);
}
const PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& a) const{
    if(!checkType(a))
        throw "you're trying to add two different types!";
    return PhysicalNumber(_num-Diff(a)*a._num,_type);
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
    return *(this);
}
const PhysicalNumber PhysicalNumber::operator-() const {
    return PhysicalNumber(-_num,_type);
}
const bool PhysicalNumber::operator==(const PhysicalNumber &a) const{
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(::Diff(*(this))*_num==(::Diff(a)*a._num))
        return true;
    return false;
}
const bool PhysicalNumber::operator<(const PhysicalNumber &a) const{
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(::Diff(*(this))*_num<(::Diff(a)*a._num))
        return true;
    return false;
}
const bool PhysicalNumber::operator>(const PhysicalNumber &a) const{
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(::Diff(*(this))*_num>(::Diff(a)*a._num))
        return true;
    return false;
}
const bool PhysicalNumber::operator<=(const PhysicalNumber &a) const{
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(::Diff(*(this))*_num<=(::Diff(a)*a._num))
        return true;
    return false;
}
const bool PhysicalNumber::operator>=(const PhysicalNumber &a) const{
    if(!checkType(a))
        throw "you're trying to comparee two different types!";
    if(::Diff(*(this))*_num>=(::Diff(a)*a._num))
        return true;
    return false;
}
const bool PhysicalNumber::operator!=(const PhysicalNumber &a) const{return !(*(this)==a);}

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


const PhysicalNumber PhysicalNumber::operator++ (int){
    PhysicalNumber a(*(this));
    ++*(this);
    return a;
}
const PhysicalNumber PhysicalNumber::operator--(int){
    PhysicalNumber a(*(this));
    --*(this);
    return a;
}
