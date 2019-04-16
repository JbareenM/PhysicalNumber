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
        Unit _type;
        double Diff(const PhysicalNumber &a) const;
        bool checkType(const PhysicalNumber &a) const;
        
    public:
        double get_num() const;
        Unit get_type() const;
        PhysicalNumber(double numb,Unit type):_num(numb),_type(type){};
        const PhysicalNumber operator+(const PhysicalNumber& a) const;
        const PhysicalNumber operator-(const PhysicalNumber& a) const;
        
        PhysicalNumber& operator+=(const PhysicalNumber& a);
        PhysicalNumber& operator-=(const PhysicalNumber& a);
        
        PhysicalNumber& operator=(const PhysicalNumber& a);
        
        const PhysicalNumber operator+() const ;
        const PhysicalNumber operator-() const ;
        
        const bool operator==(const PhysicalNumber &a) const;
        const bool operator<(const PhysicalNumber &a) const;
        
        const bool operator>(const PhysicalNumber &a) const;
        
        const bool operator<=(const PhysicalNumber &a) const;
        const bool operator>=(const PhysicalNumber &a) const;
        const bool operator!=(const PhysicalNumber &a) const;
        
        const PhysicalNumber operator++ (int);
        const PhysicalNumber operator--(int);
        PhysicalNumber& operator++();
        PhysicalNumber& operator--();
        
        friend std::ostream& operator<< (std::ostream& os, const PhysicalNumber& a);
        friend std::istream& operator>> (std::istream& is, PhysicalNumber& a);
        
    };
    
    std::ostream& operator<< (std::ostream& os, const PhysicalNumber& a);
    std::istream& operator>>(std::istream& is, PhysicalNumber& a);
}
#endif /* PhysicalNumber_h */
