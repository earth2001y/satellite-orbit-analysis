/******************************************************************************
 * 衛星の位置・速度計算ソルバの基底クラス
 *****************************************************************************/

#include "tle.hpp"

#ifndef __ORBIT_SOLVER_HPP__
#define __ORBIT_SOLVER_HPP__

#ifdef UNITTEST
# define protected public
# define private   public
#endif

class orb_solver {
  const TLE* tle;

public:
  orb_solver();
  virtual ~orb_solver();

  virtual int setTLE(const TLE* tle);
  virtual int solve_position(double* res, const double& t) = 0;
  virtual int solve_velocity(double* res, const double& t) = 0;
};

#undef protected
#undef private

#endif // __ORBIT_SOLVER_HPP__

