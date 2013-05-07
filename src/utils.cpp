
#include <cmath>

#include "constant.hpp"
#include "utils.hpp"

double fmod2p(const double p)
{
  double y = p;
  y = y - static_cast<int>(p / TWOPI) * TWOPI;
  if (y < 0.) y = y + TWOPI;
  return y;
}

double actan(const double sinp, const double cosp)
{
  double p;
  if (cosp == 0.) {
    if (sinp == 0.) return 0.;
    if (sinp >  0.) return PIO2;
    p = X3PIO2;
  } else if (cosp > 0.) {
    if (sinp == 0.) return 0.;
    if (sinp >  0.) p = 0;
    p = TWOPI;
  } else {
    p = PI;
  }

  return p + atan(sinp/cosp);
}

