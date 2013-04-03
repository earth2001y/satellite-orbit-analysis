
#include <cmath>
#include <cstdio>

#include "tle.hpp"
#include "orbit.hpp"

orbit::orbit()
{
  k2  = CK2;
  k4  = CK4;
  aE  = XKMPER;
  ke  = sqrt(G*M);
//ke  = sqrt(GE);
  J2  = 2.0*k2/pow(aE,2);        // because, k2 = (1/2)J2.aE**2
  J3  = XJ3;
  J4  = -(8.0/3.0)*k4/pow(aE,4); // because, k4 = -(3/8)J4.aE**4
  A30 = -J3*pow(aE,3);
}

orbit::~orbit()
{
}

double orbit::fmod2p(const double x)
{
  double y = x;
  y = y - static_cast<int>(x / TWOPI) * TWOPI;
  if (y < 0.) y = y + TWOPI;
  return y;
}

int orbit::setTLE(const TLE* tle)
{
  orbit::tle = tle;

  n0   = tle->motion;
  dn0  = tle->dmotion;
  ddn0 = tle->ddmotion;
  e0   = tle->eccentricity;
  i0   = tle->inclination * PI/180.;
  M0   = tle->anomaly * PI/180.;
  w0   = tle->perigee * PI/180.;
  Om0  = tle->ascension * PI/180.;
#if 0
  printf("n0   = %e\n",n0);
  printf("dn0  = %e\n",dn0);
  printf("ddn0 = %e\n",ddn0);
  printf("e0 = %e\n",e0);
  printf("i0 = %e\n",i0);
  printf("M0 = %e\n",M0);
  printf("w0 = %e\n",w0);
  printf("W0 = %e\n",Om0);
#endif

  return 0;
}

