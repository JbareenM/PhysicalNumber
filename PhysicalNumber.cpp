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
            case km:
                if(a._type==km) return 1;
                else if (a._type==m) return 0.001;
                else return 0.00001;
                break;
            case m:
                if(a._type==km) return 1000;
                else if (a._type==m) return 1;
                else return 0.01;
                break;
            case cm:
                if(a._type==km) return 1000*100;
                else if (a._type==m) return 100;
                else return 1;
                break;
            case hour:
                if(a._type==hour) return 1;
                else if (a._type==min) return 0.0166666667;
                else return 0.0002777778;
                break;
            case min:
                if(a._type==hour) return 60;
                else if (a._type==min) return 1;
                else return 0.0166666667;
                break;
            case sec:
                if(a._type==hour) return 60*60;
                else if (a._type==min) return 60;
                else return 1;
                break;
            case ton:
                if(a._type==ton) return 1;
                else if (a._type==kg) return 0.001;
                else return 0.00001;
                break;
            case kg:
                if(a._type==ton) return 1000;
                else if (a._type==kg) return 1;
                else return 1000;
                break;
            case g:
                if(a._type==ton) return 1000*1000;
                else if (a._type==kg) return 1000;
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
    if(!checkType(a))
        throw "can't compare!";
    if(_num==Diff(a)*a._num)
        return true;
    return false;
}
const bool PhysicalNumber::operator<(const PhysicalNumber &a){
    if(!checkType(a))
        throw "can't compare!";
    if(_num<Diff(a)*a._num)
        return true;
    return false;
}
const bool PhysicalNumber::operator>( const PhysicalNumber &a){
    if(!checkType(a))
        throw "can't compare!";
    if(_num>Diff(a)*a._num)
        return true;
    return false;
}

const bool PhysicalNumber::operator<=(const PhysicalNumber &a){
    if(!checkType(a))
        throw "can't compare!";
    if(_num<=Diff(a)*a._num)
        return true;
    return false;
}
const bool PhysicalNumber::operator>=(const PhysicalNumber &a){
    if(!checkType(a))
        throw "can't compare!";
    if(_num>=Diff(a)*a._num)
        return true;
    return false;
}
const bool PhysicalNumber::operator!=(const PhysicalNumber &a){
    if(!checkType(a))
        throw "can't compare!";
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
            case km:
                os<<a._num<<"[km]";
                break;
            case m:
                os<<a._num<<"[m]";
                break;
            case cm:
                os<<a._num<<"[cm]";
                break;
            case hour:
                os<<a._num<<"[hour]";
                break;
            case min:
                os<<a._num<<"[min]";
                break;
            case sec:
                os<<a._num<<"[sec]";
                break;
            case ton:
                os<<a._num<<"[ton]";
                break;
            case kg:
                os<<a._num<<"[kg]";
                break;
            default:
                os<<a._num<<"[g]";
                break;
        }
        return os;
    }
    std::istream& operator>>(std::istream& is, PhysicalNumber& c){
        std::string s;
        is>>s;
        
        return is;
    }
}


