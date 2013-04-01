
#include "tle.hpp"
#include "orbit-solver.hpp"

orb_solver::orb_solver()
{
}

orb_solver::~orb_solver()
{
}

int orb_solver::setTLE(const TLE* tle)
{
  orb_solver::tle = tle;
  return 0;
}

