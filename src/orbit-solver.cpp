
#include <cmath>

#include "tle.hpp"
#include "orbit-solver.hpp"

orb_solver::orb_solver()
{
  k2  = CK2;
  k4  = CK4;
  aE  = XKMPER;
//ke  = sqrt(G*M);
  ke  = sqrt(GE);
  J2  = 2.0*k2/pow(aE,2);        // because, k2 = (1/2)J2.aE**2
  J3  = XJ3;
  J4  = -(8.0/3.0)*k4/pow(aE,4); // because, k4 = -(3/8)J4.aE**4
  A30 = -J3*pow(aE,3);
}

orb_solver::~orb_solver()
{
}

int orb_solver::setTLE(const TLE* tle)
{
  orb_solver::tle = tle;

  n0  = tle->motion;
  e0  = tle->eccentricity;
  i0  = tle->inclination;
  M0  = tle->anomaly;
  w0  = tle->perigee;

  return 0;
}