int orbit::sgp(double* position, double* velocity, const double& t)
{
  // The NORAD mean element sets can be used for prediction with SGP.
  // All symbols not defined below are defined in the list of symbols in Section Twelve.
  // Predictions are made by first calculating the constants.
  double a1,d1,a0,p0,q0,L0;
  double dOm_dt,dw_dt;

  a1 = pow(ke/n0, 2./3.);
  d1 = (3./4.)*J2*(pow(aE,2)/pow(a1,2))*(3.*pow(cos(i0),2)-1.)/pow(1.-pow(e0,2),3./2.);
  a0 = a1*(1. - (1./3.)*d1 - pow(d1,2) - (134./81.)*pow(d1,3));
  p0 = a0 * (1. - pow(e0,2));
  q0 = a0 * (1. - e0);
  L0 = fmod2p(M0 + w0 + Om0);
#if 0
  printf("a1 = %e\n",a1);
  printf("d1 = %e\n",d1);
  printf("a0 = %e\n",a0);
  printf("p0 = %e\n",p0);
  printf("q0 = %e\n",q0);
  printf("L0 = %e\n",L0);
#endif

  dOm_dt = -(3./2.)*J2*(pow(aE,2)/pow(p0,2))*n0*cos(i0);
  dw_dt  =  (3./4.)*J2*(pow(aE,2)/pow(p0,2))*n0*(5.*pow(cos(i0),2)-1.);
  printf("dW/dt = %e\n",dOm_dt);
  printf("dw/dt = %e\n",dw_dt);

  // The secular effects of atmospheric drag and gravitation are included through the equations
  double a,e,p;
  double Oms0,ws0,Ls;

  a = a0 * pow(n0/(n0 + 2.*(dn0/2.)*t + 3.*(ddn0/6.)*pow(t,2)),2./3.);
  e = (a > q0)? 1-(q0/a): 1.E-6;
  p = a*(1-pow(e,2));
#if 0
  printf("a = %e\n",a);
  printf("e = %e\n",e);
  printf("p = %e\n",p);
#endif

  Oms0 = fmod2p(Om0 + dOm_dt * t);
  ws0  = fmod2p(w0 + dw_dt * t);
  Ls   = fmod2p(L0 + (n0+dw_dt+dOm_dt)*t + (dn0/2.)*pow(t,2) + (ddn0/6.)*pow(t,3));
#if 0
  printf("Ws0 = %e\n",Oms0);
  printf("ws0 = %e\n",ws0);
  printf("Ls  = %e\n",Ls);
#endif

  // Long-period periodics are included through the equations
  double L,axNSL,ayNSL;

  axNSL = e*cos(ws0);
  ayNSL = e*sin(ws0) - (1./2.)*(J3/J2)*(aE/p)*sin(i0);
#if 0
  printf("axNSL = %e\n",axNSL);
  printf("ayNSL = %e\n",ayNSL);
#endif

  L = fmod2p(Ls - (1./4.)*(J3/J2)*(aE/p)*axNSL*sin(i0)*((3.+5*cos(i0))/(1.+cos(i0))));
#if 0
  printf("L = %e\n",L);
#endif

  // solve Kepler's equation
  double U,Ew,dEw;

  U = fmod2p(L - Oms0);
  Ew = U;
  dEw = 1.;
  while(std::abs(dEw) >= 1.E-6) {
    dEw = (U - ayNSL*cos(Ew) + axNSL*sin(Ew) - Ew)/(-ayNSL*sin(Ew) - axNSL*cos(Ew) + 1.);
    Ew += dEw;
  }

#if 0
  printf("U = %e\n",U);
  printf("Ew  = %e\n",Ew);
  printf("dEw = %e\n",dEw);
#endif

  // Then calculate the intermediate (partially osculating) quantities
  double ecosE,esinE;
  double eL2,pL,r,dr,rdv;
  double u,sinu,cosu;

  ecosE = axNSL*cos(Ew) + ayNSL*sin(Ew);
  esinE = axNSL*sin(Ew) - ayNSL*cos(Ew);
#if 0
  printf("e.cosE = %e\n",ecosE);
  printf("e.sinE = %e\n",esinE);
#endif

  eL2 = pow(axNSL,2) + pow(ayNSL,2);
  pL  = a*(1. - eL2);
  r   = a*(1. - ecosE);
  dr  = ke*(sqrt(a)/r)*esinE;
  rdv = ke*(sqrt(pL)/r);
#if 0
  printf("e.L2 = %e\n",eL2);
  printf("p.L  = %e\n",pL);
  printf("r    = %e\n",r);
  printf("dr   = %e\n",dr);
  printf("rdv  = %e\n",rdv);
#endif

  sinu = (a/r)*(sin(Ew) - ayNSL - axNSL*(esinE/(1.-sqrt(1.-eL2))));
  cosu = (a/r)*(cos(Ew) - axNSL - ayNSL*(esinE/(1.-sqrt(1.-eL2))));

  u = atan(sinu/cosu);

  // Short-period perturbations are now included by
  double rk,uk,Omk,ik;
  rk  = r + (1./4.)*J2*(pow(aE,2)/pL)*pow(sin(i0),2)*cos(2.*u);
  uk  = u - (1./8.)*J2*(pow(aE,2)/pow(pL,2))*(7.-pow(cos(i0),2)-1.)*sin(2.*u);
  Omk = Oms0 + (3./4.)*J2*(pow(aE,2)/pow(pL,2))*cos(i0)*sin(2.*u);
  ik  = i0 + (3./4.)*J2*(pow(aE,2)/pow(pL,2))*sin(i0)*cos(i0)*cos(2.*u);

  // Then unit orientation vectors are calculated by
  double Mx,My,Mz;
  double Nx,Ny,Nz;
  double Ux,Uy,Uz;
  double Vx,Vy,Vz;

  Mx = -sin(Omk)*cos(ik);
  My =  cos(Omk)*cos(ik);
  Mz =           sin(ik);
  Nx = cos(Omk);
  Ny = sin(Omk);
  Nz = 0.;

  Ux = Mx*sin(uk) + Nx*cos(uk);
  Uy = My*sin(uk) + Ny*cos(uk);
  Uz = Mz*sin(uk) + Nz*cos(uk);
  Vx = Mx*cos(uk) + Mx*sin(uk);
  Vy = My*cos(uk) + My*sin(uk);
  Vz = Mz*cos(uk) + Mz*sin(uk);

  // Then position and velocity are given by
  position[0] = rk*Ux;
  position[1] = rk*Uy;
  position[2] = rk*Uz;
  velocity[0] = dr*Ux + rdv*Vx;
  velocity[1] = dr*Uy + rdv*Vy;
  velocity[2] = dr*Uz + rdv*Vz;

  return 0;
}

int orbit::sgp4(double* position, double* velocity, const double& t)
{
  return 0;
}

