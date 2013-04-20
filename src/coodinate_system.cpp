
#include <cmath>
#include <ctime>
#include <cstdio>

#include "constant.hpp"
#include "coodinate_system.hpp"


// 経度0度方向をX、東経90方向をY、北極方向をZ の地心直交座標系から
// 経度、緯度、高さ(楕円面からの高さ)の極座標系に変換する。
// aに赤道半径[km], bに極半径[km]
rectangular polar::toRectangular(const double a = AE * XKMPER,
                                 const double b = 6356.752 ) const
{
  rectangular r;

  // N=a/(1-e^2 * sin^2φ)^0.5
  // Xj=(N+h) cosφ cosλ
  // Yj=(N+h) cosφ sinλ
  // Zj=(N(1-e^2)+h) sinφ
  //
  double f  = (a - b) / a;  // 扁平率
  double e2 = f * (2. - f); // 離心率の2乗
  double e  = sqrt(e2);     // 離心率

  double sinp = sin(latitude);
  double cosp = cos(latitude);
  double cosl = cos(longitude);
  double sinl = sin(longitude);
  double N = a / sqrt(1. - e*e * sinp*sinp);
  double h = altitude;

  r.X = (N+h) * cosp * cosl;
  r.Y = (N+h) * cosp * sinl;
  r.Z = (N*(1.-e*e)+h) * sinp;

  return r;
}

// 測地座標系を赤道座標系に変換する
polar polar::toEquatorial(const time_t* t) const
{
  // グリニッジ恒星時をもとにした赤道座標系での地球回転角
  double Pg = 2. * M_PI * greenwich_sidereal_time(t) / 24.;
  polar p;
  p.latitude  = this->latitude;
  p.longitude = this->longitude + Pg; // 東経方向に回す
  p.altitude  = this->altitude;
  return p;
}

// 赤道座標系を測地座標系に変換する
polar polar::toGeodetic(const time_t* t) const
{
  // グリニッジ恒星時をもとにした赤道座標系での地球回転角
  double Pg = 2. * M_PI * greenwich_sidereal_time(t) / 24.;
  polar p;
  p.latitude  = this->latitude;
  p.longitude = this->longitude - Pg; // 西経方向に回す
  p.altitude  = this->altitude;
  return p;
}

// 経度、緯度、高さ(楕円面からの高さ)の極座標系から、
// 経度0度方向をX、東経90方向をY、北極方向をZ の地心直交座標系に変換する。
// aに赤道半径[km], bに極半径[km]
polar rectangular::toPolar(const double a = AE * XKMPER,
                           const double b = 6356.752 ) const
{
  double f  = (a - b) / a;  // 扁平率
  double e2 = f * (2. - f); // 離心率の2乗
  double e  = sqrt(e2);     // 離心率
  double P  = sqrt(X*X + Y*Y);
  double dp = 1.;
  double p0 = 0.;
  double p1 = 0.;

  while (std::abs(dp) > 1.e-12) {
    double sinp = sin(p0);
    double cosp = sin(p0);
    double N = a / sqrt(1. - e*e * sinp*sinp);
    double tanp1 = Z / (P - e*e * N * cosp);
    p1 = atan(tanp1);
    dp = p1 - p0;
    p0 = p1;
  }

  polar pl;
  double sinp = sin(p1);
  double N = a / sqrt(1. - e*e * sinp*sinp);

  pl.latitude  = p1;
  pl.longitude = atan(Y/X);
  pl.altitude  = P / cos(p1) - N;

  return pl;
}

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
  double Pg; // グリニッジ恒星時の1日未満部分[rad]
  R = 0.671262 + 1.0027379094 * TJD;
  R -= floor(R);
  Pg = 24 * R;

  return Pg;
}

