/******************************************************************************
 * TLE (Two-line elements) 形式の軌道要素データを読むクラス
 *
 * TLEのフォーマットはこのあたりを参照
 *  - http://celestrak.com/NORAD/documentation/tle-fmt.asp
 *  - http://celestrak.com/columns/v04n03/
 *
 *****************************************************************************/

#include <string>

#ifndef __TLE_HPP__
#define __TLE_HPP__

#ifdef UNITTEST
# define protected public
# define private   public
#endif

class TLE {

protected:
  std::string line[2];   // Raw TLE string

  // primitive data, loaded from TLE format
  int    number;         // Satellite Number in NORAD Catalog
  char   classification; // Classification 'S' or 'U'
  int    IDYY;           // International Designator (Last two digits of launch year)
  int    IDNY;           // International Designator (Launch number of the year)
  char   IDPL[4];        // International Designator (Piece of the launch)
  int    epoch_year;     // Epoch Year (Last two digits of year)
  double epoch_day;      // Epoch (Day of the year and fractional portion of the day)
  double dmotion;        // First Time Derivative of the Mean Motion
  double ddmotion;       // Second Time Derivative of Mean Motion
  double BSTAR;          // BSTAR drag term
  char   ephemeris;      // Ephemeris type - '0':no information, '1':SGP, '2':SGP4, '3':SDP4, '4':SGP8, '5':SDP8
  int    elemnum;        // Element number

  double inclination;    // Inclination [degrees]
  double ascension;      // Right Ascension of the Ascending Node [Degrees]
  double eccentricity;   // Eccentricity
  double perigee;        // Argument of Perigee [Degrees]
  double anomaly;        // Mean Anomaly [Degrees]
  double motion;         // Mean Motion [Revs per day]
  int    revolution;     // Revolution number at epoch [Revs]

public:
  TLE();
  virtual ~TLE();

  bool set(const std::string& line1, const std::string& line2);

private:
  bool validation(const std::string& line);

};

#undef protected
#undef private

#endif // __TLE_HPP__

