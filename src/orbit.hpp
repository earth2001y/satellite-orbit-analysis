/******************************************************************************
 * 衛星軌道のクラス
 *****************************************************************************/

#include <gsl/gsl_const_mksa.h>

#include <ctime>
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

  // orbital parameters set
  double n0;   // the SGP type "meean" mean motion at epoch
  double e0;   // the "mean" eccentricity at epoch
  double i0;   // the "mean" inclination at epoch
  double M0;   // the "mean" mean anomaly at epoch
  double w0;   // the "mean" argument of perigee at epoch
  double W0;   // the "mean" longitude of ascending node at epoch
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

public:
  orbit();
  virtual ~orbit();

  int setTLE(const TLE* tle);
  double elapsed_day(const time_t* t);

  int sgp(double* position, double* velocity, const double& t);
  int sgp4(double* position, double* velocity, const double& t);
};

#undef protected
#undef private

#endif // __ORBIT_HPP__

