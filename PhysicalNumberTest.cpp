/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main()
{
    badkan::TestCase testcase;
    int grade = 0;
    int signal = setjmp(badkan::longjmp_buffer);
    if (signal == 0)
    {
        // BASIC TESTS - DO NOT CHANGE
        PhysicalNumber a(2, Unit::KM);
        PhysicalNumber b(300, Unit::M);
        PhysicalNumber c(2, Unit::HOUR);
        PhysicalNumber d(30, Unit::MIN);
        // CUSTOM TESTING
        // Length
        PhysicalNumber cm(10.0, Unit::CM);
        PhysicalNumber met(5.3, Unit::M);
        PhysicalNumber km(3.3, Unit::KM);
        // Time
        PhysicalNumber s(30.5, Unit::SEC);
        PhysicalNumber min(5, Unit::MIN);
        PhysicalNumber h(2, Unit::HOUR);
        // Weight
        PhysicalNumber g(10.0, Unit::G);
        PhysicalNumber kg(5.3, Unit::KG);
        PhysicalNumber t(3.3, Unit::TON);
        
        bool x;
        
        testcase
        .setname("Basic output")
        .CHECK_OUTPUT(a, "2[km]")
        .CHECK_OUTPUT(b, "300[m]")
        
        .setname("Compatible dimensions")
        .CHECK_OUTPUT(b + a, "2300[m]")
        .CHECK_OUTPUT((a += b), "2.3[km]")
        .CHECK_OUTPUT(a, "2.3[km]")
        .CHECK_OUTPUT(a + a, "4.6[km]")
        .CHECK_OUTPUT(b - b, "0[m]")
        .CHECK_OUTPUT(c, "2[hour]")
        .CHECK_OUTPUT(d, "30[min]")
        .CHECK_OUTPUT(d + c, "150[min]")
        
        .setname("Incompatible dimensions")
        .CHECK_THROWS(a + c)
        .CHECK_THROWS(a + d)
        .CHECK_THROWS(b + c)
        .CHECK_THROWS(b + d)
        
        .setname("Basic input")
        .CHECK_OK(istringstream("700[kg]") >> a)
        .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")
        
        // YOUR TESTS - INSERT AS MANY AS YOU WANT
        // CUSTOM TESTS
        .setname("Compatiblility")
        .setname("Length with TIME")
        // CM
        .CHECK_THROWS(cm + s)
        .CHECK_THROWS(cm + min)
        .CHECK_THROWS(cm + h)
        .CHECK_THROWS(cm - s)
        .CHECK_THROWS(cm - min)
        .CHECK_THROWS(cm - h)
        .CHECK_THROWS(x = cm > s)
        .CHECK_THROWS(x = cm < s)
        .CHECK_THROWS(x = cm >= s)
        .CHECK_THROWS(x = cm <= s)
        .CHECK_THROWS(x = cm != s)
        .CHECK_THROWS(x = cm == s)
        .CHECK_THROWS((cm += PhysicalNumber(1, Unit::SEC)))
        .CHECK_THROWS((cm += PhysicalNumber(0, Unit::SEC)))
        .CHECK_THROWS((cm += PhysicalNumber(-1, Unit::SEC)))
        .CHECK_THROWS((cm += PhysicalNumber(100, Unit::SEC)))
        .CHECK_THROWS((cm -= PhysicalNumber(1, Unit::SEC)))
        .CHECK_THROWS((cm -= PhysicalNumber(0, Unit::SEC)))
        .CHECK_THROWS((cm -= PhysicalNumber(-1, Unit::SEC)))
        .CHECK_THROWS((cm -= PhysicalNumber(100, Unit::SEC)))
        .CHECK_THROWS(x = cm > min)
        .CHECK_THROWS(x = cm < min)
        .CHECK_THROWS(x = cm >= min)
        .CHECK_THROWS(x = cm <= min)
        .CHECK_THROWS(x = cm != min)
        .CHECK_THROWS(x = cm == min)
        .CHECK_THROWS((cm += PhysicalNumber(1, Unit::MIN)))
        .CHECK_THROWS((cm += PhysicalNumber(0, Unit::MIN)))
        .CHECK_THROWS((cm += PhysicalNumber(-1, Unit::MIN)))
        .CHECK_THROWS((cm += PhysicalNumber(100, Unit::MIN)))
        .CHECK_THROWS((cm -= PhysicalNumber(1, Unit::MIN)))
        .CHECK_THROWS((cm -= PhysicalNumber(0, Unit::MIN)))
        .CHECK_THROWS((cm -= PhysicalNumber(-1, Unit::MIN)))
        .CHECK_THROWS((cm -= PhysicalNumber(100, Unit::MIN)))
        .CHECK_THROWS(x = cm > h)
        .CHECK_THROWS(x = cm < h)
        .CHECK_THROWS(x = cm >= h)
        .CHECK_THROWS(x = cm <= h)
        .CHECK_THROWS(x = cm != h)
        .CHECK_THROWS(x = cm == h)
        .CHECK_THROWS((cm += PhysicalNumber(1, Unit::HOUR)))
        .CHECK_THROWS((cm += PhysicalNumber(0, Unit::HOUR)))
        .CHECK_THROWS((cm += PhysicalNumber(-1, Unit::HOUR)))
        .CHECK_THROWS((cm += PhysicalNumber(100, Unit::HOUR)))
        .CHECK_THROWS((cm -= PhysicalNumber(1, Unit::HOUR)))
        .CHECK_THROWS((cm -= PhysicalNumber(0, Unit::HOUR)))
        .CHECK_THROWS((cm -= PhysicalNumber(-1, Unit::HOUR)))
        .CHECK_THROWS((cm -= PhysicalNumber(100, Unit::HOUR)))
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        .setname("Basic output")
        // Length output
        .CHECK_OUTPUT(cm, "10[cm]")
        .CHECK_OUTPUT(met, "5.3[m]")
        .CHECK_OUTPUT(km, "3.3[km]")
        // Time output
        .CHECK_OUTPUT(s, "30.5[sec]")
        .CHECK_OUTPUT(min, "5[min]")
        .CHECK_OUTPUT(h, "2[hour]")
        // Weight ouput
        .CHECK_OUTPUT(g, "10[g]")
        .CHECK_OUTPUT(kg, "5.3[kg]")
        .CHECK_OUTPUT(t, "3.3[ton]")
        .setname("Compatible dimensions: Length")
        // CM with CM
        .CHECK_OUTPUT(cm + cm, "20[cm]")
        .CHECK_OUTPUT((cm += cm), "20[cm]")
        .CHECK_OUTPUT(cm, "20[cm]")
        .CHECK_OK(istringstream("10[cm]") >> cm)
        .CHECK_OUTPUT(cm - cm, "0[cm]")
        .CHECK_OUTPUT((cm -= cm), "0[cm]")
        .CHECK_OUTPUT(cm, "0[cm]")
        .CHECK_OK(istringstream("10.0[cm]") >> cm)
        .CHECK_EQUAL(cm, PhysicalNumber(10, Unit::CM))
        .CHECK_EQUAL(cm == cm, true)
        .CHECK_EQUAL(cm >= cm, true)
        .CHECK_EQUAL(cm <= cm, true)
        .CHECK_EQUAL(cm < cm, false)
        .CHECK_EQUAL(cm > cm, false)
        // CM with METER
        .CHECK_OUTPUT(cm + met, "540[cm]")
        .CHECK_OUTPUT((cm += met), "540[cm]")
        .CHECK_OUTPUT(cm, "540[cm]")
        .CHECK_OK(istringstream("10.0[cm]") >> cm)
        .CHECK_OUTPUT(cm - met, "-520[cm]")
        .CHECK_OUTPUT((cm -= met), "-520[cm]")
        .CHECK_OUTPUT(cm, "-520[cm]")
        .CHECK_OK(istringstream("10.0[cm]") >> cm)
        .CHECK_EQUAL(cm, PhysicalNumber(0.1, Unit::M))
        .CHECK_EQUAL(cm != met, true)
        .CHECK_EQUAL(cm == met, false)
        .CHECK_EQUAL(cm >= met, false)
        .CHECK_EQUAL(cm <= met, true)
        .CHECK_EQUAL(cm > met, false)
        .CHECK_EQUAL(cm < met, true)
        // CM with KM
        .CHECK_OUTPUT(cm + km, "330010[cm]")
        .CHECK_OUTPUT((cm += km), "330010[cm]")
        .CHECK_OUTPUT(cm, "330010[cm]")
        .CHECK_OK(istringstream("10.0[cm]") >> cm)
        .CHECK_OUTPUT(cm - km, "-329990[cm]")
        .CHECK_OUTPUT((cm -= km), "-329990[cm]")
        .CHECK_OUTPUT(cm, "-329990[cm]")
        .CHECK_OK(istringstream("10.0[cm]") >> cm)
        .CHECK_EQUAL(cm, PhysicalNumber(0.0001, Unit::KM))
        .CHECK_EQUAL(cm != km, true)
        .CHECK_EQUAL(cm == km, false)
        .CHECK_EQUAL(cm >= km, false)
        .CHECK_EQUAL(cm <= km, true)
        .CHECK_EQUAL(cm > km, false)
        .CHECK_EQUAL(cm < km, true)
        ///////////////////////////////////////////////////////////
        // METER with CM
        .CHECK_OUTPUT(met + cm, "5.4[m]")
        .CHECK_OUTPUT((met += cm), "5.4[m]")
        .CHECK_OUTPUT(met, "5.4[m]")
        .CHECK_OK(istringstream("5.3[m]") >> met)
        .CHECK_OUTPUT(met - cm, "5.2[m]")
        .CHECK_OUTPUT((met -= cm), "5.2[m]")
        .CHECK_OUTPUT(met, "5.2[m]")
        .CHECK_OK(istringstream("5.3[m]") >> met)
        .CHECK_EQUAL(met, PhysicalNumber(530, Unit::CM))
        .CHECK_EQUAL(met != cm, true)
        .CHECK_EQUAL(met == cm, false)
        .CHECK_EQUAL(met >= cm, true)
        .CHECK_EQUAL(met <= cm, false)
        .CHECK_EQUAL(met > cm, true)
        .CHECK_EQUAL(met < cm, false)
        // METER with METER
        .CHECK_OUTPUT(met + met, "10.6[m]")
        .CHECK_OUTPUT((met += met), "10.6[m]")
        .CHECK_OUTPUT(met, "10.6[m]")
        .CHECK_OK(istringstream("5.3[m]") >> met)
        .CHECK_OUTPUT(met - met, "0[m]")
        .CHECK_OUTPUT((met -= met), "0[m]")
        .CHECK_OUTPUT(met, "0[m]")
        .CHECK_OK(istringstream("5.3[m]") >> met)
        .CHECK_EQUAL(met == met, true)
        .CHECK_EQUAL(met != met, false)
        .CHECK_EQUAL(met >= met, true)
        .CHECK_EQUAL(met <= met, true)
        .CHECK_EQUAL(met > met, false)
        .CHECK_EQUAL(met < met, false)
        // METER with KM
        .CHECK_OUTPUT(met + km, "3305.3[m]")
        .CHECK_OUTPUT((met += km), "3305.3[m]")
        .CHECK_OUTPUT(met, "3305.3[m]")
        .CHECK_OK(istringstream("5.3[m]") >> met)
        .CHECK_OUTPUT(met - km, "-3294.7[m]")
        .CHECK_OUTPUT((met -= km), "-3294.7[m]")
        .CHECK_OUTPUT(met, "-3294.7[m]")
        .CHECK_OK(istringstream("5.3[m]") >> met)
        .CHECK_EQUAL(met, PhysicalNumber(0.0053, Unit::KM))
        .CHECK_EQUAL(met != km, true)
        .CHECK_EQUAL(met == km, false)
        .CHECK_EQUAL(met >= km, false)
        .CHECK_EQUAL(met <= km, true)
        .CHECK_EQUAL(met > km, false)
        .CHECK_EQUAL(met < km, true)
        ///////////////////////////////////////////////////////////
        // KM with CM
        .CHECK_OUTPUT(km + cm, "3.3001[km]")
        .CHECK_OUTPUT((km += cm), "3.3001[km]")
        .CHECK_OUTPUT(km, "3.3001[km]")
        .CHECK_OK(istringstream("3.3[km]") >> km)
        .CHECK_OUTPUT(km - cm, "3.2999[km]")
        .CHECK_OUTPUT((km -= cm), "3.2999[km]")
        .CHECK_OUTPUT(km, "3.2999[km]")
        .CHECK_OK(istringstream("3.3[km]") >> km)
        .CHECK_EQUAL(km,PhysicalNumber(330000, Unit::CM))
        .CHECK_EQUAL(km != cm, true)
        .CHECK_EQUAL(km == cm, false)
        .CHECK_EQUAL(km >= cm, true)
        .CHECK_EQUAL(km <= cm, false)
        .CHECK_EQUAL(km > cm, true)
        .CHECK_EQUAL(km < cm, false)
        // KM with METER
        .CHECK_OUTPUT(km + met, "3.3053[km]")
        .CHECK_OUTPUT((km += met), "3.3053[km]")
        .CHECK_OUTPUT(km, "3.3053[km]")
        .CHECK_OK(istringstream("3.3[km]") >> km)
        .CHECK_OUTPUT(km - met, "3.2947[km]")
        .CHECK_OUTPUT((km -= met), "3.2947[km]")
        .CHECK_OUTPUT(km, "3.2947[km]")
        .CHECK_OK(istringstream("3.3[km]") >> km)
        .CHECK_EQUAL(PhysicalNumber(330000, Unit::CM),km)
        .CHECK_EQUAL(PhysicalNumber(3300, Unit::M),km)
        .CHECK_EQUAL(km != cm, true)
        .CHECK_EQUAL(km == cm, false)
        .CHECK_EQUAL(km >= cm, true)
        .CHECK_EQUAL(km <= cm, false)
        .CHECK_EQUAL(km > cm, true)
        .CHECK_EQUAL(km < cm, false)
        // KM with KM
        .CHECK_OUTPUT(km + km, "6.6[km]")
        .CHECK_OUTPUT((km += km), "6.6[km]")
        .CHECK_OUTPUT(km, "6.6[km]")
        .CHECK_OK(istringstream("3.3[km]") >> km)
        .CHECK_OUTPUT(km - km, "0[km]")
        .CHECK_OUTPUT((km -= km), "0[km]")
        .CHECK_OUTPUT(km, "0[km]")
        .CHECK_OK(istringstream("3.3[km]") >> km)
        .CHECK_EQUAL(km != km, false)
        .CHECK_EQUAL(km == km, true)
        .CHECK_EQUAL(km >= km, true)
        .CHECK_EQUAL(km <= km, true)
        .CHECK_EQUAL(km > km, false)
        .CHECK_EQUAL(km < km, false)
        .setname("Compatible dimensions: Time")
        // SEC with SEC
        .CHECK_OUTPUT(s + s, "61[sec]")
        .CHECK_OUTPUT((s += s), "61[sec]")
        .CHECK_OUTPUT(s, "61[sec]")
        .CHECK_OK(istringstream("30.5[sec]") >> s)
        .CHECK_OUTPUT(s - s, "0[sec]")
        .CHECK_OUTPUT((s -= s), "0[sec]")
        .CHECK_OUTPUT(s, "0[sec]")
        .CHECK_OK(istringstream("30.5[sec]") >> s)
        .CHECK_EQUAL(s, PhysicalNumber(30.5, Unit::SEC))
        .CHECK_EQUAL(s == s, true)
        .CHECK_EQUAL(s >= s, true)
        .CHECK_EQUAL(s <= s, true)
        .CHECK_EQUAL(s < s, false)
        .CHECK_EQUAL(s > s, false)
        // SEC with MIN
        .CHECK_OUTPUT(s + min, "330.5[sec]")
        .CHECK_OUTPUT((s += min), "330.5[sec]")
        .CHECK_OUTPUT(s, "330.5[sec]")
        .CHECK_OK(istringstream("30.5[sec]") >> s)
        .CHECK_OUTPUT(s - min, "-269.5[sec]")
        .CHECK_OUTPUT((s -= min), "-269.5[sec]")
        .CHECK_OUTPUT(s, "-269.5[sec]")
        .CHECK_OK(istringstream("30[sec]") >> s)
        .CHECK_EQUAL(s, PhysicalNumber(0.5, Unit::MIN))
        .CHECK_EQUAL(s != min, true)
        .CHECK_EQUAL(s >= min, false)
        .CHECK_EQUAL(s <= min, true)
        .CHECK_EQUAL(s < min, true)
        .CHECK_EQUAL(s > min, false)
        
        .CHECK_OK(istringstream("200[g") >> g)
        .CHECK_OK(istringstream("0.2[]") >> a)
        .CHECK_OK(istringstream("200g]") >> g)
        .CHECK_OK(istringstream("0.2[kgg]") >> a)
        .CHECK_OK(istringstream("122.2kg") >> a)
        .CHECK_OK(istringstream("1332.2[to n]") >> a)
        .CHECK_OK(istringstream("[ton]1332.2") >> a)
        .CHECK_OUTPUT((km += PhysicalNumber(6, Unit::KM)), "9.3[km]")
        .CHECK_OUTPUT((km -= PhysicalNumber(2, Unit::KM)), "7.3[km]")
        .CHECK_OUTPUT((met += PhysicalNumber(4.2, Unit::M)), "9.5[m]")
        .CHECK_OUTPUT((met -= PhysicalNumber(2.1, Unit::M)), "7.4[m]")
        .CHECK_OUTPUT((cm += PhysicalNumber(600, Unit::CM)), "610[cm]")
        .CHECK_OUTPUT((cm -= PhysicalNumber(0, Unit::M)), "610[cm]")
        .setname("boolean")
        .CHECK_EQUAL(cm == met, false)
        .CHECK_EQUAL(met == km, false)
        .CHECK_EQUAL(cm == cm, true)
        .CHECK_EQUAL(cm == PhysicalNumber(6.1, Unit::M), true)
        .CHECK_EQUAL(cm == PhysicalNumber(0.0061, Unit::KM), true)
        .CHECK_EQUAL(cm != PhysicalNumber(6.1, Unit::M), false)
        .CHECK_EQUAL(cm > PhysicalNumber(0.0061, Unit::KM), false)
        .CHECK_EQUAL(met < PhysicalNumber(7.5, Unit::M), true)
        .CHECK_EQUAL(cm >= PhysicalNumber(0.0061, Unit::KM), true)
        .CHECK_EQUAL(km >= PhysicalNumber(3, Unit::CM), true)
        .setname("unary")
        .CHECK_EQUAL(-met, PhysicalNumber(-7.4, Unit::M))
        .setname("postfix++")
        .CHECK_OUTPUT(cm++, "610[cm]")
        .CHECK_OUTPUT(met++, "7.4[m]")
        .CHECK_OUTPUT(km++, "7.3[km]")
        .setname("postfix--")
        .CHECK_OUTPUT(cm--, "611[cm]")
        .CHECK_OUTPUT(met--, "8.4[m]")
        .CHECK_OUTPUT(km--, "8.3[km]")
        .setname("++prefix")
        .CHECK_OUTPUT(++cm, "611[cm]")
        .CHECK_OUTPUT(++met, "8.4[m]")
        .CHECK_OUTPUT(++km, "8.3[km]")
        .setname("--prefix")
        .CHECK_OUTPUT(--cm, "610[cm]")
        .CHECK_OUTPUT(--met, "7.4[m]")
        .CHECK_OUTPUT(--km, "7.3[km]")
        .setname("MISC")
        .setname("Input")
        .CHECK_OK(istringstream("300[kg]") >> kg)
        .CHECK_OUTPUT(kg, "300[kg]")
        .CHECK_OK(istringstream("22[hour]") >> h)
        .CHECK_OUTPUT(h, "22[hour]")
        .CHECK_OK(istringstream("0.3[m]") >> met)
        .CHECK_OUTPUT(met, "0.3[m]")
        .CHECK_OK(istringstream("700[kg]") >> met)
        .CHECK_OUTPUT(met, "700[kg]")
        .CHECK_OK(istringstream("5[m]") >> h)
        .CHECK_OUTPUT(h, "5[m]")
        
        .print(cout, /*show_grade=*/false);
        grade = testcase.grade();
    }
    else
    {
        testcase.print_signal(signal);
        grade = 0;
    }
    cout << "*** Grade: " << grade << " ***" << endl;
    return grade;
}
