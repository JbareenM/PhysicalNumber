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
#include <string.h>
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

const PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& a){
    if(!checkType(a))
        throw "you're trying to add two different types!";
    return PhysicalNumber(_num+(Diff(a)*a._num),_type);
}
const PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& a){
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
    return PhysicalNumber(_num,_type);
}
const PhysicalNumber PhysicalNumber::operator-() const {
    return PhysicalNumber(-_num,_type);
}
const bool PhysicalNumber::operator==(const PhysicalNumber& a){
    if(checkType(a))
        if(_num==Diff(a)*a._num)
            return true;
    return false;
}
const bool PhysicalNumber::operator<(const PhysicalNumber &a){
    if(checkType(a))
        if(_num<Diff(a)*a._num)
            return true;
    return false;
}
const bool PhysicalNumber::operator>( const PhysicalNumber &a){
    if(checkType(a))
        if(_num>Diff(a)*a._num)
            return true;
    return false;
}

const bool PhysicalNumber::operator<=(const PhysicalNumber &a){
    if(checkType(a))
        if(_num<=Diff(a)*a._num)
            return true;
    return false;
}
const bool PhysicalNumber::operator>=(const PhysicalNumber &a){
    if(checkType(a))
        if(_num>=Diff(a)*a._num)
            return true;
    return false;
}
const bool PhysicalNumber::operator!=(const PhysicalNumber &a){
    if(checkType(a))
        if(_num!=Diff(a)*a._num)
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
namespace ariel {
    std::ostream& operator<<(std::ostream& os, const PhysicalNumber& a){
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
    double string_double(std::string &s){
        char* str=(char*)malloc(s.length());
        for (int i=0; i<s.length(); i++) {
            str[i]=s[i];
        }
        double a=atof(str);
        free(str);
        return a;
    }
    int string_type(std::string &s){
        char* str=(char*)malloc(s.length()-1);
        for (int i=0; i<s.length()+1; i++) {
            str[i]=s[i];
        }
        if(strstr(str, "km")) return 0;
        else if(strstr(str, "m")) return 1;
        else if(strstr(str, "cm")) return 2;
        else if(strstr(str, "hour")) return 3;
        else if(strstr(str, "min")) return 4;
        else if(strstr(str, "sec")) return 5;
        else if(strstr(str, "ton")) return 6;
        else if(strstr(str, "kg")) return 7;
        free(str);
        return 8;
    }
    std::istream& operator>>(std::istream& is, PhysicalNumber& c){
        std::string input,s;
        is>>input;
        std::istringstream iss(input);
        getline( iss, s, '[' );
        c._num=string_double(s);
        getline( iss, s, ']' );
        c._type=(Unit)string_type(s);
        return is;
    }
}

PhysicalNumber& PhysicalNumber::operator++ (int){
    ++(*this);
    return *this;
}
PhysicalNumber& PhysicalNumber::operator--(int){
    --(*this);
    return *this;
}
