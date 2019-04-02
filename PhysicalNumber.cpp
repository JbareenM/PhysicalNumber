//
//  PhysicalNumber.cpp
//  PhysicalNumber
//
//  Created by Jeme Jbareen on 4/2/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#include "PhysicalNumber.h"
#include "Unit.h"
using namespace ariel;
bool PhysicalNumber::checkType(const PhysicalNumber &a){
    if(_type>=0 && _type<=2 && a._type>=0 && a._type<=2) return true;
    else if(_type>=3 && _type<=5 && a._type>=3 && a._type<=5) return true;
    else if(_type>=6 && _type<=8 && a._type>=6 && a._type<=8) return true;
    return false;
}

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
                os<<a._num<<"[KM]";
                break;
            case M:
                os<<a._num<<"[M]";
                break;
            case CM:
                os<<a._num<<"[CM]";
                break;
            case HOUR:
                os<<a._num<<"[HOUR]";
                break;
            case MIN:
                os<<a._num<<"[MIN]";
                break;
            case SEC:
                os<<a._num<<"[SEC]";
                break;
            case TON:
                os<<a._num<<"[TON]";
                break;
            case KG:
                os<<a._num<<"[KG]";
                break;
            default:
                os<<a._num<<"[G]";
                break;
        }
        return os;
    }
    std::istream& operator>>(std::istream& is, PhysicalNumber& c){
        is>>c._num;
        unsigned int unit = 0;
        is>>unit;
        c._type=(Unit)unit;
        return is;
    }
}


