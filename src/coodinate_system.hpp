/******************************************************************************
 * 座標系を扱うクラスの集合体
 *
 * SGPアルゴリズムは地心赤道座標系で計算する。
 * 他の座標系への変換を行う。
 *****************************************************************************/

#ifndef __COODINATE_SYSTEM_HPP__
#define __COODINATE_SYSTEM_HPP__

#ifdef UNITTEST
# define protected public
# define private   public
#endif

#include "constant.hpp"

class geodetic;
class rectangular;

// 測地座標系
class geodetic {
public:
  double latitude;  // 緯度
  double longitude; // 経度
  double altitude;  // 高度[km]

  rectangular toRectangular(const double Pg = 0.,
                            const double a = GRS80::a,
                            const double f = GRS80::f ) const;
};

// 直交座標系
class rectangular {
public:
  double X;
  double Y;
  double Z;

  geodetic toGeodetic(const double Pg = 0.,
                      const double a = GRS80::a,
                      const double f = GRS80::f ) const;
};

// 指定時刻のグリニッジ恒星時を求める
double greenwich_sidereal_time(const time_t* t);

#undef protected
#undef private

#endif // __COODINATE_SYSTEM_HPP__

