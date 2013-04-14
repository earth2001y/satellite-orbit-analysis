
#include <cmath>
#include <cstdio>

#include "tle.hpp"
#include "orbit.hpp"
#include "constant.hpp"

orbit::orbit()
{
  k2  = CK2;
  k4  = CK4;
  aE  = AE;
  ke  = XKE;
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

double orbit::actan(const double sinx, const double cosx)
{
  double x;
  if (cosx == 0.) {
    if (sinx == 0.) return 0.;
    if (sinx >  0.) return PIO2;
    x = X3PIO2;
  } else if (cosx > 0.) {
    if (sinx == 0.) return 0.;
    if (sinx >  0.) x = 0;
    x = TWOPI;
  } else {
    x = PI;
  }

  return x + atan(sinx/cosx);
}

int orbit::setTLE(const TLE* tle)
{
  orbit::tle = tle;

  n0   = tle->motion   * TWOPI/XMNPDA;
  dn0  = tle->dmotion  * TWOPI/XMNPDA/XMNPDA;
  ddn0 = tle->ddmotion * TWOPI/XMNPDA/XMNPDA/XMNPDA;
  e0   = tle->eccentricity;
  i0   = tle->inclination * DE2RA;
  M0   = tle->anomaly     * DE2RA;
  w0   = tle->perigee     * DE2RA;
  W0   = tle->ascension   * DE2RA;
#if 0
  printf("n0   = %e\n",n0);
  printf("dn0  = %e\n",dn0);
  printf("ddn0 = %e\n",ddn0);
  printf("e0 = %e\n",e0);
  printf("i0 = %e\n",i0);
  printf("M0 = %e\n",M0);
  printf("w0 = %e\n",w0);
  printf("W0 = %e\n",W0);
#endif

  return 0;
}

int orbit::sgp(double* position, double* velocity, const double& t)
{
  // The NORAD mean element sets can be used for prediction with SGP.
  // All symbols not defined below are defined in the list of symbols in Section Twelve.
  // Predictions are made by first calculating the constants.
  double a1,d1,a0,p0,q0,L0;
  double cosio,sinio;
  double dW_dt,dw_dt;

  cosio = cos(i0);
  sinio = sin(i0);

  a1 = pow(ke/n0, 2./3.);
  d1 = 1.5*CK2/(a1*a1)*(3.*cosio*cosio-1.)/pow(1.- e0*e0,3./2.);
  a0 = a1*(1. - (1./3.)*d1 - d1*d1 - (134./81.)*d1*d1*d1);
  p0 = a0 * (1. - e0*e0);
  q0 = a0 * (1. - e0);
  L0 = fmod2p(M0 + w0 + W0);
#if 0
  printf("a1 = %e\n",a1);
  printf("d1 = %e\n",d1);
  printf("a0 = %e\n",a0);
  printf("p0 = %e\n",p0);
  printf("q0 = %e\n",q0);
  printf("L0 = %e\n",L0);
#endif

  dW_dt = -3.*CK2/(p0*p0)*n0*cosio;
  dw_dt = 1.5*CK2/(p0*p0)*n0*(5.*cosio*cosio-1.);
#if 0
  printf("dW/dt = %e\n",dW_dt);
  printf("dw/dt = %e\n",dw_dt);
#endif

  // The secular effects of atmospheric drag and gravitation are included through the equations
  double a,e,p;
  double Ws0,ws0,Ls;

  a = a0 * pow(n0/(n0 + 2.*(dn0/2.)*t + 3.*(ddn0/6.)*pow(t,2)),2./3.);
  e = (a > q0)? 1-(q0/a): 1.E-6;
  p = a*(1 - e*e);
#if 0
  printf("a = %e\n",a);
  printf("e = %e\n",e);
  printf("p = %e\n",p);
#endif

  Ws0 = fmod2p(W0 + dW_dt*t);
  ws0 = fmod2p(w0 + dw_dt*t);
  Ls  = fmod2p(L0 + (n0+dw_dt+dW_dt)*t + (dn0/2.)*t*t + (ddn0/6.)*t*t*t);
#if 0
  printf("Ws0 = %e\n",Ws0);
  printf("ws0 = %e\n",ws0);
  printf("Ls  = %e\n",Ls);
#endif

  // Long-period periodics are included through the equations
  double L,axNSL,ayNSL;

  axNSL = e*cos(ws0);
  ayNSL = e*sin(ws0) - (1./2.)*(J3/J2)*(aE/p)*sinio;
#if 0
  printf("axNSL = %e\n",axNSL);
  printf("ayNSL = %e\n",ayNSL);
#endif

  L = fmod2p(Ls - (1./4.)*(J3/J2)*(aE/p)*axNSL*sinio*((3.+5.*cosio)/(1.+cosio)));
#if 0
  printf("L = %e\n",L);
#endif

  // solve Kepler's equation
  double U,Ew,dEw;
  double cosEw,sinEw;

  U = fmod2p(L - Ws0);
  Ew = U;
  dEw = 1.;
  while(std::abs(dEw) >= E6A) {
    cosEw = cos(Ew);
    sinEw = sin(Ew);
    dEw = (U - ayNSL*cosEw + axNSL*sinEw - Ew)/(-ayNSL*sinEw - axNSL*cosEw + 1.);
    Ew += dEw;
  }

#if 0
  printf("U = %e\n",U);
  printf("Ew  = %e\n",Ew);
  printf("dEw = %e\n",dEw);
#endif

  // Then calculate the intermediate (partially osculating) quantities
  double ecosE,esinE;
  double eL2,pL,pL2,r,dr,rdv;
  double u,sinu,cosu;

  ecosE = axNSL*cos(Ew) + ayNSL*sin(Ew);
  esinE = axNSL*sin(Ew) - ayNSL*cos(Ew);
#if 0
  printf("e.cosE = %e\n",ecosE);
  printf("e.sinE = %e\n",esinE);
#endif

  eL2 = pow(axNSL,2) + pow(ayNSL,2);
  pL  = a*(1. - eL2);
  pL2 = pL * pL;
  r   = a*(1. - ecosE);
  dr  = ke*(sqrt(a)/r)*esinE;
  rdv = ke*(sqrt(pL)/r);
#if 0
  printf("eL2 = %e\n",eL2);
  printf("pL  = %e\n",pL);
  printf("pL2 = %e\n",pL2);
  printf("r   = %e\n",r);
  printf("dr  = %e\n",dr);
  printf("rdv = %e\n",rdv);
#endif

  sinu = (a/r)*(sin(Ew) - ayNSL - axNSL*esinE/(1.+sqrt(1.-eL2)));
  cosu = (a/r)*(cos(Ew) - axNSL + ayNSL*esinE/(1.+sqrt(1.-eL2)));
#if 0
  printf("cos u = %e\n",cosu);
  printf("sin u = %e\n",sinu);
#endif

  u = actan(sinu,cosu);
#if 0
  printf("s/c = %e\n",sinu/cosu);
  printf("u   = %e\n",u);
#endif

  // Short-period perturbations are now included by
  double rk,uk,Wk,ik;
  double sin2u,cos2u;

  sin2u = sin(2.*u);
  cos2u = cos(2.*u);

  rk = r   + .50 * CK2/pL  * sinio*sinio*cos2u ;
  uk = u   - .25 * CK2/pL2 * (7.*cosio*cosio - 1.)*sin2u;
  Wk = Ws0 + 1.5 * CK2/pL2 * cosio*sin2u;
  ik = i0  + 1.5 * CK2/pL2 * sinio*cosio*cos2u;
#if 0
  printf("rk = %e\n",rk);
  printf("uk = %e\n",uk);
  printf("Wk = %e\n",Wk);
  printf("ik = %e\n",ik);
#endif

  // Then unit orientation vectors are calculated by
  double Mx,My,Mz;
  double Nx,Ny,Nz;
  double Ux,Uy,Uz;
  double Vx,Vy,Vz;

  Mx = -sin(Wk)*cos(ik);
  My =  cos(Wk)*cos(ik);
  Mz =           sin(ik);
  Nx = cos(Wk);
  Ny = sin(Wk);
  Nz = 0.;

  Ux = Mx*sin(uk) + Nx*cos(uk);
  Uy = My*sin(uk) + Ny*cos(uk);
  Uz = Mz*sin(uk) + Nz*cos(uk);
  Vx = Mx*cos(uk) - Nx*sin(uk);
  Vy = My*cos(uk) - Ny*sin(uk);
  Vz = Mz*cos(uk) - Nz*sin(uk);

#if 0
  printf("Ux = %e\n",Ux);
  printf("Uy = %e\n",Uy);
  printf("Uz = %e\n",Uz);
  printf("Vx = %e\n",Vx);
  printf("Vy = %e\n",Vy);
  printf("Vz = %e\n",Vz);
#endif

  // Then position and velocity are given by
  position[0] = (rk*Ux) * XKMPER/AE;
  position[1] = (rk*Uy) * XKMPER/AE;
  position[2] = (rk*Uz) * XKMPER/AE;
  velocity[0] = (dr*Ux + rdv*Vx) * XKMPER/AE * XMNPDA/86400;
  velocity[1] = (dr*Uy + rdv*Vy) * XKMPER/AE * XMNPDA/86400;
  velocity[2] = (dr*Uz + rdv*Vz) * XKMPER/AE * XMNPDA/86400;

#if 0
  printf("X    = %e\n",position[0]);
  printf("Y    = %e\n",position[1]);
  printf("Z    = %e\n",position[2]);
  printf("XDOT = %e\n",velocity[0]);
  printf("YDOT = %e\n",velocity[1]);
  printf("ZDOT = %e\n",velocity[2]);
#endif

  return 0;
}

int orbit::sgp4(double* position, double* velocity, const double& t)
{
  return 0;
}

