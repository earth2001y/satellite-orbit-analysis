/******************************************************************************
 * 各種定数
 *****************************************************************************/

#include <gsl/gsl_const_mksa.h>

#ifndef __CONSTANT_HPP__
#define __CONSTANT_HPP__

// physical and mathematical constants.
  static const double CK2    = 5.413080E-4;    // (1/2)J2.aE**2, equiv k2
  static const double CK4    = .62098875E-6;   // -(3/8)J4.aE**4, equiv k4
  static const double E6A    = 1.0E-6;
  static const double QOMS2T = 1.88027916E-9;  // (q0-s)**4 * (er)**4
  static const double S      = 1.01222928;     // s(er)
  static const double TOTHRD = .66666667;      // 2/3
  static const double XJ3    = -.253881E-5;    // J3
  static const double XKE    = .74366916E-1;   // ke(er/min)**(3/2)
  static const double XKMPER = 6378.135;       // Earth radii [km]
  static const double XMNPDA = 1440.0;         // time units per day
  static const double AE     = 1.0;            // distance units/Earth radii
  static const double DE2RA  = .174532925E-1;  // radians/degree
  static const double PI     = 3.14159265;     // pi
  static const double PIO2   = 1.57079633;     // pi/2
  static const double TWOPI  = 6.2831853;      // 2.pi
  static const double X3PIO2 = 4.71238898;     // 3.pi/2
//static const double PI     = M_PI;           // pi
//static const double PIO2   = M_PI_2;         // pi/2
//static const double TWOPI  = 2.0*M_PI;       // 2.pi
//static const double X3PIO2 = 3.0*M_PI_2;     // 3.pi/2
  static const double M      = 5.9736E24;      // mass of the Earth [kg] (by NASA)
  static const double G      = 6.67384E-11;    // gravitational constant [m3.s-2.kg-1]
  static const double GE     = 3.986004418E14; // equiv G*M [m3.s-2]
//static const double G      = GSL_CONST_MKSA_GRAVITATIONAL_CONSTANT;

#endif // __CONSTANT_HPP__

