
#include <cmath>
#include <ctime>
#include <cstdio>

#include "constant.hpp"
#include "utils.hpp"
#include "coodinate_system.hpp"


// 経度、緯度、高さ(楕円面からの高さ)の測地系から、
// 経度0度方向をX、東経90方向をY、北極方向をZ の地心直交座標系に変換する。
// Pgに自転角, aに赤道半径[km], fに扁平率
rectangular geodetic::toRectangular(const double Pg,
                                    const double a,
                                    const double f ) const
{
  rectangular r;

  // N=a/(1-e^2 * sin^2 p)^0.5
  // Xj=(N+h) cos p cos l
  // Yj=(N+h) cos p sin l
  // Zj=(N(1-e^2)+h) sin p
  //
  double e2 = f * (2. - f); // 離心率の2乗

  double sinp = sin(latitude);
  double cosp = cos(latitude);
  double cosl = cos(longitude + Pg);
  double sinl = sin(longitude + Pg);
  double N = a / sqrt(1. - e2 * sinp*sinp);
  double h = altitude;

  r.X = (N+h) * cosp * cosl;
  r.Y = (N+h) * cosp * sinl;
  r.Z = (N*(1.-e2)+h) * sinp;

  return r;
}

// 経度0度方向をX、東経90方向をY、北極方向をZ の地心直交座標系から
// 経度、緯度、高さ(楕円面からの高さ)の測地系に変換する。
// Pgに自転角, aに赤道半径[km], fに扁平率
geodetic rectangular::toGeodetic(const double Pg,
                                 const double a,
                                 const double f ) const
{
  double e2 = f * (2. - f); // 離心率の2乗
  double P  = sqrt(X*X + Y*Y);
  double dp = 1.;
  double p0 = atan(Z/P);
  double p1 = 0.;

  while (std::abs(dp) > 1.e-12) {
    double sinp = sin(p0);
    double cosp = cos(p0);
    double N = a / sqrt(1. - e2 * sinp*sinp);
    double tanp1 = Z / (P - e2 * N * cosp);
    p1 = atan(tanp1);
    dp = p1 - p0;
    p0 = p1;
  }

  geodetic g;
  double sinp = sin(p1);
  double N = a / sqrt(1. - e2 * sinp*sinp);

  g.latitude  = p1;
  g.longitude = fmod2p(actan(Y/a,X/a) - Pg);
  g.altitude  = P / cos(p1) - N;

  return g;
}

// グレゴリオ暦からグリニッジ恒星時を算出する
double greenwich_sidereal_time(const time_t* t)
{
  char str[20];
  int Y,M,D,h,m,s;
  struct tm* ptm = gmtime(t);
  strftime (str,20,"%Y %m %d %H %M %S",ptm);
  sscanf(str,"%04d %02d %02d %02d %02d %02d",&Y,&M,&D,&h,&m,&s);

  double JD; // ユリウス日
  if ( M <= 2 ) { M += 12; Y -= 1; }
  JD = floor(365.25*Y) + floor(Y/400.) - floor(Y/100.)
     + floor(30.59*(M-2)) + D + 1721088.5
     + h / 24. + m / 1440. + s / 86400.;

  double TJD; // NASA世界時(1968年3月24日0時からの日数)
  TJD = JD - 2440000.5;

  double R;
  double Pg; // グリニッジ恒星時
  R = 0.671262 + 1.0027379094 * TJD;
  Pg = 24 * R;

  return Pg;
}

