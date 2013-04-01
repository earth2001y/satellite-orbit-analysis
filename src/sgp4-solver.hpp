/******************************************************************************
 * 衛星の位置・速度をSGP4で計算するソルバ
 *****************************************************************************/

#include "orbit-solver.hpp"

#ifndef __SGP4_SOLVER_HPP__
#define __SGP4_SOLVER_HPP__

#ifdef UNITTEST
# define protected public
# define private   public
#endif

class sgp4_solver : public orb_solver {

public:
  sgp4_solver();
  virtual ~sgp4_solver();

  virtual int solve_position(double* res, const double& t);
  virtual int solve_velocity(double* res, const double& t);
};

#undef protected
#undef private

#endif // __SGP4_SOLVER_HPP__

