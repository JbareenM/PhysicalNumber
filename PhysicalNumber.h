//
//  PhysicalNumber.h
//  PhysicalNumber
//
//  Created by Jeme Jbareen on 4/2/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#ifndef PhysicalNumber_h
#define PhysicalNumber_h

#include <iostream>
#include "Unit.h"
using std::ostream,std::istream;
namespace ariel{
    
    class PhysicalNumber {
    private:
        double _num;
        double Diff(const PhysicalNumber &a);
        Unit _type;
        bool checkType(const PhysicalNumber &a);
        
        
    public:
        int get_num();
        int _group;
        Unit get_type();
        PhysicalNumber(double numb,Unit type):_num(numb),_type(type){
            if(type>=0 && type<=2 && type>=0 && type<=2) _group=1;
            else if(type>=3 && type<=5 && type>=3 && type<=5) _group=2;
            else if(type>=6 && type<=8 && type>=6 && type<=8) _group=3;
        };
        const PhysicalNumber operator+(const PhysicalNumber& a) const;
        const PhysicalNumber operator-(const PhysicalNumber& a) const;
        
        PhysicalNumber& operator+=(const PhysicalNumber& a);
        PhysicalNumber& operator-=(const PhysicalNumber& a);
        
        PhysicalNumber& operator=(const PhysicalNumber& a);
        
        const PhysicalNumber operator+() const ;
        const PhysicalNumber operator-() const ;
        
        const bool operator==(const PhysicalNumber &a);
        const bool operator<(const PhysicalNumber &a);
        
        const bool operator>( const PhysicalNumber &a);
        
        const bool operator<=(const PhysicalNumber &a);
        const bool operator>=(const PhysicalNumber &a);
        const bool operator!=(const PhysicalNumber &a);
        
        PhysicalNumber& operator++ (int);
        PhysicalNumber& operator--(int);
        PhysicalNumber& operator++();
        PhysicalNumber& operator--();
        
        friend std::ostream& operator<< (std::ostream& os, const PhysicalNumber& a);
        friend std::istream& operator>> (std::istream& is, PhysicalNumber& a);
        
    };
    
    std::ostream& operator<< (std::ostream& os, const PhysicalNumber& a);
    std::istream& operator>>(std::istream& is, PhysicalNumber& a);
}
#endif /* PhysicalNumber_h */
