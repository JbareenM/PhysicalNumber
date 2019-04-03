#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
    badkan::TestCase testcase;
    int grade=0;
    int signal = setjmp(badkan::longjmp_buffer);
    if (signal == 0) {
        
        // BASIC TESTS - DO NOT CHANGE
        PhysicalNumber a(2, Unit::KM);
        PhysicalNumber b(300, Unit::M);
        PhysicalNumber c(2, Unit::HOUR);
        PhysicalNumber d(30, Unit::MIN);
        
        testcase
        .setname("Basic output")
        .CHECK_OUTPUT(a, "2[km]")
        .CHECK_OUTPUT(b, "300[m]")
        
        .setname("Compatible dimensions")
        .CHECK_OUTPUT(b+a, "2300[m]")
        .CHECK_OUTPUT((a+=b), "2.3[km]")
        .CHECK_OUTPUT(a, "2.3[km]")
        .CHECK_OUTPUT(a+a, "4.6[km]")
        .CHECK_OUTPUT(b-b, "0[m]")
        .CHECK_OUTPUT(c, "2[hour]")
        .CHECK_OUTPUT(d, "30[min]")
        .CHECK_OUTPUT(d+c, "150[min]")
        
        .setname("Incompatible dimensions")
        .CHECK_THROWS(a+c)
        .CHECK_THROWS(a+d)
        .CHECK_THROWS(b+c)
        .CHECK_THROWS(b+d)
        
        .setname("Basic input")
        .CHECK_OK(istringstream("700[kg]") >> a)
        .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")
        
        // YOUR TESTS - INSERT AS MANY AS YOU WANT
        .CHECK_OUTPUT((a++), "1701[kg]")
        .CHECK_THROWS(a+PhysicalNumber(300,Unit::HOUR))
        .CHECK_THROWS(PhysicalNumber(300,Unit::HOUR)+PhysicalNumber(300,Unit::G))
        .CHECK_THROWS(PhysicalNumber(300,Unit::SEC)+PhysicalNumber(300,Unit::TON))
        .CHECK_THROWS(PhysicalNumber(300,Unit::KM)+PhysicalNumber(300,Unit::HOUR))
        .CHECK_THROWS(PhysicalNumber(300,Unit::HOUR)+PhysicalNumber(300,Unit::M))
        .CHECK_OUTPUT(PhysicalNumber(3,Unit::HOUR)+PhysicalNumber(300,Unit::MIN), "8[hour]")
        .CHECK_OUTPUT(PhysicalNumber(300,Unit::MIN)+PhysicalNumber(3,Unit::HOUR), "480[min]")
        .CHECK_OK(a=PhysicalNumber(300,Unit::HOUR))
        .CHECK_OUTPUT(a, "300[hour]")
        .CHECK_OK(++a)
        .CHECK_OUTPUT(a, "301[hour]")
        .CHECK_OK(a--)
        .CHECK_OUTPUT(a, "300[hour]")
        .CHECK_OK(--a)
        .CHECK_OUTPUT(a, "299[hour]")
        .CHECK_OK(a-=PhysicalNumber(200,Unit::HOUR))
        .CHECK_OUTPUT(a, "99[hour]")
        .CHECK_OK(istringstream("700[min]") >> b)
        .CHECK_OUTPUT((b) , "700[min]")
        .CHECK_OUTPUT((a<b) , "0")
        .CHECK_OUTPUT((a>=b) , "1")
        .CHECK_OK(istringstream("700[m]") >> b)
        .CHECK_OUTPUT((b) , "700[m]")
        .CHECK_THROWS(a<b)
        .CHECK_THROWS(a>=b)
        .CHECK_THROWS(a-b)
        .CHECK_THROWS(a-=b)
        .CHECK_OK(b=-b)
        .CHECK_OUTPUT((b) , "-700[m]")
        .CHECK_OUTPUT((-b) , "700[m]")
        
        .setname("...")
        
        .print(cout, /*show_grade=*/false);
        grade = testcase.grade();
    } else {
        testcase.print_signal(signal);
        grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
