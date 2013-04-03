/******************************************************************************
 * 衛星軌道のクラス
 *****************************************************************************/

#include <gsl/gsl_const_mksa.h>

#include "tle.hpp"

#ifndef __ORBIT_HPP__
#define __ORBIT_HPP__

#ifdef UNITTEST
# define protected public
# define private   public
#endif

class orbit {

protected:
  const TLE* tle;

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

  // orbital parameters set
  double n0;   // the SGP type "meean" mean motion at epoch
  double e0;   // the "mean" eccentricity at epoch
  double i0;   // the "mean" inclination at epoch
  double M0;   // the "mean" mean anomaly at epoch
  double w0;   // the "mean" argument of perigee at epoch
  double Om0;  // the "mean" longitude of ascending node at epoch
  double dn0;  // the time rate of change of "mean" mean motion at epoch
  double ddn0; // the second time rate of change of "mean" mean motion at epoch
  double Bc;   // the SGP4 type drag coefficient
  double ke;   // sqrt(G.M) where G is Newton's universal gravitational constant and M is the mass of the Earth
  double aE;   // the equatorial radius of the Earth
  double J2;   // the second gravitational zonal harmonic of the Earth
  double J3;   // the third gravitational zonal harmonic of the Earth
  double J4;   // the fourth gravitational zonal harmonic of the Earth
  double k2;   // k2 = (1/2)J2.aE**2
  double k4;   // k4 = -(3/8)J4.aE**4
  double A30;  // A30 = -J3.aE**3
  double qo;   // parameter for the SGP4/SGP8 density function
  double s;    // parameter for the SGP4/SGP8 density function
  double B;    // B = (1/2)CD(A/m)
               //   the ballistic coefficient for SGP8 where CD is a dimensionless drag
               //   coefficient and A is the average cross-sectional area of the satellite of mass m

private:
  double fmod2p(const double x);

public:
  orbit();
  virtual ~orbit();

  int setTLE(const TLE* tle);

  int sgp(double* position, double* velocity, const double& t);
  int sgp4(double* position, double* velocity, const double& t);
};

#undef protected
#undef private

#endif // __ORBIT_HPP__

